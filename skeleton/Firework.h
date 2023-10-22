#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include <memory>
class Firework : public Particle
{
protected:
	std::list<std::shared_ptr<ParticleGenerator>> _gens;
	//std::list<ParticleGenerator*> _gens;
public:
	Firework(bool v = true, Vector3 pos = { 0.0, 0.0, 0.0 }, Vector3 Vel = { 0.0, 0.0, 0.0 },
		Vector3 Acc = { 0.0, 0.0, 0.0 }, double m = 0.25, double damp = 0.998, double ls = 2,
		Vector4 c = { 1.0, 0.1, 0.2, 1.0 }, unsigned t = 0, int gen = 3);
	Firework(ParticleInfo pInf = partType[FIREWORK]);
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	std::list<Particle*> explode();
	void addGenerator(std::shared_ptr<ParticleGenerator> p);
	std::list<std::shared_ptr<ParticleGenerator>>* getGens() { return &_gens; };
	virtual Particle* clone() const;
};

