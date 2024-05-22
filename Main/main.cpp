#include <GL/glew.h> // 尽量放在开头
#include <QtWidgets/qapplication.h>

#include <AppDelegate.hpp>
#include <Config.hpp>
#include <QtCore/qcoreapplication.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AppDelegate::GetInstance()->Initialize();

    AppDelegate::GetInstance()->Run();

    // 自动销毁
    QObject::connect(&app, &QCoreApplication::aboutToQuit, []()
                     { AppDelegate::ReleaseInstance(); });

    app.exec();
    return 0;
}