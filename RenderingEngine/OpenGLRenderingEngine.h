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
#include "OpenGLShadersRepository.h"
#include "OpenGLShaderSourcePreprocessor.h"
#include <variant>
#include "DirectionalLight.h"
#include "PointLight.h"

namespace RenderingEngine {
	using Light = std::variant<std::shared_ptr<DirectionalLight>, std::shared_ptr<PointLight>>;

	class OpenGLRenderingEngine {
		std::shared_ptr<OpenGLErrorDetector> m_openGLErrorDetector;
		std::shared_ptr<OpenGLShadersRepository> m_shaderRepository;
		std::shared_ptr<OpenGLShaderSourcePreprocessor> m_shaderSourcePreprocessor;
		std::map<uint32_t, std::shared_ptr<RenderableMeshInternal>> m_renderableMeshes;

		static const std::string AMBIENT_VERTEX_SHADER_NAME;
		static const std::string AMBIENT_FRAGMENT_SHADER_NAME;
		static const std::string AMBIENT_SHADER_PROGRAM_NAME;

		static const std::string DIRECTIONAL_LIGHT_VERTEX_SHADER_NAME;
		static const std::string DIRECTIONAL_LIGHT_FRAGMENT_SHADER_NAME;
		static const std::string DIRECTIONAL_LIGHT_SHADER_PROGRAM_NAME;

		static const GLuint POSITION_ATTRIBUTE_LOCATION;
		static const GLuint NORMAL_ATTRIBUTE_LOCATION;

		void initShader(
			const std::string &vertexShaderName,
			const std::string &vertexShaderPath,
			const std::string &fragmentShaderName,
			const std::string &fragmentShaderPath,
			const std::string &shaderProgramName
		);

		void renderMesh(
			Camera &camera, 
			BaseLight &ambient,
			const glm::mat4 &vpMatrix, 
			std::shared_ptr<OpenGLShaderProgramContainer> shader, 
			std::shared_ptr<RenderableMeshInternal> mesh
		);

	public:
		OpenGLRenderingEngine(
			std::shared_ptr<OpenGLErrorDetector> openGLErrorDetector,
			std::shared_ptr<OpenGLShadersRepository> shaderRepository,
			std::shared_ptr<OpenGLShaderSourcePreprocessor> openGLShaderSourcePreprocessor
		);

		std::shared_ptr<RenderableMesh> createRenderableMesh(
			Mesh &mesh,
			std::shared_ptr<Transformation> transformation,
			std::shared_ptr<Material> material
		);

		void freeRenderableMesh(uint32_t id);

		void render(
			Camera &camera,
			BaseLight &ambient,
			const std::vector<Light>
		);

		static const std::string LOG_TAG;
	};
}
