#pragma once

#include <glm/glm.hpp>

namespace RenderingEngine {
	class Vertex {
	public:
        static constexpr int VERTEX_POSITION_COMPONENTS = 3;
        static constexpr int VERTEX_NORMAL_COMPONENTS = 3;
        static constexpr int VERTEX_UV_COMPONENTS = 2;
        static constexpr int VERTEX_COMPONENTS =
			VERTEX_POSITION_COMPONENTS +
            VERTEX_NORMAL_COMPONENTS +
            VERTEX_UV_COMPONENTS;

		virtual const glm::vec3 &position() =  0;
		virtual const glm::vec3 &normal() = 0;
		virtual const glm::vec2 &uv() = 0;
	};
}