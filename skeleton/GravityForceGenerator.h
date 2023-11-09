#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator 
{
protected:
	Vector3 _gravity;
public:
	GravityForceGenerator(const Vector3& g) : _gravity(g) {};

	virtual void updateForce(Particle* p, double t);

	inline void setGravity(Vector3 g) { _gravity = g; }
};

