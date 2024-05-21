#pragma once
#include <model/impl/ModelManager.hpp>
#include <QtWidgets/qopenglwidget.h>


class Scene: public QOpenGLWidget
{
public:
    Scene(ModelManager *manager);
    ~Scene();
protected:
    void initializeGL();
    void timerEvent(QTimerEvent *event);
    void paintGL();
    void resizeGL(int w, int h);
private:
    ModelManager *_modelManager;
    int _timer;
};

