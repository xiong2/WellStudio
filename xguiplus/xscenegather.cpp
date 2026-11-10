#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <qpainter.h>
#include "xscenegather.h"
#include "xsectionbuilder.h"
#include "xcolormap.h"
#include "xprestackgather.h"
#include "xglobal.h"
#include "xfunctiontemplate.h"
#include "xdlggatherwin.h"
#include "xviewgather.h"
#include "xitemfb.h"

XSceneGather::XSceneGather(QObject *parent) : QGraphicsScene(parent)
{
}

XSceneGather::~XSceneGather()
{
	if (m_pBuilder)
	{
		delete m_pBuilder;
		m_pBuilder = nullptr;
	}

	if (m_pItemFB)
	{
		removeItem(m_pItemFB);
		delete m_pItemFB;
		m_pItemFB = nullptr;
	}

	ClearSection();
}

void XSceneGather::InitOpenGLBuilder()
{
	if (m_pBuilder)
		return;

	XDlgGatherWin *pWin = (XDlgGatherWin *)parent();
	pWin->GetView()->GetGLWidget()->makeCurrent();
	m_pBuilder = new CXSectionBuilder;
	pWin->GetView()->GetGLWidget()->doneCurrent();
}

void XSceneGather::ClearSection()
{
	m_iTraceNum = 0;
	m_iSampleNum = 0;

	if (m_pData)
	{
		delete[]m_pData;
		m_pData = nullptr;
	}

	if (m_pImgData)
	{
		delete[]m_pImgData;
		m_pImgData = nullptr;
	}

	m_vecAreaCount.clear();
}

void XSceneGather::BuildSection(CXPreStackGather* pGather, int iShotID)
{
	ClearSection();

	if (!pGather->GetOneShotDimension(iShotID, m_iTraceNum, m_iSampleNum))
		return;

	if (m_iShotID == -1)
	{
		//	Initialize it now.
		auto pColormap = CXColormap::GetColormap("Landmark");
		for (auto i = 0; i < 256; ++i)
		{
			QColor color = (i == 255) ? pColormap->GetInvalidColor() : pColormap->GetColorAt(i);
			m_colors[i].setX(color.redF());
			m_colors[i].setY(color.greenF());
			m_colors[i].setZ(color.blueF());
			m_colors[i].setW(color.alphaF());
		}

		pGather->GetZInfo(m_fStartZ, m_fZInc);
	}

	m_iShotID = iShotID;

	qint64 iLen = m_iTraceNum * m_iSampleNum;
	m_pData = new float[iLen];

	if (!pGather->ReadOneShot(iShotID, m_pData))
	{
		ClearSection();
		return;
	}

	m_fDMin = m_pData[0];
	m_fDMax = m_pData[0];
	for (qint64 k = 1; k < iLen; k++)
	{
		m_fDMin = m_fDMin < m_pData[k] ? m_fDMin : m_pData[k];
		m_fDMax = m_fDMax > m_pData[k] ? m_fDMax : m_pData[k];
	}

	RedrawSection();
}

void XSceneGather::RedrawSection()
{
	if (m_iShotID == -1)
		return;

	calVI();

	calVA();
}

void XSceneGather::CreateFBItem(CXPreStackGather* pGather)
{
	if (m_iShotID == -1)
		return;

	if (!m_pItemFB)
	{
		m_pItemFB = new XItemFB(this);
		addItem(m_pItemFB);
	}

	float *pData = new float[m_iTraceNum];
	if (pGather->ReadOneShotFB(m_iShotID, pData))
		m_pItemFB->UpdateData(pData, m_iTraceNum);
	else
		delete[]pData;
}

void XSceneGather::RemoveFBItem()
{
	if (!m_pItemFB)
		return;

	removeItem(m_pItemFB);
	delete m_pItemFB;
	m_pItemFB = nullptr;
}

void XSceneGather::RedrawFB()
{
	if (m_pItemFB)
		m_pItemFB->MapToScene();
}

