#include "Shooter.h"

Shooter::Shooter() {}

Shooter::~Shooter()
{
}

void Shooter::integrate(double t)
{
	for (auto e : shotParticles) {
		e->integrate(t);
	}
}

void Shooter::shoot(currentShotType cst)
{
	Particle* temp = new Particle();
	shotParticles.push_back(temp);
	float m = 0, v = 0;
	Vector3 a = {0.0f, 0.0f, 0.0f};

	switch (cst)
	{
	case PISTOL:
		m = 2.0;
		v =  35.0f;
		a = { 0.0f, -1.0f, 0.0f };
		break;
	case ARTILLERY:
		m = 200.0f; // 200.0 Kg
		v = 40.0f;
		a ={ 0.0f, -20.0f, 0.0f };
		break;
	case FIREBALL:
		m = 1.0f; // 1.0 Kg
		v = 10.0f;
		a = { 0.0f, 0.6f, 0.0f }; // floats
		break;
	case LASER:
		m = 0.1f; // almost no weight
		v = 100.0f; // No gravity
		a = { 0.0f, 0.0f, 0.0f };
		break;
	}

	temp->getMass() = m; // almost no weight
	temp->getVelocity() = GetCamera()->getDir() * v;
	temp->getAcceleration() = a;
	temp->getPose() = PxTransform(GetCamera()->getEye());
}
