#include "gameobserver.h"
#include "basicboard.h"
#include "mover.h"
#include "selector.h"
#include "movechecker.h"

#define UNDEFINED_GEOMETRY QRectF(-1, -1, 0, 0)

GameObserver::GameObserver(BasicBoard *board)
    : m_board(board)
    , m_mover(new Mover(board))
    , m_selector(new Selector(board))
    , m_moveChecker(new MoveChecker(board))
{

}

GameObserver::~GameObserver()
{
    delete m_moveChecker;
    delete m_selector;
    delete m_mover;
}

void GameObserver::startMove(BasicPiece *piece)
{
    QList<QPoint> moves = m_moveChecker->rawMoves(piece);
    m_selector->updateSelection(piece, moves);
    m_selector->updateHover(piece->geometry());
    m_mover->startMove(piece);
}

void GameObserver::move(BasicPiece *piece, const QRectF &geometry)
{
    m_selector->updateHover(geometry);
    m_mover->move(piece, geometry);
}

void GameObserver::finishMove(BasicPiece *piece)
{
    m_mover->finishMove(piece);
    clearSelection();
}

void GameObserver::clearSelection()
{
    m_selector->updateSelection(nullptr);
    m_selector->updateHover(UNDEFINED_GEOMETRY);
}

