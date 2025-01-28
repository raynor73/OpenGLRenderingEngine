#pragma once

#include <RenderingEngine/Transformation.h>
#include <glm/ext/quaternion_float.hpp>

namespace Research
{
class Transformation : public RenderingEngine::Transformation {

	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;

public:
	Transformation() : m_position(0), m_rotation(glm::identity<glm::quat>()), m_scale(1) {}

	Transformation(
		const glm::vec3 &position,
		const glm::quat &rotation,
		const glm::vec3 &scale
	) : m_position(position), m_rotation(rotation), m_scale(scale) {}

	const glm::vec3 &position() { return m_position; }
	const glm::quat &rotation() { return m_rotation; }
	const glm::vec3 &scale() { return m_scale; }
};
}