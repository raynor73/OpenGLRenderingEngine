#include "WindowsReadOnlyFs.h"
#include <fstream>
#include <filesystem>
#include <sstream>

using namespace PlatformDependent::Windows;
using namespace std;

bool WindowsReadOnlyFs::isFileExists(const std::string &path) {
    std::ifstream f(path.c_str());
    return f.good();
}

std::vector<uint8_t> WindowsReadOnlyFs::readBinaryFileContent(const std::string &path) {
    std::ifstream f(path.c_str(), std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        stringstream ss;
        ss << "Can't open file: " << path;
        throw domain_error(ss.str());
    }

    auto fileSize = std::filesystem::file_size(path);
    std::vector<uint8_t> buffer(fileSize);
    f.read(reinterpret_cast<char *>(buffer.data()), fileSize);
    f.close();

    return buffer;
}

std::string WindowsReadOnlyFs::readTextFileContent(const std::string &path) {
    std::stringstream ss;

    std::ifstream f(path.c_str(), std::ios::in);

    if (!f.is_open()) {
        stringstream ss;
        ss << "Can't open file: " << path;
        throw domain_error(ss.str());
    }

    ss << f.rdbuf();
    f.close();

    return ss.str();
}
