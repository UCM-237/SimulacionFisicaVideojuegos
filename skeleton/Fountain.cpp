#include "Fountain.h"

Fountain::Fountain(Vector3 _origin, Vector3 _mean_velocity)
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	_model_particle = new Particle(_origin, _mean_velocity, { 0.0, 0.0, 0.0 }, 1, 0.998, 1000, 
		CreateShape(PxSphereGeometry(1)), { 0.0, 0.1, 0.8, 1.0 });
	setParticle(p);
}

Fountain::~Fountain()
{
	delete p;
}

std::list<Particle*> Fountain::generateParticles()
{
	return std::list<Particle*>();
}

void Fountain::integrate(double t)
{
	int i = 
}
