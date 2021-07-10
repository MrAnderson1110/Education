#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QObject>

/*
 * Класс, представляющий модель шахмотной доски.
 * Содержит объекты клеток доски и фигур, а также управляет временем жизни этих объектов
 * Содержит методы для манипуляции фигурами на доске, а также методы доступа к клеткам доски и фигурам
 */

class Cell;

class BoardModel : public QObject
{
    Q_OBJECT

public:
    explicit BoardModel(QObject *parent = nullptr);

private:
};

#endif // BOARDMODEL_H
