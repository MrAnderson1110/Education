#include "basicboard.h"
#include "basicgridcell.h"

BasicBoard::BasicBoard(QQuickItem *parent)
    : QQuickItem(parent)
    , m_grid()
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
            if(cell != nullptr && m_grid[cell->rowIndex()][cell->columnIndex()] != nullptr) {
                m_grid[cell->rowIndex()][cell->columnIndex()] = cell;
                continue;
            }
            // Тоже самое для фигур
            else
                newChildren.append(child->childItems());
        }
        if(children.isEmpty())
            hasUncheckedChildren = false;

        children = newChildren;
    }

    QQuickItem::componentComplete();
}
