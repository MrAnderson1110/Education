#ifndef VISITORSHANDLER_H
#define VISITORSHANDLER_H

#include "../chesscore_global.h"

class BasicBoard;
class PremoveVisitor;
class MoveVisitor;
class PostmoveVisitor;
class BoardCellVisitor;

class CHESSCORE_EXPORT VisitorsHandler
{
public:
    VisitorsHandler();

    void premoveVisit();
    void moveVisit();
    void postMoveVisit();

private:
    BasicBoard *m_board;
    PremoveVisitor *m_premoveVisitor;
    MoveVisitor *m_moveVisitor;
    PostmoveVisitor *m_postmoveVisitor;
    BoardCellVisitor *m_cellVisitor;
};

#endif // VISITORSHANDLER_H
