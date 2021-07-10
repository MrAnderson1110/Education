#ifndef QUEEN_H
#define QUEEN_H

#include "ipiece.h"
#include "chesscore_global.h"

class CHESSCORE_EXPORT Queen : public IPiece
{
    Q_OBJECT
public:
    explicit Queen(QQuickItem *parent = nullptr);

public slots:
    virtual void setType(PieceType) override final;
};

#endif // QUEEN_H
