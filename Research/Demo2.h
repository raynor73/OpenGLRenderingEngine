#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <RenderingEngine/OpenGLErrorDetector.h>
#include <memory>
#include <PlatformDependent/Windows/WindowsReadOnlyFs.h>
#include <RenderingEngine/OpenGLShaderSourceLoader.h>
#include <RenderingEngine/OpenGLShaderSourcePreprocessor.h>
#include <RenderingEngine/OpenGLShadersRepository.h>
#include "MeshLoader.h"
#include "Material.h"
#include <vector>
#include <RenderingEngine/OpenGLRenderingEngine.h>
#include "Transformation.h"
#include "PerspectiveCamera.h"

namespace Research
{
class Demo2 {

    GLFWwindow *m_window;

    std::shared_ptr<RenderingEngine::OpenGLErrorDetector> m_openGLErrorDetector;
    std::shared_ptr<PlatformDependent::Windows::WindowsReadOnlyFs> m_readOnlyFs;
    std::shared_ptr<RenderingEngine::OpenGLShaderSourceLoader> m_shaderSourceLoader;
    std::shared_ptr<RenderingEngine::OpenGLShaderSourcePreprocessor> m_shaderSourcePreprocessor;
    std::shared_ptr<RenderingEngine::OpenGLShadersRepository> m_shaderRepository;
    std::shared_ptr<MeshLoader> m_meshLoader;

    std::shared_ptr<RenderingEngine::OpenGLRenderingEngine> m_openGLRenderingEngine;

    std::shared_ptr<Mesh> m_sphereMesh;
    std::shared_ptr<Transformation> m_transformation;
    std::shared_ptr<Material> m_material;
    std::shared_ptr<PerspectiveCamera> m_camera;
    RenderingEngine::Light m_ambient;
    std::vector<RenderingEngine::Light> m_lights;
    float m_yAngle;
    float m_xAngle;
    float m_zAngle;
    bool m_isWireframe;
    bool m_isUnlit;
    bool m_isDoubleSided;
    bool m_isTranslucent;

    void createPlane();
    void createSphere();

public:
    Demo2(GLFWwindow *window);

	void update();
};
}