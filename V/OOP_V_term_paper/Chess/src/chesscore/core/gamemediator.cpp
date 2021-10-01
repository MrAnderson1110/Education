#include "gamemediator.h"
#include "mover.h"
#include "selector.h"
#include "movechecker.h"

#include "../gui/basicboard.h"

#define UNDEFINED_GEOMETRY QRectF(-1, -1, 0, 0)

GameMediator::GameMediator(BasicBoard *board)
    : m_board(board)
    , m_mover(new Mover(board))
    , m_selector(new Selector(board))
    , m_moveChecker(new MoveChecker(board))
{

}

GameMediator::~GameMediator()
{
    delete m_moveChecker;
    delete m_selector;
    delete m_mover;
}

void GameMediator::startMove(BasicPiece *piece)
{
    QList<QPoint> moves = m_moveChecker->filteredMoves(piece);
    m_selector->updateSelection(piece, moves);
    m_selector->updateHover(piece->geometry());
    m_mover->startMove(piece);
}

void GameMediator::move(BasicPiece *piece, const QRectF &geometry)
{
    m_selector->updateHover(geometry);
    m_mover->move(piece, geometry);
}

void GameMediator::finishMove(BasicPiece *piece)
{
    QPoint finishPoint = m_selector->hoveredPoint();
    QList<QPoint> moves = m_moveChecker->filteredMoves(piece);

    if(!moves.contains(finishPoint)) {
        m_mover->resetPosition(piece);
        return;
    }

    m_mover->finishMove(piece);
    clearSelection();
}

void GameMediator::clearSelection()
{
    m_selector->updateSelection(nullptr);
    m_selector->updateHover(UNDEFINED_GEOMETRY);
}

