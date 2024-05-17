#include <GL/glew.h> // 尽量放在开头
#include <widgets/impl/Scene.hpp>
#include <Config.hpp>
#include <utils/Log.hpp>
#include <QtWidgets/qapplication.h>

#include <CubismFramework.hpp>
#include <live2d/LAppPal.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!Config::Initialize())
    {
        return -1;
    }

    Scene scene;

    scene.show();

    scene.resize(Config::GetSceneWidth(), Config::GetSceneHeight());

    app.exec();

    ModelManager::ReleaseInstance();
    Csm::CubismFramework::Dispose();

    return 0;
}