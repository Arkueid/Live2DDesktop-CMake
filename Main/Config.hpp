#pragma once

#define KEY_RESOURCE_DIR "resource_dir"
#define KEY_SCENE "scene"
#define KEY_SCENE_WIDTH "width"
#define KEY_SCENE_HEIGHT "height"
#define KEY_MODEL "model"
#define KEY_MODEL_NAME "name"

#include <iostream>

namespace Config
{
    extern bool Initialize();
    extern bool GenerateDefaultConfig();
    extern bool SaveConfig();

    // get
    extern std::string GetResourceDir();
    extern int GetSceneWidth();
    extern int GetSceneHeight();
    extern std::string GetModelName();

    // set
    extern void SetResourceDir(std::string resource_dir);
    extern void SetSceneWidth(int width);
    extern void SetSceneHeight(int height);
    extern void SetModelName(std::string name);
};