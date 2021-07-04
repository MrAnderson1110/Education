#ifndef CELL_H
#define CELL_H

#include <QObject>

/*
 * Класс клетки шахматной доски.
 * Содержит информацию о наличии фигуры в данной позиции.
 * Предоставляет доступ к фигуре, которую содержит
 */

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QObject *parent = nullptr);

private:
};

#endif // CELL_H
