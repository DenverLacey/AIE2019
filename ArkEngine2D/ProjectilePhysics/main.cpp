#include "ProjectilePhysicsApp.h"

#include <iostream>

int main() {
	
	// log memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// allocation
	auto app = new ProjectilePhysicsApp();

	// initialise and loop
	app->run("ARK: Projectile Physics", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}