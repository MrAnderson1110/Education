#ifndef BASICPAWN_H
#define BASICPAWN_H

#include "ipiece.h"

class BasicPawn : public IPiece
{
    Q_OBJECT
public:
    explicit BasicPawn(QQuickItem *parent);
};

#endif // BASICPAWN_H
