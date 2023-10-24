#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator
{
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;

	std::normal_distribution<float> _n{ minVar, maxVar };
public:
	GaussianParticleGenerator(Vector3 origin = { 0.0, 0.0, 0.0 }, 
		Vector3 mean_velocity = { 0.0, 0.0, 0.0 });
	~GaussianParticleGenerator() {};
	virtual std::list<Particle*> generateParticles();
	virtual void setVars();
};
