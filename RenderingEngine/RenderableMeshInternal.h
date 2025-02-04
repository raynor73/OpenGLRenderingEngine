#pragma once

#include "RenderableMesh.h"
#include <GL/glew.h>
#include "IboInfo.h"

namespace RenderingEngine {
class RenderableMeshInternal : public RenderableMesh {

	GLuint m_vao;
	GLuint m_vbo;
	IboInfo m_iboInfo;

	bool m_isValid;

public:
	RenderableMeshInternal(
		std::shared_ptr<Transformation> transformation,
		std::shared_ptr<Material> material,
		const std::vector<std::string> &layers,
		GLuint vao, 
		GLuint vbo, 
		const IboInfo &iboInfo
	) : RenderableMesh(transformation, material, layers),
		m_vao(vao),
		m_vbo(vbo),
		m_iboInfo(iboInfo),
		m_isValid(true)
	{}

	GLuint vbo() const { return m_vbo; }
	const IboInfo &iboInfo() const { return m_iboInfo; }
	GLuint vao() const { return m_vao; }
	bool isValid() const override { return m_isValid; }
	void setValid(bool isValid) { m_isValid = isValid; }
};
}
