#include <QGuiApplication>
#include <QSurfaceFormat>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    MainWindow win;
    win.open();

    return app.exec();
}
