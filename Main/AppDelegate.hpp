// 总管理类
#pragma once

#include <IAppDelegate.hpp>

#include <widgets/scene/Scene.hpp>

#include <live2d/LAppPal.hpp>
#include <live2d/LAppAllocator.hpp>

class AppDelegate : public IAppDelegate
{
public:
    // 单例模式
    static AppDelegate *GetInstance();
    static void ReleaseInstance();
    /// @brief 初始化，失败直接退出程序
    // todo: 需要显示释放资源
    void Initialize();
    /// @brief 显示释放所有资源
    void Release();
    /// @brief 程序入口
    void Run();

    IModelManager *GetModelManager();
    Scene *GetScene();

private:
    AppDelegate();
    ~AppDelegate();

    LAppAllocator _cubismAllocator;             // 内存分配器
    Csm::CubismFramework::Option _cubismOption; // 框架设置

    Scene *_scene;               // 绘图窗口
    ModelManager *_modelManager; // 模型管理类

    // 初始化 Cubism 框架
    void InitializeCubism();
};
