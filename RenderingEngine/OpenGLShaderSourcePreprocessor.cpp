#include "OpenGLShaderSourcePreprocessor.h"

using namespace RenderingEngine;
using namespace std;

const string OpenGLShaderSourcePreprocessor::INCLUDE_TOKEN_PREFIX = "#include \"";
const string OpenGLShaderSourcePreprocessor::INCLUDE_TOKEN_POSTFIX = "\"";

string OpenGLShaderSourcePreprocessor::loadShaderSource(const string &path) {
    auto source = m_shaderSourceLoader->loadShaderSource(path);

    for (size_t currentPosition = 0;;) {
        auto prefixPosition = source.find(INCLUDE_TOKEN_PREFIX, currentPosition);
        if (prefixPosition != string::npos) {
            auto postfixPosition = source.find(INCLUDE_TOKEN_POSTFIX, prefixPosition + INCLUDE_TOKEN_PREFIX.size());
            if (postfixPosition != string::npos) {
                auto includePath = source.substr(
                    prefixPosition + INCLUDE_TOKEN_PREFIX.size(),
                    postfixPosition - prefixPosition - INCLUDE_TOKEN_PREFIX.size() - INCLUDE_TOKEN_POSTFIX.size()
                );
                auto includeSource = m_shaderSourceLoader->loadShaderSource(includePath);
                source.replace(
                    prefixPosition + INCLUDE_TOKEN_POSTFIX.size(),
                    includePath.size() + INCLUDE_TOKEN_POSTFIX.size(),
                    includeSource
                );
                currentPosition = prefixPosition + includeSource.size();
                continue;
            }
        }
        break;
    }

    return source;
}