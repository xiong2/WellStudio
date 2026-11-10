#ifndef XSECTIONBUILDER_H
#define XSECTIONBUILDER_H

#include <QOpenGLFunctions>
#include <QVector4D>
#include "xguiplus_global.h"

/*!
*  @class  CXSectionBuilder in kesectionbuilder.h
*  @brief  Abstract shader action.
*  @author pezy
*  @date   2016-01-06
*  @see    CXSectionScene
*/

class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLTexture;

class XGUIPLUS_EXPORT CXSectionBuilder : protected QOpenGLFunctions
{
public:
    CXSectionBuilder();
    ~CXSectionBuilder();

    void SetTextureData(const QImage& image, const QVector4D(&colormap)[256]);
    void SetWiggleData(float* pData, int size);
    void SetAreaData(float* pData, int size);

    void DrawTexture(bool bShow);
    void DrawWiggle(int nI, int nK, const QVector4D& color, bool bShow);
	void DrawArea(const std::vector<int>& vecCount, const QVector4D& color, bool bShow);

    void UpdateROI(float fLeft, float fRight, float fBottom, float fTop);
	void Update(const QColor& color);

    void EnableBackgroundSwitch(const QColor& clearColor);
    void DisableBackgroundSwitch();

    void EnableForegroundSwitch();
    void DisableForegroundSwitch();

    void SetAlphaValue(float foreAlpha);

private:
    // texture
    void _InitTextureShader();
    void _InitTextureBuffer();

    // wiggle
    void _InitWiggleShader();
    void _InitWiggleBuffer();

    // area
    void _InitAreaShader();
    void _InitAreaBuffer();

private:
    QList<QOpenGLShader*> m_listShader;

    // texture
    QOpenGLShaderProgram* m_pTextureProgram;
    int m_locTexVertex, m_locTexCoord, m_locTexMatrix, m_locTexSampler, m_locColormap;
    QOpenGLBuffer* m_pTexVertexBuffer;
    QOpenGLTexture* m_pTexture;
    QVector4D m_colormap[256];

    // wiggle
    QOpenGLShaderProgram* m_pWiggleProgram;
    int m_locWiggleVertex, m_locWiggleMatrix, m_locWiggleColor;
    QOpenGLBuffer* m_pWiggleVertexBuffer;

    // area
    QOpenGLShaderProgram* m_pAreaProgram;
    int m_locAreaVertex, m_locAreaMatrix, m_locAreaColor;
    QOpenGLBuffer* m_pAreaVertexBuffer;

    float m_fLeft, m_fRight, m_fBottom, m_fTop;
};

#endif // KESECTIONBUILDER_H
