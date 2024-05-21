#include "AppDelegate.hpp"

#include <Config.hpp>
#include <utils/Log.hpp>
#include <QtWidgets/qapplication.h>

static AppDelegate *_instance = nullptr;

AppDelegate::AppDelegate() : _scene(nullptr), _modelManager(nullptr), _trayIcon(nullptr)
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

    _modelManager = new ModelManager();

    _scene = new Scene(_modelManager);

    _trayIcon = new TrayIcon(_scene);

    InitializeCubism();
}

void AppDelegate::Release()
{
    if (_trayIcon != nullptr)
        delete _trayIcon;

    if (_scene != nullptr)
    {
        _scene->hide();

        delete _scene;
    }
    if (_modelManager != nullptr)
        delete _modelManager;

    _scene = nullptr;
    _modelManager = nullptr;

    Csm::CubismFramework::Dispose();

    qApp->exit();
}

void AppDelegate::Run()
{
    assert(_scene != nullptr);
    assert(_trayIcon != nullptr);
    assert(_modelManager != nullptr);

    _trayIcon->Show();
    _scene->show();
}

IModelManager *AppDelegate::GetModelManager()
{
    return _modelManager;
}

Scene *AppDelegate::GetScene()
{
    return _scene;
}

void AppDelegate::InitializeCubism()
{
    // 一个窗口对应一个Cubism
    _cubismOption.LogFunction = LAppPal::PrintMessage;
    _cubismOption.LoggingLevel = Csm::CubismFramework::Option::LogLevel_Verbose;
    Csm::CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);
    Csm::CubismFramework::Initialize();
}
