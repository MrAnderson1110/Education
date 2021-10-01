#ifndef ROOK_H
#define ROOK_H

#include "basicpiece.h"

class CHESSCORE_EXPORT Rook : public BasicPiece
{
    Q_OBJECT
public:
    MAKE_VISITABLE()

    explicit Rook(QQuickItem *parent = nullptr);
    virtual ~Rook();
};

#endif // ROOK_H
