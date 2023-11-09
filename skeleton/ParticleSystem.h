#pragma once
#include <list>
#include <iostream>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Firework.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "ParticleForceRegistry.h"

using namespace std;
class ParticleSystem
{
	list<Particle*> _particles;
	list<Particle*> _dumpster;
	// These are the registred generators(for on demand set generation prob.to 0)
	list<ParticleGenerator*> _pGenerator;
	Vector3 _gravity;

	int payload;
	// This generator is only to shoot the firework!!
	ParticleGenerator* _firework_generator;
	// Fireworks to be used as models!
	vector<Firework*> _firework_pool;
	ParticleForceRegistry pfr;
	list<ForceGenerator*> forces;
	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);
public:
	ParticleSystem(const Vector3& g = { 0.0f, -9.8f, 0.0f });
	~ParticleSystem();

	void update(double t);
	// Method to generate a Firework with the appropiate type
	void generateFirework(unsigned firework_type);
	// Gets a particle generator with name...
	ParticleGenerator* getParticleGenerator(const string& n);

	void addGenerator(unsigned type);
};

