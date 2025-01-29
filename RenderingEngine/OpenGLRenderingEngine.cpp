#include "OpenGLRenderingEngine.h"
#include "RenderableMeshInternal.h"
#include <Logger.h>
#include <sstream>

using namespace RenderingEngine;

std::string OpenGLRenderingEngine::LOG_TAG = "OpenGLRenderingEngine";

std::shared_ptr<RenderableMesh> OpenGLRenderingEngine::createRenderableMesh(
    Mesh &mesh,
    std::shared_ptr<Transformation> transformation,
    std::shared_ptr<Material> material
) {
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<float> vertexData(mesh.numberOfVertices() * Vertex::VERTEX_COMPONENTS);

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

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_openGLErrorDetector->checkOpenGLErrors("createRenderableMesh#1");

    GLuint ibo;
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        mesh.indices().size() * sizeof(uint16_t),
        mesh.indices().data(),
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    auto iboInfo = IboInfo{ ibo, mesh.indices().size()};

    m_openGLErrorDetector->checkOpenGLErrors("createRenderableMesh#2");

    std::shared_ptr<RenderableMeshInternal> renderableMesh = std::make_shared<RenderableMeshInternal>(vbo, iboInfo);
	m_renderableMeshes.emplace(renderableMesh->id(), renderableMesh);

    return renderableMesh;
}

void OpenGLRenderingEngine::freeRenderableMesh(uint32_t id) {
    if (m_renderableMeshes.count(id) == 0) {
        std::stringstream ss;
        ss << "freeRenderableMesh: mesh with id: " << id << " not found";
        L::e(LOG_TAG, ss.str());
        return;
    }

    auto renderableMesh = m_renderableMeshes[id];
    auto vbo = renderableMesh->vbo();
    auto iboInfo = renderableMesh->iboInfo();
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &iboInfo.ibo);
    renderableMesh->setValid(false);
    m_renderableMeshes.erase(id);

    m_openGLErrorDetector->checkOpenGLErrors("freeRenderableMesh");
}

void OpenGLRenderingEngine::render(Camera &camera) {
    auto clearColor = camera.clearColor();
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);


}