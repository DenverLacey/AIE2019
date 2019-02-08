#pragma once
#include "PhysicsObject.h"

class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType shapeID, const glm::vec2& position, const glm::vec2& velocity, float rotation, float mass);
	~Rigidbody();

public:
	void fixedUpdate(const glm::vec2& gravity, float timeStep) override;
	
	void applyForce(const glm::vec2& force);
	void applyForceToActor(Rigidbody* actor2, const glm::vec2& force);

	virtual bool checkCollision(PhysicsObject* pOther) const = 0;

	glm::vec2 getPosition() const;
	float getRotation() const;
	glm::vec2 getVelocity() const;
	float getMass() const;

	void setMass(float mass);

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;  // 2D so we only need a single float to represent our rotation
};

