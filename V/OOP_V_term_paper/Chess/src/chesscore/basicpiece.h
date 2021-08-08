#ifndef BASICPIECE_H
#define BASICPIECE_H

#include "graphicitem.h"
#include "chesscore_global.h"

class BasicBoard;

class CHESSCORE_EXPORT BasicPiece : public GraphicItem
{
    Q_OBJECT
    Q_PROPERTY(Command command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Q_PROPERTY(bool onFight READ onFight NOTIFY onFightChanged)

public:
    enum Command
    {
        White,
        Black
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

    Command command() const;
    Type type() const;
    BasicBoard *board() const;
    bool onFight() const;

    void setCommand(Command newCommand);
    void setBoard(BasicBoard *board);
    void setOnFight(bool enable);

public slots:
    virtual void startMove();
    virtual void move(const QRect &geometry);
    virtual void finishMove();
    virtual QList<QPoint> availableMoves() = 0;

protected:
    void setType(Type newType);

    virtual bool canMove(int row, int column);

signals:
    void commandChanged(Command);
    void typeChanged(Type);
    void onFightChanged(bool);

private:
    BasicBoard *m_board;
    Command m_command;
    Type m_type;
    bool m_onFight;
};

#endif // BASICPIECE_H
