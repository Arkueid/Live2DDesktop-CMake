#include "TrayIcon.hpp"

#include <Config.hpp>
#include <AppDelegate.hpp>
#include <utils/log/Log.hpp>

#include <QtWidgets/qapplication.h>

TrayIcon::TrayIcon()
{
    setIcon(QIcon(Config::GetSysTrayIconPath().c_str()));

    _actions = {
        new QAction("角色显示"),
        new QAction("视线追踪"),
        new QAction("锁定窗口"),
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
        &TrayIcon::SwitchMouseClickTranparent,
        &TrayIcon::SwitchStayOnTop,
        &TrayIcon::ShowSettings,
        &TrayIcon::Exit,
    };

    for (int i = 0; i < _slots.size(); i++)
    {
        connect(_actions.at(i), &QAction::triggered, this, _slots[i]);
    }

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(PopUpScene(QSystemTrayIcon::ActivationReason)));
}

TrayIcon::~TrayIcon()
{
    for (QAction *action : _actions)
    {
        delete action;
    }
    setParent(nullptr);
}

void TrayIcon::Initialize()
{
    // _actions = {
    //     new QAction("角色显示"),
    //     new QAction("视线追踪"),
    //     new QAction("锁定窗口"),
    //     new QAction("窗口置顶"),
    //     new QAction("打开设置"),
    // };
    bool values[] = {
        Config::GetSceneVisible(),
        Config::GetMouseTrack(),
        Config::GetMouseClickTransparent(),
        Config::GetSceneStayOnTop()};

    for (int i = 0; i < 4; i++)
    {
        _actions[i]->setCheckable(true);
        _actions[i]->setChecked(values[i]);
    }
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
    bool enable = !Config::GetMouseTrack();
    Info("SetMouseTrack %d", enable);

    AppDelegate::GetInstance()->GetMouseActionManager()->SetMouseTrackEnable(enable);

    // 关闭功能后视线复位
    if (!enable)
        AppDelegate::GetInstance()->GetModelManager()->OnDrag(0.0f, 0.0f);

    Config::SetMouseTrack(enable);
}

void TrayIcon::SwitchMouseClickTranparent()
{
    bool enable = !Config::GetMouseClickTransparent();
    Info("SetMouseEventsTranparent %d", enable);

    AppDelegate::GetInstance()->GetMouseActionManager()->SetMouseClickTransparentEnable(enable);

    Config::SetMouseClickTransparent(enable);
}

void TrayIcon::SwitchStayOnTop()
{
    // TODO Scene.SetOnTop()
    bool enable = !Config::GetSceneStayOnTop();

    Info("SetStayOnTop %d", enable);

    Config::SetSceneStayOnTop(enable);

    // TODO new function SetStayOnTopEnable
    AppDelegate::GetInstance()->GetScene()->SetStayOnTop(enable);
}

void TrayIcon::ShowSettings()
{
    // TODO Settings.Show()
    Info("open settings");
}

void TrayIcon::PopUpScene(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::ActivationReason::DoubleClick)
    {
        Config::SetSceneVisible(true);
        _actions[0]->setChecked(true);
        AppDelegate::GetInstance()->GetScene()->Popup();
    }
}