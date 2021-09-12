#include "basicpiece.h"
#include "basicgridcell.h"
#include "basicboard.h"
#include "gameobserver.h"

BasicPiece::BasicPiece(QQuickItem *parent)
    : GraphicItem(parent)
    , m_board(nullptr)
    , m_command(Black)
    , m_type(Pawn)
    , m_movable(true)
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

void BasicPiece::setType(Type newType)
{
    if (m_type == newType)
        return;

    m_type = newType;
    emit typeChanged(m_type);
}

BasicBoard *BasicPiece::board() const
{
    return m_board;
}

void BasicPiece::setBoard(BasicBoard *board)
{
    if(m_board == board)
        return;

    m_board = board;
}

void BasicPiece::startMove()
{
    m_board->observer()->startMove(this);
}

void BasicPiece::move(const QRectF &geometry)
{
    m_board->observer()->move(this, geometry);
}

void BasicPiece::finishMove()
{
    m_board->observer()->finishMove(this);
}

bool BasicPiece::movable() const
{
    return m_movable;
}

void BasicPiece::setMovable(bool newMovable)
{
    if (m_movable == newMovable)
        return;

    m_movable = newMovable;
    emit movableChanged(m_movable);
}
