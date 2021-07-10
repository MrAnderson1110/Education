#include "chessboard.h"
#include "mover.h"
#include "ipiece.h"

ChessBoard::ChessBoard(QQuickItem *parent)
    : QQuickItem(parent)
    , m_pieces()
    , m_mover(new Mover)
{

}

void ChessBoard::componentComplete()
{
    QObjectList childList = children();
    for(QObject *child : childList) {
        IPiece *piece = qobject_cast<IPiece *>(child);
        if(piece->type() != IPiece::Undefined) {
            piece->setBoard(this);
            m_pieces.append(piece);
        }
        else
            qWarning() << "ChessBoard::componentComplete():: cannot create new piece with Undefined type";
    }

    QQuickItem::componentComplete();
}
