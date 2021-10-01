#ifndef KING_H
#define KING_H

#include "basicpiece.h"

class CHESSCORE_EXPORT King : public BasicPiece
{
    Q_OBJECT
public:
    MAKE_VISITABLE()

    explicit King(QQuickItem *parent = nullptr);
    virtual ~King();
};

#endif // KING_H
