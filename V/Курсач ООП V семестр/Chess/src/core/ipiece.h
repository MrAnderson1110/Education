#ifndef PIECE_H
#define PIECE_H

#include <QObject>

/*
 * Базовый класс для представления фигуры на доске
 * Содержит базовые методы фигуры: ее тип, позиция на доске и пр.
 * Содержит стратегию фигуры для ее движения по доске
 */

class Piece : public QObject
{
    Q_OBJECT
public:
    enum PieceType {
        Undefined = -1,     // Неопределенный тип, на случай возникновения ошибок
        King,
        Queen,
        Bishop,
        Knife,
        Rook,
        Pawn
    };
    explicit Piece(QObject *parent = nullptr);

private:
};

#endif // PIECE_H
