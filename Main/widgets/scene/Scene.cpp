#include "Scene.hpp"
#include <Config.hpp>

#include <LAppPal.hpp>

Scene::Scene(ModelManager *manager) : _modelManager(manager)
{
    setWindowFlags(Qt::FramelessWindowHint);          // 无边框
    setAttribute(Qt::WA_TranslucentBackground, true); // 透明背景
    setAttribute(Qt::WA_AlwaysStackOnTop, true);      // 置于最上层
}

Scene::~Scene()
{
    _modelManager = nullptr;
    this->killTimer(_timer);
}

void Scene::initializeGL()
{

    // 设置当前 opengl 上下文为 _scene
    makeCurrent();

    resize(Config::GetSceneWidth(), Config::GetSceneHeight());

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

    glViewport(0, 0, Config::GetSceneWidth(), Config::GetSceneHeight());

    // 必须在CubismFramework初始化后调用
    _modelManager->SetModel(Config::GetModelName().c_str());

    _timer = startTimer(1000 / 60);
}

void Scene::timerEvent(QTimerEvent *event)
{
    update(); // 刷新窗口缓冲
}

void Scene::paintGL()
{
    LAppPal::UpdateTime();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);

    // modelManager updateModel
    _modelManager->UpdateModel(width(), height());
}

void Scene::resizeGL(int w, int h)
{
    // 用户修改长宽的时候会被自动调用，不存在多线程竞争的问题
    int windowWidth = Config::GetSceneWidth();
    int windowHeight = Config::GetSceneHeight();

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
