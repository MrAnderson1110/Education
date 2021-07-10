#include "knife.h"

Knife::Knife(QQuickItem *parent)
    : IPiece(parent)
{
    IPiece::setType(IPiece::Knife);
}

void Knife::setType(PieceType)
{
    qWarning() << "Knife::setType():: piece cannot change it's type";
}
