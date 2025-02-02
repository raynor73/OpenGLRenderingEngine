#include "OpenGLRenderingEngine.h"
#include "RenderableMeshInternal.h"
#include <Logger.h>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace RenderingEngine;
using namespace std;

const string OpenGLRenderingEngine::LOG_TAG = "OpenGLRenderingEngine";

const string OpenGLRenderingEngine::AMBIENT_VERTEX_SHADER_NAME = "AmbientVertexShader";
const string OpenGLRenderingEngine::AMBIENT_FRAGMENT_SHADER_NAME = "AmbientFragmentShader";
const string OpenGLRenderingEngine::AMBIENT_SHADER_PROGRAM_NAME = "AmbientShader";

const string OpenGLRenderingEngine::DIRECTIONAL_LIGHT_VERTEX_SHADER_NAME = "DirectionalLightVertexShader";
const string OpenGLRenderingEngine::DIRECTIONAL_LIGHT_FRAGMENT_SHADER_NAME = "DirectionalLightFragmentShader";
const string OpenGLRenderingEngine::DIRECTIONAL_LIGHT_SHADER_PROGRAM_NAME = "DirectionalLightShader";

const GLuint OpenGLRenderingEngine::POSITION_ATTRIBUTE_LOCATION = 0;
const GLuint OpenGLRenderingEngine::NORMAL_ATTRIBUTE_LOCATION = 1;

OpenGLRenderingEngine::OpenGLRenderingEngine(
    shared_ptr<OpenGLErrorDetector> openGLErrorDetector,
    shared_ptr<OpenGLShadersRepository> shaderRepository,
    shared_ptr<OpenGLShaderSourcePreprocessor> shaderSourcePreprocessor
) : m_openGLErrorDetector(openGLErrorDetector), 
    m_shaderRepository(shaderRepository),
    m_shaderSourcePreprocessor (shaderSourcePreprocessor)
{
    initShader(
        AMBIENT_VERTEX_SHADER_NAME,
        "./Shaders/AmbientVertexShader.glsl",
        AMBIENT_FRAGMENT_SHADER_NAME,
        "./Shaders/AmbientFragmentShader.glsl",
        AMBIENT_SHADER_PROGRAM_NAME
    );

    initShader(
        DIRECTIONAL_LIGHT_VERTEX_SHADER_NAME,
        "./Shaders/DirectionalLightVertexShader.glsl",
        DIRECTIONAL_LIGHT_FRAGMENT_SHADER_NAME,
        "./Shaders/DirectionalLightFragmentShader.glsl",
        DIRECTIONAL_LIGHT_SHADER_PROGRAM_NAME
    );

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
}

void OpenGLRenderingEngine::initShader(
    const std::string &vertexShaderName,
    const std::string &vertexShaderPath,
    const std::string &fragmentShaderName,
    const std::string &fragmentShaderPath,
    const std::string &shaderProgramName
) {
    m_shaderRepository->createVertexShader(
        vertexShaderName,
        m_shaderSourcePreprocessor->loadShaderSource(vertexShaderPath)
    );
    m_shaderRepository->createFragmentShader(
        fragmentShaderName,
        m_shaderSourcePreprocessor->loadShaderSource(fragmentShaderPath)
    );
    m_shaderRepository->createShaderProgram(
        shaderProgramName,
        vertexShaderName,
        fragmentShaderName
    );
}

