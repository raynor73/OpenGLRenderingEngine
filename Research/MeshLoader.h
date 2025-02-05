#pragma once

#include <string>
#include "Mesh.h"
#include <RenderingEngine/ReadOnlyFs.h>
#include <memory>

namespace Research
{
class MeshLoader
{
    std::shared_ptr<RenderingEngine::ReadOnlyFs> m_readOnlyFs;

public:
    MeshLoader(std::shared_ptr<RenderingEngine::ReadOnlyFs> readOnlyFs) : m_readOnlyFs(readOnlyFs) {}

    Mesh loadMesh(const std::string &path);
};
}