#pragma once

#include <glm/glm.hpp>

namespace RenderingEngine {
	class Transformation {
	public:
		virtual const glm::vec3& position() = 0;
		virtual const glm::quat& rotation() = 0;
		virtual const glm::vec3& scale() = 0;
	};
}
