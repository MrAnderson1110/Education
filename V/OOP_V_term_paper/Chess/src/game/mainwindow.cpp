#include "mainwindow.h"

#include <QQmlApplicationEngine>
#include <QQuickView>

#include <ChessBoard>

MainWindow::MainWindow(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
    , m_view(nullptr)
    , m_board(nullptr)
{
    m_engine->load(MAIN_QML);
//    m_engine->addImportPath(APP_DIR);
    // Проверяем, что root существует
//    QObjectList roots = m_engine->rootObjects();
//    Q_ASSERT(roots.size() == 1);

//    // Так как root только один, берем первый из списка
//    m_view = qobject_cast<QQuickView *>(roots.first());
//    Q_ASSERT(m_view != nullptr);

//    m_board = m_view->findChild<ChessBoard *>("board");
}
