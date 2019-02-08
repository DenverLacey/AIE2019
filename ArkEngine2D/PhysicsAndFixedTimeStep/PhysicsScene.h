#pragma once
#include <glm/ext.hpp>
#include <vector>

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

public:
	void addActor(PhysicsObject* actor);
	bool removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();

	void setGravity(const glm::vec2& gravity);
	glm::vec2 getGravity() const;

	void setTimeStep(const float timeStep);
	float getTimeStep() const;

	void debugScene() const;

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

