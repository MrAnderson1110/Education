#include "gllight.h"

GLLight::GLLight(float x, float y, float z,
                 QColor color, QObject *parent) :
    QObject(parent)
  , m_model()
  , m_color(color)
{
    setPosition(x, y, z);
}

QVector3D GLLight::position() const
{
    return m_position;
}

void GLLight::setPosition(float x, float y, float z)
{
    m_position = QVector3D(x, y, z);
    QMatrix4x4 newMat;
    m_model = newMat;
    m_model.translate(m_position);
    m_model.scale(0.2);
    emit positionChanged();
}

void GLLight::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(m_color);
}

QMatrix4x4 GLLight::model() const
{
    return m_model;
}

QVector3D GLLight::colorAsVector() const
{
    return QVector3D(m_color.redF(), m_color.greenF(), m_color.blueF());
}

QColor GLLight::color() const
{
    return m_color;
}
