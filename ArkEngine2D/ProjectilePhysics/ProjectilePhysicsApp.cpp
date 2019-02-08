#include "ProjectilePhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <Gizmos.h>

#include <PhysicsScene.h>
#include <Sphere.h>

ProjectilePhysicsApp::ProjectilePhysicsApp() {

}

ProjectilePhysicsApp::~ProjectilePhysicsApp() {

}

bool ProjectilePhysicsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	setupConimuousDemo(glm::vec2(0, 0), 35.f, 3.f, 1.f);

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

void ProjectilePhysicsApp::setupConimuousDemo(const glm::vec2& startPos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.f;
	int segments = 12;
	glm::vec4 colour(1, 1, 0, 1);

	while (t <= 5) {
		// calculate x, y position at time t
		float x, y;
		glm::vec2 u = glm::vec2(cosf(inclination), sinf(inclination)) * speed;

		x = startPos.x + u.x * t;
		y = startPos.y + u.y + (gravity * (t * t)) / 2;

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		t += tStep;
	}
}
