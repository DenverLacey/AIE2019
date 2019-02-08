#pragma once
#include <glm\ext.hpp>

enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {};

public:
	virtual void fixedUpdate(const glm::vec2& gravity, float timeStep) = 0;
	virtual void debug() const = 0;
	virtual void makeGizmo() const = 0;
	virtual void resetPosition() {}

protected:
	ShapeType m_shapeID;
};

