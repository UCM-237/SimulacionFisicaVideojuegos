#pragma once
#include "ParticleGenerator.h"

using namespace std;

class UniformParticleGenerator : public ParticleGenerator
{
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
public:
	UniformParticleGenerator(Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 });
	~UniformParticleGenerator() {};
	virtual std::list<Particle*> generateParticles();
};

