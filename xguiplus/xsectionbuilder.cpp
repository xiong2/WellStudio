#include "xsectionbuilder.h"

#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QColor>

CXSectionBuilder::CXSectionBuilder()
    : QOpenGLFunctions()
    , m_pTextureProgram(nullptr)
    , m_locTexVertex(0)
    , m_locTexCoord(0)
    , m_locTexMatrix(0)
    , m_locTexSampler(0)
    , m_locColormap(0)
    , m_pTexVertexBuffer(nullptr)
    , m_pTexture(nullptr)
    , m_pWiggleProgram(nullptr)
    , m_locWiggleVertex(0)
    , m_locWiggleMatrix(0)
    , m_locWiggleColor(0)
    , m_pWiggleVertexBuffer(nullptr)
    , m_pAreaProgram(nullptr)
    , m_locAreaVertex(0)
    , m_locAreaMatrix(0)
    , m_locAreaColor(0)
    , m_pAreaVertexBuffer(nullptr)
    , m_fLeft(-1.f)
    , m_fRight(1.f)
    , m_fBottom(-1.f)
    , m_fTop(1.f)
{
    initializeOpenGLFunctions();

    _InitTextureShader();
    _InitTextureBuffer();

    _InitWiggleShader();
    _InitWiggleBuffer();

    _InitAreaShader();
    _InitAreaBuffer();
}

CXSectionBuilder::~CXSectionBuilder()
{
    if (m_pTextureProgram)      { delete m_pTextureProgram; m_pTextureProgram = NULL; }
    if (m_pTexVertexBuffer)     { m_pTexVertexBuffer->destroy(); delete m_pTexVertexBuffer; m_pTexVertexBuffer = NULL; }
    if (m_pTexture)             { m_pTexture->destroy(); delete m_pTexture; m_pTexture = NULL; }

    // Wiggle
    if (m_pWiggleProgram)       { delete m_pWiggleProgram; m_pWiggleProgram = NULL; }
    if (m_pWiggleVertexBuffer)  { m_pWiggleVertexBuffer->destroy(); delete m_pWiggleVertexBuffer; m_pWiggleVertexBuffer = NULL; }

    // Area
    if (m_pAreaProgram)         { delete m_pAreaProgram; m_pAreaProgram = NULL; }
    if (m_pAreaVertexBuffer)    { m_pAreaVertexBuffer->destroy(); delete m_pAreaVertexBuffer; m_pAreaVertexBuffer = NULL; }

    qDeleteAll(m_listShader);
    m_listShader.clear();
}

void CXSectionBuilder::_InitTextureShader()
{
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_listShader << vshader;
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute highp vec4 texCoord;\n"
        "varying highp vec4 texc;\n"
        "uniform highp mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix*vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_listShader << fshader;
    const char *fsrc =
        "uniform highp sampler2D sampler;\n"
        "uniform highp vec4 colormap[256];\n"
        "varying highp vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    float fIndex = texture2D(sampler, texc.st).x;\n"
        "    int index = int(fIndex*255.0);\n"
        "    gl_FragColor = colormap[index];\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    m_pTextureProgram = new QOpenGLShaderProgram;
    m_pTextureProgram->addShader(vshader);
    m_pTextureProgram->addShader(fshader);
    m_pTextureProgram->link();

    m_locTexVertex = m_pTextureProgram->attributeLocation("vertex");
    m_locTexCoord = m_pTextureProgram->attributeLocation("texCoord");
    m_locTexMatrix = m_pTextureProgram->uniformLocation("matrix");
    m_locTexSampler = m_pTextureProgram->uniformLocation("sampler");
    m_locColormap = m_pTextureProgram->uniformLocation("colormap");
}

void CXSectionBuilder::_InitWiggleShader()
{
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_listShader << vshader;
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "uniform highp mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix*vertex;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_listShader << fshader;
    const char *fsrc =
        "uniform vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    m_pWiggleProgram = new QOpenGLShaderProgram;
    m_pWiggleProgram->addShader(vshader);
    m_pWiggleProgram->addShader(fshader);
    m_pWiggleProgram->link();

    m_locWiggleVertex = m_pWiggleProgram->attributeLocation("vertex");
    m_locWiggleMatrix = m_pWiggleProgram->uniformLocation("matrix");
    m_locWiggleColor = m_pWiggleProgram->uniformLocation("color");
}

