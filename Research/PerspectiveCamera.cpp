#include "PerspectiveCamera.h"
#include "Constants.h"

using namespace Research;

PerspectiveCamera::PerspectiveCamera(
	float zNear,
	float zFar,
	float fov,
	float viewportWidth,
	float viewportHeight
) : m_zNear(zNear),
	m_zFar(zFar),
	m_fov(fov),
	m_clearColor(0),
	m_viewportWidth(viewportWidth),
	m_viewportHeight(viewportHeight),
	m_position(0),
	m_rotation(glm::identity<glm::quat>())
{
	calculateViewMatrix();
	calculateProjectionMatrix();
}

void PerspectiveCamera::calculateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(
		m_fov,
		m_viewportWidth / m_viewportHeight,
		m_zNear,
		m_zFar
	);
}

void PerspectiveCamera::calculateViewMatrix() {
	glm::vec3 lookAtDirection;
	glm::vec3 up;

	lookAtDirection = Constants::DEFAULT_FORWARD_DIRECTION;
	lookAtDirection = m_rotation * lookAtDirection;

	up = Constants::CAMERA_UP_DIRECTION;
	up = m_rotation * up;

	m_viewMatrix = glm::lookAt(m_position, m_position + lookAtDirection, up);
}

void PerspectiveCamera::setPosition(const glm::vec3 &position) {
	m_position = position;
	calculateViewMatrix();
}

void PerspectiveCamera::setRotation(const glm::quat &rotation) {
	m_rotation = rotation;
	calculateViewMatrix();
}

void PerspectiveCamera::setViewportWidth(float width) {
	m_viewportWidth = width;
	calculateProjectionMatrix();
}

void PerspectiveCamera::setViewportHeight(float height) {
	m_viewportHeight = height;
	calculateProjectionMatrix();
}
