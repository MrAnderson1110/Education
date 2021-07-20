#include "basicboard.h"
#include "basicgridcell.h"
#include "mover.h"

BasicBoard::BasicBoard(QQuickItem *parent)
    : QQuickItem(parent)
    , m_grid()
    , m_pieces()
    , m_inverted(false)
    , m_mover(new Mover(this))
{

}

void BasicBoard::componentComplete()
{
    QList<QQuickItem *> children = childItems();
    bool hasUncheckedChildren = true;
    while(hasUncheckedChildren) {
        QList<QQuickItem *> newChildren;
        for(QQuickItem *child : qAsConst(children)) {
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

BasicGridCell *BasicBoard::cell(int rowIndex, int columnIndex)
{
    if(m_grid.size() <= rowIndex)
        return nullptr;

    const QHash<int, BasicGridCell *> &column = m_grid.value(rowIndex);

    if(rowIndex < 0 || columnIndex < 0 || column.size() == 0
            || rowIndex >= 8 || columnIndex >= 8)
        return nullptr;

    Q_ASSERT(column.value(columnIndex) != nullptr);

    return column.value(columnIndex);
}

BasicGridCell *BasicBoard::cellUnderMouse(const QPointF &mouse)
{
    for(const QHash<int, BasicGridCell *> &celles : qAsConst(m_grid)) {
        for(BasicGridCell *cell : celles) {
            if(cell->geometry().contains(mouse))
                return cell;
        }
    }

    return nullptr;
}

void BasicBoard::select(int rowIndex, int columnIndex)
{
    BasicGridCell *cellForSelect = cell(rowIndex, columnIndex);

    if(cellForSelect != nullptr)
        cellForSelect->setSelected(true);
}

void BasicBoard::deselect(int rowIndex, int columnIndex)
{
    BasicGridCell *cellForDeselect = cell(rowIndex, columnIndex);

    if(cellForDeselect != nullptr)
        cellForDeselect->setSelected(false);
}

void BasicBoard::clearSelection()
{
    m_mover->updateSelection(nullptr);
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
    case BasicPiece::Type::Knight:
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
        break;
    case BasicPiece::Type::Undefined:
    default:
        break;
    }

    Q_ASSERT(row >= 0 && column >= 0);
    BasicGridCell *cell = m_grid.value(row).value(column);

    Q_ASSERT(cell != nullptr);
    piece->setRowIndex(row);
    piece->setColumnIndex(column);
    piece->setBoard(this);
    cell->setPiece(piece);
}

int BasicBoard::findColumnForPawn(int row)
{
    Q_ASSERT(row >= 0);
    // Ошибка поиска, возвращаем невалидный индекс
    if(m_grid.value(row).isEmpty())
        return -1;

    const QHash<int, BasicGridCell *> celles = m_grid.value(row);
    for(int i = 0; i < 8; ++i)
        if(celles.value(i)->piece() == nullptr)
            return i;

    // Ошибка поиска, возвращаем невалидный индекс
    return -1;
}

Mover *BasicBoard::mover() const
{
    return m_mover;
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
