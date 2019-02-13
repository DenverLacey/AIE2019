#include "PhysicsScene.h"

#include "Rigidbody.h"
#include <iostream>
#include <algorithm>
#include <list>

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

	// static std::list<PhysicsObject*> dirty;

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
		// dirty.clear();
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
				// did collision occur?
				(*collisionFnPtr)(a, b);
			}
		}
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* a, PhysicsObject* b)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* a, PhysicsObject* b)
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
			// add resolution later
			sphere->applyForce(-sphere->getVelocity() * sphere->getMass());
			return true;
		}
	}
	return false;
}

bool PhysicsScene::plane2Box(PhysicsObject* a, PhysicsObject* b)
{
	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* a, PhysicsObject* b)
{
	return plane2Sphere(b, a);
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* a, PhysicsObject* b)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(a);
	Sphere* sphere2 = dynamic_cast<Sphere*>(b);

	if (sphere1 != nullptr && sphere2 != nullptr) {
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		float combinedRadius = sphere1->getRadius() + sphere2->getRadius();

		if (distance <= combinedRadius) {
			// adding collision resolution later
			sphere1->applyForce(-sphere1->getVelocity());
			sphere2->applyForce(-sphere2->getVelocity());

			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject* a, PhysicsObject* b)
{
	return false;
}

bool PhysicsScene::box2Plane(PhysicsObject* a, PhysicsObject* b)
{
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject* a, PhysicsObject* b)
{
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject* a, PhysicsObject* b)
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
			box1->applyForce(-box1->getVelocity() * box1->getMass());
			box2->applyForce(-box2->getVelocity() * box2->getMass());
			return true;
		}
	}
	return false;
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
