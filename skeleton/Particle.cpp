#include "Particle.h"

using namespace physx;

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double d, double t,
	ParticleType type)
{
	_vel = Vel;
	_acc = Acc;
	_damp = damping;
	_remaining_time = d;
	_duration = d;
	_creation_time = t;
	setMass(1.0);
	
	_pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	// TODO: view different geometries!
	switch (type) {
	case BULLET:
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(0.5f)), &_pose, { 0.5, 0.5, 0.7, 1.0 });
		break;

	case LASER:
		_render_item = new RenderItem(CreateShape(PxBoxGeometry(5.0f, 0.1f, 0.1f)), &_pose, {0.0, 1.0, 1.0, 0.9});
		break;

	case FOG:
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(0.1f)), &_pose, { 0.8, 0.8, 0.8, 0.1 });
		break;
	case DROP:
		_render_item = new RenderItem(CreateShape(PxCapsuleGeometry(0.1f, 0.5f)), &_pose, { 0,0.1,0.8,1 });
		break;
	case WIND:
		_inv_mass = 0;
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(30.0f)), &_pose, { 0.8, 0.0, 0.0, 0.1 });
		break;
	case BOX:
		_render_item = new RenderItem(CreateShape(PxBoxGeometry(1.0f, 3.0f, 1.0f)), &_pose, { 0.4, 0.4, 0.4, 1.0 });
		setMass(1500);
		break;
	case WATER:
		_render_item = new RenderItem(CreateShape(PxBoxGeometry(100.0f, 0.5f, 100.0f)), &_pose, { 0.0, 0.0, 1.0, 1.0 });
		break;
	case BALL:
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(1.0)), &_pose, { 0.5,0,0.5,1 });
		break;
	default:
		_render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &_pose, { 0.8,0,0.1,1 });
	}
	_type = type;

	clearAccum();
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damp , double duration, double t , Vector4 color , ParticleType type ) {
	_vel = Vel;
	_acc = Acc;
	_damp = damp;
	_remaining_time = duration;
	_duration = duration;
	_creation_time = t;
	setMass(1.0);

	_pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);

	switch (type) {
	case BULLET:
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(0.5f)), &_pose, color);
		break;

	case LASER:
		_render_item = new RenderItem(CreateShape(PxBoxGeometry(5.0f, 0.1f, 0.1f)), &_pose,color);
		break;

	case FOG:
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(0.1f)), &_pose, color);
		break;
	case DROP:
		_render_item = new RenderItem(CreateShape(PxCapsuleGeometry(0.1f, 0.5f)), &_pose, color);
		break;
	case WIND:
		_inv_mass = 0;
		_render_item = new RenderItem(CreateShape(PxSphereGeometry(30.0f)), &_pose, color);
		break;
	case BOX:
		_render_item = new RenderItem(CreateShape(PxBoxGeometry(1.0f, 3.0f, 1.0f)), &_pose, color);
		setMass(1500);
		break;
	case WATER:
		_render_item = new RenderItem(CreateShape(PxBoxGeometry(100.0f, 0.5f, 100.0f)), &_pose, color);
		break;
	case BALL:
		_render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(1.5f)), &_pose, color);
		break;
	default:
		_render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5)), &_pose, color);
	}
	_type = type;

	clearAccum();
}


Particle::~Particle()
{
	DeregisterRenderItem(_render_item);
}

bool Particle::update(double delta_t) {
	// Semi-implicit Euler algorithm
	

	// Get the accel considering the force accum
	Vector3 resulting_accel = _acc + _force_accum * _inv_mass;
	_pose.p += _vel * delta_t;
	_remaining_time -= delta_t;
	_vel += resulting_accel * delta_t;  // Ex. 1.3 --> add acceleration

	_vel *= powf(_damp, delta_t);   // Exercise 1.3 --> add damping 

	// Clear accum
	clearAccum();

	return _remaining_time > 0.0;
}


Particle* Particle::clone() const {
	return new Particle(_pose.p, _vel, _acc, _damp, _duration, _creation_time, _type);
}
