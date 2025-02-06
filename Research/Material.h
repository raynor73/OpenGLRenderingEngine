#pragma once

#include <RenderingEngine/Material.h>

namespace Research
{
class Material : public RenderingEngine::Material {

    glm::vec4 m_diffuseColor;
    bool m_isWireframe;
    bool m_isUnlit;
    bool m_isDoubleSided;
    bool m_isTranslucent;

public:
    Material() : m_diffuseColor(0), m_isWireframe(false), m_isUnlit(false), m_isDoubleSided(false), m_isTranslucent(false) {}
    Material(
        const glm::vec4 &diffuseColor,
        bool isWireframe,
        bool isUnlit, 
        bool isDoubleSided,
        bool isTranslucent
    ) : m_diffuseColor(diffuseColor), 
        m_isWireframe(isWireframe),
        m_isUnlit(isUnlit),
        m_isDoubleSided(isDoubleSided),
        m_isTranslucent(isTranslucent)
    {}

    const glm::vec4 &diffuseColor() override { return m_diffuseColor; }
    void setDiffuseColor(const glm::vec4 &color) { m_diffuseColor = color; }

    bool isWireframe() override { return m_isWireframe; }
    void setWireframe(bool isWireframe) { m_isWireframe = isWireframe; }

    bool isUnlit() override { return m_isUnlit; }
    void setUnlit(bool isUnlit) { m_isUnlit = isUnlit; }

    bool isDoubleSided() override { return m_isDoubleSided; }
    void setDoubleSided(bool isDoubleSided) { m_isDoubleSided = isDoubleSided; }

    bool isTranslucent() override { return m_isTranslucent; }
    void setTranslucent(bool isTranslucent) { m_isTranslucent = isTranslucent; }
};
}
