#include "ProjectilePhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <Gizmos.h>

#include <PhysicsScene.h>
#include <Sphere.h>

#include "Constants.h"

ProjectilePhysicsApp::ProjectilePhysicsApp() {

}

ProjectilePhysicsApp::~ProjectilePhysicsApp() {

}



bool ProjectilePhysicsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(.5f);

	glm::vec2 startPos(-40, 0);
	float incline = TAU / 8;
	float speed = 35.f;

	glm::vec2 velocity = glm::vec2(cosf(incline), sinf(incline)) * speed;

	auto* sphere = new Sphere(startPos, velocity, 1, 1.f, glm::vec4(1, 0, 0, 1));
	m_physicsScene->addActor(sphere);

	setupContinuousDemo(startPos, incline, speed, m_physicsScene->getGravity().y);

	return true;
}

void ProjectilePhysicsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;

	aie::Gizmos::destroy();

	delete m_physicsScene;
}

void ProjectilePhysicsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// update physics scene
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ProjectilePhysicsApp::draw() {

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

void ProjectilePhysicsApp::setupContinuousDemo(const glm::vec2& startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tStep = m_physicsScene->getTimeStep();
	float radius = 1.f;
	int segments = 12;
	glm::vec4 colour(1, 1, 0, 1);
	glm::vec2 u = glm::vec2(cosf(inclination), sinf(inclination)) * speed;
	
	while (t <= 5) {
		// calculate x, y position at time t
		float x, y;

		// x = x0 + u.x * t
		x = startPos.x + u.x * t;

		// y = y0 + u.y * t + 1/2gt^2
		y = startPos.y + u.y * t + (gravity * (t * t)) / 2;

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		t += tStep;
	}
}
