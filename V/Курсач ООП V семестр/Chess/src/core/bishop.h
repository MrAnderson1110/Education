#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
public:
    explicit Bishop(QObject *parent = nullptr);
};

#endif // BISHOP_H
