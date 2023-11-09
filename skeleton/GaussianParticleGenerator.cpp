#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 origin, Vector3 mean_velocity)
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	_origin = origin;
	_mean_velocity = mean_velocity;
	setParticle(new Particle(false, _origin, _mean_velocity, { 0.0, 0.0, 0.0 }, 0.25, 0.998, 5, { 0.0, 0.1, 0.8, 1.0 }));
	_mt = std::mt19937{ std::random_device()() };
}

void GaussianParticleGenerator::setVars()
{
	_n = std::normal_distribution<float>(minVar, maxVar);
}

Vector3 GaussianParticleGenerator::getRandomDist()
{
	return Vector3(_n(_mt), _n(_mt), _n(_mt));
}