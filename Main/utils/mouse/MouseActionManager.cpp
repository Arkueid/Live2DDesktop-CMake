#include "MouseActionManager.hpp"

#include <AppDelegate.hpp>
#include <utils/log/Log.hpp>
#include <Config.hpp>

static void default_on_enter_callback(int x, int y, int button);
static void default_on_leave_callback(int x, int y, int button);
static void default_on_move_callback(int x, int y, int button);
static void default_on_click_start_callback(int x, int y, int button);
static void default_on_click_end_callback(int x, int y, int button);
static void default_on_double_click_callback(int x, int y, int button);
static void default_on_move_per_frame_callback(int x, int y, int button);

MouseActionManager::MouseActionManager() : _clickEnable(true),
                                           _trackEnable(true),
                                           _onEnter(default_on_enter_callback),
                                           _onLeave(default_on_leave_callback),
                                           _onMove(default_on_move_callback),
                                           _onClickStart(default_on_click_start_callback),
                                           _onClickEnd(default_on_click_end_callback),
                                           _onDoubleClick(default_on_double_click_callback),
                                           _onMovePerFrame(default_on_move_per_frame_callback)
{
}

MouseActionManager::~MouseActionManager()
{
}

void MouseActionManager::Initialize()
{
    SetMouseClickTransparentEnable(Config::GetMouseClickTransparent());
    SetMouseTrackEnable(Config::GetMouseTrack());
}

void MouseActionManager::SetOnEnterCallback(Callback callback)
{
    _onEnter = callback;
}

void MouseActionManager::SetOnLeaveCallback(Callback callback)
{
    _onLeave = callback;
}

void MouseActionManager::SetOnMoveCallback(Callback callback)
{
    _onMove = callback;
}

void MouseActionManager::SetOnClickStartCallback(Callback callback)
{
    _onClickStart = callback;
}

void MouseActionManager::SetOnClickEndCallback(Callback callback)
{
    _onClickEnd = callback;
}

void MouseActionManager::SetOnDoubleClickCallback(Callback callback)
{
    _onDoubleClick = callback;
}

void MouseActionManager::SetOnMovePerFrameCallback(Callback callback)
{
    _onMovePerFrame = callback;
}

void MouseActionManager::OnEnter(int x, int y)
{
    if (!_trackEnable) return;
    _onEnter(x, y, -1);
}

void MouseActionManager::OnLeave(int x, int y)
{
    if (!_trackEnable) return;
    _onLeave(x, y, -1);
}

void MouseActionManager::OnClickStart(int x, int y, int button)
{
    if (!_clickEnable) return;
    _onClickStart(x, y, button);
}

void MouseActionManager::OnClickEnd(int x, int y, int button)
{
    if (!_clickEnable) return;
    _onClickEnd(x, y, button);
}

void MouseActionManager::OnMovePerFrame(int x, int y, int button)
{
    if (!_trackEnable) return;
    _onMovePerFrame(x, y, button);
}

void MouseActionManager::OnMove(int x, int y, int button)
{
    if (!_clickEnable) return;
    _onMove(x, y, button);
}

void MouseActionManager::OnDoubleClick(int x, int y, int button)
{
    if (!_clickEnable) return;
    _onDoubleClick(x, y, button);
}

void MouseActionManager::SetMouseTrackEnable(bool enable)
{
    _trackEnable = enable;   
}

void MouseActionManager::SetMouseClickTransparentEnable(bool enable)
{
    _clickEnable = enable;
}

// default callbacks

static int lastX = 0;
static int lastY = 0;
static bool _pressed = false;

void default_on_enter_callback(int x, int y, int button)
{
    Info("default on enter callback(x=%d, y=%d, button=%d)", x, y, button);
}

void default_on_leave_callback(int x, int y, int button)
{
    Info("default on leave callback(x=%d, y=%d, button=%d)", x, y, button);
}

void default_on_move_callback(int x, int y, int button)
{
    Info("default on move callback(x=%d, y=%d, button=%d)", x, y, button);
}

void default_on_click_start_callback(int x, int y, int button)
{
    Info("default on click start callback(x=%d, y=%d, button=%d)", x, y, button);
}

void default_on_click_end_callback(int x, int y, int button)
{
    Info("default on click end callback(x=%d, y=%d, button=%d)", x, y, button);
}

void default_on_double_click_callback(int x, int y, int button)
{
    Info("default on double click callback(x=%d, y=%d, button=%d)", x, y, button);
}

void default_on_move_per_frame_callback(int x, int y, int button)
{
    Info("default on move per frame callback(x=%d, y=%d, button=%d)", x, y, button);
}