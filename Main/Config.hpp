#pragma once

#define KEY_RESOURCE_DIR "resource_dir"
#define KEY_SCENE "scene"
#define KEY_SCENE_WIDTH "width"
#define KEY_SCENE_HEIGHT "height"
#define KEY_SCENE_VISIBLE "visible"
#define KEY_SCENE_STAY_ON_TOP "stay_on_top"
#define KEY_MODEL "model"
#define KEY_MODEL_NAME "name"
#define KEY_SYS_TRAY "systray"
#define KEY_SYS_TRAY_ICON_PATH "icon_path"
#define KEY_MOUSE "mouse"
#define KEY_MOUSE_TRACK "track"
#define KEY_MOUSE_CLICK_TRANSPARENT "click_transparent"

#include <iostream>

namespace Config
{
    extern bool Initialize();
    extern bool GenerateDefaultConfig();
    extern bool SaveConfig();

    // resource
    extern void SetResourceDir(std::string resource_dir);
    extern std::string GetResourceDir();
    // scene
    extern void SetSceneWidth(int width);
    extern void SetSceneHeight(int height);
    extern void SetSceneVisible(bool visible);
    extern void SetSceneStayOnTop(bool enable);
    extern int GetSceneWidth();
    extern int GetSceneHeight();
    extern bool GetSceneVisible();
    extern bool GetSceneStayOnTop();
    // model
    extern void SetModelName(std::string name);
    extern std::string GetModelName();

    // sys tray icon
    extern void SetSysTrayIconPath(std::string iconPath);
    extern std::string GetSysTrayIconPath();

    // mouse
    extern void SetMouseTrack(bool enable);
    extern void SetMouseClickTransparent(bool enable);
    extern bool GetMouseTrack();
    extern bool GetMouseClickTransparent();
};