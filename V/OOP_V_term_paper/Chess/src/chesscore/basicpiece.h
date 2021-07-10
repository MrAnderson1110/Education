#ifndef BASICPIECE_H
#define BASICPIECE_H

#include "ipiece.h"

class BasicPiece : public IPiece
{
    Q_OBJECT
public:
    explicit BasicPiece(QQuickItem *parent = nullptr);
};

#endif // BASICPIECE_H
