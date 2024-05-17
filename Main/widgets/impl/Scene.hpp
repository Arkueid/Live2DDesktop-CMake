#pragma once
#include <model/impl/ModelManager.hpp>
#include <QtWidgets/qopenglwidget.h>

#include <live2d/LAppAllocator.hpp>

class Scene: public QOpenGLWidget
{
public:
    LAppAllocator _cubismAllocator;             ///< メモリのアロケーター
    Csm::CubismFramework::Option _cubismOption; ///< CubismFrameworkに関するオプション
    Scene();
    ~Scene();
protected:
    void initializeGL();
    void timerEvent(QTimerEvent *event);
    void paintGL();
    void resizeGL(int w, int h);
};

