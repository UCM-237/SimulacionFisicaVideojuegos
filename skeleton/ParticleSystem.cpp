#include "ParticleSystem.h"

void ParticleSystem::onParticleDeath(Particle* p)
{
	switch (p->getType())
	{
	case FIREWORK: {
		for (auto e : static_cast<Firework*>(p)->explode()) {
			if (e->getGeneration() > -1) {
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
	forces.push_back(new GravityForceGenerator({ 0.0, -9.8, 0.0 }));
}

ParticleSystem::~ParticleSystem()
{
	_particles.clear();
	for (auto pg : _pGenerator)
		delete pg;
}

void ParticleSystem::update(double t)
{
	for (auto g : _pGenerator) {
		auto partGens = pfr.getPartGens();
		for (auto pg : g->generateParticles()) {
			for (auto& e : partGens[g]) {
				pfr.addRegistry(e, pg);
			}
			_particles.push_back(pg);
		}
	}
	pfr.updateForces(t);
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
	case 0: { //??
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->getPose() = PxTransform(0.0, 0.0, 0.0);
		temp->getAcceleration() += Vector3{0.0, -9.8, 0.0};
		temp->getGeneration() = 2;


		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[CHERRY_BLOSSOM]);
		aux1->getMass() = 3;
		auxGen1->setParticle(aux1);
		auxGen1->setRandomLifespan(true);
		auxGen1->setNParticles(5);

		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator());
		Firework* aux2 = new Firework(partType[FIREWORK]);
		aux2->getColor() = colorsInfo[LIGHT_BLUE];
		aux2->getMass() = 3;
		aux2->addGenerator(auxGen1);
		auxGen2->setParticle(aux2);
		auxGen2->setRandomLifespan(true);
		auxGen2->setNParticles(7);


		temp->addGenerator(auxGen1);
		temp->addGenerator(auxGen2);
 
		_particles.push_back(temp);
		delete aux1;
		delete aux2;
		break;
	}
	case 1: { //RAINBOW
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->getGeneration() = 2;
		temp->getPose() = PxTransform(0.0, 0.0, 0.0);
		temp->getAcceleration() += Vector3{ 0.0, -9.8, 0.0 };

		for (int i = 0; i < 7; ++i) {
			std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
			Firework* aux1 = new Firework(partType[DEFAULT]);
			aux1->getColor() = colorsInfo[RED + i];
			auxGen1->setParticle(aux1);
			auxGen1->setNParticles(2);
			auxGen1->setRandomLifespan(true);
			temp->addGenerator(auxGen1);
			delete aux1;
		}

		_particles.push_back(temp);
		break;
	}
	case 2: { //LAME 
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->getGeneration() = 4;
		temp->getPose() = PxTransform(0.0, 0.0, 0.0);
		temp->getAcceleration() += Vector3{ 0.0, -9.8, 0.0 };

		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator());
		Firework* aux1 = new Firework(partType[DEFAULT]);
		aux1->getColor() = colorsInfo[RED];
		auxGen1->setParticle(aux1);
		auxGen1->setNParticles(100);
		auxGen1->setRandomLifespan(true);
		temp->addGenerator(auxGen1);
		delete aux1;

		_particles.push_back(temp);
		break;
	}
	case 3: { //wtfd
		Firework* temp = new Firework(partType[FIREWORK]);
		temp->getGeneration() = 4;
		temp->getPose() = PxTransform(0.0, 0.0, 0.0);
		temp->getAcceleration() += Vector3{ 0.0, -9.8, 0.0 };

		std::shared_ptr<ParticleGenerator> auxGen1(new GaussianParticleGenerator()); //genera aux1234
		std::shared_ptr<ParticleGenerator> auxGen2(new GaussianParticleGenerator()); //genera aux234
		std::shared_ptr<ParticleGenerator> auxGen3(new GaussianParticleGenerator()); //genera aux34
		std::shared_ptr<ParticleGenerator> auxGen4(new GaussianParticleGenerator()); //genera aux4

		Firework* aux1 = new Firework(partType[FIREWORK]);
		aux1->getColor() = colorsInfo[RED];
		Firework* aux2 = new Firework(partType[FIREWORK]);
		aux2->getColor() = colorsInfo[LIGHT_BLUE];
		Firework* aux3 = new Firework(partType[FIREWORK]); //aux3 genera particulas aux4
		aux3->getColor() = colorsInfo[GREEN];
		Firework* aux4 = new Firework(partType[DEFAULT]); //aux4 genera particulas normales

		auxGen1->setNParticles(4);
		auxGen2->setNParticles(4);
		auxGen3->setNParticles(4);
		auxGen4->setNParticles(4);
		auxGen1->setRandomLifespan(true);
		auxGen2->setRandomLifespan(true);
		auxGen3->setRandomLifespan(true);
		auxGen4->setRandomLifespan(true);

		aux4->getColor() = colorsInfo[PINK];
		auxGen4->setParticle(aux4);

		aux3->addGenerator(auxGen4);
		auxGen3->setParticle(aux3);

		aux2->addGenerator(auxGen3);
		aux2->addGenerator(auxGen4);
		auxGen2->setParticle(aux2);

		aux1->addGenerator(auxGen2);
		aux1->addGenerator(auxGen3);
		aux1->addGenerator(auxGen4);
		auxGen1->setParticle(aux1);

		temp->addGenerator(auxGen1);
		temp->addGenerator(auxGen2);
		temp->addGenerator(auxGen3);
		temp->addGenerator(auxGen4);

		_particles.push_back(temp);

		delete aux1;
		delete aux2;
		delete aux3;
		delete aux4;
		break;
	}
	default:
		break;
	}
}

