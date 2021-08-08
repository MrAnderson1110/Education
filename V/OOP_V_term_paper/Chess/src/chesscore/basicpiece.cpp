#include "basicpiece.h"
#include "basicgridcell.h"
#include "basicboard.h"
#include "mover.h"

BasicPiece::BasicPiece(QQuickItem *parent)
    : GraphicItem(parent)
    , m_board(nullptr)
    , m_command(Black)
    , m_type(Pawn)
    , m_onFight(false)
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

bool BasicPiece::onFight() const
{
    return m_onFight;
}

void BasicPiece::setOnFight(bool enable)
{
    if(m_onFight == enable)
        return;

    m_onFight = enable;
    emit onFightChanged(m_onFight);
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

bool BasicPiece::canMove(int row, int column)
{
    BasicGridCell *cell = board()->cell(row, column);    
    if(!cell)
        return false;

    BasicPiece *piece = cell->piece();
    return !piece || (piece != nullptr && piece->command() != command());
}
