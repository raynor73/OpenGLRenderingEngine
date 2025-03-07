#include "OpenGLRenderingEngine.h"
#include "RenderableMeshInternal.h"
#include <Logger.h>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <set>

using namespace RenderingEngine;
using namespace std;

const string OpenGLRenderingEngine::LOG_TAG = "OpenGLRenderingEngine";

const string OpenGLRenderingEngine::AMBIENT_VERTEX_SHADER_NAME = "AmbientVertexShader";
const string OpenGLRenderingEngine::AMBIENT_FRAGMENT_SHADER_NAME = "AmbientFragmentShader";
const string OpenGLRenderingEngine::AMBIENT_SHADER_PROGRAM_NAME = "AmbientShader";

const string OpenGLRenderingEngine::DIRECTIONAL_LIGHT_VERTEX_SHADER_NAME = "DirectionalLightVertexShader";
const string OpenGLRenderingEngine::DIRECTIONAL_LIGHT_FRAGMENT_SHADER_NAME = "DirectionalLightFragmentShader";
const string OpenGLRenderingEngine::DIRECTIONAL_LIGHT_SHADER_PROGRAM_NAME = "DirectionalLightShader";

const string OpenGLRenderingEngine::UNLIT_SHADER_PROGRAM_NAME = "UnlitShader";

const GLuint OpenGLRenderingEngine::POSITION_ATTRIBUTE_LOCATION = 0;
const GLuint OpenGLRenderingEngine::NORMAL_ATTRIBUTE_LOCATION = 1;

struct TranslucentMeshEntry {
    shared_ptr<RenderableMeshInternal> mesh;
    float zDistanceToCamera;
};

struct DescendingOrder {
    bool operator()(TranslucentMeshEntry a, TranslucentMeshEntry b) const {
        return a.zDistanceToCamera > b.zDistanceToCamera;
    }
};

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

    initShader(
        "UnlitVertexShader",
        "./Shaders/AmbientVertexShader.glsl",
        "UnlitFragmentShader",
        "./Shaders/UnlitFragmentShader.glsl",
        UNLIT_SHADER_PROGRAM_NAME
    );

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
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
    shared_ptr<Material> material,
    const std::vector<std::string> &layers
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

    shared_ptr<RenderableMeshInternal> renderableMesh = make_shared<RenderableMeshInternal>(transformation, material, layers, vao, vbo, iboInfo);
	m_renderableMeshes.emplace(renderableMesh->id(), renderableMesh);
    for (auto layer : layers) {
        m_renderableMeshLayers.emplace(renderableMesh->id(), layer);
        m_layerRenderableMeshes.emplace(layer, renderableMesh->id());
    }

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

    auto range = m_renderableMeshLayers.equal_range(id);
    for (auto it = range.first; it != range.second; it++) {
        m_layerRenderableMeshes.erase(it->second);
    }

    m_renderableMeshLayers.erase(id);

    m_openGLErrorDetector->checkOpenGLErrors("freeRenderableMesh");
}

void OpenGLRenderingEngine::renderMesh(
    Camera &camera,
    Light &light,
    const glm::mat4 &modelMatrix,
    const glm::mat4 &viewProjectionMatrix,
    shared_ptr<RenderableMeshInternal> mesh
) {
    shared_ptr<OpenGLShaderProgramContainer> shader;

    auto material = mesh->material();

    if (material->isUnlit()) {
        shader = m_shaderRepository->getShaderProgramContainer(UNLIT_SHADER_PROGRAM_NAME);
        glUseProgram(shader->shaderProgram());
    } else if (holds_alternative<shared_ptr<BaseLight>>(light)) {
        shader = m_shaderRepository->getShaderProgramContainer(AMBIENT_SHADER_PROGRAM_NAME);
        glUseProgram(shader->shaderProgram());

        auto ambient = get<shared_ptr<BaseLight>>(light);
        glUniform3f(
            shader->ambientLightColorUniform(),
            ambient->color().r,
            ambient->color().g,
            ambient->color().b
        );
        glUniform1f(
            shader->ambientLightIntensityUniform(),
            ambient->intensity()
        );
    } else if (holds_alternative<shared_ptr<DirectionalLight>>(light)) {
        shader = m_shaderRepository->getShaderProgramContainer(DIRECTIONAL_LIGHT_SHADER_PROGRAM_NAME);
        glUseProgram(shader->shaderProgram());

        auto directionalLight = get<shared_ptr<DirectionalLight>>(light);
        glUniform3f(
            shader->directionalLightColorUniform(),
            directionalLight->color().r,
            directionalLight->color().g,
            directionalLight->color().b
        );
        glUniform3f(
            shader->directionalLightDirectionUniform(),
            directionalLight->direction().x,
            directionalLight->direction().y,
            directionalLight->direction().z
        );
        glUniform1f(
            shader->directionalLightIntensityUniform(),
            directionalLight->intensity()
        );
    } else {
        stringstream ss;
        ss << "Unexpected light variant with index: " << light.index();
        throw domain_error(ss.str());
    }

    glBindVertexArray(mesh->vao());

    auto mvpMatrix = viewProjectionMatrix * modelMatrix;
    glUniformMatrix4fv(shader->mvpMatrixUniform(), 1, false, &mvpMatrix[0][0]);
    
    auto modelMatrixUniform = shader->modelMatrixUniform();
    if (modelMatrixUniform >= 0) {
        glUniformMatrix4fv(modelMatrixUniform, 1, false, &modelMatrix[0][0]);
    }

    glUniform4f(
        shader->diffuseColorUniform(),
        material->diffuseColor().r,
        material->diffuseColor().g,
        material->diffuseColor().b,
        material->diffuseColor().a
    );

    GLenum mode = 0;
    if (material->isWireframe()) {
        mode = GL_LINE_STRIP;
    } else {
        mode = GL_TRIANGLES;
    }

    if (material->isDoubleSided()) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
    }

    glDrawElements(
        mode,
        mesh->iboInfo().numberOfIndices,
        GL_UNSIGNED_SHORT,
        reinterpret_cast<void *>(0)
    );

    glBindVertexArray(0);

    m_openGLErrorDetector->checkOpenGLErrors("OpenGLRenderingEngine::renderMesh");
}

