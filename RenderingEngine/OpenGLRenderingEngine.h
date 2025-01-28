#pragma once

#include "RenderableMeshInternal.h"
#include "Mesh.h"
#include "Transformation.h"
#include "Material.h"
#include "Camera.h"
#include "OpenGLErrorDetector.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

namespace RenderingEngine {
	class OpenGLRenderingEngine {
		std::shared_ptr<OpenGLErrorDetector> m_openGLErrorDetector;
		std::map<uint32_t, std::shared_ptr<RenderableMeshInternal>> m_renderableMeshes;

	public:
		OpenGLRenderingEngine(std::shared_ptr<OpenGLErrorDetector> openGLErrorDetector) : m_openGLErrorDetector(openGLErrorDetector) {}

		std::shared_ptr<RenderableMesh> createRenderableMesh(
			Mesh &mesh,
			std::shared_ptr<Transformation> transformation,
			std::shared_ptr<Material> material
		);

		void freeRenderableMesh(uint32_t id);

		void render(Camera &camera);

		static std::string LOG_TAG;
	};
}
