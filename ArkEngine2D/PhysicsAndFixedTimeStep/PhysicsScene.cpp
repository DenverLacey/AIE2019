#include "PhysicsScene.h"

#include "Rigidbody.h"
#include <iostream>
#include <algorithm>
#include <list>

PhysicsScene::PhysicsScene() 
	: m_timeStep(0.01f), m_gravity(glm::vec2(0,0))
{
}

PhysicsScene::~PhysicsScene() {

	for (PhysicsObject* pActor : m_actors) {
		if (pActor != nullptr) {
			delete pActor;
			pActor = nullptr;
		}
	}
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

	static std::list<PhysicsObject*> dirty;

	// update physics at fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep) {
		for (PhysicsObject* pActor : m_actors) {
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		// check for collisions (ideally you'd want some sort of scene managment in place)
		for (PhysicsObject* pActor : m_actors) {
			for (PhysicsObject* pOther : m_actors) {
				if (pActor == pOther) {
					continue;
				}
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end()) {
					continue;
				}

				Rigidbody* pRigid = reinterpret_cast<Rigidbody*>(pActor);
				if (pRigid->checkCollision(pOther) == true) {
					pRigid->applyForceToActor(
					reinterpret_cast<Rigidbody*>(pOther), pRigid->getVelocity() * pRigid->getMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}
		dirty.clear();
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

void PhysicsScene::debugScene() const
{
	int count = 0;
	for (PhysicsObject* pActor : m_actors) {
		std::cout << count << ": ";
		pActor->debug();
		count++;
	}
}
