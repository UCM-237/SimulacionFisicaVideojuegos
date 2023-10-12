#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3& g) : _gravity(g)
{
	_pGenerator.push_back(new Fountain({ 0.0, 0.0, 0.0 }, {5.0, 10.0, 5.0}));
}

ParticleSystem::~ParticleSystem()
{
	//for (auto e : _particles) {
	//	e->die();
	//}
	_particles.clear();
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
		float ls = e->getLifespan();
		e->setLifespan(ls - t);
		if (ls < 0) {
			//_particles.remove(e);
			//e->die();
			_dumpster.push_back(e);
		}
	}

	for (auto d : _dumpster) {
		_particles.remove(d);
		d->die();
	}
	_dumpster.clear();
}
