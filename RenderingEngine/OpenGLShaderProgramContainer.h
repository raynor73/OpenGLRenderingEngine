#pragma once

#include <memory>
#include "OpenGLErrorDetector.h"

namespace RenderingEngine
{
class OpenGLShaderProgramContainer
{
    std::shared_ptr<OpenGLErrorDetector> m_openGLErrorDetector;

    GLuint m_shaderProgram;

    GLint m_mvpMatrixUniform;
    GLint m_modelMatrixUniform;
    /*GLint m_mvMatrixUniform;
    GLint m_textureUniform;*/
    GLint m_diffuseColorUniform;
    //GLint m_useDiffuseColorUniform;

    GLint m_ambientColorUniform;
    GLint m_directionalLightColorUniform;
    GLint m_directionalLightDirectionUniform;

public:
    OpenGLShaderProgramContainer(std::shared_ptr<OpenGLErrorDetector> openGLErrorDetector, GLuint shaderProgram);

    GLuint shaderProgram() const { return m_shaderProgram; }

    //GLint positionAttribute() const { return m_positionAttribute; }
    //GLint normalAttribute() const { return m_normalAttribute; }
    //GLint uvAttribute() const { return m_uvAttribute; }

    GLint mvpMatrixUniform() const { return m_mvpMatrixUniform; }
    GLint modelMatrixUniform() const { return m_modelMatrixUniform; }
    /*GLint mvMatrixUniform() const { return m_mvMatrixUniform; }
    GLint textureUniform() const { return m_textureUniform; }*/
    GLint diffuseColorUniform() const { return m_diffuseColorUniform; }

    //GLint useDiffuseColorUniform() const { return m_useDiffuseColorUniform; }

    GLint ambientColorUniform() const { return m_ambientColorUniform; }
    GLint directionalLightColorUniform() const { return m_directionalLightColorUniform; }
    GLint directionalLightDirectionUniform() const { return m_directionalLightDirectionUniform; }
};
}
