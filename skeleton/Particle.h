#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class Particle
{
public:
	Particle(Vector3 pos = { 0.0, 0.0, 0.0 }, Vector3 Vel = { 0.0, 0.0, 0.0 },
		Vector3 Acc = { 0.0, 0.0, 0.0 }, double m = 1, double damp = 0.998, double ls = 5, 
		PxShape* s = CreateShape(PxSphereGeometry(5)), Vector4 c = { 0.19, 0.1, 0.2, 1.0 });
	Particle(Particle* p);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	Vector3 acc;
	PxTransform pose;
	RenderItem* renderItem;
	PxShape* shape;
	Vector4 color;

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
	void setLifespan(const double ls);

	inline PxTransform getPose() { return pose; };
	inline Vector3 getVelocity() { return vel; };
	inline Vector3 getAcceleration() { return acc; };
	inline double getLifespan() { return lifespan; };
	
	bool isAlive();

	enum ParticleType { DEFAULT, BULLET, FIREWORK};

	virtual Particle* clone() const;
	inline void die() { DeregisterRenderItem(renderItem); };
};

