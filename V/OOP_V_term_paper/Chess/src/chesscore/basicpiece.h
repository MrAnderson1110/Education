#ifndef BASICPIECE_H
#define BASICPIECE_H

#include "graphicitem.h"
#include "chesscore_global.h"

class BasicGridCell;

class CHESSCORE_EXPORT BasicPiece : public GraphicItem
{
    Q_OBJECT
    Q_PROPERTY(Command command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)

public:
    enum class Command { Undefined, White, Black };
    Q_ENUM(Command)

    enum class Type
    {
        Undefined,
        King,
        Queen,
        Knife,
        Bishop,
        Rook,
        Pawn
    };
    Q_ENUM(Type)

    explicit BasicPiece(QQuickItem *parent = nullptr);

    Command command() const;
    Type type() const;

public slots:
    void setCommand(Command newCommand);
    void setType(Type newType);

signals:
    void commandChanged(Command);
    void typeChanged(Type);

private:
    Command m_command;
    Type m_type;
};

#endif // BASICPIECE_H
