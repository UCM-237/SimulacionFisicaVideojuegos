#pragma once
#include  <list>
#include <vector>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Firework.h"

using namespace std;
class ParticleSystem
{
	list<Particle*> _particles;
	list<ParticleGenerator*> _pGenerator;
	Vector3 _gravity;

	int payload;
	ParticleGenerator* _firework_generator;
	vector<Firework*> _firework_pool;
	void onParticleDeath(Particle* p);
public:
	ParticleSystem(const Vector3& g = { 0.0f, -9.8f, 0.0f });
	~ParticleSystem();

	void update(double t);
	void generateFirework(unsigned firework_type);
	ParticleGenerator* getParticleGenerator(const string& n);
	void createFireworkSystem();
};

