#include "basicgridcell.h"
#include "basicpiece.h"

BasicGridCell::BasicGridCell(QQuickItem *parent)
    : GraphicItem(parent)
    , m_rowIndex(0)
    , m_columnIndex(0)
    , m_piece(nullptr)
{

}

int BasicGridCell::rowIndex() const
{
    return m_rowIndex;
}

void BasicGridCell::setRowIndex(int newRowIndex)
{
    if (m_rowIndex == newRowIndex)
        return;

    m_rowIndex = newRowIndex;
    emit rowIndexChanged(m_rowIndex);
}

int BasicGridCell::columnIndex() const
{
    return m_columnIndex;
}

void BasicGridCell::setColumnIndex(int newColumnIndex)
{
    if (m_columnIndex == newColumnIndex)
        return;

    m_columnIndex = newColumnIndex;
    emit columnIndexChanged(m_columnIndex);
}

BasicPiece *BasicGridCell::piece() const
{
    return m_piece;
}

void BasicGridCell::polishContent()
{
    if(m_piece) {
        Q_ASSERT(m_piece->parentItem() == this);
        m_piece->setX(0);
        m_piece->setY(0);
        m_piece->setWidth(width());
        m_piece->setHeight(height());
    }

    GraphicItem::polishContent();
}

void BasicGridCell::setPiece(BasicPiece *newPiece)
{
    if (m_piece == newPiece)
        return;

    m_piece = newPiece;
    newPiece->setParentItem(this);
    polishContent();

    emit pieceChanged(m_piece);
}
