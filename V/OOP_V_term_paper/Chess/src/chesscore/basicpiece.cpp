#include "basicpiece.h"
#include "basicgridcell.h"
#include "basicboard.h"
#include "mover.h"

BasicPiece::BasicPiece(QQuickItem *parent)
    : GraphicItem(parent)
    , m_board(nullptr)
    , m_command(Command::Undefined)
    , m_type(Type::Undefined)
    , m_moved(false)
{

}

BasicPiece::Command BasicPiece::command() const
{
    return m_command;
}

void BasicPiece::setCommand(Command newCommand)
{
    if (m_command == newCommand)
        return;

    m_command = newCommand;
    emit commandChanged(m_command);
}

BasicPiece::Type BasicPiece::type() const
{
    return m_type;
}

void BasicPiece::setBoard(BasicBoard *board)
{
    if(m_board == board)
        return;

    m_board = board;
}

void BasicPiece::setType(Type newType)
{
    if (m_type == newType)
        return;

    m_type = newType;
    emit typeChanged(m_type);
}

void BasicPiece::startMove()
{
    m_board->mover()->startMove(this);
}

void BasicPiece::move(const QRect &geometry)
{
    m_board->mover()->move(this, geometry);
}

void BasicPiece::finishMove()
{
    m_board->mover()->finishMove(this);
}

bool BasicPiece::moved() const
{
    return m_moved;
}

void BasicPiece::setMoved(bool newMoved)
{
    m_moved = newMoved;
}
