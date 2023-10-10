#include "SceneManager.h"

SceneManager::SceneManager() 
{
	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	sceneDesc = new PxSceneDesc(gPhysics->getTolerancesScale());
	sceneDesc->gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc->cpuDispatcher = gDispatcher;
	sceneDesc->filterShader = contactReportFilterShader;
	sceneDesc->simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(*sceneDesc);

	changeScene(0);
}

SceneManager::~SceneManager()
{
	clear();
	switch (currScene)
	{
	case 0:
	{
		delete shoot;
	}
	default:
		break;
	}

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

	for (auto e : particles)
		delete e;
}

void SceneManager::update(double t)
{
	gScene->simulate(t);
	gScene->fetchResults(true);

	switch (currScene)
	{
	case 0: {
		shoot->integrate(t);
	}
	default:
		break;
	}

	for (auto e : particles)
		e->integrate(t);
}

void SceneManager::keyPress(unsigned char key, const PxTransform& camera)
{
	switch (currScene)
	{
	case 0:
	{
		switch (toupper(key))
		{
		case 'B':
		{
			shoot->shoot(Shooter::PISTOL);
			break;
		}
		case 'L':
		{
			shoot->shoot(Shooter::LASER);
			break;
		}
		case 'J':
		{
			shoot->shoot(Shooter::ARTILLERY);
			break;
		}
		case 'F':
		{
			shoot->shoot(Shooter::FIREBALL);
			break;
		}
		}
	default:
		break;
	}
	}
}

void SceneManager::changeScene(int scene)
{
	clear();
	currScene = scene;
	switch (currScene)
	{
	case 0:
	{
		shoot = new Shooter();
	}
	default:
		break;
	}
}

void SceneManager::clear()
{
	//gScene->release();
	//gScene = gPhysics->createScene(*sceneDesc);
}