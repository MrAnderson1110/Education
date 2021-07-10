#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QQuickItem>

#include "chesscore_global.h"

/*
 * Класс, представляющий модель шахмотной доски.
 * Содержит объекты клеток доски и фигур, а также управляет временем жизни этих объектов
 * Содержит методы для манипуляции фигурами на доске, а также методы доступа к клеткам доски и фигурам
 */

class IPiece;
class Mover;

class CHESSCORE_EXPORT ChessBoard : public QQuickItem
{
    Q_OBJECT

public:
    explicit ChessBoard(QQuickItem *parent = nullptr);

    void componentComplete();

private:
    QList<IPiece *> m_pieces;
    Mover *m_mover;
};

#endif // CHESSBOARD_H
