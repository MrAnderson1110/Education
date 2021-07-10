#include "pawn.h"

Pawn::Pawn(QQuickItem *parent)
    : IPiece(parent)
{
    IPiece::setType(IPiece::Pawn);
}

void Pawn::setType(PieceType type)
{
    if(type == IPiece::King) {
        qWarning() << "Pawn::setType():: Pawn cannot be a King";
        return;
    }

    IPiece::setType(type);
}
