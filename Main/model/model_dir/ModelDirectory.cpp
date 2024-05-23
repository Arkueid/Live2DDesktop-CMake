#include "ModelDirectory.hpp"

#include <dirent.h>
#include <utils/log/Log.hpp>
#include <Default.hpp>

#include <sys/stat.h>

#define MAX_DIR_NAME_LEN 256

static std::vector<std::string> _modelDirs;

// o(n)
static void get_basename(const char *path, char *name)
{
    char *ptr = (char *)path;
    char *ret = ptr;
    while (*ptr != '\0')
    {
        if ((*ptr == '\\' || *ptr == '/') && (*(ptr + 1) != '\0'))
        {
            ret = ptr + 1;
        }
        ptr++;
    }
    // ret != "/"
    int i = 0;
    while (*ret != '\0' && *ret != '\\' && *ret != '/')
    {
        *name++ = *ret++;
        i++;
    }
    *name = '\0';
}

bool ModelDirectory::SetResourceDirectory(const char *resourceDir)
{
    std::string _resourceDir(resourceDir);
    DIR *dir = opendir(resourceDir);

    struct dirent *entry;

    // o(n)
    while ((entry = readdir(dir)) != nullptr)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        std::string dir = _resourceDir + entry->d_name;
        if (IsModelDir(dir.c_str()))
        {
            _modelDirs.push_back(entry->d_name);
        }
    }
    return !_modelDirs.empty();  // there must be at least one model
}

bool ModelDirectory::IsModelDir(const char *path)
{
    std::string _path = path;

    struct stat st;
    char name[MAX_DIR_NAME_LEN];
    get_basename(path, name);

    if (stat((_path + "/" + name + MODEL_JSON_SUFFIX).c_str(), &st) == -1) return false;

    if (stat((_path + "/" + name + MODEL_MOC_SUFFIX).c_str(), &st) == -1) return false;

    return true;
}

std::vector<std::string>& ModelDirectory::GetModelDirs()
{
    return _modelDirs;
}