void ParticleSystem::addGenerator(unsigned type) {
	switch (type)
	{
	case 0: {
		UniformParticleGenerator* mistGen = new UniformParticleGenerator();
		Particle* mistParticle = new Particle(partType[MIST]);
		mistGen->setParticle(mistParticle);
		mistGen->setOffset({ 50.0f, 50.0f, 50.0f });
		mistGen->setMeanVelocity({ 0.1, 0.1, 0.1 });
		_pGenerator.push_back(mistGen);
		delete mistParticle;
		break;
	}
	case 1: {
		GaussianParticleGenerator* cherryGen = new GaussianParticleGenerator();
		Particle* cherryParticle = new Particle(partType[CHERRY_BLOSSOM]);
		cherryGen->setParticle(cherryParticle);
		cherryGen->setOffset({ 50.0f, 50.0f, 50.0f });
		cherryGen->setMeanVelocity({ 0.05, 0.00, 0.05 });
		_pGenerator.push_back(cherryGen);
		delete cherryParticle;
		break;
	}
	case 2: {
		UniformParticleGenerator* rainGen = new UniformParticleGenerator();
		Particle* waterParticle = new Particle(partType[WATER]);
		rainGen->setParticle(waterParticle);
		rainGen->setOffset({ 50.0f, 5.0f, 50.0f });
		rainGen->setMeanVelocity({ 0.05, 0.00, 0.05 });
		rainGen->setOrigin({ 00.0f, 100.0f, 0.0f });
		_pGenerator.push_back(rainGen);
		delete waterParticle;
		break;
	}
	case 3: {
		UniformParticleGenerator* uniGen = new UniformParticleGenerator();
		Particle* auxParticle = new Particle(partType[ICE], true);
		uniGen->setParticle(auxParticle);
		uniGen->setMeanVelocity({ 3, 3, 3 });
		uniGen->setOrigin({ 20.0f, 20.0f, 20.0f });
		pfr.addPaticleGenerator(new GravityForceGenerator({ 0.0, -9.8, 0.0, }), uniGen);

		_pGenerator.push_back(uniGen);

		delete auxParticle;
		break;
	}
	case 4: {
		GaussianParticleGenerator* gausGen = new GaussianParticleGenerator();
		Particle* auxParticle2 = new Particle(partType[ICE]);
		gausGen->setParticle(auxParticle2);
		gausGen->setMeanVelocity({ 3, 3, 3 });
		gausGen->setOrigin({ -20.0f, 20.0f, 20.0f });
		pfr.addPaticleGenerator(new GravityForceGenerator({ 0.0, -2, 0.0, }), gausGen);

		_pGenerator.push_back(gausGen);

		delete auxParticle2;
		break;
	}
	case 9: { //hose
		UniformParticleGenerator* hoseGen = new UniformParticleGenerator();
		Particle* waterParticle = new Particle(partType[WATER]);
		hoseGen->setParticle(waterParticle);
		hoseGen->setMinVar(0);
		hoseGen->setMaxVar(0.4f);
		hoseGen->setMeanVelocity({ 100, 10, -10 });
		hoseGen->setOrigin({ 20.0f, 20.0f, 20.0f });
		_pGenerator.push_back(hoseGen);
		delete waterParticle;
		break;
	}
	default:
		break;
	}
}