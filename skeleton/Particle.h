#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

namespace part {
	const int nColors = 9;
	const int nTypes = 9;

	enum _colors : int {
		GRAY,
		RED,
		GREEN,
		BLUE,
		PINK,
		PURPLE,
		BLACK,
		WHITE,
		LIGHT_BLUE
	};

	static Vector4 colorsInfo[nColors] = {
		{0.2, 0.2, 0.2, 1.0},
		{1.0, 0.0, 0.0, 1.0},
		{0.0, 1.0, 0.0, 1.0},
		{0.0, 0.0, 1.0, 1.0},
		{1.0, 0.2, 0.1, 1.0},
		{1.0, 0.2, 1.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{0.0, 0.2, 1.0, 1.0}
	};

	enum _types : int {
		DEFAULT,
		BULLET,
		FIREWORK,
		CHERRY_BLOSSOM,
		ICE,
		WATER,
		FIRE,
		LIGHT,
		DARK
	};

	struct ParticleInfo {
		int _type;
		PxTransform pose;
		Vector3 velocity;
		Vector3 acceleration;
		double mass;
		double damping;
		double lifespan;
		Vector4 color;
		int _generation;

		bool visible;
		bool alive;
		RenderItem* renderItem;
	};

	static ParticleInfo partType[nTypes] = {
		{DEFAULT, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 2, 0.998, 5,
		colorsInfo[GRAY], 0, false, true, nullptr},

		{BULLET, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 1, 0.998, 3,
		colorsInfo[BLACK], 0, true, true, nullptr},

		{FIREWORK, { 0.0, 0.0, 0.0 }, { 0.0, 25.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 0.8, 0.998, 2,
		colorsInfo[RED], 4, true, true, nullptr},

		{CHERRY_BLOSSOM, { 0.0, 0.0, 0.0 }, { 0.2, 0.2, -0.2 },
		{ 0.0, 0.0, -0.01 }, 0.1, 0.998, 10,
		colorsInfo[PINK], 0, true, true, nullptr},

		{ICE, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }, 0.1, 0.998, 10,
		colorsInfo[LIGHT_BLUE], 0, true, true, nullptr},
	};
}

using namespace part;

class Particle
{
public:
	Particle(bool v = true, Vector3 pos = { 0.0, 0.0, 0.0 }, Vector3 Vel = { 0.0, 0.0, 0.0 },
		Vector3 Acc = { 0.0, 0.0, 0.0 }, double m = 0.1, double damp = 0.998, double ls = 5, 
		Vector4 c = { 0.19, 0.1, 0.2, 1.0 }, unsigned t = 0, int gen = 0);
	Particle(int type, bool v = true);
	Particle(Particle* p, bool v = true);
	Particle(ParticleInfo pI, bool v = true);
	~Particle();

	void integrate(double t);

protected:

	ParticleInfo pInfo;

public:

	inline PxTransform* getPose() { return &pInfo.pose; };
	inline Vector3* getVelocity() { return &pInfo.velocity; };
	inline Vector3* getAcceleration() { return &pInfo.acceleration; };
	inline double* getLifespan() { return &pInfo.lifespan; };
	inline Vector4* getColor() { return &pInfo.color; };
	inline double* getMass() { return &pInfo.mass; };
	inline int* getType() { return &pInfo._type; };
	inline int* getGeneration() { return &pInfo._generation; };

	double _ls;
	
	bool isAlive();

	enum ParticleType { DEFAULT, BULLET, FIREWORK};

	virtual Particle* clone() const;
	inline void die() { if (pInfo.renderItem != nullptr) pInfo.renderItem->release(); };
	inline void show() { if(pInfo.renderItem == nullptr) pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color); }
	inline int randomColor() { return rand() % nColors ; }
};

