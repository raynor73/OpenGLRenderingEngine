#pragma once

#include <string>
#include "ReadOnlyFs.h"
#include <memory>

namespace RenderingEngine
{
class OpenGLShaderSourceLoader {

	std::shared_ptr<ReadOnlyFs> m_readOnlyFs;

public:
	OpenGLShaderSourceLoader(std::shared_ptr<ReadOnlyFs> readOnlyFs) : m_readOnlyFs(readOnlyFs) {}

	std::string loadShaderSource(const std::string &path);
};
}
