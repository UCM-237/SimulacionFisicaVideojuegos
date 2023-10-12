#include "Firework.h"

void Firework::addGenerator(ParticleGenerator* p)
{
	_gens.push_back(&p);
}
