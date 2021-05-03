#include <QGuiApplication>
#include <QSurfaceFormat>
#include "mainwindow.h"
#include "quickitem.h"
#include <glvector.h>
#include <glmatrix.h>

int main(int argc, char *argv[])
{

    QGuiApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<QuickItem>("opengl_lib", 1, 0, "QuickItem");

    MainWindow win;
    win.open();


    return app.exec();


    return 0;
}
