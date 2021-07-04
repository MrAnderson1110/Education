#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QUrl>

/*
 * Псевдо окно приложения.
 * Так как MainWindow создается из QML, данный класс выполняет функцию "инициализатора" и точки остчета приложения
 * Класс содержит глобальные объекты приложения (Шахматная доска, TCP-сокеты и пр.), а также методы изх взаимодействия
 * между собой
 */

class QQmlApplicationEngine;
class BoardModel;

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);

    QQmlApplicationEngine *qmlEngine() const;
    QUrl appUrl() const;

private:
    QQmlApplicationEngine *m_engine;
    QUrl m_appUrl;
};

#endif // MAINWINDOW_H
