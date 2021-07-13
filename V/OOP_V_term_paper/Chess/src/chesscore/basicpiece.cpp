#include "basicpiece.h"
#include "basicgridcell.h"

BasicPiece::BasicPiece(QQuickItem *parent)
    : GraphicItem(parent)
    , m_command(Command::Undefined)
    , m_type(Type::Undefined)
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
