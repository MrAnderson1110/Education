#include "rook.h"

Rook::Rook(QQuickItem *parent)
    : IPiece(parent)
{
    IPiece::setType(IPiece::Rook);
}

void Rook::setType(PieceType)
{
    qWarning() << "Rook::setType():: piece cannot change it's type";
}