void XSceneGather::calVI()
{
	qint64 iLen = m_iTraceNum * m_iSampleNum;
	m_pImgData = new unsigned int[iLen];

	float dSpan = m_fDMax - m_fDMin;
	if (dSpan == 0.)
	{
		ClearSection();
		return;
	}
	//dSpan *= 0.8;

	for (auto i = 0; i < m_iTraceNum; ++i)
	{
		for (auto k = 0; k < m_iSampleNum; ++k)
		{
			float dCurrValue = m_pData[i * m_iSampleNum + k];

			int index;
			index = static_cast<int>((dCurrValue - m_fDMin) / dSpan * 254);
			//index = 128 - dCurrValue / dSpan * 140;
			index = qBound(0, index, 254);

			m_pImgData[(m_iSampleNum - 1 - k) * m_iTraceNum + i] = QColor(index, index, index).rgba();
		}
	}

	QImage image(reinterpret_cast<uchar*>(m_pImgData), m_iTraceNum, m_iSampleNum, QImage::Format_RGB32);

	m_pBuilder->SetTextureData(image, m_colors);
}

void XSceneGather::calWiggleData(float* pXYData)
{
	float fWiggleMin, fWiggleMax;
	if (m_fDMin * m_fDMax < 0)
	{
		fWiggleMax = qMax(qAbs(m_fDMin), m_fDMax);
		fWiggleMin = -fWiggleMax;
	}
	else
	{
		fWiggleMax = m_fDMax;
		fWiggleMin = 0.f;
	}

	// parameters
	float fXUnit = 2.0 / m_iTraceNum;
	float fYUnit = 2.0 / (m_iSampleNum - 1);
	float fClipping = 4. * fXUnit;
	float fExcursion = m_viewInfo.GetExcusion() * fXUnit;

	float x, y, length, value;
	auto index = -1;

	for (auto i = 0; i < m_iTraceNum; ++i)
	{
		for (auto k = 0; k < m_iSampleNum; ++k)
		{
			value = m_pData[i * m_iSampleNum + k];

			// In seismic part, we see invalid value as zero.
			if (qFuzzyCompare(value, (float)::g_dInvalidData))
			{
				value = 0.f;
			}

			// X
			length = qMin(qAbs(value) / fWiggleMax * fExcursion, fClipping);
			if (fWiggleMin == 0.f)
			{
				x = -1.f + i * fXUnit + length;
			}
			else
			{
				x = -1.f + (i + 0.5f) * fXUnit + Sign(value) * length;
			}

			// Y
			y = 1.f - k * fYUnit;

			// set x and y
			pXYData[++index] = x;
			pXYData[++index] = y;
		}
	}
}

