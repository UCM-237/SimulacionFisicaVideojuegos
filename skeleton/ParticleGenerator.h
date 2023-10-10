#pragma once
#include <time.h>
#include <list>
#include <random>
#include "Particle.h"
#include "core.hpp"


class ParticleGenerator
{
protected:
	ParticleGenerator() {};
	~ParticleGenerator() {};

	int _n_particles = 3; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0,1 };
	float variancex = 5;
	float variancey = 10;
	float variancez = 5;
	std::uniform_real_distribution<float> _velx{ -variancex,variancex };
	std::uniform_real_distribution<float> _vely{ -variancey,variancey };
	std::uniform_real_distribution<float> _velz{ -variancez,variancez };
	std::string _name;


public:
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->setLifespan(new_duration);
	}
	//! @brief --> sets the particle, including its type, lifetime and mean positionsand velocities
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		delete _model_particle;
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getPose().p;
			_mean_velocity = p->getVelocity();
		}
		_model_particle->setPosition({ -1000.0f, -1000.0f, -1000.0f });
	}
	inline void setNParticles(int n_p) { _n_particles = n_p; }

	inline void setXvariance(float f) { variancex = f; };
	inline void setYvariance(float f) { variancey = f; };
	inline void setZvariance(float f) { variancez = f; };
};

