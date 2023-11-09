#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;

	std::uniform_real_distribution<float> _uVel{ minVar, maxVar };
public:
	UniformParticleGenerator(Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 });
	~UniformParticleGenerator() {};
	virtual void setVars();
	virtual Vector3 getRandomDist();
};

