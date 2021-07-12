#include "basicgridcell.h"

BasicGridCell::BasicGridCell(QQuickItem *parent)
    : QQuickItem(parent)
    , m_background(nullptr)
{

}

QQuickItem *BasicGridCell::background() const
{
    return m_background;
}

void BasicGridCell::setBackground(QQuickItem *newBackground)
{
    if(m_background == newBackground)
        return;

    if(m_background)
        delete m_background;

    m_background = newBackground;
    m_background->setParent(this);
    m_background->setParentItem(this);

    emit backgroundChanged(m_background);
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
