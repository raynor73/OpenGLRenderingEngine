#pragma once

#include <RenderingEngine/Camera.h>
#include <glm/ext/quaternion_float.hpp>
#include <vector>
#include <string>

namespace Research
{
	class PerspectiveCamera : public RenderingEngine::Camera {

		float m_zNear;
		float m_zFar;
		float m_fov;
		glm::vec4 m_clearColor;

		glm::ivec2 m_viewportLowerLeftCorner;
		glm::uvec2 m_viewportSize;

		glm::ivec2 m_scissorLowerLeftCorner;
		glm::uvec2 m_scissorSize;

		glm::vec3 m_position;
		glm::quat m_rotation;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		std::vector<std::string> m_layers;

		bool m_shouldClearDepth;
		bool m_shouldClearColor;

		void calculateProjectionMatrix();
		void calculateViewMatrix();

	public:
		PerspectiveCamera(
			float zNear,
			float zFar,
			float fov,
			const glm::uvec2 &viewportSize,
			const glm::uvec2 &scissorSize,
			const std::vector<std::string> &layers
		);

		void setPosition(const glm::vec3 &position);
		void setRotation(const glm::quat &rotation);

		void setViewportSize(const glm::uvec2 &size);

		void setScissorSize(const glm::uvec2 &size) { m_scissorSize = size; }

		float zNear() override { return m_zNear; }
		float zFar() override { return m_zFar; }
		const glm::vec4 &clearColor() override { return m_clearColor; }
		const glm::mat4 &viewMatrix() override { return m_viewMatrix; }
		const glm::mat4 &projectionMatrix() override { return m_projectionMatrix; }

		const glm::ivec2 &viewportLowerLeftCorner() { return m_viewportLowerLeftCorner; }
		const glm::uvec2 &viewportSize() { return m_viewportSize; }

		const glm::ivec2 &scissortLowerLeftCorner() { return m_scissorLowerLeftCorner; }
		const glm::uvec2 &scissorSize() { return m_scissorSize; }

		const std::vector<std::string> &layers() override { return m_layers; }

		bool shouldClearDepth() override { return m_shouldClearDepth; }
		void setShouldClearDepth(bool shouldClearDepth) override { m_shouldClearDepth = shouldClearDepth; }

		bool shouldClearColor() override { return m_shouldClearColor; }
		void setShouldClearColor(bool shouldClearColor) override { m_shouldClearColor = shouldClearColor; }
	};
}