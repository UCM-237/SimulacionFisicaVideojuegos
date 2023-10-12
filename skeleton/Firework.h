#pragma once
#include <list>
#include "ParticleGenerator.h"
#include <memory>
class Firework : public Particle
{
public:
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	std::list<Particle*> explode();
	void addGenerator(ParticleGenerator* p);
	virtual Particle* clone() const;
protected:
	// Type
	unsigned _type;
	std::list<std::shared_ptr<ParticleGenerator> > _gens;
};

