#pragma once

#include <string>

namespace RenderingEngine
{
class OpenGLShaderSourceLoader {
public:
	std::string loadShaderSource(const std::string &path);
};
}
