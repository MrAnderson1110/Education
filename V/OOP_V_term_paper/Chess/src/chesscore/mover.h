#ifndef MOVER_H
#define MOVER_H

#include <QObject>

#include "basicpiece.h"
#include "chesscore_global.h"

class BasicGridCell;
class BasicBoard;

class CHESSCORE_EXPORT Mover : public QObject
{
    Q_OBJECT
public:
    explicit Mover(BasicBoard *board, QObject *parent = nullptr);

    void startMove(BasicPiece *piece);
    void move(BasicPiece *piece, const QRect &geometry);
    void finishMove(BasicPiece *piece);

    void updateSelection(BasicPiece *piece);

private:
    QList<QPoint> getWhiteMoves(BasicPiece *piece) const;
    QList<QPoint> getBlackMoves(BasicPiece *piece) const;

private:
    BasicBoard *m_board;
    BasicPiece *m_movingPiece;
    BasicGridCell *m_preMovingCell;
    QList<BasicGridCell *> m_selectionList;
};

#endif // MOVER_H
