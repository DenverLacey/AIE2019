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

void Rigidbody::resolveCollisionDxD(Rigidbody* a, Rigidbody* b, const glm::vec2& normal)
{
	glm::vec2 relVelocity = b->getVelocity() - a->m_velocity;

	float elasticity = 1.f;
	float j = glm::dot(-(1 + elasticity) * (relVelocity), normal) /
		glm::dot(normal, normal * ((1 / a->m_mass) + (1 / b->getMass())));

	glm::vec2 force = normal * j;

	a->applyForceToActor(b, force);
}

void Rigidbody::resolveCollisionDxS(Rigidbody* rb, const glm::vec2& normal)
{
	glm::vec2 relVelocity = rb->getVelocity();

	float elasticity = 1.f;
	float j = glm::dot(-(1 + elasticity) * (relVelocity), normal) /
		glm::dot(normal, normal * ((1 / rb->getMass())));

	glm::vec2 force = normal * j;
	rb->applyForce(force);
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

void Rigidbody::setMass(float mass)
{
	m_mass = mass;
}

