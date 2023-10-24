#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 origin, Vector3 mean_velocity)
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	_origin = origin;
	_mean_velocity = mean_velocity;
	setParticle(new Particle(false, _origin, _mean_velocity, { 0.0, 0.0, 0.0 }, 0.25, 0.998, 5, { 0.0, 0.1, 0.8, 1.0 }));
	_mt = std::mt19937{ std::random_device()() };
}

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
	std::list<Particle*> ret;
	if (_u(_mt) <= _generation_prob) {
		for (int i = 0; i < _n_particles; ++i) {
			Vector3 v = Vector3( _n(_mt), _n(_mt) , _n(_mt) ) * _mean_velocity;
			*_model_particle->getPose() = PxTransform(_origin + Vector3((_n(_mt) * offset.x), (_n(_mt) * offset.y), (_n(_mt) * offset.z)));
			*_model_particle->getVelocity() = v;
			if(randomLifespan) {
				*_model_particle->getLifespan() = (_u(_mt) * randomLifespanLimits) + minLifespan;
			}
			ret.push_back(_model_particle);

			setParticle(_model_particle, false);
		}
	}
	return ret;
}

void GaussianParticleGenerator::setVars()
{
	_n = std::normal_distribution<float>(minVar, maxVar);
}