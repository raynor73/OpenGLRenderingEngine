#pragma once

#include "RenderableMesh.h"
#include <GL/glew.h>

namespace RenderingEngine {
class RenderableMeshInternal : public RenderableMesh {

	GLuint m_buffer;
	bool m_isValid;

public:
	RenderableMeshInternal(GLuint buffer) : m_buffer(buffer), m_isValid(true) {}

	GLuint buffer() const { return m_buffer; }
	bool isValid() const override { return m_isValid; }
	void setValid(bool isValid) { m_isValid = isValid; }
};
}
