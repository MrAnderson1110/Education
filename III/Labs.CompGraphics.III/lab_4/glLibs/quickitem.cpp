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
  , m_lightProgram(nullptr)
  , m_camera(new GLCamera)
  , m_light_1(new GLLight(0.0f, 0.0f, 4.0f, QColor("red")))
  , m_light_2(new GLLight(-2.0f, 0.0f, 4.0f, QColor("green")))
  , m_light_3(new GLLight(2.0f, 0.0f, 4.0f, QColor("blue")))
  , m_isOpenGLInitialized(false)
  , m_specStrength(32)
  , m_specIntensity(0.5f)
  , m_objectColor(200,200,200)
{
    setFlag(QQuickItem::ItemHasContents);
    setFocus(true);
    connect(this, &QuickItem::specStrengthChanged, this, &QuickItem::update);
    connect(this, &QuickItem::specIntensityChanged, this, &QuickItem::update);
    connect(m_light_1, &GLLight::positionChanged, this, &QuickItem::update);
    connect(m_light_2, &GLLight::positionChanged, this, &QuickItem::update);
    connect(m_light_3, &GLLight::positionChanged, this, &QuickItem::update);
    connect(m_light_1, &GLLight::colorChanged, this, &QuickItem::update);
    connect(m_light_2, &GLLight::colorChanged, this, &QuickItem::update);
    connect(m_light_3, &GLLight::colorChanged, this, &QuickItem::update);
    connect(this, &QuickItem::objectColorChanged, this, &QuickItem::update);
}

QuickItem::~QuickItem()
{
}

float QuickItem::specStrength() const
{
    return m_specStrength;
}

float QuickItem::specIntensity() const
{
    return m_specIntensity;
}

GLLight *QuickItem::light_1() const
{
    return m_light_1;
}

GLLight *QuickItem::light_2() const
{
    return m_light_2;
}

GLLight *QuickItem::light_3() const
{
    return m_light_3;
}

QColor QuickItem::objectColor() const
{
    return m_objectColor;
}

void QuickItem::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        m_camera->rotate(-3, m_camera->right().normalized());
        break;
    case Qt::Key_D:
        m_camera->rotate(3, m_camera->up().normalized());
        break;
    case Qt::Key_S:
        m_camera->rotate(3, m_camera->right().normalized());
        break;
    case Qt::Key_A:
        m_camera->rotate(-3, m_camera->up().normalized());
        break;
    case Qt::Key_Q:
        m_camera->rotate(3, m_camera->target());
        break;
    case Qt::Key_E:
        m_camera->rotate(-3, m_camera->target());
        break;
    default:
        return;
    }
    update();
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

void QuickItem::setSpecStrength(float specStrength)
{
    if (qFuzzyCompare(m_specStrength, specStrength))
        return;

    m_specStrength = specStrength;
    emit specStrengthChanged(m_specStrength);
}

void QuickItem::setSpecIntensity(float specIntensity)
{
    if (qFuzzyCompare(m_specIntensity, specIntensity))
        return;

    m_specIntensity = specIntensity;
    emit specIntensityChanged(m_specIntensity);
}

