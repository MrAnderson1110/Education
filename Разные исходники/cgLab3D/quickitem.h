#ifndef QUICKITEM_H
#define QUICKITEM_H

#include <QQuickItem>
#include <QQuickWindow>
#include <QtGui/QOpenGLFunctions>
#include <QSGSimpleTextureNode>

class QuickItem : public QQuickItem
{
    Q_OBJECT
public:
    QuickItem(QQuickItem *parent = nullptr);
    ~QuickItem();

    // QQuickItem interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    virtual QSGNode *updatePaintNode(QSGNode *pNode, UpdatePaintNodeData *pData) Q_DECL_OVERRIDE;

signals:
    void updateDone();

private:
    void initFBO(int width, int height, QSGSimpleTextureNode *node);
    void doRender(QSGSimpleTextureNode *pTextureNode);
    void initGLStates();
    void popOpenGLMatrix();
    void pushOpenGLMatrix();
    void initShader();
    void useShader();


    QOpenGLFramebufferObject *m_pSourceFbo;
    QOpenGLFramebufferObject *m_pTargetFbo;

    QOpenGLShaderProgram *m_program;

    GLfloat m_verts[9]{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
};

#endif // QUICKITEM_H
