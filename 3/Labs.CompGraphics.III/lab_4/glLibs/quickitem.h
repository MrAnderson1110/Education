#ifndef QUICKITEM_H
#define QUICKITEM_H

#include <QQuickItem>
#include <QtGui/QOpenGLFunctions_3_3_Core>
#include <QQuickWindow>

class GLCamera;
class GLLight;
class QSGSimpleTextureNode;
class QOpenGLTexture;
class QOpenGLShaderProgram;

class QuickItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(float specStrength READ specStrength WRITE setSpecStrength NOTIFY specStrengthChanged)
    Q_PROPERTY(float specIntensity READ specIntensity WRITE setSpecIntensity NOTIFY specIntensityChanged)
    Q_PROPERTY(GLLight* light_1 READ light_1 NOTIFY light_1Changed)
    Q_PROPERTY(GLLight* light_2 READ light_2 NOTIFY light_2Changed)
    Q_PROPERTY(GLLight* light_3 READ light_3 NOTIFY light_3Changed)
    Q_PROPERTY(QColor objectColor READ objectColor WRITE setObjectColor NOTIFY objectColorChanged)

    struct LightUniforms {
        GLint modelLoc;
        GLint viewLoc;
        GLint projLoc;
        GLint colorLoc;
    };

    struct MainUniforms {
        GLint modelLoc;
        GLint viewLoc;
        GLint projLoc;
        GLint objectColorLoc;
        GLint lightPosLoc_1;
        GLint lightPosLoc_2;
        GLint lightPosLoc_3;
        GLint viewPosLoc;
        GLint scepStrengthLoc;
        GLint scepIntensityLoc;
        GLint lightColorLoc_1;
        GLint lightColorLoc_2;
        GLint lightColorLoc_3;
        GLint lightCount;
    };

public:
    QuickItem(QQuickItem *parent = nullptr);
    ~QuickItem();

    float specStrength() const;
    float specIntensity() const;

    GLLight *light_1() const;
    GLLight *light_2() const;
    GLLight *light_3() const;

    QColor objectColor() const;

protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual QSGNode *updatePaintNode(QSGNode *pNode, UpdatePaintNodeData *pData) Q_DECL_OVERRIDE;

public slots:
    void setSpecStrength(float specStrength);
    void setSpecIntensity(float specIntensity);

    void setObjectColor(QColor objectColor);

signals:
    void specStrengthChanged(float specStrength);
    void specIntensityChanged(float specIntensity);
    void light_1Changed(GLLight* light_1);
    void light_2Changed(GLLight* light_2);
    void light_3Changed(GLLight* light_3);
    void objectColorChanged(QColor objectColor);

private:
    void initFBO(int width, int height, QSGSimpleTextureNode *node);
    void doRender(QSGSimpleTextureNode *pTextureNode);
    void pushOpenGLMatrix();
    void initShader();
    void initOpenGLState();

    QOpenGLFramebufferObject *m_pSourceFbo;
    QOpenGLFramebufferObject *m_pTargetFbo;
    QOpenGLShaderProgram *m_program;
    QOpenGLShaderProgram *m_lightProgram;
    //    QOpenGLTexture *text1;
    //    QOpenGLTexture *text;
    GLCamera *m_camera;
    GLLight *m_light_1;
    GLLight *m_light_2;
    GLLight *m_light_3;
    QOpenGLFunctions_3_3_Core m_glFuncts;
    bool m_isOpenGLInitialized;
    GLuint m_VBO, m_VAO;
    GLuint m_firstLightVAO, m_secLightVAO, m_thirdLightVAO;
    GLfloat m_specStrength;
    GLfloat m_specIntensity;
    MainUniforms m_mainUn;
    LightUniforms m_lightUn;
    QColor m_objectColor;
    GLfloat m_verts[216]{
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    QVector3D objPos[3] = {
        QVector3D( 1.5f,  0.0f, 0.0f),
        QVector3D( 0.0f,  1.5f, 0.0f),
        QVector3D( 1.5f,  0.0f, 1.5f),
    };
};

#endif // QUICKITEM_H
