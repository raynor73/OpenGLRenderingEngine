#pragma once

#include <glm/glm.hpp>

namespace RenderingEngine {
	class Transformation {
	public:
		virtual const glm::vec3& position() const = 0;
		virtual const glm::quat& rotation() const = 0;
		virtual const glm::vec3& scale() const = 0;
	};
}
