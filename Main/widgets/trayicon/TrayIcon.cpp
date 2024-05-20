#include "TrayIcon.hpp"

#include <Config.hpp>
#include <AppDelegate.hpp>
#include <utils/Log.hpp>

#include <QtWidgets/qapplication.h>

TrayIcon::TrayIcon(QWidget *parent): QSystemTrayIcon(parent)
{
    setIcon(QIcon(Config::GetSysTrayIconPath().c_str()));

    _actions = {
        new QAction("角色显示"),
        new QAction("鼠标追踪"),
        new QAction("鼠标事件"),
        new QAction("窗口置顶"),
        new QAction("打开设置"),
    };

    _menu.addActions(_actions);
    _actions.append(new QAction("退出程序"));
    _menu.addSeparator();
    _menu.addAction(_actions.back());
    setContextMenu(&_menu);

    // setup signals
    QList<void (TrayIcon::*)()> _slots = {
        &TrayIcon::SwitchSceneVisible,
        &TrayIcon::SwitchMouseTrack,
        &TrayIcon::SwitchMouseEventsTranparent,
        &TrayIcon::SwitchStayOnTop,
        &TrayIcon::ShowSettings,
        &TrayIcon::Exit,
    };

    for (int i = 0; i < _slots.size(); i++)
    {
        connect(_actions.at(i), &QAction::triggered, this, _slots[i]);
    }
}

TrayIcon::~TrayIcon()
{
    for (QAction *action: _actions)
    {
        delete action;
    }
    setParent(nullptr);
}

void TrayIcon::Exit()
{
    AppDelegate::ReleaseInstance();
}

void TrayIcon::Show()
{
    show();
}

void TrayIcon::Hide()
{
    hide();
}

void TrayIcon::SwitchSceneVisible()
{
    bool visible = !Config::GetSceneVisible();
    AppDelegate::GetInstance()->GetScene()->setVisible(visible);

    Config::SetSceneVisible(visible);
}

void TrayIcon::SwitchMouseTrack()
{
    // TODO Scene.SetMouseTrackEnable()

    bool enable = !Config::GetMouseTrack();
    Info("SetMouseTrack %d", enable);

    Config::SetMouseTrack(enable);
}

void TrayIcon::SwitchMouseEventsTranparent()
{
    // TODO Scene.SetMouseEventsTransparent()
    bool enable = !Config::GetMouseEventsTransparent();

    Info("SetMouseEventsTranparent %d", enable);

    Config::SetMouseEventsTransparent(enable);
}

void TrayIcon::SwitchStayOnTop()
{
    // TODO Scene.SetMouseEventsTransparent()
    bool enable = !Config::GetSceneStayOnTop();

    Info("SetStayOnTop %d", enable);

    Config::SetSceneStayOnTop(enable);
}

void TrayIcon::ShowSettings()
{
    // TODO Settings.Show()
    Info("open settings");
}
