#pragma once
#include "ParticleGenerator.h"
class Fountain : public ParticleGenerator
{
public:
	Fountain(Vector3 origin = { 0.0, 0.0, 0.0 }, Vector3 mean_velocity = { 0.0, 0.0, 0.0 });
	~Fountain();
	virtual std::list<Particle*> generateParticles();
};

