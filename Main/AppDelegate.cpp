#include "AppDelegate.hpp"

#include <Config.hpp>
#include <utils/log/Log.hpp>
#include <QtWidgets/qapplication.h>

static AppDelegate *_instance = nullptr;

AppDelegate::AppDelegate() : _scene(nullptr),
                             _modelManager(nullptr),
                             _trayIcon(nullptr),
                             _mouseActionManager(nullptr),
                             _matrixManager(nullptr)  
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
    assert(_trayIcon == nullptr);
    assert(_modelManager == nullptr);
    assert(_matrixManager == nullptr);

    if (!Config::Initialize())
    {
        Error("config file open error");
        return;
    }

    // 初始化 _modelManager
    _modelManager = new ModelManager();
    _modelManager->Initialize();

    // 初始化 _mouseActionManager
    _mouseActionManager = new MouseActionManager();
    _mouseActionManager->Initialize();

    // 初始化 _matrixManager
    _matrixManager = new MatrixManager();
    _matrixManager->Initialize();

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
        _scene->setVisible(false);

        delete _scene;
    }
    if (_modelManager != nullptr)
        delete _modelManager;

    if (_mouseActionManager != nullptr)
        delete _mouseActionManager;

    if (_matrixManager != nullptr)
        delete _matrixManager;

    _scene = nullptr;
    _modelManager = nullptr;
    _mouseActionManager = nullptr;
    _matrixManager = nullptr;

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
    assert(_matrixManager != nullptr);

    _trayIcon->Show();

    _scene->Start();
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

MatrixManager *AppDelegate::GetMatrixManager()
{
    return _matrixManager;
}

void AppDelegate::InitializeCubism()
{
    // 一个窗口对应一个Cubism
    _cubismOption.LogFunction = LAppPal::PrintLn;
    _cubismOption.LoggingLevel = Csm::CubismFramework::Option::LogLevel_Verbose;
    Csm::CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);
    Csm::CubismFramework::Initialize();
}
