#include "Fountain.h"

Fountain::Fountain(Vector3 origin, Vector3 mean_velocity)
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	_origin = origin;
	_mean_velocity = mean_velocity;
	setParticle(new Particle(_origin, _mean_velocity, { 0.0, 0.0, 0.0 }, 1, 0.998, 5,
		CreateShape(PxSphereGeometry(1)), { 0.0, 0.1, 0.8, 1.0 }));
	_mt = std::mt19937{ std::random_device()() };
}

Fountain::~Fountain()
{
	delete _model_particle;
}

std::list<Particle*> Fountain::generateParticles()
{
	std::list<Particle*> ret;
	if (_u(_mt) < _generation_prob) {
		for (int i = 0; i < _n_particles; ++i) {
			ret.push_back(new Particle(_origin, { _velx(_mt) * _mean_velocity.x, _vely(_mt) * _mean_velocity.y, _velz(_mt) * _mean_velocity.z },
				{0.0, 0.0, 0.0}, 1, 0.998, 5, CreateShape(PxSphereGeometry(1)), { 0.0, 0.1, 0.8, 1.0 }));
		}
	}
	return ret;
}

