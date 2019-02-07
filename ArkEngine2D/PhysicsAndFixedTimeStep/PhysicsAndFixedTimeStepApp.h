#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "PhysicsScene.h"

class PhysicsAndFixedTimeStepApp : public aie::Application {
public:

	PhysicsAndFixedTimeStepApp();
	virtual ~PhysicsAndFixedTimeStepApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;
};