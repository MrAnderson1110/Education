#ifndef IPIECE_H
#define IPIECE_H

#include <QQuickItem>

#include "chesscore_global.h"
/*
 * Базовый класс для представления фигуры на доске
 * Содержит базовые методы фигуры: ее тип, позиция на доске и пр.
 * Содержит стратегию фигуры для ее движения по доске
 */

class ChessBoard;

class CHESSCORE_EXPORT IPiece : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(PieceType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(ChessBoard *board READ board WRITE setBoard NOTIFY boardChanged)

public:
    struct Position
    {
        Position(int xPos, int yPos)
            : x(xPos), y(yPos) {}
        int x;
        int y;
    };

    enum PieceType {
        Undefined = -1,     // Неопределенный тип, на случай возникновения ошибок
        King,
        Queen,
        Bishop,
        Knife,
        Rook,
        Pawn
    };Q_ENUM(PieceType)

    explicit IPiece(QQuickItem *parent = nullptr);

    PieceType type() const;
    Position currentPosition() const;
    Position pinnedPosition() const;
    ChessBoard *board() const;

public slots:
    void setType(PieceType type);
    void setCurrentPosition(Position pos);
    void setPinnedPosition(Position pos);
    void setBoard(ChessBoard *board);

    void startMove();
    void move();
    void finishMove();

signals:
    void typeChanged(PieceType);
    void boardChanged(ChessBoard *);

private:
    PieceType m_type;
    ChessBoard *m_board;
    Position m_currentPos;
    Position m_pinnedPos;
};

#endif // IPIECE_H
