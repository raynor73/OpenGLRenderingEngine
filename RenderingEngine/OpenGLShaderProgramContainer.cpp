#include "OpenGLShaderProgramContainer.h"

using namespace RenderingEngine;
using namespace std;

OpenGLShaderProgramContainer::OpenGLShaderProgramContainer(
    shared_ptr<OpenGLErrorDetector> openGLErrorDetector,
    GLuint shaderProgram
) : m_openGLErrorDetector(move(openGLErrorDetector)),
    m_shaderProgram(shaderProgram),

    m_mvpMatrixUniform(glGetUniformLocation(shaderProgram, "mvpMatrixUniform")),
    m_modelMatrixUniform(glGetUniformLocation(shaderProgram, "modelMatrixUniform")),

    m_diffuseColorUniform(glGetUniformLocation(shaderProgram, "diffuseColorUniform")),

    m_ambientLightColorUniform(glGetUniformLocation(shaderProgram, "ambientColorUniform.color")),
    m_ambientLightIntensityUniform(glGetUniformLocation(shaderProgram, "ambientColorUniform.intensity")),

    m_directionalLightColorUniform(glGetUniformLocation(shaderProgram, "directionalLightUniform.base.color")),
    m_directionalLightIntensityUniform(glGetUniformLocation(shaderProgram, "directionalLightUniform.base.intensity")),
    m_directionalLightDirectionUniform(glGetUniformLocation(shaderProgram, "directionalLightUniform.direction"))
{
    m_openGLErrorDetector->checkOpenGLErrors("OpenGLShaderProgramContainer::OpenGLShaderProgramContainer");
}