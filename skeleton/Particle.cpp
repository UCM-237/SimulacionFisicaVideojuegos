#include "Particle.h"

Particle::Particle(bool v, Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, Vector4 c, unsigned t, int gen)
	//: pose(PxTransform(pos.x, pos.y, pos.z)), velocity(Vel), acceleration(Acc), mass(m), damping(damp), lifespan(ls), 
	//_ls(ls), alive(true), color(c), _type(t), _generation(gen)
{
	pInfo.pose = PxTransform(pos.x, pos.y, pos.z);
	pInfo.velocity = Vel;
	pInfo.acceleration = Acc;
	pInfo.mass = m;
	pInfo.damping = damp;
	pInfo.lifespan = ls;
	pInfo.color = c;
	pInfo._type = t;
	pInfo._generation = gen;
	pInfo.visible = v;

	_ls = ls;

	if (v)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(m)), &pInfo.pose, c);
	else
		pInfo.renderItem = nullptr;
}

Particle::Particle(int type, bool v)
{
	pInfo = partType[type];
	_ls = pInfo.lifespan;

	if (v)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color);
	else
		pInfo.renderItem = nullptr;
}

Particle::Particle(Particle* p, bool v) : pInfo(p->pInfo), _ls(p->_ls)
{
	if (v)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color);
	else
		pInfo.renderItem = nullptr;
}

Particle::Particle(ParticleInfo pI, bool v) : pInfo(pI), _ls(pI.lifespan)
{
	if (v)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color);
	else
		pInfo.renderItem = nullptr;
}

Particle::~Particle()
{
	die();
}

void Particle::integrate(double t)
{
	pInfo.pose.p += pInfo.velocity * t;
	pInfo.velocity += pInfo.acceleration * t;
	pInfo.velocity *= powf(pInfo.damping, t);
}

bool Particle::isAlive()
{
	return pInfo.alive;
}

Particle* Particle::clone() const
{
	//Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, PxShape* s, Vector4 c
	return new Particle((pInfo.renderItem != nullptr), pInfo.pose.p, pInfo.velocity, pInfo.acceleration, 
		pInfo.mass, pInfo.damping, pInfo.lifespan, pInfo.color, pInfo._type, pInfo._generation);
}
