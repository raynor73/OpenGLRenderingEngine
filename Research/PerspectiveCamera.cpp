#include "PerspectiveCamera.h"
#include "Constants.h"

using namespace Research;

PerspectiveCamera::PerspectiveCamera(
	float zNear,
	float zFar,
	float fov,
	const glm::uvec2 &viewportSize,
	const glm::uvec2 &scissorSize,
	const std::vector<std::string> &layers
) : m_zNear(zNear),
	m_zFar(zFar),
	m_fov(fov),
	m_clearColor(0),
	m_viewportLowerLeftCorner(0),
	m_viewportSize(viewportSize),
	m_scissorLowerLeftCorner(0),
	m_scissorSize(scissorSize),
	m_position(0),
	m_rotation(glm::identity<glm::quat>()),
	m_layers(layers),
	m_shouldClearDepth(true),
	m_shouldClearColor(true)
{
	calculateViewMatrix();
	calculateProjectionMatrix();
}

void PerspectiveCamera::calculateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(
		m_fov,
		float(m_viewportSize.x) / m_viewportSize.y,
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

void PerspectiveCamera::setViewportSize(const glm::uvec2 &size) {
	if (m_viewportSize != size) {
		m_viewportSize = size;
		calculateProjectionMatrix();
	}
}
