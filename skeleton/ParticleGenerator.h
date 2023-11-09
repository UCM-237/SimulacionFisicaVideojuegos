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

	int _n_particles = 1; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	Vector3 offset = { 0.0, 0.0, 0.0 };
	float minVar = -1, maxVar = 1;
	std::mt19937 _mt;
	std::uniform_real_distribution<float> _u{ 0,1 };
	std::string _name;
	bool randomLifespan = false;
	int randomLifespanLimits;
	int minLifespan = 1;

public:
	~ParticleGenerator() { if(_model_particle != nullptr) delete _model_particle; };

	virtual std::list<Particle*> generateParticles() {
		std::list<Particle*> ret;
		if (_u(_mt) <= _generation_prob) {
			for (int i = 0; i < _n_particles; ++i) {
				Vector3 v = getRandomDist() * _mean_velocity;
				_model_particle->getPose() = PxTransform(_origin + (getRandomDist() * offset));
				_model_particle->getVelocity() = v;
				if (randomLifespan) {
					_model_particle->getLifespan() = (_u(_mt) * randomLifespanLimits) + minLifespan;
				}

				ret.push_back(_model_particle);

				setParticle(_model_particle, false);
			}
		}
		return ret;
	};

	virtual void setVars() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setOffset(const Vector3& f) { offset = f; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_velocity = v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_velocity;
	}
	inline void setMeanDuration(double new_duration) {
		_model_particle->getLifespan() = new_duration;
	}
	//! @brief --> sets the particle, including its type, lifetime and mean positionsand velocities
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		if(_model_particle != p) delete _model_particle;
		_model_particle = p->clone();
		randomLifespanLimits = _model_particle->_ls;
		if (modify_pos_vel) {
			_origin = p->getPose().p;
			_mean_velocity = p->getVelocity();
		}
	}

	virtual Vector3 getRandomDist() = 0;

	inline void setNParticles(int n_p) { _n_particles = n_p; }

	inline void setGenerationProb(double p) { _generation_prob = p; };

	inline void setDistribution(std::uniform_real_distribution<float> d) { _u = d; };

	inline void setRandomLifespan(bool b) { randomLifespan = b; };

	inline void setRandomLifespanLimits(int ls) { randomLifespanLimits = ls; };

	inline void setMinVar(float i) { minVar = i; setVars(); };

	inline void setMaxVar(float i) { maxVar = i; setVars(); };
};

