#pragma once
#include <vector>
#include <iostream>
#include <PxScene.h>

#include "Particle.h"
#include "Shooter.h"
#include "callbacks.hpp"
#include "ParticleSystem.h"

using namespace physx;
using namespace std;

extern PxDefaultAllocator		gAllocator;
extern PxDefaultErrorCallback	gErrorCallback;

extern PxFoundation* gFoundation;
extern PxPhysics* gPhysics;
extern PxSceneDesc* sceneDesc;

extern PxMaterial* gMaterial;

extern PxPvd* gPvd;

extern PxDefaultCpuDispatcher* gDispatcher;
extern PxScene* gScene;
extern ContactReportCallback gContactReportCallback;

class SceneManager
{
private:
	vector<PxScene*> scenes;
	int currScene;
	vector<Particle*> particles;
	Shooter* shoot;
	ParticleSystem* pSys;
	
public:
	SceneManager();
	~SceneManager();
	void update(double t);
	void keyPress(unsigned char key, const PxTransform& camera);
	void changeScene(int scene);
	void clear();
};

