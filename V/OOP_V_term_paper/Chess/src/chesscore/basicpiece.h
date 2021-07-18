#ifndef BASICPIECE_H
#define BASICPIECE_H

#include "graphicitem.h"
#include "chesscore_global.h"

class BasicBoard;

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
        Knight,
        Bishop,
        Rook,
        Pawn
    };
    Q_ENUM(Type)

    explicit BasicPiece(QQuickItem *parent = nullptr);

    Command command() const;
    Type type() const;

    void setBoard(BasicBoard *board);

public slots:
    void setCommand(Command newCommand);
    void setType(Type newType);

    void startMove();
    void move(const QRect &geometry);
    void finishMove();

signals:
    void commandChanged(Command);
    void typeChanged(Type);

private:
    BasicBoard *m_board;
    Command m_command;
    Type m_type;
};

#endif // BASICPIECE_H
