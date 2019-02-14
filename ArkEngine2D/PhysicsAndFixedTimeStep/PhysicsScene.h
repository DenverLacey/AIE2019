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

	static glm::vec2 plane2Plane(PhysicsObject* a, PhysicsObject* b);
	static glm::vec2 plane2Sphere(PhysicsObject* a, PhysicsObject* b);
	static glm::vec2 plane2Box(PhysicsObject* a, PhysicsObject* b);
		  
	static glm::vec2 sphere2Plane(PhysicsObject* a, PhysicsObject* b);
	static glm::vec2 sphere2Sphere(PhysicsObject* a, PhysicsObject* b);
	static glm::vec2 sphere2Box(PhysicsObject* a, PhysicsObject* b);
		  
	static glm::vec2 box2Plane(PhysicsObject* a, PhysicsObject* b);
	static glm::vec2 box2Sphere(PhysicsObject* a, PhysicsObject* b);
	static glm::vec2 box2Box(PhysicsObject* a, PhysicsObject* b);

	void setGravity(const glm::vec2& gravity);
	const glm::vec2& getGravity() const;

	void setTimeStep(const float timeStep);
	float getTimeStep() const;

	void debugScene() const;

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;


	typedef glm::vec2(*func)(PhysicsObject*, PhysicsObject*);
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

