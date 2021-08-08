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
    void finishCastlingMove(BasicPiece *piece);

private:
    BasicBoard *m_board;
    BasicPiece *m_movingPiece;
    BasicGridCell *m_preMovingCell;
    BasicGridCell *m_hoveredCell;
    QList<BasicGridCell *> m_selectionList;
};

#endif // MOVER_H
