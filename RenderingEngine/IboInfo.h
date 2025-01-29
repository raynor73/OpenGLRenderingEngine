#pragma once

#include <GL/glew.h>

namespace RenderingEngine
{
struct IboInfo {
    GLuint ibo;
    size_t numberOfIndices;
};
}
