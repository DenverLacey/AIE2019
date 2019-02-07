#include "Sphere.h"



Sphere::Sphere(const glm::vec2 & position, const glm::vec2 & velocity, float mass, float radius, const glm::vec4 & colour)
	: Rigidbody(SPHERE, position, velocity, 0, mass), m_radius(radius), m_colour(colour)
{
}

Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
}

bool Sphere::checkCollision(PhysicsObject * pOther)
{
	return false;
}

float Sphere::getRadius() const
{
	return m_radius;
}

glm::vec4 Sphere::getColour() const
{
	return m_colour;
}
