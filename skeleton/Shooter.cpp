#include "Shooter.h"

Shooter::Shooter() 
{
}

Shooter::~Shooter()
{
}

void Shooter::integrate(double t)
{
	for (auto e : shotParticles) {
		if (e != nullptr && !e->isAlive()) delete e;
		else {
			e->integrate(t);
		}
	}
}

void Shooter::shoot(currentShotType cst)
{
	Particle* temp = new Particle();
	shotParticles.push_back(temp);

	switch (cst)
	{
	case PISTOL:
		temp->setMass(2.0f); // 2.0 Kg
		temp->setVelocity(GetCamera()->getDir() * 35.0f); // 35 m/s
		temp->setAcceleration({ 0.0f, -1.0f, 0.0f });
		temp->setDamping(0.99f);
		break;
	case ARTILLERY:
		temp->setMass(200.0f); // 200.0 Kg
		temp->setVelocity({ 0.0f, 30.0f, 40.0f });
		temp->setAcceleration({ 0.0f, -20.0f, 0.0f });
		temp->setDamping(0.99f);
		break;
	case FIREBALL:
		temp->setMass(1.0f); // 1.0 Kg
		temp->setVelocity({ 0.0f, 0.0f, 10.0f });
		temp->setAcceleration({ 0.0f, 0.6f, 0.0f }); // floats
		temp->setDamping(0.9f);
		break;
	case LASER:
		temp->setMass(0.1f); // almost no weight
		temp->setVelocity({ 0.0f, 0.0f, 100.0f }); // No gravity
		temp->setAcceleration({ 0.0f, 0.0f, 0.0f });
		temp->setDamping(0.99f);
		break;
	}

	temp->setPosition(PxTransform(GetCamera()->getEye()));
}
