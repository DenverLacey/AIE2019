#include "PhysicsScene.h"

#include "PhysicsObject.h"
#include <algorithm>

PhysicsScene::PhysicsScene() {
	m_timeStep = 0.01f;
	m_gravity = glm::vec2(0, 0);
}

PhysicsScene::~PhysicsScene() {

}


void PhysicsScene::addActor(PhysicsObject* actor) {
	m_actors.push_back(actor);
}

bool PhysicsScene::removeActor(PhysicsObject* actor) {
	auto itr = std::find(m_actors.begin(), m_actors.end(), actor);
	if (*itr == actor) {
		m_actors.erase(itr);
		return true;
	}
	return false;
}

void PhysicsScene::update(float dt) {
	// update physics at fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep) {
		for (PhysicsObject* pActor : m_actors) {
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}
}

void PhysicsScene::updateGizmos() {
	for (PhysicsObject* pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::setGravity(const glm::vec2& gravity) {
	m_gravity = gravity;
}

glm::vec2 PhysicsScene::getGravity() const {
	return m_gravity;
}

void PhysicsScene::setTimeStep(const float timeStep) {
	m_timeStep = timeStep;
}

float PhysicsScene::getTimeStep() const {
	return m_timeStep;
}