#if defined(_DEBUG) && defined(NDEBUG)
#pragma message("⚠️ ¡ALERTA! Ambas macros (_DEBUG y NDEBUG) están definidas a la vez.")
#elif defined(_DEBUG)
#pragma message("ℹ️ Solo _DEBUG está definida.")
#elif defined(NDEBUG)
#pragma message("ℹ️ Solo NDEBUG está definida.")
#else
#pragma message("⚠️ ¡ALERTA! Ninguna macro está definida.")
#endif


#include <ctype.h>

#include <PxPhysicsAPI.h>
#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include <foundation/PxSimpleTypes.h>
#include <PxPhysicsVersion.h> // <- Macros for PhysX version checking

#define PVD_HOST "127.0.0.1" // IP localhost for PVD connection


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

// Global variables for physics timing. We use a fixed timestep for physics simulation, and accumulate time to determine when to step the physics simulation.
double gPhysicsTimeAccumulator = 0.0;
const double gFixedTimestep = 1.0 / 60.0;

// Initialize physics engine (Updated for PhysX 5.0)
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	if (!gFoundation)
	{
		std::cerr << "PxCreateFoundation failed!" << std::endl;
		exit(1);
	}

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	
	if(transport){
		gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
	}
	

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	if (!gPhysics)
	{
		std::cerr << "PxCreatePhysics failed!" << std::endl;
		exit(1);
	}

	// Mandatory in PhysX 5.0 to initialize extensions 
	PxInitExtensions(*gPhysics, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);

	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	
	
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	/*
	if (gScene && gPvd->isConnected()) {
		PxScenePvdClient* pvdClient = gScene->getScenePvdClient();
		if (pvdClient) {
			pvdClient->setScenePvdFlag(PxScenePvdFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(PxScenePvdFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(PxScenePvdFlag::eTRANSMIT_SCENEQUERIES, true);
		}
	}
	*/
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in SECONDS (PhysX 5.0 uses seconds as time unit)

void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	
	if (!gScene) return;

	// Accumulate time and step the physics simulation in fixed timesteps
	gPhysicsTimeAccumulator += t;

	// Step the physics simulation in fixed timesteps
	// This loop allows for multiple physics steps if the accumulated time exceeds the fixed timestep
	while (gPhysicsTimeAccumulator >= gFixedTimestep)
	{
		// simulate() arranca la simulación de forma asíncrona en el hilo de físicas
		gScene->simulate(static_cast<PxReal>(gFixedTimestep));

		// fetchResults(true) bloquea el hilo de renderizado hasta que la física termine.
		// En prácticas avanzadas es vital para que el renderizado no lea datos corruptos.
		gScene->fetchResults(true);

		gPhysicsTimeAccumulator -= gFixedTimestep;
	}
}

// Function to clean data (for PhysX 5.0)
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	 
	// Clean scene and dispatcher first to avoid memory leaks
	if (gScene) {
		gScene->release();
		gScene = nullptr;
	}
	if (gDispatcher) {
		gDispatcher->release();
		gDispatcher = nullptr;
	}
	
	//Clean extensions before releasing physics
	PxCloseExtensions();
	
	// Clean material and physics
	if (gMaterial) {
		gMaterial->release();
		gMaterial = nullptr;
	}
	if (gPhysics) {
		gPhysics->release();
		gPhysics = nullptr;
	}

	// Clean PVD and transport
	if (gPvd) {
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();
		gPvd = nullptr;
		if (transport) {
			transport->release();
		}
	}

	// Clean foundation
	if (gFoundation) {
		gFoundation->release();
		gFoundation = nullptr;
	}
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