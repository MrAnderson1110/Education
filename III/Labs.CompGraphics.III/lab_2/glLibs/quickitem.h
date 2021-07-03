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

    struct MainUniforms {
        GLint modelLoc;
        GLint viewLoc;
        GLint projLoc;
    };

public:
    QuickItem(QQuickItem *parent = nullptr);
    ~QuickItem();

protected:
    virtual QSGNode *updatePaintNode(QSGNode *pNode, UpdatePaintNodeData *pData) Q_DECL_OVERRIDE;

private:
    void initFBO(int width, int height, QSGSimpleTextureNode *node);
    void doRender(QSGSimpleTextureNode *pTextureNode);
    void pushOpenGLMatrix();
    void initShader();
    void initOpenGLState();

    QOpenGLFramebufferObject *m_pSourceFbo;
    QOpenGLFramebufferObject *m_pTargetFbo;
    QOpenGLShaderProgram *m_program;
    GLCamera *m_camera;
    QOpenGLFunctions_3_3_Core m_glFuncts;
    bool m_isOpenGLInitialized;
    GLuint m_VBO, m_VAO;
    MainUniforms m_mainUn;
    GLfloat m_verts[118]{
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
};

#endif // QUICKITEM_H
