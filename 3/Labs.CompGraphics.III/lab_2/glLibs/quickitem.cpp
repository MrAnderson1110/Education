#include "quickitem.h"
#include <QKeyEvent>
#include <QOpenGLFramebufferObject>
#include <QSGSimpleTextureNode>
#include <QOpenGLTexture>
#include "glcamera.h"
#include "gllight.h"
#include <cmath>

QuickItem::QuickItem(QQuickItem *parent) :
    QQuickItem(parent)
  , m_pSourceFbo(nullptr)
  , m_pTargetFbo(nullptr)
  , m_program(nullptr)
  , m_camera(new GLCamera)
  , m_isOpenGLInitialized(false)
{
    setFlag(QQuickItem::ItemHasContents);
    setFocus(true);
}

QuickItem::~QuickItem()
{
}

QSGNode *QuickItem::updatePaintNode(QSGNode *pNode, QQuickItem::UpdatePaintNodeData *pData)
{
    Q_UNUSED(pData)

    QSGSimpleTextureNode* pTextureNode = static_cast<QSGSimpleTextureNode*>(pNode);

    if (pTextureNode == NULL)
    {
        pTextureNode = new QSGSimpleTextureNode();
        pTextureNode->setTexture(this->window()->createTextureFromId(0, QSize(0,0)));
    }

    doRender(pTextureNode);
    return pTextureNode;
}

void QuickItem::initFBO(int width, int height, QSGSimpleTextureNode *pTextureNode)
{
    delete m_pSourceFbo;
    m_pSourceFbo = nullptr;

    delete m_pTargetFbo;
    m_pTargetFbo = nullptr;

    if ((width > 0) && (height > 0)) {
        QOpenGLFramebufferObjectFormat sourceFormat;
        sourceFormat.setAttachment(QOpenGLFramebufferObject::Depth);
        sourceFormat.setSamples(16);

        m_pSourceFbo= new QOpenGLFramebufferObject(width, height, sourceFormat);
        m_pTargetFbo= new QOpenGLFramebufferObject(width, height);
    }
    else {
        pTextureNode->setTexture(this->window()->createTextureFromId(0, QSize(0,0)));
        pTextureNode->setRect(this->boundingRect());
    }
}

void QuickItem::doRender(QSGSimpleTextureNode *pTextureNode)
{
    int width= this->width();
    int height= this->height();

    pTextureNode->setTextureCoordinatesTransform(QSGSimpleTextureNode::MirrorVertically);

    initFBO(width, height, pTextureNode);
    initShader();


    if (m_pTargetFbo && m_pTargetFbo->isValid() && m_pSourceFbo && m_pSourceFbo->isValid())
    {
        initOpenGLState();

        m_pSourceFbo->bind();

        m_glFuncts.glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        m_glFuncts.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        m_program->bind();
        m_camera->setCam(m_camera->eye(),
                         m_camera->eye() + m_camera->front(),
                         m_camera->up());

        m_program->setUniformValue(m_mainUn.modelLoc, m_camera->model());
        m_program->setUniformValue(m_mainUn.viewLoc, m_camera->view());
        m_program->setUniformValue(m_mainUn.projLoc, m_camera->projection());
        m_program->release();

        m_program->bind();
        m_glFuncts.glBindVertexArray(m_VAO);
        m_glFuncts.glDrawArrays(GL_TRIANGLES, 0, 36);
        m_glFuncts.glBindVertexArray(0);
        m_program->release();

        m_pSourceFbo->release();

        QRect rect(0, 0, width, height);
        QOpenGLFramebufferObject::blitFramebuffer(m_pTargetFbo, rect, m_pSourceFbo, rect);
        pTextureNode->setTexture(this->window()->createTextureFromId(m_pSourceFbo->texture(), m_pSourceFbo->size()));
        pTextureNode->setRect(this->boundingRect());

        delete m_pSourceFbo;
        m_pSourceFbo= NULL;
    }
    else
    {
        delete m_pSourceFbo;
        m_pSourceFbo= NULL;

        delete m_pTargetFbo;
        m_pTargetFbo= NULL;
    }
}

void QuickItem::initShader()
{
    if(m_program)
        return;

    m_program = new QOpenGLShaderProgram();
    QOpenGLShader m_vert(QOpenGLShader::Vertex);
    if(!m_vert.compileSourceFile(":/mainVert.vert"))
        qFatal("QuickItem::initShader: m_program: vertex shader did not compiled");
    m_program->addShader(&m_vert);
    QOpenGLShader m_frag(QOpenGLShader::Fragment);
    if(!m_frag.compileSourceFile(":/mainFrag.frag"))
        qFatal("QuickItem::initShader: m_program: fragment shader did not compiled");
    m_program->addShader(&m_frag);
    m_program->link();

    m_program->bind();
    m_mainUn.modelLoc = m_program->uniformLocation("model");
    m_mainUn.viewLoc = m_program->uniformLocation("view");
    m_mainUn.projLoc = m_program->uniformLocation("projection");
    m_program->release();
}

void QuickItem::initOpenGLState()
{
    if(m_isOpenGLInitialized)
        return;

    m_camera->projection(45.0f, this->width()/this->height(), 0.1f, 100.0f);
    m_camera->rotate(30, m_camera->up());
    m_camera->rotate(10, m_camera->right());

    m_glFuncts.initializeOpenGLFunctions();

    m_glFuncts.glViewport(0,0, this->width(), this->height());

    m_glFuncts.glGenBuffers(1, &m_VBO);
    m_glFuncts.glGenVertexArrays(1, &m_VAO);

    m_glFuncts.glBindVertexArray(m_VAO);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_glFuncts.glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
    m_glFuncts.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    m_glFuncts.glEnableVertexAttribArray(0);
    m_glFuncts.glBindVertexArray(0);

    m_glFuncts.glEnable(GL_DEPTH_TEST);

    m_isOpenGLInitialized = true;
}
