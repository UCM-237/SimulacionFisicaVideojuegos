#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c)
	: pose(PxTransform(pos.x, pos.y, pos.z)), vel(Vel), acc(Acc), mass(m), damping(damp), lifespan(ls), alive(true)
{
	renderItem = new RenderItem(s, &pose, c);
}

Particle::~Particle()
{
	die();
}

void Particle::integrate(double t)
{
	pose.p += vel * t;
	vel += acc * t;
	vel *= powf(damping, t);

	lifespan -= t;
	if (lifespan < 0) {
		die();
	}
}

void Particle::setMass(const double m)
{
	mass = m;
}

void Particle::setPosition(const PxTransform p)
{
	pose = p;
}

void Particle::setVelocity(const Vector3 v)
{
	vel = v;
}

void Particle::setAcceleration(const Vector3 a)
{
	acc = a;
}

void Particle::setDamping(const double d)
{
	damping = d;
}

void Particle::setLifespan(const double ls)
{
	lifespan = ls;
}

bool Particle::isAlive()
{
	return alive;
}
