#include "king.h"

King::King(QQuickItem *parent)
    : IPiece(parent)
{
    IPiece::setType(IPiece::King);
}

void King::setType(PieceType)
{
    qWarning() << "King::setType():: piece cannot change it's type";
}
