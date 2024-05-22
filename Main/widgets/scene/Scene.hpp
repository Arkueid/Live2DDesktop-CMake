#pragma once
#include <model/impl/ModelManager.hpp>
#include <QtWidgets/qopenglwidget.h>

#include <QtGui/qevent.h>

class Scene: public QOpenGLWidget
{
public:
    Scene();
    ~Scene();
    void Popup();
    void SetStayOnTop(bool on);
    void Start();
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
    void setMouseClickEnable(bool on);
private:
    int _timer;
    QCursor _cursor;
};

