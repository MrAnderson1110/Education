#include "bishop.h"

Bishop::Bishop(QQuickItem *parent)
    : IPiece(parent)
{    
    IPiece::setType(IPiece::Bishop);
}

void Bishop::setType(PieceType)
{
    qWarning() << "Bishop::setType():: piece cannot change it's type";
}
