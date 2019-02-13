#include "CollisionDetectionApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <Gizmos.h>

#include <PhysicsScene.h>
#include <Sphere.h>
#include <Plane.h>
#include <AABB.h>

CollisionDetectionApp::CollisionDetectionApp() {

}

CollisionDetectionApp::~CollisionDetectionApp() {

}

bool CollisionDetectionApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	// initialise new physics scene
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimeStep(0.01f);

	//auto* sphere = new Sphere(glm::vec2(-40, 4), glm::vec2(20, 20), 1.f, 3.f, glm::vec4(0, 1, 0, 1));
	//auto* plane = new Plane(glm::vec2(-0.5f, 0.5f), -4);
	//auto* box = new AABB(glm::vec2(-40, 40), glm::vec2(0, 0), 1.f, glm::vec2(5, 5));

	//m_physicsScene->addActor(sphere);
	//m_physicsScene->addActor(plane);
	//m_physicsScene->addActor(box);

	auto* box1 = new AABB(glm::vec2(-15, 0), glm::vec2(10, 0), 1.f, glm::vec2(5, 5));
	auto* box2 = new AABB(glm::vec2(15, 0), glm::vec2(-10, 0), 1.f, glm::vec2(5, 5));

	auto* box3 = new AABB(glm::vec2(-30, 0), glm::vec2(10, 0), 1.f, glm::vec2(5, 5));
	auto* box4 = new AABB(glm::vec2(30, 0), glm::vec2(-10, 0), 1.f, glm::vec2(5, 5));

	auto* box5 = new AABB(glm::vec2(-45, 0), glm::vec2(10, 0), 1.f, glm::vec2(5, 5));
	auto* box6 = new AABB(glm::vec2(45, 0), glm::vec2(-10, 0), 1.f, glm::vec2(5, 5));

	m_physicsScene->addActor(box1);
	m_physicsScene->addActor(box2);
	m_physicsScene->addActor(box3);
	m_physicsScene->addActor(box4);
	m_physicsScene->addActor(box5);
	m_physicsScene->addActor(box6);

	return true;
}

void CollisionDetectionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	aie::Gizmos::destroy();
	delete m_physicsScene;
}

void CollisionDetectionApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CollisionDetectionApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}