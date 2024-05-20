#pragma once

#include <QtWidgets/qsystemtrayicon.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>

class TrayIcon: public QSystemTrayIcon
{
    Q_OBJECT
public:
    TrayIcon(QWidget *parent);
    ~TrayIcon();
    /// @brief 显示图标
    void Show();
    /// @brief 隐藏图标
    void Hide();
protected:
private:
    QList<QAction *> _actions;
    QMenu _menu;
private slots:
    /// @brief 退出程序
    void Exit();
    /// @brief 开关角色显示
    void SwitchSceneVisible();
    /// @brief 开关鼠标追踪
    void SwitchMouseTrack();
    /// @brief 开关鼠标事件
    void SwitchMouseEventsTranparent();
    /// @brief 窗口置顶
    void SwitchStayOnTop();
    /// @brief 打开设置窗口
    void ShowSettings();
};