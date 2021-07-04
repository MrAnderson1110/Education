#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    explicit Queen(QObject *parent = nullptr);
};

#endif // QUEEN_H
