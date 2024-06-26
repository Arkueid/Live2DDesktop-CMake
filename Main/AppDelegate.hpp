// 总管理类
#pragma once

#include <IAppDelegate.hpp>

#include <widgets/scene/Scene.hpp>
#include <widgets/trayicon/TrayIcon.hpp>

#include <live2d/LAppPal.hpp>
#include <live2d/LAppAllocator.hpp>

#include <utils/mouse/MouseActionManager.hpp>

#include <utils/matrix/MatrixManager.hpp>

class AppDelegate : public IAppDelegate
{
public:
    // 单例模式
    static AppDelegate *GetInstance();
    static void ReleaseInstance();
    /// @brief 初始化，失败直接退出程序
    void Initialize();
    /// @brief 显示释放所有资源
    void Release();
    /// @brief 程序入口
    void Run();

    IModelManager *GetModelManager();
    Scene *GetScene();
    TrayIcon *GetTrayIcon();
    MouseActionManager *GetMouseActionManager();
    MatrixManager *GetMatrixManager();
private:
    AppDelegate();
    ~AppDelegate();

    LAppAllocator _cubismAllocator;             // 内存分配器
    Csm::CubismFramework::Option _cubismOption; // 框架设置

    // widgets
    Scene *_scene;       // 绘图窗口
    TrayIcon *_trayIcon; // 系统托盘
    // live2d
    ModelManager *_modelManager;             // 模型管理类
    MouseActionManager *_mouseActionManager; // 鼠标管理类
    MatrixManager *_matrixManager;           // 坐标矩阵管理类

    // 初始化 Cubism 框架
    void InitializeCubism();
};
