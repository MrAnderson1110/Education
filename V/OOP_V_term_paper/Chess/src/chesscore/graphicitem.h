#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QQuickItem>

class GraphicItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged)
public:
    explicit GraphicItem(QQuickItem *parent = nullptr);

    QQuickItem *background() const;

public slots:
    void setBackground(QQuickItem *newBackground);

signals:
    void backgroundChanged(QQuickItem *);

private:
    QQuickItem *m_background;
};

#endif // GRAPHICITEM_H
