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

    void open();
    void loop();

    bool isRendering() const;
    void setIsRendering(bool isRendering);

public slots:
    void renderingDone() { m_isRendering = false; }

private:
    QQuickView *m_view;
    QuickItem *m_item;
    QQmlEngine *m_engine;
    bool m_isRendering;
};

#endif // MAINWINDOW_H
