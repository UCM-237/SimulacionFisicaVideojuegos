#include "ParticleSystem.h"

void ParticleSystem::onParticleDeath(Particle* p)
{
	switch (*p->getType())
	{
	case FIREWORK: {
		for (auto e : static_cast<Firework*>(p)->explode()) {
			if (--*e->getGeneration() > -1) {
				e->show();
				*e->getVelocity() * 10;
				*e->getColor() = colorsInfo[e->randomColor()];
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

	delete _firework_generator;
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
		*temp->getAcceleration() += Vector3{0.0, -2.0, 0.0};


		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[FIREWORK]);
		auxGen1->setParticle(aux1);

		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator());
		Firework* aux2 = new Firework(partType[FIREWORK]);
		auxGen2->setParticle(aux2);

		std::shared_ptr<ParticleGenerator> auxGen3(new GaussianParticleGenerator());
		Firework* aux3 = new Firework(partType[FIREWORK]);
		auxGen3->setParticle(aux3);

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
	//_firework_generator = new GaussianParticleGenerator(new Firework(), {0.0, 0.0, 0.0}, {0.0, 25.0, 0.0}, 0.0);
	_firework_generator = new UniformParticleGenerator();
	//Firework* aux = new Firework();
	//Particle* aux = new Particle();
	//_firework_generator->setParticle(aux);
	_firework_generator->setMeanVelocity({ 0.0, 100.0, 0.0 });
	_firework_generator->setGenerationProb(0);
	_firework_generator->setNParticles(1);

	//delete aux;
}
