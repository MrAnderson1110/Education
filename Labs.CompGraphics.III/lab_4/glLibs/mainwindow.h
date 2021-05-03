#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

class QuickItem;
class QQuickView;
class QQmlEngine;

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);

public slots:
    void open();

private:
    QQuickView *m_view;
    QuickItem *m_item;
    QQmlEngine *m_engine;
};

#endif // MAINWINDOW_H
