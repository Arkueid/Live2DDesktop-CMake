#include <QtWidgets/qopenglwidget.h>


class Scene: public QOpenGLWidget
{
public:
    Scene();
    ~Scene();
protected:
    void initializeGL();
    void timerEvent(QTimerEvent *event);
    void paintGL();
    void resizeGL(int w, int h);
};