void QuickItem::setObjectColor(QColor objectColor)
{
    if (m_objectColor == objectColor)
        return;

    m_objectColor = objectColor;
    emit objectColorChanged(m_objectColor);
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
        m_lightProgram->setUniformValue(m_mainUn.viewLoc, m_camera->view());
        m_lightProgram->setUniformValue(m_mainUn.projLoc, m_camera->projection());
        m_lightProgram->setUniformValue(m_mainUn.objectColorLoc, m_objectColor.redF(), m_objectColor.greenF(), m_objectColor.blueF());
        m_lightProgram->setUniformValue(m_mainUn.lightColorLoc_1,  m_light_1->colorAsVector());
        m_lightProgram->setUniformValue(m_mainUn.lightColorLoc_2,  m_light_2->colorAsVector());
        m_lightProgram->setUniformValue(m_mainUn.lightColorLoc_3,  m_light_3->colorAsVector());

        m_program->setUniformValue(m_mainUn.viewPosLoc, m_camera->eye());
        m_program->setUniformValue(m_mainUn.lightPosLoc_1, m_light_1->position());
        m_program->setUniformValue(m_mainUn.lightPosLoc_2, m_light_2->position());
        m_program->setUniformValue(m_mainUn.lightPosLoc_3, m_light_3->position());
        m_program->release();

        m_lightProgram->bind();
        m_lightProgram->setUniformValue(m_lightUn.modelLoc, m_light_1->model());
        m_lightProgram->setUniformValue(m_lightUn.viewLoc, m_camera->view());
        m_lightProgram->setUniformValue(m_lightUn.projLoc,  m_camera->projection());
        m_lightProgram->setUniformValue(m_lightUn.colorLoc, m_light_1->colorAsVector());
        m_lightProgram->release();

        m_lightProgram->bind();
        m_glFuncts.glBindVertexArray(m_firstLightVAO);
        m_glFuncts.glDrawArrays(GL_TRIANGLES, 0, 36);
        m_glFuncts.glBindVertexArray(0);
        m_lightProgram->release();

        m_lightProgram->bind();
        m_lightProgram->setUniformValue(m_lightUn.modelLoc, m_light_2->model());
        m_lightProgram->setUniformValue(m_lightUn.viewLoc, m_camera->view());
        m_lightProgram->setUniformValue(m_lightUn.projLoc,  m_camera->projection());
        m_lightProgram->setUniformValue(m_lightUn.colorLoc, m_light_2->colorAsVector());
        m_lightProgram->release();

        m_lightProgram->bind();
        m_glFuncts.glBindVertexArray(m_secLightVAO);
        m_glFuncts.glDrawArrays(GL_TRIANGLES, 0, 36);
        m_glFuncts.glBindVertexArray(0);
        m_lightProgram->release();

        m_lightProgram->bind();
        m_lightProgram->setUniformValue(m_lightUn.modelLoc, m_light_3->model());
        m_lightProgram->setUniformValue(m_lightUn.viewLoc, m_camera->view());
        m_lightProgram->setUniformValue(m_lightUn.projLoc,  m_camera->projection());
        m_lightProgram->setUniformValue(m_lightUn.colorLoc, m_light_3->colorAsVector());
        m_lightProgram->release();

        m_lightProgram->bind();
        m_glFuncts.glBindVertexArray(m_thirdLightVAO);
        m_glFuncts.glDrawArrays(GL_TRIANGLES, 0, 36);
        m_glFuncts.glBindVertexArray(0);
        m_lightProgram->release();

        m_program->bind();
        m_program->release();

        for(int i = 0; i < 3; ++i) {
            QMatrix4x4 mat = m_camera->model();
            mat.translate(objPos[i]);
            mat.rotate(20.0f * i, QVector3D(1.0f, 0.3f, 0.5f));
            GLfloat specInt = 0.0f;
            GLfloat specStr = 0.0f;
            switch(i) {
            case 0:
                specInt = 0.5f;
                specStr = 32.0f;
                break;
            case 1:
                specInt = 1.0f;
                specStr = 128.0f;
                break;
            case 2:
                specInt = 1.5f;
                specStr = 256.0f;
                break;
            }
            setSpecStrength(specStr);
            setSpecIntensity(specInt);
            m_program->bind();
            m_program->setUniformValue(m_mainUn.scepStrengthLoc, m_specStrength);
            m_program->setUniformValue(m_mainUn.scepIntensityLoc, m_specIntensity);
            m_lightProgram->setUniformValue(m_mainUn.modelLoc, mat);
            m_glFuncts.glBindVertexArray(m_VAO);
            m_glFuncts.glDrawArrays(GL_TRIANGLES, 0, 36);
            m_glFuncts.glBindVertexArray(0);
            m_program->release();
        }

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

    if(m_lightProgram)
        return;

    m_lightProgram = new QOpenGLShaderProgram();
    QOpenGLShader m_lightVert(QOpenGLShader::Vertex);
    if(!m_lightVert.compileSourceFile(":/lightVert.vert"))
        qFatal("QuickItem::initShader: m_lightProgram: vertex shader did not compiled");
    m_lightProgram->addShader(&m_lightVert);
    QOpenGLShader m_lightFrag(QOpenGLShader::Fragment);
    if(!m_lightFrag.compileSourceFile(":/lightFrag.frag"))
        qFatal("QuickItem::initShader: m_lightProgram: fragment shader did not compiled");
    m_lightProgram->addShader(&m_lightFrag);
    m_lightProgram->link();

    m_program->bind();
    m_mainUn.modelLoc = m_program->uniformLocation("model");
    m_mainUn.viewLoc = m_program->uniformLocation("view");
    m_mainUn.projLoc = m_program->uniformLocation("projection");
    m_mainUn.objectColorLoc = m_program->uniformLocation("objectColor");
    m_mainUn.lightColorLoc_1  = m_program->uniformLocation("lights[0].color");
    m_mainUn.lightColorLoc_2  = m_program->uniformLocation("lights[1].color");
    m_mainUn.lightColorLoc_3  = m_program->uniformLocation("lights[2].color");
    m_mainUn.lightPosLoc_1 = m_program->uniformLocation("lights[0].position");
    m_mainUn.lightPosLoc_2 = m_program->uniformLocation("lights[1].position");
    m_mainUn.lightPosLoc_3 = m_program->uniformLocation("lights[2].position");
    m_mainUn.viewPosLoc = m_program->uniformLocation("viewPos");
    m_mainUn.scepStrengthLoc = m_program->uniformLocation("specStrength");
    m_mainUn.scepIntensityLoc = m_program->uniformLocation("specIntensity");
    m_mainUn.lightCount = m_program->uniformLocation("lightCount");
    m_program->release();

    m_lightProgram->bind();
    m_lightUn.modelLoc = m_lightProgram->uniformLocation("model");
    m_lightUn.viewLoc = m_lightProgram->uniformLocation("view");
    m_lightUn.projLoc = m_lightProgram->uniformLocation("projection");
    m_lightUn.colorLoc = m_lightProgram->uniformLocation("lightColor");
    m_lightProgram->release();
}

