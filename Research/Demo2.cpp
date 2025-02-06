#include "Demo2.h"
#include <imgui.h>
#include "BaseLight.h"
#include <vector>
#include <memory>
#include "PerspectiveCamera.h"
#include "DirectionalLight.h"

using namespace Research;
using namespace PlatformDependent::Windows;
using namespace std;

#define DEFAULT_LAYER_NAME "default"

Demo2::Demo2(GLFWwindow *window) :
    m_window(window),
	m_openGLErrorDetector(make_shared<RenderingEngine::OpenGLErrorDetector>()),
	m_readOnlyFs(make_shared<WindowsReadOnlyFs>()),
	m_shaderSourceLoader(make_shared<RenderingEngine::OpenGLShaderSourceLoader>(m_readOnlyFs)),
	m_shaderSourcePreprocessor(make_shared<RenderingEngine::OpenGLShaderSourcePreprocessor>(m_shaderSourceLoader)),
	m_shaderRepository(make_shared<RenderingEngine::OpenGLShadersRepository>(m_openGLErrorDetector)),
	m_meshLoader(make_shared<MeshLoader>(m_readOnlyFs)),
	m_openGLRenderingEngine(make_shared<RenderingEngine::OpenGLRenderingEngine>(m_openGLErrorDetector, m_shaderRepository, m_shaderSourcePreprocessor)),
	m_yAngle(0),
	m_xAngle(0),
	m_zAngle(0),
    m_isWireframe(false),
    m_isUnlit(false),
    m_isDoubleSided(false)
{
    createSphere();
    createPlane();

    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
    m_camera = make_shared<Research::PerspectiveCamera>(
        0.1f,
        1000,
        90,
        glm::uvec2{ windowWidth, windowHeight },
        glm::uvec2{ windowWidth, windowHeight },
        vector<string>{ DEFAULT_LAYER_NAME }
    );

    m_ambient = make_shared<Research::BaseLight>(glm::vec3(1), 0.1);
    
    auto directionalLight = make_shared<Research::DirectionalLight>(glm::vec3(0, 1, 0), 1, glm::vec3(-1, 0, 0));
    m_lights.push_back(directionalLight);
}

void Demo2::update() {
    ImGuiIO &io = ImGui::GetIO();

    ImGui::Begin("Hello, world!");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::SliderAngle("Y angle", &m_yAngle);
    ImGui::SliderAngle("X angle", &m_xAngle);
    ImGui::SliderAngle("Z angle", &m_zAngle);
    ImGui::Checkbox("Wireframe", &m_isWireframe);
    ImGui::Checkbox("Unlit", &m_isUnlit);
    ImGui::Checkbox("Double-sided", &m_isDoubleSided);
    ImGui::Checkbox("Translucent", &m_isTranslucent);
    ImGui::End();

    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

    m_camera->setViewportSize(glm::uvec2(windowWidth, windowHeight));

    m_transformation->setRotation(glm::quat(glm::vec3(m_xAngle, m_yAngle, m_zAngle)));
    m_material->setWireframe(m_isWireframe);
    m_material->setUnlit(m_isUnlit);
    m_material->setDoubleSided(m_isDoubleSided);
    m_material->setTranslucent(m_isTranslucent);

    m_openGLRenderingEngine->render(*m_camera, m_ambient, m_lights);
}

void Demo2::createPlane() {

}

void Demo2::createSphere() {
    m_sphereMesh = make_shared<Mesh>();
    *m_sphereMesh = m_meshLoader->loadMesh("./Meshes/Sphere.obj");

    m_transformation = make_shared<Research::Transformation>();
    m_transformation->setPosition(glm::vec3(0, 0, -2));

    m_material = make_shared<Research::Material>(glm::vec4(1), false, false, false, false);

    m_openGLRenderingEngine->createRenderableMesh(*m_sphereMesh, m_transformation, m_material, { DEFAULT_LAYER_NAME });
}