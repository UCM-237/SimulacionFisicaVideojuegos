#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class Particle
{
public:
	Particle(bool v = true, Vector3 pos = { 0.0, 0.0, 0.0 }, Vector3 Vel = { 0.0, 0.0, 0.0 },
		Vector3 Acc = { 0.0, 0.0, 0.0 }, double m = 0.1, double damp = 0.998, double ls = 5, 
		Vector4 c = { 0.19, 0.1, 0.2, 1.0 }, unsigned t = 0, int gen = 0);
	Particle(Particle* p, bool v = true);
	~Particle();

	void integrate(double t);

protected:
	Vector3 velocity;
	Vector3 acceleration;
	PxTransform pose;
	RenderItem* renderItem;
	Vector4 color;

	double lifespan;
	double damping;
	double mass;

	bool alive;
	unsigned _type;
	int _generation;

public:
	void setMass(const double m);
	void setPosition(const PxTransform p);
	void setVelocity(const Vector3 v);
	void setAcceleration(const Vector3 a);
	void setDamping(const double d);
	void setLifespan(const double ls);
	inline void setColor(const Vector4 c) { color = c; };
	inline int* getGeneration() { return &_generation; };

	inline PxTransform getPose() { return pose; };
	inline Vector3 getVelocity() { return velocity; };
	inline Vector3 getAcceleration() { return acceleration; };
	inline double getLifespan() { return lifespan; };
	inline Vector4 getColor() { return color; };
	inline double getMass() { return mass; };
	inline unsigned getType() { return _type; };
	double _ls;
	
	bool isAlive();

	enum ParticleType { DEFAULT, BULLET, FIREWORK};

	virtual Particle* clone() const;
	inline void die() { if (renderItem != nullptr) renderItem->release(); };
	inline void show() { if(renderItem == nullptr) renderItem = new RenderItem(CreateShape(PxSphereGeometry(mass)), &pose, color); }
};

