#pragma once

#include <RenderingEngine/Vertex.h>
#include <vector>

namespace Research
{
class Vertex : public RenderingEngine::Vertex
{
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_uv;

public:
	Vertex(
		const glm::vec3 &position,
		const glm::vec3 &normal, 
		const glm::vec2 &uv
	) : m_position(position), m_normal(normal), m_uv(uv) {}

	virtual const glm::vec3 &position() override { return m_position; };
	virtual const glm::vec3 &normal() override { return m_normal; }
	virtual const glm::vec2 &uv() override { return m_uv; }
};
}

