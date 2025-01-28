#pragma once

#include <vector>
#include <cstdint>
#include "Vertex.h"

namespace RenderingEngine {
	class Mesh {
	public:
		virtual size_t numberOfVertices() = 0;
		virtual Vertex &vertexAt(size_t) = 0;
		virtual std::vector<uint16_t> indices() = 0;
	};
}
