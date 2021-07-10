#ifndef ROOK_H
#define ROOK_H

#include "ipiece.h"
#include "chesscore_global.h"

class CHESSCORE_EXPORT Rook : public IPiece
{
    Q_OBJECT
public:
    explicit Rook(QQuickItem *parent = nullptr);

public slots:
    virtual void setType(PieceType) override final;
};

#endif // ROOK_H