void OpenGLRenderingEngine::render(
    Camera &camera,
    Light &ambient,
    const std::vector<Light> &lights
) {
    if (m_openGLErrorDetector->isOpenGLErrorDetected()) {
        return;
    }

    auto clearColor = camera.clearColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

    GLbitfield clearMask = 0;
    if (camera.shouldClearColor()) {
        clearMask |= GL_COLOR_BUFFER_BIT;
    }
    if (camera.shouldClearDepth()) {
        clearMask |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(clearMask);

    glViewport(
        camera.viewportLowerLeftCorner().x,
        camera.viewportLowerLeftCorner().y,
        camera.viewportSize().x,
        camera.viewportSize().y
    );

    glScissor(
        camera.scissortLowerLeftCorner().x,
        camera.scissortLowerLeftCorner().y,
        camera.scissorSize().x,
        camera.scissorSize().y
    );

    auto viewProjectionMatrix = camera.projectionMatrix() * camera.viewMatrix();

    multiset<TranslucentMeshEntry, DescendingOrder> translucentMeshes;

    for (auto cameraLayer : camera.layers()) {
        auto meshesRange = m_layerRenderableMeshes.equal_range(cameraLayer);

        for (auto it = meshesRange.first; it != meshesRange.second; it++) {
            auto mesh = m_renderableMeshes.find(it->second)->second;

            auto transformation = mesh->transformation();
            auto modelMatrix = glm::translate(glm::identity<glm::mat4>(), transformation->position());
            modelMatrix *= glm::toMat4(transformation->rotation());
            modelMatrix = glm::scale(modelMatrix, transformation->scale());

            if (mesh->material()->isTranslucent()) {
                auto meshOriginInViewCoordinates = modelMatrix * glm::vec4(transformation->position(), 1);
                translucentMeshes.insert({ mesh, meshOriginInViewCoordinates.z });
            } else {
                renderMeshWithAllLightShaders(camera, ambient, lights, modelMatrix, viewProjectionMatrix, mesh);
            }
        }
    }

    for (auto translucentMeshEntry : translucentMeshes) {
        auto mesh = translucentMeshEntry.mesh;

        auto transformation = mesh->transformation();
        auto modelMatrix = glm::translate(glm::identity<glm::mat4>(), transformation->position());
        modelMatrix *= glm::toMat4(transformation->rotation());
        modelMatrix = glm::scale(modelMatrix, transformation->scale());

        renderMeshWithAllLightShaders(camera, ambient, lights, modelMatrix, viewProjectionMatrix, mesh);
    }

    m_openGLErrorDetector->checkOpenGLErrors("OpenGLRenderingEngine::render");
}

void OpenGLRenderingEngine::renderMeshWithAllLightShaders(
    Camera &camera,
    Light &ambient,
    const std::vector<Light> &lights,
    const glm::mat4 &modelMatrix,
    const glm::mat4 &viewProjectionMatrix,
    std::shared_ptr<RenderableMeshInternal> mesh
) {
    if (mesh->material()->isTranslucent()) {
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    renderMesh(camera, ambient, modelMatrix, viewProjectionMatrix, mesh);

    if (mesh->material()->isTranslucent()) {
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
    }

    if (mesh->material()->isUnlit()) {
        return;
    }

    glEnable(GL_BLEND);
    if (mesh->material()->isTranslucent()) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glBlendFunc(GL_ONE, GL_ONE);
    }
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_EQUAL);

    for (auto light : lights) {
        renderMesh(camera, light, modelMatrix, viewProjectionMatrix, mesh);
    }

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
