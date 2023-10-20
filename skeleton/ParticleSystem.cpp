#include "ParticleSystem.h"

void ParticleSystem::onParticleDeath(Particle* p)
{
	switch (p->getType())
	{
	case Particle::FIREWORK: {
		for (auto e : static_cast<Firework*>(p)->explode()) {
			e->show();
			e->setLifespan(e->_ls / 2);
			_particles.push_back(e);
		}
	}
	default:
		break;
	}
}

ParticleSystem::ParticleSystem(const Vector3& g) : _gravity(g)
{
	//_pGenerator.push_back(new UniformParticleGenerator({ 0.0, 0.0, 0.0 }, {5.0, 20.0, 5.0}));
	//_pGenerator.push_back(new GaussianParticleGenerator(new Particle(), {20.0, 0.0, 0.0}, {5.0, 20.0, 5.0}));
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
			pg->setAcceleration(pg->getAcceleration() + _gravity);
			_particles.push_back(pg);
		}
	}
	for (auto e : _particles) {
		e->integrate(t);
		e->_ls -= t;
		if (e->_ls < 0) {
			//_particles.remove(e);
			//e->die();
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
		Firework* temp = new Firework(true);
		temp->setPosition(PxTransform(0.0, 0.0, 0.0));
		temp->setAcceleration(temp->getAcceleration() + Vector3{0.0, -2.0, 0.0});

		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Particle* aux1 = new Particle(false);
		aux1->setColor({ 1.0, 0.0, 0.0, 1.0 });
		aux1->setMass(0.5);
		auxGen1->setParticle(aux1);

		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator());
		Particle* aux2 = new Particle(false);
		aux2->setColor({ 0.0, 1.0, 0.0, 1.0 });
		aux2->setMass(0.5);
		auxGen2->setParticle(aux2);

		std::shared_ptr<ParticleGenerator> auxGen3(new GaussianParticleGenerator());
		Particle* aux3 = new Particle(false);
		aux3->setColor({ 0.0, 0.0, 1.0, 1.0 });
		aux3->setMass(0.5);
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
