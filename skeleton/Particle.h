#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class Particle
{
public:
	Particle(Vector3 pos = { 0.0, 0.0, 0.0 }, Vector3 Vel = { 0.0, 0.0, 0.0 },
		Vector3 Acc = { 0.0, 0.0, 0.0 }, double m = 1, double damp = 0.998, double ls = 1000);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	Vector3 acc;
	PxTransform pose;
	RenderItem* renderItem;

	double lifespan;
	double damping;
	double mass;

	bool alive;

public:
	void setMass(const double m);
	void setPosition(const PxTransform p);
	void setVelocity(const Vector3 v);
	void setAcceleration(const Vector3 a);
	void setDamping(const double d);
	
	bool isAlive();
};

