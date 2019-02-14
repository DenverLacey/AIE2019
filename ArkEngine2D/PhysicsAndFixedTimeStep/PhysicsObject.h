#pragma once
#include <glm\ext.hpp>

const enum ShapeType {
	PLANE = 0,
	SPHERE,
	BOX,
	
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {};

public:
	~PhysicsObject() {}
	virtual void fixedUpdate(const glm::vec2& gravity, float timeStep) = 0;
	virtual void debug() const = 0;
	virtual void makeGizmo() const = 0;
	virtual void resetPosition() {}

	ShapeType getShapeID() const { return m_shapeID;  }

protected:
	ShapeType m_shapeID;
};

