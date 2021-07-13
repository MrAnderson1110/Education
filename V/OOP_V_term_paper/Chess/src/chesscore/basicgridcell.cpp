#include "basicgridcell.h"

BasicGridCell::BasicGridCell(QQuickItem *parent)
    : GraphicItem(parent)
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
