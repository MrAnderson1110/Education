#ifndef MOVER_H
#define MOVER_H

#include <QRectF>

#include "chesscore_global.h"

class BasicGridCell;
class BasicPiece;
class BasicBoard;

class CHESSCORE_EXPORT Mover
{
public:
    explicit Mover(BasicBoard *board);

    void startMove(BasicPiece *piece);
    void move(BasicPiece *piece, const QRectF &geometry);
    void finishMove(BasicPiece *piece);
    void resetPosition(BasicPiece *piece);

private:
    BasicBoard *m_board;
    BasicPiece *m_movingPiece;
    BasicGridCell *m_preMovingCell;
};

#endif // MOVER_H
