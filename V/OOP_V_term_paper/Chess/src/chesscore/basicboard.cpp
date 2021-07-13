#include "basicboard.h"
#include "basicgridcell.h"
#include "basicpiece.h"

BasicBoard::BasicBoard(QQuickItem *parent)
    : QQuickItem(parent)
    , m_grid()
    , m_pieces()
{

}

void BasicBoard::componentComplete()
{
    QList<QQuickItem *> children = childItems();
    bool hasUncheckedChildren = true;
    while(hasUncheckedChildren) {
        QList<QQuickItem *> newChildren;
        for(QList<QQuickItem *>::const_iterator it = children.cbegin(); it != children.cend(); ++it) {
            QQuickItem *child = *it;
            if(!child)
                continue;

            BasicGridCell *cell = qobject_cast<BasicGridCell *>(child);
            BasicPiece *piece = qobject_cast<BasicPiece *>(child);
            if(cell != nullptr && m_grid[cell->rowIndex()][cell->columnIndex()] != nullptr) {
                m_grid[cell->rowIndex()][cell->columnIndex()] = cell;
                continue;
            }
            else if(piece != nullptr) {
                m_pieces.append(piece);
                continue;
            }
            else
                newChildren.append(child->childItems());
        }
        if(children.isEmpty())
            hasUncheckedChildren = false;

        children = newChildren;
    }
    Q_ASSERT(m_pieces.size() == 32);
    QQuickItem::componentComplete();
}
