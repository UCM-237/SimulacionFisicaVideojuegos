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
		delete pSys;
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
		pSys->update(t);
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
			//case 'P':
			//{
			//	shoot->shoot(Shooter::PISTOL);
			//	break;
			//}
			//case 'L':
			//{
			//	shoot->shoot(Shooter::LASER);
			//	break;
			//}
			//case 'J':
			//{
			//	shoot->shoot(Shooter::ARTILLERY);
			//	break;
			//}
			//case 'B':
			//{
			//	shoot->shoot(Shooter::FIREBALL);
			//	break;
			//}
			case 'M':
			{
				pSys->addGenerator(9);
				break;
			}
			case 'F' :
			{
				pSys->generateFirework(0);
				break;
			}
			case 'G':
			{
				pSys->generateFirework(1);
				break;
			}
			case 'H':
			{
				pSys->generateFirework(2);
				break;
			}
			case 'J':
			{	pSys->generateFirework(3);
				break;
			}
			case '0': 
			{
				pSys->addGenerator(0);
				break;
			}
			case '1':
			{
				pSys->addGenerator(1);
				break;
			}
			case '2':
			{
				pSys->addGenerator(2);
				break;
			}
			case '3':
			{
				pSys->addGenerator(3);
				pSys->addGenerator(4);
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
		pSys = new ParticleSystem();
	}
	case 1: 
	{
		pSys = new ParticleSystem();
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
