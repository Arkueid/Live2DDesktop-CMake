#pragma once

// 全局默认参数

// 全局设置文件路径
#define APP_CONFIG_PATH "config.json"
// Scene 宽度
#define APP_SCENE_WIDTH 400
// Scene 高度
#define APP_SCENE_HEIGHT 500

#define APP_SCENE_VISIBLE true

#define APP_SCENE_STAY_ON_TOP false

// 资源文件夹
#define APP_RESOURCE_DIR "Resources/"
// 模型名称
#define APP_MODEL_NAME "Hiyori"

#define APP_SYS_TRAY_ICON_PATH "Resources/icon.png"

#define APP_MOUSE_TRACK true

#define APP_MOUSE_CLICK_TRANSPARENT false

// 动作优先级
#define MOTION_PRIORITY_NONE 0
#define MOTION_PRIORITY_IDLE 1
#define MOTION_PRIORITY_NORMAL 2
#define MOTION_PRIORITY_FORCE 3

// default motion groups
#define MOTION_GROUP_IDLE "Idle"
#define MOTION_GROUP_TAP_HEAD "TapHead"

// hit area must be as same as its related motion group name
#define HIT_AREA_HEAD MOTION_GROUP_TAP_HEAD
