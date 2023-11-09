#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	//chek if particle has finite mass
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	//compute the drag force
	Vector3 v = particle->getVelocity();
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;

	std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << "\n";
	particle->addForce(dragF);

}
