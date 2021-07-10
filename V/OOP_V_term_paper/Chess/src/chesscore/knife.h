#ifndef KNIFE_H
#define KNIFE_H

#include "ipiece.h"
#include "chesscore_global.h"

class CHESSCORE_EXPORT Knife : public IPiece
{
    Q_OBJECT
public:
    explicit Knife(QQuickItem *parent = nullptr);

public slots:
    virtual void setType(PieceType) override final;
};

#endif // KNIFE_H
