#pragma once

#include <memory>
#include "OpenGLErrorDetector.h"
#include <unordered_map>
#include "OpenGLShaderProgramContainer.h"

namespace RenderingEngine
{
class OpenGLShadersRepository
{
    std::shared_ptr<OpenGLErrorDetector> m_openGLErrorDetector;

    std::unordered_map<std::string, GLuint> m_vertexShaders;
    std::unordered_map<std::string, GLuint> m_fragmentShaders;
    std::unordered_map<std::string, std::shared_ptr<OpenGLShaderProgramContainer>> m_shaderProgramContainers;

public:
    explicit OpenGLShadersRepository(std::shared_ptr<OpenGLErrorDetector> openGLErrorDetector) :
        m_openGLErrorDetector(openGLErrorDetector) {}

    GLuint getVertexShader(const std::string &name) const;
    GLuint getFragmentShader(const std::string &name) const;
    std::shared_ptr<OpenGLShaderProgramContainer> getShaderProgramContainer(const std::string &name) const;

    GLuint createVertexShader(const std::string &name, const std::string &source);
    GLuint createFragmentShader(const std::string &name, const std::string &source);
    std::shared_ptr<OpenGLShaderProgramContainer> createShaderProgram(
        const std::string &name,
        const std::string &vertexShaderName,
        const std::string &fragmentShaderName
    );

    void removeAllShadersAndPrograms();
};
}
