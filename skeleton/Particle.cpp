#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls)
	: pose(PxTransform(pos.x, pos.y, pos.z)), vel(Vel), acc(Acc), mass(m), damping(damp), lifespan(ls), alive(true)
{
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(5)), &pose, { 0.19, 0.1, 0.2, 1.0 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p += vel * t;
	vel += acc * t;
	vel *= powf(damping, t);

	lifespan -= t;
	if (lifespan < 0) {
		alive = false;
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

bool Particle::isAlive()
{
	return alive;
}
