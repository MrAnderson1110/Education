#include "mainwindow.h"
#include "quickitem.h"
#include <QQuickView>
#include <QQmlEngine>

MainWindow::MainWindow(QObject *parent) :
    QObject(parent)
  , m_engine(new QQmlEngine)
  , m_isRendering(false)
{
    m_view = new QQuickView(m_engine, nullptr);
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->setSource(QUrl("qrc:/main.qml"));

    m_item = m_view->rootObject()->findChild<QuickItem *>();

    connect(m_item, &QuickItem::updateDone, this, &MainWindow::renderingDone);
}

void MainWindow::open()
{
    m_view->show();
    loop();
}

void MainWindow::loop()
{
    while (true) {
        m_isRendering = true;
        m_item->update();
        while (m_isRendering)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
    }
}

bool MainWindow::isRendering() const
{
    return m_isRendering;
}

void MainWindow::setIsRendering(bool isRendering)
{
    m_isRendering = isRendering;
}
