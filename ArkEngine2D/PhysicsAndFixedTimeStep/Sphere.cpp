#include "Sphere.h"

#include <iostream>
#include <Gizmos.h>

Sphere::Sphere(const glm::vec2 & position, const glm::vec2 & velocity, float mass, float radius, const glm::vec4 & colour)
	: Rigidbody(SPHERE, position, velocity, 0, mass), m_radius(radius), m_colour(colour)
{
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo() const {
	aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_colour);
}

bool Sphere::checkCollision(PhysicsObject* pOther) const {
	
	Sphere* other = dynamic_cast<Sphere*>(pOther);

	if (other != nullptr) {
		float combinedRadius = m_radius + other->m_radius;
		float distance = glm::distance(m_position, other->m_position);
		return distance <= combinedRadius;
	}
	return false;
}

float Sphere::getRadius() const {
	return m_radius;
}

glm::vec4 Sphere::getColour() const {
	return m_colour;
}

void Sphere::debug() const {
	std::cout << "Shape ID: Sphere, Rdaius: " << m_radius << "\n";
	std::cout << m_mass;
}
