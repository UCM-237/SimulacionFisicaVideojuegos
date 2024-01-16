#pragma once
#include <vector>
#include "Particle.h"
#include "RenderUtils.hpp"

using namespace std;

class SceneManager
{
private:
	vector <Particle*> _projectiles;
	Camera* cam;
	int _num_projectiles;
public:
	SceneManager(unsigned char scene);
	void update(double t);
	void addProjectile(void);
	~SceneManager(void);

};

