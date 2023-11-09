#pragma once
#include <iostream>
#include "ForceGenerator.h"
#include "core.hpp"

class ParticleDragGenerator : public ForceGenerator
{
public:
	ParticleDragGenerator() {};
	~ParticleDragGenerator() {};
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return _k1; }
	inline float getK2() { return _k2; }

protected:
	float _k1; // coef for velocity
	float _k2; //coef fpr square velocity
};

