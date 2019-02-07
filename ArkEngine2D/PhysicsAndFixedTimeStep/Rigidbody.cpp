#include "Rigidbody.h"



Rigidbody::Rigidbody(ShapeType shapeID, const glm::vec2& position, const glm::vec2& velocity, float rotation, float mass)
	: PhysicsObject(shapeID), m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass)
{
}

Rigidbody::~Rigidbody() {

}



void Rigidbody::fixedUpdate(const glm::vec2& gravity, float timeStep) {
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

void Rigidbody::applyForce(const glm::vec2& force) {
	m_velocity += force / m_mass;
}

void Rigidbody::applyForceToActor(Rigidbody* actor2, const glm::vec2& force) {
	actor2->applyForce(force);
	applyForce(-force);
}

glm::vec2 Rigidbody::getPosition() const {
	return m_position;
}

float Rigidbody::getRotation() const {
	return m_rotation;
}

glm::vec2 Rigidbody::getVelocity() const {
	return m_velocity;
}

float Rigidbody::getMass() const {
	return m_mass;
}

