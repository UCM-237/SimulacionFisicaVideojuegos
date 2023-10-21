#include "Firework.h"

Firework::Firework(bool v, Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, Vector4 c, unsigned t, int generation)
	: Particle(v, { 0.0, 0.0, 0.0 }, { 0.0, 25.0, 0.0 }, Acc, m, damp, ls, c, t, generation)
{
	_type = Particle::FIREWORK;
}

Firework::Firework(Firework* f, bool v) : Particle(v, { 0.0, 0.0, 0.0 }, { 0.0, 25.0, 0.0 }, 
	f->acceleration, f->mass, f->damping, f->lifespan, f->color, f->_type, f->_generation) {
}

std::list<Particle*> Firework::explode()
{
	std::list<Particle*> ret;
	for (auto e : _gens) {
		e->setParticle(this, false);
		e->setOrigin(Vector3(pose.p));
		e->setMeanVelocity({20, 20, 20});
		e->setMeanDuration(lifespan);

		for (auto g : e->generateParticles()) {
			ret.push_back(g);
		}
	}
	return ret;
}

void Firework::addGenerator(std::shared_ptr<ParticleGenerator> p)
{
	//_gens.push_back(std::make_shared<ParticleGenerator>(&p));
	_gens.push_back(p);
}

Particle* Firework::clone() const
{
	Firework* aux = new Firework(false, pose.p, velocity, acceleration, mass, damping, lifespan, color, _type, _generation);
	aux->_gens = _gens;
	return aux;
}
