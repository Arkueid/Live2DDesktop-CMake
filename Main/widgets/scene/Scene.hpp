#pragma once
#include <model/impl/ModelManager.hpp>
#include <QtWidgets/qopenglwidget.h>

#include <QtGui/qevent.h>

class Scene: QOpenGLWidget
{
public:
    Scene();
    ~Scene();
    void SetVisible(bool visible);
    /// @brief 开关鼠标点击事件，鼠标点击、拖动
    /// @param enable 
    void SetClickTransparentEnable(bool enable);
protected:
    void initializeGL();
    void timerEvent(QTimerEvent *event);
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    int _timer;
    QCursor _cursor;
};

