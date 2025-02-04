#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace RenderingEngine {
	class Camera {
	public:
		virtual float zNear() = 0;
		virtual float zFar() = 0;
		virtual const glm::vec4& clearColor() = 0;
		virtual const glm::mat4& viewMatrix() = 0;
		virtual const glm::mat4& projectionMatrix() = 0;

		virtual const glm::ivec2 &viewportLowerLeftCorner() = 0;
		virtual const glm::uvec2 &viewportSize() = 0;

		virtual const glm::ivec2 &scissortLowerLeftCorner() = 0;
		virtual const glm::uvec2 &scissorSize() = 0;

		virtual const std::vector<std::string> &layers() = 0;

		/*bool shouldClearDepth() const { return m_shouldClearDepth; }
		void setShouldClearDepth(bool shouldClearDepth) { m_shouldClearDepth = shouldClearDepth; }
		bool shouldClearColor() const { return m_shouldClearColor; }
		void setShouldClearColor(bool shouldClearColor) { m_shouldClearColor = shouldClearColor; }*/
	};
}
