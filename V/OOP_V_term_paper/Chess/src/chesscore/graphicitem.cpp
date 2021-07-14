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

void GraphicItem::polishContent()
{
    if(m_background) {
        Q_ASSERT(m_background->parentItem() == this);
        m_background->setX(0);
        m_background->setY(0);
        m_background->setWidth(width());
        m_background->setHeight(height());
    }
}

void GraphicItem::setBackground(QQuickItem *newBackground)
{
    if (m_background == newBackground)
        return;

    if(m_background != nullptr)
        delete m_background;

    m_background = newBackground;
    m_background->setParentItem(this);
    polishContent();

    emit backgroundChanged(m_background);
}

void GraphicItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);

    polishContent();
}
