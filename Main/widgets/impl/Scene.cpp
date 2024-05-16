#include "Scene.hpp"

Scene::Scene()
{
    setWindowFlags(Qt::FramelessWindowHint);          // 无边框
    setAttribute(Qt::WA_TranslucentBackground, true); // 透明背景
    setAttribute(Qt::WA_AlwaysStackOnTop, true);      // 置于最上层
}

Scene::~Scene()
{
}

void Scene::initializeGL()
{
    makeCurrent();
    startTimer(1000 / 60);
}

void Scene::timerEvent(QTimerEvent *event)
{
    update(); // 刷新窗口缓冲
}

void Scene::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);

    // modelManager updateModel
}

void Scene::resizeGL(int w, int h)
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
