#pragma once

#include <glm/glm.hpp>
#include "BaseLight.h"

namespace RenderingEngine
{
class DirectionalLight : public BaseLight {
public:
	virtual const glm::vec3 &direction() = 0;
};
}
