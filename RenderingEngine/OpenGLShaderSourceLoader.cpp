#include "OpenGLShaderSourceLoader.h"

using namespace RenderingEngine;

std::string OpenGLShaderSourceLoader::loadShaderSource(const std::string &path) {
	return m_readOnlyFs->readTextFileContent(path);
}
