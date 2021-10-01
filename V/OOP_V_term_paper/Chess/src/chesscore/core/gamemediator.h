#ifndef GAMEMEDIATOR_H
#define GAMEMEDIATOR_H

#include <QRectF>
#include <memory>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;
class Selector;
class Mover;
class MoveChecker;
class VisitorsHandler;

class CHESSCORE_EXPORT GameMediator
{
public:
    explicit GameMediator(BasicBoard *board);
    ~GameMediator();

    void startMove(BasicPiece *piece);
    void move(BasicPiece *piece, const QRectF &geometry);
    void finishMove(BasicPiece *piece);

    void clearSelection();

private:
    BasicBoard *m_board;
    Mover *m_mover;
    Selector *m_selector;
    MoveChecker *m_moveChecker;
    VisitorsHandler *handler;
};

#endif // GAMEMEDIATOR_H
