#include "mainwindow.h"
#include "quickitem.h"
#include "gllight.h"
#include <QQuickView>
#include <QQmlEngine>
#include <QGuiApplication>

MainWindow::MainWindow(QObject *parent) :
    QObject(parent)
  , m_engine(new QQmlEngine)
{
    qmlRegisterType<QuickItem>("opengl_lib", 1, 0, "QuickItem");
    qmlRegisterType<GLLight>("opengl_lib", 1, 0, "GLLight");

    m_view = new QQuickView(m_engine, nullptr);
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->setSource(QUrl("qrc:/main.qml"));

    m_item = m_view->rootObject()->findChild<QuickItem *>();
}

void MainWindow::open()
{
    m_view->show();
    m_item->update();
}
