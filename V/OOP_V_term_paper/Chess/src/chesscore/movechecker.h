#ifndef MOVECHECKER_H
#define MOVECHECKER_H

#include <QList>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;

class MoveChecker
{
public:
    explicit MoveChecker(BasicBoard *board);

    QList<QPoint> rawMoves(BasicPiece *piece);
    QList<QPoint> filterMoves(const QList<QPoint> &rawMoves, BasicPiece *piece);

private:
    // TODO это тоже должны быть шаблонные функции
    QList<QPoint> kingFilter(BasicPiece *king, const QList<QPoint> &rawMoves);
    QList<QPoint> queenFilter(BasicPiece *queen, const QList<QPoint> &rawMoves);
    QList<QPoint> bishopFilter(BasicPiece *bishop, const QList<QPoint> &rawMoves);
    QList<QPoint> knightFilter(BasicPiece *knight, const QList<QPoint> &rawMoves);
    QList<QPoint> rookFilter(BasicPiece *rook, const QList<QPoint> &rawMoves);
    QList<QPoint> pawnFilter(BasicPiece *pawn, const QList<QPoint> &rawMoves);

private:
    BasicBoard *m_board;
};

#endif // MOVECHECKER_H
