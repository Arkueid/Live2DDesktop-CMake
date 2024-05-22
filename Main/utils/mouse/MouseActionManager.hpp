#pragma once

#define BUTTON_NONE 0
#define BUTTON_LEFT 1
#define BUTTON_RIGHT 2

/// @brief void function(x, y, button)
typedef void (*Callback)(int, int, int);

/// @brief 鼠标时间管理类
// 鼠标事件分类由界面类产生
class MouseActionManager
{
public:
    MouseActionManager();
    ~MouseActionManager();
    void Initialize();
    /// @brief onMove -> enter / leave / drag
    /// @param x
    /// @param y
    void SetOnEnterCallback(Callback callback);
    void SetOnLeaveCallback(Callback callback);
    void SetOnMoveCallback(Callback callback);
    void SetOnClickStartCallback(Callback callback);
    void SetOnClickEndCallback(Callback callback);
    void SetOnDoubleClickCallback(Callback callback);
    void SetOnMovePerFrameCallback(Callback callback);
    void OnEnter(int x, int y);
    void OnLeave(int x, int y);
    void OnClickStart(int x, int y, int button);
    void OnClickEnd(int x, int y, int button);
    /// @brief this function is called when mouse is moving even if no button is down
    /// @param x
    /// @param y
    void OnMovePerFrame(int x, int y, int button);
    /// @brief this function is called only when mouse button is down and mouse is in motion
    /// @param x
    /// @param y
    /// @param button
    void OnMove(int x, int y, int button);
    void OnDoubleClick(int x, int y, int button);
    void SetMouseTrackEnable(bool enable);
    void SetMouseClickTransparentEnable(bool enable);
    /// @brief to test if mouse is on the character
    bool IsHover(int x, int y);
private:
    Callback _onEnter;
    Callback _onLeave;
    Callback _onMove;
    Callback _onClickStart;
    Callback _onClickEnd;
    Callback _onDoubleClick;
    Callback _onMovePerFrame;
    bool _trackEnable;
    bool _clickEnable;
};