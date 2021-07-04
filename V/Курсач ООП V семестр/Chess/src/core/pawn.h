#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    explicit Pawn(QObject *parent = nullptr);
};

#endif // PAWN_H
