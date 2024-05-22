#include "Scene.hpp"
#include <Config.hpp>

#include <live2d/LAppPal.hpp>
#include <AppDelegate.hpp>
#include <utils/log/Log.hpp>

#include <QtGui/qcursor.h>

Scene::Scene()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); // 无边框
    setAttribute(Qt::WA_TranslucentBackground, true);   // 透明背景

    _cursor.setShape(Qt::CursorShape::OpenHandCursor);

    setCursor(_cursor);
}

Scene::~Scene()
{
    this->killTimer(_timer);
}

void Scene::Popup()
{
    setWindowFlag(Qt::WindowStaysOnTopHint, true);
    show();
    setWindowFlag(Qt::WindowStaysOnTopHint, false);
    show();
}

void Scene::SetStayOnTop(bool on)
{
    setWindowFlag(Qt::WindowStaysOnTopHint, on);
    show();
}

void Scene::Start()
{
    show();
}

void Scene::initializeGL()
{
    // 设置当前 opengl 上下文为 _scene
    makeCurrent();

    resize(Config::GetSceneWidth(), Config::GetSceneHeight());

    if (glewInit() != GLEW_OK)
    {
        Info("Can't initilize glew.");
    }
    // テクスチャサンプリング設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // 透過設定
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, Config::GetSceneWidth(), Config::GetSceneHeight());

    // 必须在CubismFramework初始化后调用
    AppDelegate::GetInstance()->GetModelManager()->SetModel(Config::GetModelName().c_str());

    _timer = startTimer(1000 / 60);
}

void Scene::paintGL()
{
    LAppPal::UpdateTime();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);

    // modelManager updateModel
    AppDelegate::GetInstance()->GetModelManager()->UpdateModel(width(), height());
}

void Scene::resizeGL(int w, int h)
{
    // 用户修改长宽的时候会被自动调用，不存在多线程竞争的问题
    int windowWidth = Config::GetSceneWidth();
    int windowHeight = Config::GetSceneHeight();

    glViewport(0, 0, windowWidth, windowHeight);

    if ((windowWidth != w || windowHeight != h) && w > 0 && h > 0)
    {
        // サイズを保存しておく
        windowWidth = w;
        windowHeight = h;

        // ビューポート変更
        glViewport(0, 0, w, h);
    }

    AppDelegate::GetInstance()->GetMatrixManager()->AdaptToSceneSize();
}

void Scene::timerEvent(QTimerEvent *event)
{
    int x = QCursor::pos().x();
    int y = QCursor::pos().y();

    setMouseClickEnable(AppDelegate::GetInstance()->GetMouseActionManager()->IsHover(x, y));

    AppDelegate::GetInstance()->GetMouseActionManager()->OnMovePerFrame(x, y, 0);
    update(); // 刷新窗口缓冲
}

void Scene::mousePressEvent(QMouseEvent *event)
{
    AppDelegate::GetInstance()->GetMouseActionManager()->OnClickStart(event->x(), event->y(), event->button());
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    AppDelegate::GetInstance()->GetMouseActionManager()->OnClickEnd(event->x(), event->y(), event->button());
}

void Scene::mouseDoubleClickEvent(QMouseEvent *event)
{
    AppDelegate::GetInstance()->GetMouseActionManager()->OnDoubleClick(event->x(), event->y(), event->button());
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    AppDelegate::GetInstance()->GetMouseActionManager()->OnMove(event->x(), event->y(), event->buttons());
}

void Scene::enterEvent(QEvent *event)
{
    QMouseEvent *e = (QMouseEvent *)event;
    AppDelegate::GetInstance()->GetMouseActionManager()->OnEnter(e->x(), e->y());
}

void Scene::leaveEvent(QEvent *event)
{
    QMouseEvent *e = (QMouseEvent *)event;
    AppDelegate::GetInstance()->GetMouseActionManager()->OnLeave(e->x(), e->y());
}

void Scene::setMouseClickEnable(bool on)
{
#ifdef Q_OS_LINUX
    if (on)
    {
        XRectangle rect;
        rect.x = 0;
        rect.y = 0;
        rect.width = width();
        rect.height = height();
        XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0,
                                0, &rect, 1, ShapeSet, YXBanded);
    }
    else
    {
        XShapeCombineRectangles(QX11Info::display(), winId(), ShapeInput, 0,
                                0, NULL, 0, ShapeSet, YXBanded);
    }
#endif
#ifdef Q_OS_WIN
    if (on)
    {
        SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) & ~WS_EX_TRANSPARENT // ignore all events（except WM_PAINT）
                                                      | WS_EX_LAYERED);                                          
    }
    else
    {
        SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) | WS_EX_TRANSPARENT
                                                      | WS_EX_LAYERED);                                         
    }
#endif
}
