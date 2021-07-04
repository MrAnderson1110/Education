#include "mainwindow.h"

#include <QQmlApplicationEngine>

#include <BoardModel>

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
    , m_engine(new QQmlApplicationEngine)
    , m_appUrl(QStringLiteral("qrc:/main.qml"))
{
    m_engine->load(m_appUrl);
}

QQmlApplicationEngine *MainWindow::qmlEngine() const
{
    return m_engine;
}

QUrl MainWindow::appUrl() const
{
    return m_appUrl;
}
