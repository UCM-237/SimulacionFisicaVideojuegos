#pragma once
#include "ParticleGenerator.h"
class Fountain : public ParticleGenerator
{
public:
	Fountain(Vector3 _origin = { 0.0, 0.0, 0.0 }, Vector3 _mean_velocity = { 0.0, 0.0, 0.0 });
	~Fountain();
	virtual std::list<Particle*> generateParticles();

	virtual void integrate(double t);
};

