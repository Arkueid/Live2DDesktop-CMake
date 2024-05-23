#include "ModelDirectory.hpp"

#include <dirent.h>
#include <utils/log/Log.hpp>
#include <Default.hpp>

#include <sys/stat.h>

#define MAX_DIR_NAME_LEN 256

static std::vector<std::string> _modelDirs;

// o(n)
static char *get_basename(const char *path)
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
    return ret;
}

bool ModelDirectory::Initialize(const char *resourceDir)
{
    std::string _resourceDir(resourceDir);
    DIR *dir = opendir(resourceDir);

    struct dirent *entry;

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
    bool moc3 = false, model3_json = false;
    char moc3_name[MAX_DIR_NAME_LEN];
    char model3_json_name[MAX_DIR_NAME_LEN];

    struct stat st;
    if (stat(path, &st) == 1) // no such file
    {
        return false;
    }

    if (!S_ISDIR(st.st_mode)) // is not a dir
    {
        return false;
    }

    DIR *dir = opendir(path);

    struct dirent *entry;

    int i = 0;
    char *ptr = get_basename(path);
    while (*ptr != '\0')
    {
        if (*ptr == '\\' || *ptr == '/')
            break;
        model3_json_name[i] = *ptr;
        moc3_name[i] = *ptr;
        ptr++;
        i++;
    }

    strcpy(model3_json_name + i, MODEL_JSON_SUFFIX);
    strcpy(moc3_name + i, MODEL_MOC_SUFFIX);

    while ((entry = readdir(dir)) != nullptr)
    {
        if (model3_json && moc3)
            break;
        if (!model3_json && strcmp(entry->d_name, model3_json_name) == 0)
            model3_json = true;
        if (!moc3 && strcmp(entry->d_name, moc3_name) == 0)
            moc3 = true;
    }
    return model3_json && moc3;
}

std::vector<std::string>& ModelDirectory::GetModelDirs()
{
    return _modelDirs;
}