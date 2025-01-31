#pragma once

#include "OpenGLShaderSourceLoader.h"

namespace RenderingEngine
{
class OpenGLShaderSourcePreprocessor
{
    std::shared_ptr<OpenGLShaderSourceLoader> m_shaderSourceLoader;

public:
    OpenGLShaderSourcePreprocessor(std::shared_ptr<OpenGLShaderSourceLoader> shaderSourceLoader) :
        m_shaderSourceLoader(shaderSourceLoader) {}

    std::string loadShaderSource(const std::string &path);

private:
    static const std::string INCLUDE_TOKEN_PREFIX;
    static const std::string INCLUDE_TOKEN_POSTFIX;
};
}
