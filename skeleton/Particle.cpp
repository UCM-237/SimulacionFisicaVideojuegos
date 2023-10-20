#include "Particle.h"

Particle::Particle(bool v, Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, Vector4 c, unsigned t)
	: pose(PxTransform(pos.x, pos.y, pos.z)), velocity(Vel), acceleration(Acc), mass(m), damping(damp), lifespan(ls), _ls(ls), alive(true), color(c), _type(t)
{
	if (v)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(m)), &pose, c);
	else
		renderItem = nullptr;
}

Particle::Particle(Particle* p, bool v) : pose(p->pose), velocity(p->velocity), acceleration(p->acceleration), mass(p->mass), damping(p->damping), lifespan(p->lifespan), _ls(p->lifespan), alive(true), _type(p->_type)
{
	if (v)
		renderItem = p->renderItem;
	else
		renderItem = nullptr;
}

Particle::~Particle()
{
	die();
}

void Particle::integrate(double t)
{
	pose.p += velocity * t;
	velocity += acceleration * t;
	velocity *= powf(damping, t);
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
	velocity = v;
}

void Particle::setAcceleration(const Vector3 a)
{
	acceleration = a;
}

void Particle::setDamping(const double d)
{
	damping = d;
}

void Particle::setLifespan(const double ls)
{
	lifespan = ls;
	_ls = ls;
}

bool Particle::isAlive()
{
	return alive;
}

Particle* Particle::clone() const
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	return new Particle((renderItem != nullptr), pose.p, velocity, acceleration, mass, damping, lifespan, color, _type);
}
