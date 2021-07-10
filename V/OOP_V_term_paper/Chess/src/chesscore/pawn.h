#ifndef PAWN_H
#define PAWN_H

#include "ipiece.h"
#include "chesscore_global.h"

class CHESSCORE_EXPORT Pawn : public IPiece
{
    Q_OBJECT
public:
    explicit Pawn(QQuickItem *parent = nullptr);

    // IPiece interface
public slots:
    virtual void setType(PieceType type) override final;
};

#endif // PAWN_H
