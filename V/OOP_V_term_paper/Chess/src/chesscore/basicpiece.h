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
    Q_PROPERTY(bool movable READ movable WRITE setMovable NOTIFY movableChanged)

public:
    enum Command
    {
        White = 1,
        Black = -1
    };
    Q_ENUM(Command)

    enum Type
    {
        King,
        Queen,
        Knight,
        Bishop,
        Rook,
        Pawn
    };
    Q_ENUM(Type)

    explicit BasicPiece(QQuickItem *parent = nullptr);

    bool movable() const;
    Command command() const;
    Type type() const;
    BasicBoard *board() const;

    void setMovable(bool newMovable);
    void setCommand(Command newCommand);
    void setBoard(BasicBoard *board);
    void setType(Type newType);


public slots:
    virtual void startMove();
    virtual void move(const QRectF &geometry);
    virtual void finishMove();

signals:
    void movableChanged(bool);
    void commandChanged(Command);
    void typeChanged(Type);

private:
    BasicBoard *m_board;
    Command m_command;
    Type m_type;
    bool m_movable;
};

#endif // BASICPIECE_H
