#include "glcamera.h"

GLCamera::GLCamera() :
    m_eye(0.0f,0.0f,5.0f)
  , m_up(0.0f, 1.0f, 0.0f)
  , m_front(0.0f, 0.0f, -1.0f)
  , m_view()
  , m_model()
  , m_projection()
{}

QMatrix4x4 GLCamera::setCam(const QVector3D &eyeVec,
                            const QVector3D &targetVec,
                            const QVector3D &upVec)
{
    setEye(eyeVec);
    setFront(targetVec - m_eye);
    setUp(upVec);


    QMatrix4x4 camMat;
    camMat.lookAt(eye(), target(), up());
    camMat.translate(-eye());
    m_view = camMat;

    return m_view;
}

QVector3D GLCamera::eye() const
{
    return m_eye;
}

void GLCamera::setEye(const QVector3D &eye)
{
    if(eye == m_eye)
        return;
    m_eye = eye;
}

QVector3D GLCamera::target() const
{
    return m_eye + m_front;
}

QMatrix4x4 GLCamera::view() const
{
    return m_view;
}

QMatrix4x4 GLCamera::model() const
{
    return m_model;
}

QMatrix4x4 GLCamera::projection() const
{
    return m_projection;
}

QVector3D GLCamera::up() const
{
    return QVector3D::crossProduct(dir(), right());
}

void GLCamera::setUp(const QVector3D &up)
{
    if(up == m_up)
        return;
    m_up = up;
}

QVector3D GLCamera::right() const
{
    return QVector3D::crossProduct(m_up.normalized(), dir()).normalized();
}

QVector3D GLCamera::dir() const
{
    return QVector3D(m_eye - target()).normalized();
}

QVector3D GLCamera::front() const
{
    return m_front;
}

void GLCamera::setFront(const QVector3D &front)
{
    if(front == m_front)
        return;
    m_front = front;
}

void GLCamera::translate(const QVector3D &vec)
{
    m_model.translate(vec);
}

void GLCamera::rotate(float angle, const QVector3D &vec)
{
    m_model.rotate(angle, vec);
}

void GLCamera::scale(float zoom)
{
    m_model.scale(zoom);
}

void GLCamera::projection(float verticalAngle, float aspectRatio, float nearPlane, float farPlane)
{
    m_projection.perspective(verticalAngle, aspectRatio, nearPlane, farPlane);
}
