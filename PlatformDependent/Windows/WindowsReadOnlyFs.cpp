#include "WindowsReadOnlyFs.h"
#include <fstream>

using namespace PlatformDependent::Windows;

bool WindowsReadOnlyFs::isFileExists(const std::string &path) {
    std::ifstream f(path.c_str());
    return f.good();
}

std::vector<uint8_t> WindowsReadOnlyFs::readBinaryFileContent(const std::string &path) {

}

std::string WindowsReadOnlyFs::readTextFileContent(const std::string &path) {

}
