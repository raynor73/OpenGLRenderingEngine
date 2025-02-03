#pragma once

#include <glm/glm.hpp>
#include "BaseLight.h"
#include "Attenuation.h"

namespace RenderingEngine
{
class PointLight : public BaseLight {
public:
	virtual Attenuation &attenuation() = 0;
	virtual const glm::vec3 &position() = 0;
};
}
