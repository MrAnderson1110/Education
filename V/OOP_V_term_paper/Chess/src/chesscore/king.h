#ifndef KING_H
#define KING_H

#include "ipiece.h"
#include "chesscore_global.h"

class CHESSCORE_EXPORT King : public IPiece
{
    Q_OBJECT
public:
    explicit King(QQuickItem *parent = nullptr);

public slots:
    virtual void setType(PieceType) override final;
};

#endif // KING_H
