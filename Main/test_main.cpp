#include <GL/glew.h> // 尽量放在开头
#include <stb_image.h>
#include "LAppDefine.hpp"
#include "LAppAllocator.hpp"
#include "LAppTextureManager.hpp"
#include "LAppPal.hpp"
#include "LAppModel.hpp"
#include "TouchManager.hpp"
#include "CubismSampleViewMatrix.hpp"
#include "MouseActionManager.hpp"

#include <CubismFramework.hpp>
#include <CubismDefaultParameterId.hpp>
#include <CubismModelSettingJson.hpp>
#include <Physics/CubismPhysics.hpp>
#include <Rendering/OpenGL/CubismRenderer_OpenGLES2.hpp>
#include <Utils/CubismString.hpp>
#include <Math/CubismViewMatrix.hpp>

#include <QtWidgets/qapplication.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qopenglwidget.h>

#include <model/impl/ModelManager.hpp>
#include <Config.hpp>

static const Csm::csmChar *_modelDirectoryName = "Hiyori";

static LAppModel *_userModel; ///< ユーザーが実際に使用するモデル

static Csm::CubismFramework::Option _cubismOption; ///< CubismFrameworkに関するオプション
static LAppAllocator _cubismAllocator;             ///< メモリのアロケーター

static std::string _currentModelDirectory; ///< 現在のモデルのディレクトリ名

int windowWidth = 500, windowHeight = 400; ///< ウィンドウサイズの保存

IModelManager *modelManager = nullptr;

class GLWin : public QOpenGLWidget
{
public:
    GLWin()
    {
        setWindowFlags(Qt::FramelessWindowHint);          // 无边框
        setAttribute(Qt::WA_TranslucentBackground, true); // 透明背景
        setAttribute(Qt::WA_AlwaysStackOnTop, true);      // 置于最上层
    }
    ~GLWin()
    {
        Release();
    }

protected:
    void initializeGL()
    {
        LAppPal::PrintLogLn("START");
        makeCurrent();

        if (glewInit() != GLEW_OK)
        {
            LAppPal::PrintLogLn("Can't initilize glew.");
        }
        // テクスチャサンプリング設定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // 透過設定
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0, 0, windowWidth, windowHeight);

        // Cubism SDK の初期化
        InitializeCubism();

        // MouseActionManager::GetInstance()->Initialize(windowWidth, windowHeight);

        // <live2d>
        modelManager = ModelManager::GetInstance();

        modelManager->SetModel(_modelDirectoryName);

        _userModel = modelManager->GetModel();
        // <live2d>

        startTimer(1000 / 60);
    }
    void timerEvent(QTimerEvent *event)
    {
        update();
    }
    void paintGL()
    {
        // 時間更新
        LAppPal::UpdateTime();

        // 画面の初期化
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0);

        modelManager->UpdateModel(width(), height());
    }
    void resizeGL(int w, int h)
    {
        glViewport(0, 0, windowWidth, windowHeight);

        if ((windowWidth != w || windowHeight != h) && w > 0 && h > 0)
        {
            // MouseActionManager::GetInstance()->ViewInitialize(w, h);
            // サイズを保存しておく
            windowWidth = w;
            windowHeight = h;

            // ビューポート変更
            glViewport(0, 0, w, h);
        }
    }
    void Release()
    {
        delete modelManager;

        // MouseActionManager::ReleaseInstance();

        // Cubism SDK の解放
        Csm::CubismFramework::Dispose();
    }

    void SetAssetDirectory(const std::string &path)
    {
        _currentModelDirectory = path;
    }

    void LoadModel(const std::string modelDirectoryName)
    {
    }

private:
    void InitializeCubism()
    {
        _cubismOption.LogFunction = LAppPal::PrintMessage;
        _cubismOption.LoggingLevel = Csm::CubismFramework::Option::LogLevel_Verbose;
        Csm::CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);
        Csm::CubismFramework::Initialize();
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Config::Initialize();
    GLWin win;
    win.show();
    return app.exec();
}