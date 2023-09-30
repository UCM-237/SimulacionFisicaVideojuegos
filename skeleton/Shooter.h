#pragma once
#include <vector>

#include "Particle.h"

class Shooter 
{
	std::vector<Particle*> shotParticles;
public:
	enum currentShotType  { PISTOL = 0, ARTILLERY, FIREBALL, LASER };
	Shooter();
	~Shooter();

	void integrate(double t);

	void shoot(currentShotType cst);
};

