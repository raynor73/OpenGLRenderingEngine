#pragma once

#include <RenderingEngine/Material.h>

namespace Research
{
class Material : public RenderingEngine::Material {

    glm::vec4 m_diffuseColor;
    bool m_isWireframe;

public:
    Material() : m_diffuseColor(0), m_isWireframe(false) {}
    Material(const glm::vec4 &diffuseColor, bool isWireframe) : m_diffuseColor(diffuseColor), m_isWireframe(isWireframe) {}

    const glm::vec4 &diffuseColor() override { return m_diffuseColor; }
    void setDiffuseColor(const glm::vec4 &color) { m_diffuseColor = color; }

    bool isWireframe() { return m_isWireframe; }
    void setWireframe(bool isWireframe) { m_isWireframe = isWireframe; }
};
}
