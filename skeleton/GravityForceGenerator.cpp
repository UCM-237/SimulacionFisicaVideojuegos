#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass()) < 1e-10)
		return;

	p->addForce(_gravity * (p->getMass()));
}
