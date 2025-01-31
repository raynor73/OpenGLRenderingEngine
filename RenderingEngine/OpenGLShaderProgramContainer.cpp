#include "OpenGLShaderProgramContainer.h"

using namespace RenderingEngine;
using namespace std;

OpenGLShaderProgramContainer::OpenGLShaderProgramContainer(
    shared_ptr<OpenGLErrorDetector> openGLErrorDetector,
    GLuint shaderProgram
) : m_openGLErrorDetector(move(openGLErrorDetector)),
    m_shaderProgram(shaderProgram),
    m_positionAttribute(glGetAttribLocation(m_shaderProgram, "positionAttribute")),
    m_normalAttribute(glGetAttribLocation(shaderProgram, "normalAttribute")),
    m_uvAttribute(glGetAttribLocation(shaderProgram, "uvAttribute")),
    m_mvpMatrixUniform(glGetUniformLocation(shaderProgram, "mvpMatrixUniform")),
    m_diffuseColorUniform(glGetUniformLocation(shaderProgram, "diffuseColorUniform")),
    m_ambientColorUniform(glGetUniformLocation(shaderProgram, "ambientColorUniform"))
{
    m_openGLErrorDetector->checkOpenGLErrors("OpenGLShaderProgramContainer::OpenGLShaderProgramContainer");
}