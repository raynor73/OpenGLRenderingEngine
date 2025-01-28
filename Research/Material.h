#pragma once

#include <RenderingEngine/Material.h>

namespace Research
{
class Material : public RenderingEngine::Material {

    glm::vec4 m_diffuseColor;

public:
    Material() : m_diffuseColor(0) {}
    Material(const glm::vec4 &diffuseColor) : m_diffuseColor(diffuseColor) {}

    const glm::vec4 &diffuseColor() override { return m_diffuseColor; }
    void setDiffuseColor(const glm::vec4 &color) { m_diffuseColor = color; }
};
}
