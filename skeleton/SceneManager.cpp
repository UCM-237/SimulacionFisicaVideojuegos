#include "SceneManager.h"

SceneManager::SceneManager(unsigned char scene)
{
	cam = GetCamera();
	_num_projectiles = 0;
	switch (scene) {
	case '1': // P1
		break;
	}
	}
void SceneManager::update(double t)
{
	vector <Particle*> to_delete;
	if (_projectiles.size() == 0) {
		return;
	}
	if(_num_projectiles!=0){
		for(vector <Particle*>::iterator it=_projectiles.begin();it!=_projectiles.end();it++){
			if (!(*it)->update(t)) {
				to_delete.push_back(*it);
			}

		}
	}

	// Delete the projectiles
	std::vector<Particle*>::iterator iter = to_delete.begin();
	std::vector<Particle*>::iterator endIter = to_delete.end();
	for (; iter != endIter;iter++) {
		to_delete.erase(iter);
		if (to_delete.empty()) break;
		endIter = to_delete.end();
	}
}

void SceneManager::addProjectile(void)
{
	
	Vector3 vel = cam->getDir();
	vel *= 25; 
	Vector3 pos = cam->getEye();
	Vector3 acc = { 0,-0.1,0 };
	Particle* p;
	p = new Particle(pos, vel, acc, 0.98, 10, 0, CANNON);
	_projectiles.push_back(p);
	_num_projectiles++;
}

SceneManager::~SceneManager(void)
{
	Particle* p;
	//TODO: delete vector memory
	while (_projectiles.size() > 0) {
		p = _projectiles[_projectiles.size()];
		_projectiles.pop_back();
		delete p;
	}

}
