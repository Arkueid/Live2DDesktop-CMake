#include "AppDelegate.hpp"

#include <Config.hpp>
#include <utils/log/Log.hpp>
#include <QtWidgets/qapplication.h>

static AppDelegate *_instance = nullptr;

AppDelegate::AppDelegate() : _scene(nullptr),
                             _modelManager(nullptr),
                             _trayIcon(nullptr),
                             _mouseActionManager(nullptr)
{
}

AppDelegate::~AppDelegate()
{
}

AppDelegate *AppDelegate::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AppDelegate();
    }
    return _instance;
}

void AppDelegate::ReleaseInstance()
{
    if (_instance != nullptr)
    {
        _instance->Release();

        delete _instance;
    }

    _instance = nullptr;
}

void AppDelegate::Initialize()
{
    // 只能调用一次
    assert(_scene == nullptr);
    assert(_modelManager == nullptr);

    if (!Config::Initialize())
    {
        Error("config file open error");
        return;
    }

    // TODO 初始化 _modelManager
    _modelManager = new ModelManager();

    // 初始化 _mouseActionManager
    _mouseActionManager = new MouseActionManager();
    _mouseActionManager->Initialize();

    // 初始化 _scene
    _scene = new Scene();

    _trayIcon = new TrayIcon();
    _trayIcon->Initialize();

    InitializeCubism();
}

void AppDelegate::Release()
{
    if (_trayIcon != nullptr)
        delete _trayIcon;

    if (_scene != nullptr)
    {
        _scene->SetVisible(false);

        delete _scene;
    }
    if (_modelManager != nullptr)
        delete _modelManager;

    if (_mouseActionManager != nullptr)
        delete _mouseActionManager;

    _scene = nullptr;
    _modelManager = nullptr;
    _mouseActionManager = nullptr;

    Csm::CubismFramework::Dispose();

    Config::SaveConfig();

    qApp->exit();
}

void AppDelegate::Run()
{
    assert(_scene != nullptr);
    assert(_trayIcon != nullptr);
    assert(_modelManager != nullptr);
    assert(_mouseActionManager != nullptr);

    _trayIcon->Show();

    // TODO merge into Initialize func
    _scene->SetVisible(Config::GetSceneVisible());
}

IModelManager *AppDelegate::GetModelManager()
{
    return _modelManager;
}

Scene *AppDelegate::GetScene()
{
    return _scene;
}

TrayIcon *AppDelegate::GetTrayIcon()
{
    return _trayIcon;
}

MouseActionManager *AppDelegate::GetMouseActionManager()
{
    return _mouseActionManager;
}

void AppDelegate::InitializeCubism()
{
    // 一个窗口对应一个Cubism
    _cubismOption.LogFunction = LAppPal::PrintMessage;
    _cubismOption.LoggingLevel = Csm::CubismFramework::Option::LogLevel_Verbose;
    Csm::CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);
    Csm::CubismFramework::Initialize();
}
