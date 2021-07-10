#include "ipiece.h"

IPiece::IPiece(QQuickItem *parent)
    : QQuickItem(parent)
    , m_type(Undefined)
    , m_board(nullptr)
    , m_currentPos(0, 0)
    , m_pinnedPos(0, 0)
{

}

IPiece::PieceType IPiece::type() const
{
    return m_type;
}

IPiece::Position IPiece::currentPosition() const
{
    return m_currentPos;
}

IPiece::Position IPiece::pinnedPosition() const
{
    return m_pinnedPos;
}

void IPiece::setType(PieceType type)
{
    if(m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

void IPiece::setCurrentPosition(Position pos)
{
    m_currentPos = pos;
}

void IPiece::setPinnedPosition(Position pos)
{
    m_pinnedPos = pos;
}

void IPiece::setBoard(ChessBoard *board)
{
    if(m_board == board)
        return;

    m_board = board;
    emit boardChanged(m_board);
}

void IPiece::startMove()
{

}

void IPiece::move()
{

}

void IPiece::finishMove()
{

}

ChessBoard *IPiece::board() const
{
    return m_board;
}
