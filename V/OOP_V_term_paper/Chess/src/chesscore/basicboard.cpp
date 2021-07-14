#include "basicboard.h"
#include "basicgridcell.h"
#include "basicpiece.h"

BasicBoard::BasicBoard(QQuickItem *parent)
    : QQuickItem(parent)
    , m_grid()
    , m_pieces()
    , m_inverted(false)
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
            if(cell != nullptr && m_grid[cell->rowIndex()][cell->columnIndex()] == nullptr) {
                Q_ASSERT(cell != nullptr);
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

    for(QList<BasicPiece *>::const_iterator it = m_pieces.cbegin(); it != m_pieces.cend(); ++it)
        initializePiece(*it);

    Q_ASSERT(m_pieces.size() == 32);
    QQuickItem::componentComplete();
}

void BasicBoard::initializePiece(BasicPiece *piece)
{
    int row = -1;
    int column = -1;
    bool isPawn = piece->type() == BasicPiece::Type::Pawn;

    switch (piece->command()) {
    case BasicPiece::Command::White:
        row = isPawn ? 1 : 0;
        break;
    case BasicPiece::Command::Black:
        row = isPawn ? 6 : 7;
        break;
    case BasicPiece::Command::Undefined:
    default:
        break;
    }

    if(m_inverted)
        row = 7 - row;

    Q_ASSERT(!m_grid.value(row).isEmpty());

    switch(piece->type()) {
    case BasicPiece::Type::King:
        column = 4;
        break;
    case BasicPiece::Type::Queen:
        column = 3;
        break;
    case BasicPiece::Type::Bishop:
        if(m_grid.value(row).value(2)->piece() == nullptr)
            column = 2;
        else
            column = 5;
        break;
    case BasicPiece::Type::Knife:
        if(m_grid.value(row).value(1)->piece() == nullptr)
            column = 1;
        else
            column = 6;
        break;
    case BasicPiece::Type::Rook:
        if(m_grid.value(row).value(0)->piece() == nullptr)
            column = 0;
        else
            column = 7;
        break;
    case BasicPiece::Type::Pawn:
        column = findColumnForPawn(row);
        qDebug() << "pawn column:" << column;
        break;
    case BasicPiece::Type::Undefined:
    default:
        break;
    }

    Q_ASSERT(row >= 0 && column >= 0);
    BasicGridCell *cell = m_grid.value(row).value(column);

    Q_ASSERT(cell != nullptr);
    cell->setPiece(piece);
}

int BasicBoard::findColumnForPawn(int row)
{
    Q_ASSERT(row >= 0);
    if(m_grid.value(row).isEmpty())
        return 0;

    const QHash<int, BasicGridCell *> celles = m_grid.value(row);
    for(int i = 0; i < 8; ++i)
        if(celles.value(i)->piece() == nullptr)
            return i;

    return 0;
}

bool BasicBoard::inverted() const
{
    return m_inverted;
}

void BasicBoard::setInverted(bool newInverted)
{
    if (m_inverted == newInverted)
        return;

    m_inverted = newInverted;
    emit invertedChanged(m_inverted);
}
