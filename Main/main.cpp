#include <stb_image.h>
#include <GL/glew.h>  // 尽量放在开头
#include "LAppDefine.hpp"
#include "LAppAllocator.hpp"
#include "LAppTextureManager.hpp"
#include "LAppPal.hpp"
#include "TouchManager.hpp"
#include "CubismUserModelExtend.hpp"
#include "CubismSampleViewMatrix.hpp"
#include "MouseActionManager.hpp"

#include <CubismFramework.hpp>
#include <CubismDefaultParameterId.hpp>
#include <CubismModelSettingJson.hpp>
#include <Model/CubismUserModel.hpp>
#include <Physics/CubismPhysics.hpp>
#include <Rendering/OpenGL/CubismRenderer_OpenGLES2.hpp>
#include <Utils/CubismString.hpp>
#include <Math/CubismViewMatrix.hpp>

#include <QtWidgets/qapplication.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qopenglwidget.h> 

static const Csm::csmChar *_modelDirectoryName = "Hiyori";

static Csm::CubismUserModel *_userModel; ///< ユーザーが実際に使用するモデル

static Csm::CubismFramework::Option _cubismOption; ///< CubismFrameworkに関するオプション
static LAppAllocator _cubismAllocator;             ///< メモリのアロケーター

static LAppTextureManager *_textureManager; ///< テクスチャの管理

static std::string _currentModelDirectory;      ///< 現在のモデルのディレクトリ名
const Csm::csmChar *_currentModelDirectoryChar; ///< 現在のモデルのディレクトリ名のconst csmCharポインタ型

int windowWidth = 500, windowHeight = 400; ///< ウィンドウサイズの保存

class GLWin : public QOpenGLWidget
{
public:
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

        MouseActionManager::GetInstance()->Initialize(windowWidth, windowHeight);

        LoadModel(_modelDirectoryName);

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

        UpdateModel();
    }
    void resizeGL(int w, int h)
    {
        glViewport(0, 0, windowWidth, windowHeight);

        if ((windowWidth != w || windowHeight != h) && w > 0 && h > 0)
        {
            MouseActionManager::GetInstance()->ViewInitialize(w, h);
            // サイズを保存しておく
            windowWidth = w;
            windowHeight = h;

            // ビューポート変更
            glViewport(0, 0, w, h);
        }
    }
    void UpdateModel()
    {
        CubismUserModelExtend *model = static_cast<CubismUserModelExtend *>(_userModel);

        Csm::CubismMatrix44 projection;
        // 念のため単位行列に初期化
        projection.LoadIdentity();

        if (model->GetModel()->GetCanvasWidth() > 1.0f && width() < height())
        {
            // 横に長いモデルを縦長ウィンドウに表示する際モデルの横サイズでscaleを算出する
            model->GetModelMatrix()->SetWidth(2.0f);
            projection.Scale(1.0f, static_cast<float>(width()) / static_cast<float>(height()));
        }
        else
        {
            projection.Scale(static_cast<float>(height()) / static_cast<float>(width()), 1.0f);
        }

        // 以下两个函数访问权需要从 private 变为 public 
        model->ModelParamUpdate();
        model->Draw(projection); 
    }
    void Release()
    {
        // レンダラの解放
        _userModel->DeleteRenderer();

        // モデルデータの解放
        delete _userModel;

        // テクスチャマネージャーの解放
        delete _textureManager;

        MouseActionManager::ReleaseInstance();

        // Cubism SDK の解放
        Csm::CubismFramework::Dispose();
    }

    void SetAssetDirectory(const std::string &path)
    {
        _currentModelDirectory = path;
    }

    void LoadModel(const std::string modelDirectoryName)
    {
        // モデルのディレクトリを指定
        SetAssetDirectory(LAppDefine::ResourcesPath + modelDirectoryName + "/");

        // モデルデータの新規生成
        _userModel = new CubismUserModelExtend(modelDirectoryName, _currentModelDirectory);

        // モデルデータの読み込み及び生成とセットアップを行う
        static_cast<CubismUserModelExtend *>(_userModel)->SetupModel();

        MouseActionManager::GetInstance()->SetUserModel(_userModel);
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
    GLWin win;
    win.show();
    return app.exec();
}