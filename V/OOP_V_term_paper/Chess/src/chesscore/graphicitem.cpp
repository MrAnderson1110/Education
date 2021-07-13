#include "graphicitem.h"

GraphicItem::GraphicItem(QQuickItem *parent)
    : QQuickItem(parent)
    , m_background(nullptr)
{

}

QQuickItem *GraphicItem::background() const
{
    return m_background;
}

void GraphicItem::setBackground(QQuickItem *newBackground)
{
    if (m_background == newBackground)
        return;

    if(m_background != nullptr)
        delete m_background;

    m_background = newBackground;
    m_background->setParent(this);
    m_background->setParentItem(this);

    emit backgroundChanged(m_background);
}
