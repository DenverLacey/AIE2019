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

	void checkCollision();

	static bool plane2Plane(PhysicsObject* a, PhysicsObject* b);
	static bool plane2Sphere(PhysicsObject* a, PhysicsObject* b);
	static bool plane2Box(PhysicsObject* a, PhysicsObject* b);
	
	static bool sphere2Plane(PhysicsObject* a, PhysicsObject* b);
	static bool sphere2Sphere(PhysicsObject* a, PhysicsObject* b);
	static bool sphere2Box(PhysicsObject* a, PhysicsObject* b);

	static bool box2Plane(PhysicsObject* a, PhysicsObject* b);
	static bool box2Sphere(PhysicsObject* a, PhysicsObject* b);
	static bool box2Box(PhysicsObject* a, PhysicsObject* b);

	void setGravity(const glm::vec2& gravity);
	glm::vec2 getGravity() const;

	void setTimeStep(const float timeStep);
	float getTimeStep() const;

	void debugScene() const;

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;


	typedef bool(*func)(PhysicsObject*, PhysicsObject*);
	func m_collisionFunctionPrts[9] {
		plane2Plane,
		plane2Sphere,
		plane2Box,

		sphere2Plane,
		sphere2Sphere,
		sphere2Box,

		box2Plane,
		box2Sphere,
		box2Box
	};
};

