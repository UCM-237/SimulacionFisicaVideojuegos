#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"

typedef enum ParticleType_ {
	BALL, CANNON, BULLET, LASER, FIREWORK, FOG, DROP, WIND, BOX, WATER
}ParticleType;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel = {0.0, 0.0, 0.0}, Vector3 Acc = {0.0, 0.0, 0.0}, double damp = 0.999, double duration = 10.0f, double t = 0.0f, ParticleType type = BALL);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damp, double duration, double t, Vector4 color,ParticleType type);
	virtual ~Particle();

	//! Integrates the particle a determinate amount of time
	//! Returns true if the particle keeps going!
	virtual bool update(double t);

	inline void setMass(float new_mass) {
		_mass = new_mass;
		_inv_mass = 1.0f / new_mass;
	}

	inline void setPos(Vector3 p) {
		_pose.p = p;
	}

	inline void setVel(Vector3 v) {
		_vel = v;
	}

	inline void addForce(Vector3 f) {
		_force_accum += f;
	}

	inline void clearAccum() {
		_force_accum *= 0.0;
	}
	inline Vector3 getVel() {
		return _vel;
	}
	inline Vector3 getPos() {
		return _pose.p;
	}
//protected:
	ParticleType _type;
	Vector3 _vel, _acc, _force_accum;

	double _damp;
	double _mass;
	double _inv_mass;

	double _creation_time;
	double _remaining_time;
	double _duration;

	physx::PxTransform _pose;

	RenderItem* _render_item;

	virtual Particle* clone() const;

	//friend class ParticleSystem;
	//friend class ParticleGenerator;
protected:
	inline Particle() { _mass = _inv_mass = 1.0; }
};

