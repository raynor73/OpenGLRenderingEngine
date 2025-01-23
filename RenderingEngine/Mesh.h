#pragma once

#include <vector>
#include <cstdint>
#include "Vertex.h"

namespace RenderingEngine {
	class Mesh {
	public:
		virtual const std::vector<const Vertex> vertices() = 0;
		virtual const std::vector<uint16_t> indices() = 0;
	};
}
