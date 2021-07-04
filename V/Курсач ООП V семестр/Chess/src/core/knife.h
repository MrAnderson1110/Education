#ifndef KNIFE_H
#define KNIFE_H

#include "piece.h"

class Knife : public Piece
{
public:
    explicit Knife(QObject *parent = nullptr);
};

#endif // KNIFE_H