void QuickItem::initOpenGLState()
{
    if(m_isOpenGLInitialized)
        return;

    m_camera->projection(45.0f, this->width()/this->height(), 0.1f, 100.0f);

    m_glFuncts.initializeOpenGLFunctions();

    m_glFuncts.glViewport(0,0, this->width(), this->height());

    m_glFuncts.glGenBuffers(1, &m_VBO);
    m_glFuncts.glGenVertexArrays(1, &m_VAO);
    m_glFuncts.glGenVertexArrays(1, &m_firstLightVAO);
    m_glFuncts.glGenVertexArrays(1, &m_secLightVAO);
    m_glFuncts.glGenVertexArrays(1, &m_thirdLightVAO);

    m_glFuncts.glBindVertexArray(m_VAO);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_glFuncts.glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
    m_glFuncts.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    m_glFuncts.glEnableVertexAttribArray(0);
    m_glFuncts.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_glFuncts.glEnableVertexAttribArray(1);
    m_glFuncts.glBindVertexArray(0);

    m_glFuncts.glBindVertexArray(m_firstLightVAO);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_glFuncts.glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
    m_glFuncts.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    m_glFuncts.glEnableVertexAttribArray(0);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_glFuncts.glBindVertexArray(0);

    m_glFuncts.glBindVertexArray(m_secLightVAO);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_glFuncts.glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
    m_glFuncts.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    m_glFuncts.glEnableVertexAttribArray(0);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_glFuncts.glBindVertexArray(0);

    m_glFuncts.glBindVertexArray(m_thirdLightVAO);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_glFuncts.glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);
    m_glFuncts.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    m_glFuncts.glEnableVertexAttribArray(0);
    m_glFuncts.glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_glFuncts.glBindVertexArray(0);

    m_glFuncts.glEnable(GL_DEPTH_TEST);

    m_isOpenGLInitialized = true;
}
