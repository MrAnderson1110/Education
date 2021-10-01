#include "king.h"

King::King(QQuickItem *parent)
    : BasicPiece(parent)
{
    setType(BasicPiece::King);
}

King::~King()
{

}
