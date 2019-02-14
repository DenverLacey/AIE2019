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
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.01f);

	auto* sphere = new Sphere(glm::vec2(40, 10), glm::vec2(0, 0), 1.f, 3.f, glm::vec4(0, 1, 0, 1));
	auto* box = new AABB(glm::vec2(-40, 10), glm::vec2(0, 0), 1.f, glm::vec2(5, 5));
	auto* plane = new Plane(glm::normalize(glm::vec2(.1f, .5f)), -10);

	m_physicsScene->addActor(sphere);
	m_physicsScene->addActor(box);
	m_physicsScene->addActor(plane);

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