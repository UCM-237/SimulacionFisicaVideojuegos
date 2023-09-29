#include "Particle.h"

Particle::Particle(Vector3 pos = {0.0, 0.0, 0.0}, Vector3 Vel = {0.0, 0.0, 0.0}) : vel(Vel)
{

	pose = PxTransform(pos.x, pos.y, pos.z);
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(5)), &pose, { 1.0, 0.0, 0.0, 1.0 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p += vel;
}
