#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include "SceneManager.h"

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
Particle* ball = NULL;
SceneManager *manager=NULL;
RenderItem* item = NULL;
RenderItem* item2 = NULL;
PxRigidDynamic* palo2 = NULL;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	PxRigidStatic* palo1 = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(1, 1, 1));
	palo1->attachShape(*shape);
	item = new RenderItem(shape, palo1, { 1,0.1,0.1,1 });
	gScene->addActor(*palo1);

	palo2 = gPhysics->createRigidDynamic(PxTransform({ 0.5,-10.5,0.5 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(0.5, 10, 0.5));
	palo2->attachShape(*shape2);
	item2 = new RenderItem(shape2, palo2, { 0,0.1,0.8,1 });
	gScene->addActor(*palo2);

	PxRevoluteJoint* art = PxRevoluteJointCreate(*gPhysics, palo1, { 0,0,0 }, palo2, { 0.5,-10.5,0.5 });
	//PxFixedJoint* art = PxFixedJointCreate(*gPhysics, palo1, { 0,0,0 }, palo2, { 0.5,-10.5,0.5 });
	//PxPrismaticJoint* art = PxPrismaticJointCreate(*gPhysics, palo1, { 0,0,0 }, palo2, { 0.5,-10.5,0.5 });
	PxReal f, t;
	art->getBreakForce(f,t);
	std::cout << f;
	// My stuff
	//manager = new SceneManager(1);
	//ball = new Particle(PxVec3(0, 0, 0), PxVec3(5, 0, 0), PxVec3(0, 0, 0), 0.98, 10, 1);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	
	gScene->fetchResults(true);
	//ball->update(t);
	//manager->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		palo2->addForce({ 10,0,0 });
		//manager->addProjectile();
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}