void CXSectionBuilder::_InitAreaShader()
{
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_listShader << vshader;
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "uniform highp mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix*vertex;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_listShader << fshader;
    const char *fsrc =
        "uniform vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    m_pAreaProgram = new QOpenGLShaderProgram;
    m_pAreaProgram->addShader(vshader);
    m_pAreaProgram->addShader(fshader);
    m_pAreaProgram->link();

    m_locAreaVertex = m_pAreaProgram->attributeLocation("vertex");
    m_locAreaMatrix = m_pAreaProgram->uniformLocation("matrix");
    m_locAreaColor = m_pAreaProgram->uniformLocation("color");
}

void CXSectionBuilder::_InitTextureBuffer()
{
    float vertices[] = { -1.f, 1.f, -0.5f, 0.f, 1.f,      // 1
        1.f, 1.f, -0.5f, 1.f, 1.f,      // 2
        1.f, -1.f, -0.5f, 1.f, 0.f,      // 3
        -1.f, -1.f, -0.5f, 0.f, 0.f };    // 4

    m_pTexVertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_pTexVertexBuffer->create();
    m_pTexVertexBuffer->bind();
    m_pTexVertexBuffer->allocate(vertices, sizeof(vertices));
}

void CXSectionBuilder::_InitWiggleBuffer()
{
    m_pWiggleVertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
}

void CXSectionBuilder::_InitAreaBuffer()
{
    m_pAreaVertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
}

void CXSectionBuilder::SetTextureData(const QImage& image, const QVector4D(&colormap)[256])
{
    if (!m_pTexture)
    {
        m_pTexture = new QOpenGLTexture(image);
    }
    else
    {
        m_pTexture->destroy();
        m_pTexture->create();
        m_pTexture->setData(image);
    }

    m_pTexture->setWrapMode(QOpenGLTexture::ClampToEdge);
    m_pTexture->setMagnificationFilter(QOpenGLTexture::LinearMipMapNearest);
	m_pTexture->setMinificationFilter(QOpenGLTexture::Linear);
    m_pTexture->setAutoMipMapGenerationEnabled(true);

    for (int i = 0; i<256; ++i)
    {
        m_colormap[i] = colormap[i];
    }
}

void CXSectionBuilder::SetWiggleData(float *pData, int size)
{
    if (!m_pWiggleVertexBuffer->isCreated())
        m_pWiggleVertexBuffer->create();

    m_pWiggleVertexBuffer->bind();

    m_pWiggleVertexBuffer->allocate(pData, sizeof(float) * size);
}

void CXSectionBuilder::SetAreaData(float *pData, int size)
{
    if (!m_pAreaVertexBuffer->isCreated())
        m_pAreaVertexBuffer->create();

    m_pAreaVertexBuffer->bind();

    m_pAreaVertexBuffer->allocate(pData, sizeof(float) * size);
}

void CXSectionBuilder::DrawTexture(bool bShow)
{
    if (!m_pTexture)
        return;

    m_pTextureProgram->bind();
    m_pTexVertexBuffer->bind();

    // vertex
    m_pTextureProgram->setAttributeBuffer(m_locTexVertex, GL_FLOAT, 0, 3, 5 * sizeof(GL_FLOAT));
    m_pTextureProgram->enableAttributeArray(m_locTexVertex);

    // texcoord
    m_pTextureProgram->setAttributeBuffer(m_locTexCoord, GL_FLOAT, 3 * sizeof(GL_FLOAT), 2, 5 * sizeof(GL_FLOAT));
    m_pTextureProgram->enableAttributeArray(m_locTexCoord);

    // matrix
    QMatrix4x4 m;
    m.ortho(m_fLeft, m_fRight, m_fBottom, m_fTop, -1.f, 1.f);
    //m.translate(0.0f, 0.0f, 2.f);
    m_pTextureProgram->setUniformValue(m_locTexMatrix, m);

    // sampler
    m_pTextureProgram->setUniformValue(m_locTexSampler, 0);

    // colormap
    m_pTextureProgram->setUniformValueArray(m_locColormap, m_colormap, 256);

    // draw
	if (bShow)
	{
		m_pTexture->bind();
		glDrawArrays(GL_QUADS, 0, 4);
		m_pTexture->release();
	}

    m_pTexVertexBuffer->release();
    m_pTextureProgram->release();
}

