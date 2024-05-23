#pragma once

#include <vector>
#include <string>

namespace ModelDirectory
{
    bool Initialize(const char *resourceDir);
    bool IsModelDir(const char* path);
    std::vector<std::string>& GetModelDirs();
};