#include "ParticleSystem.h"

void ParticleSystem::onParticleDeath(Particle* p)
{
	switch (*p->getType())
	{
	case FIREWORK: {
		for (auto e : static_cast<Firework*>(p)->explode()) {
			if (--*e->getGeneration() > -1) {
				*e->getColor() = colorsInfo[e->randomColor()];
				*e->getVelocity() *= 5;
				e->show();
				_particles.push_back(e);
			}
		}
	}
	default:
		break;
	}
}

ParticleSystem::ParticleSystem(const Vector3& g) : _gravity(g)
{
	createFireworkSystem();
}

ParticleSystem::~ParticleSystem()
{
	//for (auto e : _particles) {
	//	e->die();
	//}
	_particles.clear();
	for (auto pg : _pGenerator)
		delete pg;

	//delete _firework_generator;
}

void ParticleSystem::update(double t)
{
	for (auto g : _pGenerator) {
		for (auto pg : g->generateParticles()) {
			*pg->getAcceleration() += _gravity;
			_particles.push_back(pg);
		}
	}
	for (auto e : _particles) {
		e->integrate(t);
		e->_ls -= t;
		if (e->_ls < 0) {
			onParticleDeath(e);
			_dumpster.push_back(e);
		}
	}

	for (auto d : _dumpster) {
		_particles.remove(d);
		d->die();
	}
	_dumpster.clear();
}

void ParticleSystem::generateFirework(unsigned firework_type)
{
	switch (firework_type)
	{
	case 0: {
		Firework* temp = new Firework(partType[FIREWORK]);
		*temp->getPose() = PxTransform(0.0, 0.0, 0.0);
		*temp->getAcceleration() += Vector3{0.0, -9.8, 0.0};


		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[CHERRY_BLOSSOM]);
		auxGen1->setParticle(aux1);
		auxGen1->setRandomLifespan(true);

		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator());
		Firework* aux2 = new Firework(partType[FIREWORK]);
		auxGen2->setParticle(aux2);
		auxGen2->setRandomLifespan(true);

		std::shared_ptr<ParticleGenerator> auxGen3(new GaussianParticleGenerator());
		Firework* aux3 = new Firework(partType[DEFAULT]);
		auxGen3->setParticle(aux3);
		auxGen3->setRandomLifespan(true);

		temp->addGenerator(auxGen1);
		temp->addGenerator(auxGen2);
		temp->addGenerator(auxGen3);

		_particles.push_back(temp);
		delete aux1;
		delete aux2;
		delete aux3;
		break;
	}
	default:
		break;
	}
}

void ParticleSystem::createFireworkSystem()
{
}

void ParticleSystem::addGenerator(unsigned type) {
	switch (type)
	{
	case 0: {
		UniformParticleGenerator* mistGen = new UniformParticleGenerator();
		Particle* mistParticle = new Particle(partType[MIST]);
		mistGen->setParticle(mistParticle);
		mistGen->setOffset(50.0f);
		_pGenerator.push_back(mistGen);
		break;
	}
	default:
		break;
	}
}