void XSceneGather::calVA()
{
	m_vecAreaCount.assign({ 0 });

	auto pXYData = new float[m_iTraceNum * m_iSampleNum * 2];

	calWiggleData(pXYData);

	if (m_viewInfo.GetShowWiggle())
	{
		m_pBuilder->SetWiggleData(pXYData, m_iTraceNum * m_iSampleNum * 2);
	}

	if (m_viewInfo.GetShowVA())
	{
		auto pAreaData = new float[m_iTraceNum * m_iSampleNum * 2 * 2];

		auto fXUnit = 2.0f / m_iTraceNum;
		auto fTraceStart = m_fDMin * m_fDMax < 0 ? fXUnit / 2.f : 0.f;

		float fXMiddle, fXPre, fX, fXNext, fYPre, fY, y;
		auto index = 0;
		for (auto i = 0; i < m_iTraceNum; ++i)
		{
			fXMiddle = -1.f + i * fXUnit + fTraceStart;

			for (auto k = 0; k < m_iSampleNum; ++k)
			{
				fX = pXYData[2 * (i * m_iSampleNum + k)];
				fY = pXYData[2 * (i * m_iSampleNum + k) + 1];

				// each K deals with its own and above data
				if (k == 0)
				{
					fXNext = pXYData[2 * (i * m_iSampleNum + k + 1)];

					if (fX < fXMiddle)
					{
						if (fXNext <= fXMiddle) continue;
					}
					else if (fX == fXMiddle)
					{
						if (fXNext <= fXMiddle) continue;

						pAreaData[index++] = fX;
						pAreaData[index++] = fY;
					}
					else // fX > fXMiddle
					{
						pAreaData[index++] = fXMiddle;
						pAreaData[index++] = fY;

						pAreaData[index++] = fX;
						pAreaData[index++] = fY;
					}
				}
				else if (k == m_iSampleNum - 1)
				{
					fXPre = pXYData[2 * (i * m_iSampleNum + k - 1)];
					fYPre = pXYData[2 * (i * m_iSampleNum + k - 1) + 1];

					if (fX < fXMiddle)
					{
						if (fXPre <= fXMiddle) continue;
						else
						{
							y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

							pAreaData[index++] = fXMiddle;
							pAreaData[index++] = y;

							m_vecAreaCount.push_back(index / 2);
						}
					}
					else if (fX == fXMiddle)
					{
						if (fXPre > fXMiddle)
						{
							pAreaData[index++] = fX;
							pAreaData[index++] = fY;

							m_vecAreaCount.push_back(index / 2);
						}
					}
					else // fX > fXMiddle
					{
						if (fXPre < fXMiddle)
						{
							y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

							pAreaData[index++] = fXMiddle;
							pAreaData[index++] = y;
						}

						pAreaData[index++] = fXMiddle;
						pAreaData[index++] = fY;

						pAreaData[index++] = fX;
						pAreaData[index++] = fY;

						m_vecAreaCount.push_back(index / 2);
					}
				}
				else // 0<k<data.m_nSamplingQty
				{
					fXPre = pXYData[2 * (i * m_iSampleNum + k - 1)];
					fYPre = pXYData[2 * (i * m_iSampleNum + k - 1) + 1];

					fXNext = pXYData[2 * (i * m_iSampleNum + k + 1)];
					//fYNext = pXYData[2*(i*data.m_nSamplingQty + k+1)+1];

					if (fX == fXMiddle)
					{
						if (fXPre > fXMiddle)
						{
							pAreaData[index++] = fX;
							pAreaData[index++] = fY;

							m_vecAreaCount.push_back(index / 2);
						}

						if (fXNext > fXMiddle)
						{
							pAreaData[index++] = fX;
							pAreaData[index++] = fY;
						}
					}
					else if (fX < fXMiddle)
					{
						if (fXPre <= fXMiddle) continue;
						else
						{
							y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

							pAreaData[index++] = fXMiddle;
							pAreaData[index++] = y;

							m_vecAreaCount.push_back(index / 2);
						}
					}
					else // fX > fXMiddle
					{
						if (fXPre < fXMiddle)
						{
							y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

							pAreaData[index++] = fXMiddle;
							pAreaData[index++] = y;
						}

						pAreaData[index++] = fXMiddle;
						pAreaData[index++] = fY;

						pAreaData[index++] = fX;
						pAreaData[index++] = fY;
					}
				}
			}
		}


		m_pBuilder->SetAreaData(pAreaData, m_vecAreaCount.back() * 2);
		delete[] pAreaData;
	}

	delete[] pXYData;
}

void XSceneGather::drawBackground(QPainter* painter, const QRectF&)
{
	if (!m_pBuilder)
		return;

	XDlgGatherWin *pWin = (XDlgGatherWin *)parent();

	painter->beginNativePainting();

	if (m_iTraceNum > 0)
	{
		m_pBuilder->EnableBackgroundSwitch(pWin->palette().color(pWin->backgroundRole()));
		m_pBuilder->DrawWiggle(m_iTraceNum, m_iSampleNum, QVector4D(0.f, 0.f, 0.f, 1.f), m_viewInfo.GetShowWiggle());
		m_pBuilder->DrawArea(m_vecAreaCount, QVector4D(0.f, 0.f, 0.f, 1.f), m_viewInfo.GetShowVA());
		m_pBuilder->DrawTexture(m_viewInfo.GetShowVI());
		m_pBuilder->DisableBackgroundSwitch();
	}
	else
	{
		m_pBuilder->Update(pWin->palette().color(pWin->backgroundRole()));
	}

	painter->endNativePainting();
}

void XSceneGather::UpdateROI(float fLeft, float fRight, float fBottom, float fTop)
{
	m_pView->GetGLWidget()->makeCurrent();
	if (m_pBuilder)
	{
		m_pBuilder->UpdateROI(fLeft, fRight, fBottom, fTop);
	}
	m_pView->GetGLWidget()->doneCurrent();
}

void XSceneGather::GetCanvasSize(int& iWidth, int& iHeight)
{
	iWidth = m_viewInfo.GetHScale() * m_iTraceNum;
	iHeight = m_viewInfo.GetVScale() * m_iSampleNum;
}