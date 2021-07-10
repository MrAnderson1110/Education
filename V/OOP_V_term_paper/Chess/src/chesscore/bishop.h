#ifndef BISHOP_H
#define BISHOP_H

#include "ipiece.h"
#include "chesscore_global.h"

class CHESSCORE_EXPORT Bishop : public IPiece
{
    Q_OBJECT
public:
    explicit Bishop(QQuickItem *parent = nullptr);

public slots:
    virtual void setType(PieceType) override final;
};

#endif // BISHOP_H
