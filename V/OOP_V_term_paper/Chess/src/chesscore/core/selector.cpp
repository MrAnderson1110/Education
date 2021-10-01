#include "selector.h"

#include "../gui/basicboard.h"
#include "../gui/basicpiece.h"
#include "../gui/basicgridcell.h"

Selector::Selector(BasicBoard *board)
    : m_board(board)
    , m_selectionPiece(nullptr)
    , m_hoveredCell(nullptr)
    , m_selectionList()
{

}

void Selector::updateSelection(BasicPiece *piece, const QList<QPoint> &availableMoves)
{
    for(BasicGridCell *cell : qAsConst(m_selectionList))
        cell->setSelected(false);

    m_selectionList.clear();
    if(!piece) {
        m_selectionPiece = nullptr;
        return;
    }

    QList<QPoint> moves = availableMoves;
    moves << QPoint(piece->rowIndex(), piece->columnIndex());
    for(QPoint p : qAsConst(moves)) {
        BasicGridCell *cell = m_board->cell(p.x(), p.y());

        Q_ASSERT_X(cell != nullptr,
                   "Mover::updateSelection()",
                   "cell in row: " + QString::number(p.x()).toLatin1() +
                   " column " + QString::number(p.y()).toLatin1() +
                   " is not available for piece type: " + QString::number(piece->type()).toLatin1());

        m_selectionList.append(cell);
        cell->setSelected(true);
    }
}

QPoint Selector::hoveredPoint() const
{
    if(!m_hoveredCell)
        return { -1, -1 };

    return { m_hoveredCell->rowIndex(), m_hoveredCell->columnIndex() };
}

void Selector::updateHover(const QRectF &pieceGeometry)
{
    if(m_hoveredCell != nullptr)
        m_hoveredCell->setHovered(false);

    m_hoveredCell = m_board->cellUnderMouse(pieceGeometry.center());

    if(m_hoveredCell != nullptr && m_selectionList.contains(m_hoveredCell))
        m_hoveredCell->setHovered(true);
}

