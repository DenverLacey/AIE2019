#include "CollisionResolutionApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <Gizmos.h>
#include <PhysicsScene.h>
#include <Sphere.h>
#include <AABB.h>
#include <Plane.h>

CollisionResolutionApp::CollisionResolutionApp() {

}

CollisionResolutionApp::~CollisionResolutionApp() {

}

bool CollisionResolutionApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -30));
	m_physicsScene->setTimeStep(.01f);

	//auto* b1 = new Sphere(glm::vec2(-40, -20), glm::vec2(10, 5), 1.f, 3.f, glm::vec4(0, 1, 0, 1));
	//auto* b2 = new Sphere(glm::vec2(40, 20), glm::vec2(-10, -5), 1.f, 3.f, glm::vec4(1, 0, 0, 1));
	//auto* a1 = new AABB(glm::vec2(-40, 20), glm::vec2(10, -5), 1.f, glm::vec2(3, 3));
	//auto* a2 = new AABB(glm::vec2(40, -20), glm::vec2(-10, 5), 1.f, glm::vec2(3, 3));
	//auto* a3 = new AABB(glm::vec2(-40, 30), glm::vec2(0, 0), 1.f, glm::vec2(3, 3));

	//m_physicsScene->addActor(b1);
	//m_physicsScene->addActor(b2);
	//m_physicsScene->addActor(a2);
	//m_physicsScene->addActor(a1);
	//m_physicsScene->addActor(a3);

	//auto* aC = new AABB(glm::vec2(0, 0), glm::vec2(0, 0), 5.f, glm::vec2(10, 10));
	//auto* aT = new AABB(glm::vec2(20, 30), glm::vec2(-10, -10), 1.f, glm::vec2(5, 5));
	//auto* aB = new AABB(glm::vec2(-20, -30), glm::vec2(10, 10), 1.f, glm::vec2(5, 5));
	//auto* aL = new AABB(glm::vec2(-30, 20), glm::vec2(10, -10), 1.f, glm::vec2(5, 5));
	//auto* aR = new AABB(glm::vec2(30, -20), glm::vec2(-10, 10), 1.f, glm::vec2(5, 5));

	//m_physicsScene->addActor(aC);
	//m_physicsScene->addActor(aT);
	//m_physicsScene->addActor(aB);
	//m_physicsScene->addActor(aL);
	//m_physicsScene->addActor(aR);

	auto* plane = new Plane(glm::normalize(glm::vec2(-.25f, .5f)), -50);
	// auto* plane1 = new Plane()
	auto* sphere = new Sphere(glm::vec2(40, 20), glm::vec2(0, 0.f), 1.f, 3.f, glm::vec4(0, 1, 0, 1));

	m_physicsScene->addActor(plane);
	m_physicsScene->addActor(sphere);

	return true;
}

void CollisionResolutionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	aie::Gizmos::destroy();
	delete m_physicsScene;
}

void CollisionResolutionApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CollisionResolutionApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1, 1));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}