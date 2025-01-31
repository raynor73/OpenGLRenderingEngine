#pragma once

#include <RenderingEngine/ReadOnlyFs.h>

namespace PlatformDependent
{
namespace Windows
{
class WindowsReadOnlyFs : public RenderingEngine::ReadOnlyFs {
public:
    bool isFileExists(const std::string &path) override;

    std::vector<uint8_t> readBinaryFileContent(const std::string &path) override;
    std::string readTextFileContent(const std::string &path) override;
};
}
}
