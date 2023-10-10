#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3& g) : _gravity(g)
{
	_pGenerator.push_back(new ParticleGenerator())
}

void ParticleSystem::update(double t)
{
	for (auto e : _particles) {
		e->integrate(t);
	}
}
