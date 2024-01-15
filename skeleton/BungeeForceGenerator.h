#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"

class BungeeForceGenerator : public SpringForceGenerator {
public:
	BungeeForceGenerator(double k, double resting_length, Particle* other);
	virtual void updateForce(Particle* particle);
	virtual ~BungeeForceGenerator() {}
};