void CXSectionBuilder::DrawWiggle(int nI, int nK, const QVector4D& color, bool bShow)
{
	if (nI == 0 || nK == 0 || !m_pWiggleVertexBuffer->isCreated())
        return;

    m_pWiggleProgram->bind();
    m_pWiggleVertexBuffer->bind();

    // Vertex
    m_pWiggleProgram->setAttributeBuffer(m_locWiggleVertex, GL_FLOAT, 0, 2, 0);
    m_pWiggleProgram->enableAttributeArray(m_locWiggleVertex);

    // matrix
    QMatrix4x4 m;
    m.ortho(m_fLeft, m_fRight, m_fBottom, m_fTop, -1.0f, 1.f);
    m.translate(0.0f, 0.0f, -0.4f);
    m_pWiggleProgram->setUniformValue(m_locWiggleMatrix, m);

    // color
    m_pWiggleProgram->setUniformValueArray(m_locWiggleColor, &color, 1);

    //draw
	if (bShow)
	{
		for (int i = 0; i < nI; ++i)
		{
			glDrawArrays(GL_LINE_STRIP, i * nK, nK);
		}
	}

    m_pWiggleVertexBuffer->release();
    m_pWiggleProgram->release();
}

void CXSectionBuilder::DrawArea(const std::vector<int> &vecCount, const QVector4D& color, bool bShow)
{
	if (vecCount.empty() || !m_pAreaVertexBuffer->isCreated())
		return;

    m_pAreaProgram->bind();
    m_pAreaVertexBuffer->bind();

    // Vertex
    m_pAreaProgram->setAttributeBuffer(m_locAreaVertex, GL_FLOAT, 0, 2, 0);
    m_pAreaProgram->enableAttributeArray(m_locAreaVertex);

    // matrix
    QMatrix4x4 m;
    m.ortho(m_fLeft, m_fRight, m_fBottom, m_fTop, -1.0f, 1.f);
    m.translate(0.0f, 0.0f, -0.3f);
    m_pAreaProgram->setUniformValue(m_locAreaMatrix, m);

    // color
    m_pAreaProgram->setUniformValueArray(m_locAreaColor, &color, 1);

    //draw
	if (bShow)
	{
		for (uint i = 0; i < vecCount.size() - 1; ++i)
		{
			glDrawArrays(GL_TRIANGLE_STRIP, vecCount[i], vecCount[i + 1] - vecCount[i]);
		}
	}

    m_pAreaVertexBuffer->release();
    m_pAreaProgram->release();
}

void CXSectionBuilder::UpdateROI(float fLeft, float fRight, float fBottom, float fTop)
{
    m_fLeft = fLeft;
    m_fRight = fRight;
    m_fBottom = fBottom;
    m_fTop = fTop;
}

void CXSectionBuilder::Update(const QColor& color)
{
	glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	glClear(GL_COLOR_BUFFER_BIT);
}

void CXSectionBuilder::EnableBackgroundSwitch(const QColor& clearColor)
{
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // triangles can be clockwire or counter-closewise
    glPolygonMode(GL_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_FILL);

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CXSectionBuilder::DisableBackgroundSwitch()
{
    glDisable(GL_POLYGON_MODE);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void CXSectionBuilder::EnableForegroundSwitch()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // triangles can be clockwire or counter-closewise
    glPolygonMode(GL_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void CXSectionBuilder::DisableForegroundSwitch()
{
    glDisable(GL_POLYGON_MODE);
    glDisable(GL_BLEND);
}

void CXSectionBuilder::SetAlphaValue(float alpha)
{
    for (auto i = 0; i != 256; ++i)
    {
        m_colormap[i].setW(alpha);
    }
}