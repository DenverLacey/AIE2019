#pragma once
#include "Rigidbody.h"

class AABB : public Rigidbody
{
public:
	AABB();
	~AABB();

	AABB(const glm::vec2& pos, const glm::vec2& velocity, float mass, const glm::vec2& extents);

public:
	void makeGizmo() const override;
	void resetPosition() override;

	bool checkCollision(PhysicsObject* pOther) const override { return false; }

	const glm::vec2& getMin() const;
	const glm::vec2& getMax() const;

	void debug() const override;

protected:
	glm::vec2 m_extents;
};

