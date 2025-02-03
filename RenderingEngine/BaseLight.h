#pragma once

#include <glm/glm.hpp>

namespace RenderingEngine 
{
class BaseLight {
public:
	virtual const glm::vec3 &color() = 0;
	virtual float intensity() = 0;
};
}
