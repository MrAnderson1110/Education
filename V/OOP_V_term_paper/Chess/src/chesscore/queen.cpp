#include "queen.h"

Queen::Queen(QQuickItem *parent)
    : IPiece(parent)
{
    IPiece::setType(IPiece::Queen);
}

void Queen::setType(PieceType)
{
    qWarning() << "Queen::setType():: piece cannot change it's type";
}
