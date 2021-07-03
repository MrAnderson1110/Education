#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class GLCamera
{

public:
    GLCamera();

    QMatrix4x4 setCam(const QVector3D &eye,
                      const QVector3D &target,
                      const QVector3D &right);

    QVector3D eye() const;    
    QVector3D front() const;
    QVector3D target() const;

    QMatrix4x4 view() const;
    QMatrix4x4 model() const;
    QMatrix4x4 projection() const;

    QVector3D right() const;
    QVector3D dir() const;
    QVector3D up() const;

    void setEye(const QVector3D &eye);
    void setTarget(const QVector3D &target);
    void setUp(const QVector3D &up);
    void setFront(const QVector3D &front);

    void projection(float verticalAngle, float aspectRatio, float nearPlane, float farPlane);
    void translate(const QVector3D &vec);
    void rotate(float angle, const QVector3D &vec);
    void scale(float zoom);

private:
    QVector3D m_eye;
    QVector3D m_up;
    QVector3D m_front;

    QMatrix4x4 m_view;
    QMatrix4x4 m_model;
    QMatrix4x4 m_projection;
};

#endif // GLCAMERA_H
