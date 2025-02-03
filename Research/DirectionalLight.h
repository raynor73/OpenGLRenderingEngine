#pragma once

#include <RenderingEngine/DirectionalLight.h>
#include "BaseLight.h"

namespace Research 
{
class DirectionalLight : public BaseLight, public RenderingEngine::DirectionalLight {

	glm::vec3 m_direction;

public:
	DirectionalLight(const glm::vec3 &color, float intensity, const glm::vec3 &direction) : Research::BaseLight(color, intensity), m_direction(direction) {}

	const glm::vec3 &direction() override { return m_direction; }
	const glm::vec3 &color() override { return Research::BaseLight::color(); }
	float intensity() override { return Research::BaseLight::intensity(); }
};
}
