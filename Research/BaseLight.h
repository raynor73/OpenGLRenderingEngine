#pragma once

#include <RenderingEngine/BaseLight.h>

namespace Research
{
class BaseLight : public RenderingEngine::BaseLight
{
	glm::vec3 m_color;
	float m_intensity;

public:
	BaseLight(const glm::vec3 &color, float intensity) : m_color(color), m_intensity(intensity) {}

	const glm::vec3 &color() override { return m_color; }
	float intensity() override { return m_intensity; }
};
}

