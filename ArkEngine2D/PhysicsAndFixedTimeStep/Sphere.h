#pragma once
#include "Rigidbody.h"

class Sphere : public Rigidbody
{
public:
	Sphere(const glm::vec2& position, const glm::vec2& velocity, float mass, float radius, const glm::vec4& colour);
	~Sphere();

public:
	void makeGizmo() override;
	bool checkCollision(PhysicsObject* pOther) override;

	float getRadius() const;
	glm::vec4 getColour() const;

protected:
	float m_radius;
	glm::vec4 m_colour;
};

