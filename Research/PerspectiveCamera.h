#pragma once

#include <RenderingEngine/Camera.h>
#include <glm/ext/quaternion_float.hpp>

namespace Research
{
	class PerspectiveCamera : public RenderingEngine::Camera {

		float m_zNear;
		float m_zFar;
		float m_fov;
		glm::vec4 m_clearColor;

		uint32_t m_viewportWidth;
		uint32_t m_viewportHeight;

		glm::vec3 m_position;
		glm::quat m_rotation;

		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		void calculateProjectionMatrix();
		void calculateViewMatrix();

	public:
		PerspectiveCamera(
			float zNear,
			float zFar,
			float fov,
			uint32_t viewportWidth,
			uint32_t viewportHeight
		);

		void setPosition(const glm::vec3 &position);
		void setRotation(const glm::quat &rotation);
		void setViewportSize(uint32_t width, uint32_t height);

		float zNear() override { return m_zNear; }
		float zFar() override { return m_zFar; }
		const glm::vec4 &clearColor() override { return m_clearColor; }
		const glm::mat4 &viewMatrix() override { return m_viewMatrix; }
		const glm::mat4 &projectionMatrix() override { return m_projectionMatrix; }
	};
}