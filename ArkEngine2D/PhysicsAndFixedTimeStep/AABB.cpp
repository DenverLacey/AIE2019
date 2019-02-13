#include "AABB.h"

#include <Gizmos.h>
#include <iostream>

AABB::AABB()
	: Rigidbody(BOX, glm::vec2(0, 0), glm::vec2(0, 0), 0, 1.f)
{
}


AABB::~AABB()
{
}

AABB::AABB(const glm::vec2& pos, const glm::vec2& velocity, float mass, const glm::vec2& extents)
	: Rigidbody(BOX, pos, velocity, 0, mass), m_extents(extents)
{
}


void AABB::makeGizmo() const
{
	aie::Gizmos::add2DAABB(m_position, m_extents, glm::vec4(0, 1, 0, 1));
}

void AABB::resetPosition()
{
	m_position = glm::vec2(0, 0);
}

const glm::vec2& AABB::getMin() const
{
	return m_position - m_extents;
}

const glm::vec2& AABB::getMax() const
{
	return m_position + m_extents;
}

void AABB::debug() const
{
	std::cout << "Shape ID: Box, " <<
		"HalfExtents: (" << m_extents.x << ", " << m_extents.y << ")\n";
}
