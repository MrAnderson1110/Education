#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    MainWindow window;
    QQmlApplicationEngine *engine = window.qmlEngine();
    QUrl appUrl = window.appUrl();
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     &app, [appUrl](QObject *obj, const QUrl &objUrl) {
        if (!obj && appUrl == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    return app.exec();
}
