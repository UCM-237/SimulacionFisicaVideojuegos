#include "Firework.h"

Firework::Firework(bool v, Vector3 pos, Vector3 Vel, Vector3 Acc, double m, double damp, double ls, Vector4 c, unsigned t, int gen)
	: Particle(false, { 0.0, 0.0, 0.0 }, { 0.0, 25.0, 0.0 }, Acc, m, damp, ls, c, t, gen)
{
	if (pInfo.visible)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(m)), &pInfo.pose, c);
	else
		pInfo.renderItem = nullptr;
}

Firework::Firework(ParticleInfo pInf) : Particle(pInf, false)
{
	pInfo = pInf;

	if (pInfo.visible)
		pInfo.renderItem = new RenderItem(CreateShape(PxSphereGeometry(pInfo.mass)), &pInfo.pose, pInfo.color);
	else
		pInfo.renderItem = nullptr;
}


std::list<Particle*> Firework::explode()
{
	std::list<Particle*> ret;
	for (auto e : _gens) {
		//e->setParticle(this, false);
		e->setOrigin(Vector3(pInfo.pose.p));
		e->setMeanVelocity({20, 20, 20});
		e->setMeanDuration(pInfo.lifespan);

		for (auto g : e->generateParticles()) {
			g->getGeneration() = pInfo._generation - 1;
			g->getLifespan() = pInfo.lifespan;
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
	Firework* aux = new Firework(false, pInfo.pose.p, pInfo.velocity, pInfo.acceleration, pInfo.mass, 
		pInfo.damping, pInfo.lifespan, pInfo.color, pInfo._type, pInfo._generation);
	aux->_gens = _gens;
	return aux;
}
