#include "PhysicsScene.h"

#include "Rigidbody.h"
#include <iostream>
#include <algorithm>
#include <list>

#include <Gizmos.h>

#include "Plane.h"
#include "Sphere.h"
#include "AABB.h"

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

	// update physics at fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep) {
		for (PhysicsObject* pActor : m_actors) {
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		// check for collisions (ideally you'd want some sort of scene managment in place)
		checkCollision();
	}
}

void PhysicsScene::updateGizmos() {
	for (PhysicsObject* pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::checkCollision()
{
	int actorCount = m_actors.size();

	// need to check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			PhysicsObject* a = m_actors[outer];
			PhysicsObject* b = m_actors[inner];
			int aID = a->getShapeID();
			int bID = b->getShapeID();

			// using function pointers
			int funcIndex = (aID * SHAPE_COUNT) + bID;
			func collisionFnPtr = m_collisionFunctionPrts[funcIndex];

			if (collisionFnPtr != nullptr) {
				glm::vec2 collisionNormal = (*collisionFnPtr)(a, b);

				// if collision
				if (collisionNormal != glm::zero<glm::vec2>()) {
					Rigidbody* aRb = dynamic_cast<Rigidbody*>(a);
					Rigidbody* bRb = dynamic_cast<Rigidbody*>(b);

					if (aRb != nullptr && bRb != nullptr) {
						Rigidbody::resolveCollisionDxD(aRb, bRb, collisionNormal);
					}
					else if (aRb != nullptr && bRb == nullptr) {
						Rigidbody::resolveCollisionDxS(aRb, collisionNormal);
					}
					else {
						Rigidbody::resolveCollisionDxS(bRb, collisionNormal);
					}
				}
			}
		}
	}
}

glm::vec2 PhysicsScene::plane2Plane(PhysicsObject* a, PhysicsObject* b)
{
	return glm::zero<glm::vec2>();
}

glm::vec2 PhysicsScene::plane2Sphere(PhysicsObject* a, PhysicsObject* b)
{
	Plane* plane = dynamic_cast<Plane*>(a);
	Sphere* sphere = dynamic_cast<Sphere*>(b);

	if (plane != nullptr && sphere != nullptr) {
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(
			sphere->getPosition(),
			plane->getNormal()) - plane->getDistance();

		// if we are behind plane, flip normal
		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;

		if (intersection > 0) {
			return collisionNormal;
		}
	}
	return glm::zero<glm::vec2>();
}

glm::vec2 PhysicsScene::plane2Box(PhysicsObject* a, PhysicsObject* b)
{
	Plane* plane = dynamic_cast<Plane*>(a);
	AABB* box = dynamic_cast<AABB*>(b);

	if (plane != nullptr && box != nullptr) {
		bool sides[2]{ false, false };
		glm::vec2 corners[4]{
			glm::vec2(box->getMin()),						// bottom left
			glm::vec2(box->getMin().x, box->getMax().y),	// top left
			glm::vec2(box->getMax()),						// top right
			glm::vec2(box->getMax().x, box->getMin().y)		// bottom right
		};

		for (unsigned int i = 0; i < 4; i++) {
			if (glm::dot(plane->getNormal(), corners[i]) - plane->getDistance() <= 0) {
				sides[0] = true;
			}
			else if (glm::dot(plane->getNormal(), corners[i]) - plane->getDistance() >= 0) {
				sides[1] = true;
			}
		}

		if (sides[0] && sides[1]) {
			return plane->getNormal();
		}
	}
	return glm::zero<glm::vec2>();
}

glm::vec2 PhysicsScene::sphere2Plane(PhysicsObject* a, PhysicsObject* b)
{
	return plane2Sphere(b, a);
}

glm::vec2 PhysicsScene::sphere2Sphere(PhysicsObject* a, PhysicsObject* b)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(a);
	Sphere* sphere2 = dynamic_cast<Sphere*>(b);

	if (sphere1 != nullptr && sphere2 != nullptr) {
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		float combinedRadius = sphere1->getRadius() + sphere2->getRadius();

		if (distance <= combinedRadius) {
			glm::vec2 normal = glm::normalize(sphere2->getPosition() - sphere1->getPosition());
			return normal;
		}
	}
	return glm::zero<glm::vec2>();
}

glm::vec2 PhysicsScene::sphere2Box(PhysicsObject* a, PhysicsObject* b)
{
	Sphere* sphere = dynamic_cast<Sphere*>(a);
	AABB* box = dynamic_cast<AABB*>(b);

	if (sphere != nullptr && box != nullptr) {
		glm::vec2 clampPoint = sphere->getPosition();
		clampPoint = glm::clamp(clampPoint, box->getMin(), box->getMax());

		float distanceToPoint = glm::distance(sphere->getPosition(), clampPoint);

		if (distanceToPoint <= sphere->getRadius()) {
			glm::vec2 normal = glm::normalize(clampPoint - sphere->getPosition());
			return normal;
		}
	}
	return glm::zero<glm::vec2>();
}

glm::vec2 PhysicsScene::box2Plane(PhysicsObject* a, PhysicsObject* b)
{
	return plane2Box(b, a);
}

glm::vec2 PhysicsScene::box2Sphere(PhysicsObject* a, PhysicsObject* b)
{
	return sphere2Box(b, a);
}

glm::vec2 PhysicsScene::box2Box(PhysicsObject* a, PhysicsObject* b)
{
	AABB* box1 = dynamic_cast<AABB*>(a);
	AABB* box2 = dynamic_cast<AABB*>(b);

	if (box1 != nullptr && box2 != nullptr) {
		glm::vec2 aMin = box1->getMin();
		glm::vec2 aMax = box1->getMax();
		glm::vec2 bMin = box2->getMin();
		glm::vec2 bMax = box2->getMax();

		// if collision
		if (aMin.x < bMax.x &&
			aMax.x > bMin.x &&
			aMin.y < bMax.y &&
			aMax.y > bMin.y) 
		{
			glm::vec2 roughNormal = glm::normalize(box2->getPosition() - box1->getPosition());

			if (abs(roughNormal.x) > abs(roughNormal.y)) { roughNormal.y = 0; }
			else { roughNormal.x = 0; }

			glm::vec2 normal = glm::normalize(roughNormal);
			return normal;
		}
	}
	return glm::zero<glm::vec2>();
}

void PhysicsScene::setGravity(const glm::vec2& gravity) {
	m_gravity = gravity;
}

const glm::vec2& PhysicsScene::getGravity() const {
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
