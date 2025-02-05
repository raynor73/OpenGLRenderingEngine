#pragma once

#include <glm/glm.hpp>

namespace RenderingEngine 
{
class Material {
public:
    virtual const glm::vec4& diffuseColor() = 0;
    //virtual const std::string& textureName() const = 0;
    //virtual bool useDiffuseColor() const = 0;
    //virtual bool isTranslucent() const = 0;
    virtual bool isWireframe() = 0;
    virtual bool isUnlit() = 0;
    virtual bool isDoubleSided() = 0;
};
}