shared_ptr<RenderableMesh> OpenGLRenderingEngine::createRenderableMesh(
    Mesh &mesh,
    shared_ptr<Transformation> transformation,
    shared_ptr<Material> material
) {
    GLuint vao, vbo, ibo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    vector<float> vertexData(mesh.numberOfVertices() * Vertex::VERTEX_COMPONENTS);

    for (uintptr_t i = 0; i < mesh.numberOfVertices(); i++) {
        vertexData[    i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).position().x;
        vertexData[1 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).position().y;
        vertexData[2 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).position().z;

        vertexData[3 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).normal().x;
        vertexData[4 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).normal().y;
        vertexData[5 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).normal().z;

        vertexData[6 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).uv().x;
        vertexData[7 + i * Vertex::VERTEX_COMPONENTS] = mesh.vertexAt(i).uv().y;
    }

    glBufferData(
        GL_ARRAY_BUFFER,
        vertexData.size() * sizeof(float),
        vertexData.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        POSITION_ATTRIBUTE_LOCATION,
        Vertex::VERTEX_POSITION_COMPONENTS,
        GL_FLOAT,
        false,
        Vertex::VERTEX_COMPONENTS * sizeof(float),
        reinterpret_cast<void *>(0)
    );
    glEnableVertexAttribArray(POSITION_ATTRIBUTE_LOCATION);

    glVertexAttribPointer(
        NORMAL_ATTRIBUTE_LOCATION,
        Vertex::VERTEX_NORMAL_COMPONENTS,
        GL_FLOAT,
        false,
        Vertex::VERTEX_COMPONENTS * sizeof(float),
        reinterpret_cast<void *>(Vertex::VERTEX_POSITION_COMPONENTS * sizeof(float))
    );
    glEnableVertexAttribArray(NORMAL_ATTRIBUTE_LOCATION);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        mesh.indices().size() * sizeof(uint16_t),
        mesh.indices().data(),
        GL_STATIC_DRAW
    );

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    auto iboInfo = IboInfo{ ibo, mesh.indices().size()};

    m_openGLErrorDetector->checkOpenGLErrors("OpenGLRenderingEngine::createRenderableMesh");

    shared_ptr<RenderableMeshInternal> renderableMesh = make_shared<RenderableMeshInternal>(transformation, material, vao, vbo, iboInfo);
	m_renderableMeshes.emplace(renderableMesh->id(), renderableMesh);

    return renderableMesh;
}

void OpenGLRenderingEngine::freeRenderableMesh(uint32_t id) {
    if (m_renderableMeshes.count(id) == 0) {
        stringstream ss;
        ss << "freeRenderableMesh: mesh with id: " << id << " not found";
        L::e(LOG_TAG, ss.str());
        return;
    }

    auto renderableMesh = m_renderableMeshes[id];
    auto vao = renderableMesh->vao();
    auto vbo = renderableMesh->vbo();
    auto iboInfo = renderableMesh->iboInfo();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &iboInfo.ibo);
    renderableMesh->setValid(false);
    m_renderableMeshes.erase(id);

    m_openGLErrorDetector->checkOpenGLErrors("freeRenderableMesh");
}

void OpenGLRenderingEngine::render(
    Camera &camera,
    const glm::vec3 &ambient
) {
    if (m_openGLErrorDetector->isOpenGLErrorDetected()) {
        return;
    }

    auto clearColor = camera.clearColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto mvMatrix = camera.projectionMatrix() * camera.viewMatrix();

    for (auto meshEntry : m_renderableMeshes) {
        auto shader = m_shaderRepository->getShaderProgramContainer(AMBIENT_SHADER_PROGRAM_NAME);
        glUseProgram(shader->shaderProgram());

        auto mesh = meshEntry.second;
        auto material = mesh->material();
        auto transformation = mesh->transformation();

        glBindVertexArray(mesh->vao());

        auto modelMatrix = glm::translate(glm::identity<glm::mat4>(), transformation->position());
        modelMatrix *= glm::toMat4(transformation->rotation());
        modelMatrix = glm::scale(modelMatrix, transformation->scale());

        auto mvpMatrix = mvMatrix * modelMatrix;
        glUniformMatrix4fv(shader->mvpMatrixUniform(), 1, false, &mvpMatrix[0][0]);

        glUniform4f(
            shader->diffuseColorUniform(),
            material->diffuseColor().r,
            material->diffuseColor().g,
            material->diffuseColor().b,
            material->diffuseColor().a
        );

        glUniform3f(
            shader->ambientColorUniform(),
            ambient.r,
            ambient.g,
            ambient.b
        );

        glDrawElements(
            GL_TRIANGLES,
            mesh->iboInfo().numberOfIndices,
            GL_UNSIGNED_SHORT,
            reinterpret_cast<void *>(0)
        );

        glBindVertexArray(0);

        m_openGLErrorDetector->checkOpenGLErrors("OpenGLRenderingEngine::render");
    }
}