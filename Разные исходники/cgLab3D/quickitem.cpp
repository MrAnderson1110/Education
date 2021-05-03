#include "quickitem.h"
#include <QKeyEvent>
#include <QOpenGLFramebufferObjectFormat>
#include "glmatrix.h"
#include "glvector.h"

const GLchar* vertexShaderSource =
        "#version 330\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\n";
//        "uniform mat4 projection_mat;"
//        "varying vec4 Cs;"
//        "void main(void)"
//        "{"
//        "   Cs= vec4(0.0,0.7,0.0,0);"
//        "   vec4 scaleVec = projection_mat * gl_Vertex;"
//        "   gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
//        "}";
const GLchar* fragmentShaderSource =
        "varying vec4 Cs;"
        "void main(void)"
        "{"
        "    float intensity = 0.8;"
        "    vec4 color = vec4(intensity,intensity,intensity, 1) * Cs;"
        "    color.a=0.5;"
        "    gl_FragColor = color;"
        "}";

QuickItem::QuickItem(QQuickItem *parent) :
    QQuickItem(parent)
  , m_pSourceFbo(nullptr)
  , m_pTargetFbo(nullptr)
  , m_program(nullptr)
{
    setFlag(QQuickItem::ItemHasContents);
}

QuickItem::~QuickItem()
{

}

void QuickItem::keyPressEvent(QKeyEvent *event) {}

void QuickItem::keyReleaseEvent(QKeyEvent *event) {}

void QuickItem::mousePressEvent(QMouseEvent *event) {}

void QuickItem::mouseMoveEvent(QMouseEvent *event) {}

void QuickItem::mouseReleaseEvent(QMouseEvent *event) {}

void QuickItem::wheelEvent(QWheelEvent *event) {}


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
    emit updateDone();

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
        sourceFormat.setSamples(8);

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

    if (m_pTargetFbo && m_pTargetFbo->isValid() && m_pSourceFbo && m_pSourceFbo->isValid())
    {
        QOpenGLFunctions glFuncts(QOpenGLContext::currentContext());

        initShader();
        pushOpenGLMatrix();


        m_pSourceFbo->bind();

        glViewport(0, 0, width, height);
        GLuint VBO;
        //создаем буфер
        glFuncts.glGenBuffers(1, &VBO);

        //привязываем его в VBO
        glFuncts.glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //копируем вершины в VBO
        glFuncts.glBufferData(GL_ARRAY_BUFFER, sizeof(m_verts), m_verts, GL_STATIC_DRAW);

        glFuncts.glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glFuncts.glEnableVertexAttribArray(0);

        //отвзываем буфер от VBO
        glFuncts.glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_program->bind();

        glClearColor(0.1,0.2,0.3,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


//        glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);

//        glDisable(GL_BLEND);
//        glDepthMask(GL_TRUE);
//        glEnable(GL_DEPTH_TEST);

//        glFrontFace(GL_CW);

//        glDrawElements(GL_LINE_STRIP, 180*180*180, GL_UNSIGNED_INT, m_verts);
        glDrawArrays(GL_TRIANGLES, 0, 3);


//        glPopAttrib();

        glFuncts.glDeleteBuffers(1, &VBO);

        m_program->release();
        m_pSourceFbo->release();

        QRect rect(0, 0, width, height);
        QOpenGLFramebufferObject::blitFramebuffer(m_pTargetFbo, rect, m_pSourceFbo, rect);
        pTextureNode->setTexture(this->window()->createTextureFromId(m_pTargetFbo->texture(), m_pTargetFbo->size()));
        pTextureNode->setRect(this->boundingRect());

        glFinish();
        delete m_pSourceFbo;
        m_pSourceFbo= NULL;
        popOpenGLMatrix();
    }
    else
    {
        delete m_pSourceFbo;
        m_pSourceFbo= NULL;

        delete m_pTargetFbo;
        m_pTargetFbo= NULL;
    }
}

void QuickItem::popOpenGLMatrix()
{
    glMatrixMode(GL_TEXTURE_2D);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void QuickItem::pushOpenGLMatrix()
{
    //активаровать матрицу
    //запись uniform  переменных
    glmath::GLMatrix<4> identity = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
    const double *dat = (identity).toData();
    GLfloat mat[4][4];
    GLfloat *pData = &(mat[0][0]);
    for(int i = 0; i < 16; ++i) {
        pData[i]= static_cast<GLfloat>(dat[i]);
    }

}

void QuickItem::initShader()
{
    if(!m_program) {
        m_program = new QOpenGLShaderProgram();
        QOpenGLShader m_vert(QOpenGLShader::Vertex);
        if(!m_vert.compileSourceCode(vertexShaderSource))
            qFatal("QuickItem::useShader: vertex shader did not compiled");
        m_program->addShader(&m_vert);
        QOpenGLShader m_frag(QOpenGLShader::Fragment);
        if(!m_frag.compileSourceCode(fragmentShaderSource))
            qFatal("QuickItem::useShader: fragment shader did not compiled");
        m_program->addShader(&m_frag);
        m_program->link();
    }
}
