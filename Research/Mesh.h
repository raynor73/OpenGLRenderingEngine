#pragma once

#include <RenderingEngine/Mesh.h>
#include "Vertex.h"

namespace Research
{
class Mesh : public RenderingEngine::Mesh
{
	std::vector<Vertex> m_vertices;
	std::vector<uint16_t> m_indices;

public:
	Mesh() = default;

	Mesh(
		const std::vector<Vertex> &vertices, 
		const std::vector<uint16_t> &indices
	) : m_vertices(vertices), m_indices(indices) {}

	virtual size_t numberOfVertices() override { return m_vertices.size(); }
	virtual RenderingEngine::Vertex &vertexAt(size_t index) { return m_vertices.at(index); }
	virtual std::vector<uint16_t> indices() { return m_indices; }
};
}

