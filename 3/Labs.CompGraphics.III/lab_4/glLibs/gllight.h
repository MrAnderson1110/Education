#ifndef GLLIGHT_H
#define GLLIGHT_H

#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

class GLLight : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    GLLight(float x = 0.0f, float y = 0.0f, float z = 0.0f,
            QColor color = QColor("white"),
            QObject *parent = nullptr);

    QVector3D position() const;
    QMatrix4x4 model() const;
    QVector3D colorAsVector() const;    
    QColor color() const;

public slots:
    void setPosition(float x, float y, float z);
    void setColor(QColor color);

signals:
    void positionChanged();    
    void colorChanged(QColor color);

private:
    QVector3D m_position;
    QMatrix4x4 m_model;
    QColor m_color;
};

#endif // GLLIGHT_H
