#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <qpainter.h>
#include <qevent.h>
#include <qdebug.h>
#include <vector>
#include <math.h>
#include "xthreadpyramid.h"
#include "xscenepyramid.h"
#include "xseismicdatavolume.h"
#include "xsectionbuilder.h"
#include "xcolormap.h"
#include "xitempyrect.h"
#include "xdlgpyramid.h"

XScenePyramid::XScenePyramid(QObject *parent) : QGraphicsScene(parent)
{
	m_colors[0].setW(-1.);
}

XScenePyramid::~XScenePyramid()
{
	if (m_pBuilder)
		delete m_pBuilder;

	if (m_pRectItem)
		delete m_pRectItem;

	ClearSection();
}

void XScenePyramid::SetPolygon(QPolygonF polygon)
{
	int iWWidth, iWHeight, iIWidth, iIHeight;
	QRectF bRect = polygon.boundingRect();
	iWWidth = bRect.width();
	iWHeight = bRect.height();

	iIWidth = iWWidth / m_dRatio;
	iIHeight = iWHeight / m_dRatio;
	int m, i = bRect.x() / m_dRatio, j = bRect.y() / m_dRatio, iLen = iIWidth * iIHeight;
	float *pNDataBuff = new float[iLen];
	for (m = 0; m < iIWidth; m++)
	{
		memcpy(pNDataBuff + m * iIHeight, m_pDataBuff + (i + m) * m_iImgHei + j, iIHeight * sizeof(float));
	}

	double dAvg = 0.;
	for (m = 0; m < iLen; m++)
		dAvg += pNDataBuff[m];
	dAvg /= iLen;

	m_polygon.clear();
	foreach(QPointF point, polygon)
	{
		m_polygon << QPointF(point.x() / m_dRatio, point.y() / m_dRatio);
	}

	QPolygonF imgPolygon = m_polygon.translated(0 - m_polygon.boundingRect().x(), 0 - m_polygon.boundingRect().y());

	for (i = 0; i < iIWidth; i++)
	{
		for (j = 0; j < iIHeight; j++)
		{
			if (!imgPolygon.containsPoint(QPointF(i, j), Qt::OddEvenFill))
				pNDataBuff[i * iIHeight + j] = dAvg;
		}
	}
	XDlgPyramid *pDlg = dynamic_cast<XDlgPyramid *>(parent());
	pDlg->CalVar(pNDataBuff, iWWidth, iWHeight, iIWidth, iIHeight);
}

void XScenePyramid::InitializeRect(bool bInitialize)
{
	if (bInitialize)
	{
		if (m_pRectItem)
		{
			removeItem(m_pRectItem);
			delete m_pRectItem;
		}

		m_pRectItem = new XItemPyRect(this);
		addItem(m_pRectItem);
	}
	else
	{
		if (m_pRectItem)
		{
			removeItem(m_pRectItem);
			delete m_pRectItem;
			m_pRectItem = nullptr;
		}
	}
}

void XScenePyramid::ClearSection()
{
	if (m_pImgData)
	{
		delete[]m_pImgData;
		m_pImgData = nullptr;

		delete[]m_pDataBuff;
		m_pDataBuff = nullptr;

		delete[]m_pDFiltered;
		m_pDFiltered = nullptr;
	}
}

void XScenePyramid::BuildSection(CXSeismicDataVolume *pDV, int iDir, int iNo, int iAng, bool bFilter)
{
	if (m_colors[0].w() == -1.)
	{
		//	Initialize it now.
		auto pColormap = CXColormap::GetColormap("greyscale");
		for (auto i = 0; i < 256; ++i)
		{
			QColor color = (i == 255) ? pColormap->GetInvalidColor() : pColormap->GetColorAt(i);
			m_colors[i].setX(color.redF());
			m_colors[i].setY(color.greenF());
			m_colors[i].setZ(color.blueF());
			m_colors[i].setW(color.alphaF());
		}
	}

	if (!m_pBuilder)
	{
		m_pBuilder = new CXSectionBuilder;
	}

	pDV->GetDataRange(m_dMin, m_dSpan);
	m_dSpan -= m_dMin;
	m_dSpan *= 0.8;

	if (iDir == 0)
	{
		//	Inline.
		if (!m_pImgData)
		{
			m_iImgWid = pDV->GetXlineQty();
			m_iImgHei = pDV->GetSamplingQty();
			m_pImgData = new unsigned int[m_iImgWid * m_iImgHei];
			m_pDataBuff = new float[m_iImgWid * m_iImgHei];
			m_pDFiltered = new float[m_iImgWid * m_iImgHei];
		}

		pDV->ReadInline(iNo, m_pDataBuff);
	}
	else if (iDir == 1)
	{
		//	Crossline.
		if (!m_pImgData)
		{
			m_iImgWid = pDV->GetInlineQty();
			m_iImgHei = pDV->GetSamplingQty();
			m_pImgData = new unsigned int[m_iImgWid * m_iImgHei];
			m_pDataBuff = new float[m_iImgWid * m_iImgHei];
			m_pDFiltered = new float[m_iImgWid * m_iImgHei];
		}

		pDV->ReadXline(iNo, m_pDataBuff);
	}
	else if (iDir == 2)
	{
		//	Time slice.
		if (!m_pImgData)
		{
			m_iImgWid = pDV->GetInlineQty();
			m_iImgHei = pDV->GetXlineQty();
			m_pImgData = new unsigned int[m_iImgWid * m_iImgHei];
			m_pDataBuff = new float[m_iImgWid * m_iImgHei];
			m_pDFiltered = new float[m_iImgWid * m_iImgHei];
		}

		pDV->ReadSlice(iNo, m_pDataBuff);
	}
	else
		return;

	m_dRatio = 1.;
	if (m_iImgHei < 800)
		m_dRatio = 800. / m_iImgHei;
	else if (m_iImgHei > 1000)
		m_dRatio = 1000. / m_iImgHei;

	QDialog *pDlg = (QDialog *)parent();
	//pDlg->resize(m_iImgWid + 400, m_iImgHei);
	QSize qSize(m_iImgWid * m_dRatio + 400, m_iImgHei * m_dRatio);
	QSize cSize = pDlg->maximumSize();
	if (cSize != qSize)
	{
		pDlg->setMaximumSize(qSize);
		pDlg->setMinimumSize(qSize);
		pDlg->update();
		pDlg->move(pDlg->pos() + QPoint(1, 1));
	}

	BuildSection(iAng, bFilter);
}

void XScenePyramid::BuildSection(int iAng, bool bFilter)
{
	if (!m_pImgData)
		return;

	float *pRes = m_pDataBuff;
	if (bFilter)
	{
		Pyramid_Filter::S_Filtering(m_iImgWid, m_iImgHei, m_pDataBuff, m_pDFiltered, (double)iAng);
		pRes = m_pDFiltered;
	}

	qint64 iLen = m_iImgWid * m_iImgHei;
	float dMin = pRes[0], dMax = pRes[1];
	for (qint64 k = 1; k < iLen; k++)
	{
		dMin = dMin < pRes[k] ? dMin : pRes[k];
		dMax = dMax > pRes[k] ? dMax : pRes[k];
	}
	float dSpan = dMax - dMin;
	if (dSpan == 0.)
		return;

	for (auto i = 0; i < m_iImgWid; ++i)
	{
		for (auto k = 0; k < m_iImgHei; ++k)
		{
			double dCurrValue = static_cast<double>(pRes[i * m_iImgHei + k]);

			int index;
			index = static_cast<int>((dCurrValue - dMin) / dSpan * 254);
			index = qBound(0, index, 254);

			m_pImgData[(m_iImgHei - 1 - k) * m_iImgWid + i] = QColor(index, index, index).rgba();
		}
	}

	QImage image(reinterpret_cast<uchar*>(m_pImgData), m_iImgWid, m_iImgHei, QImage::Format_RGB32);

	m_pBuilder->SetTextureData(image, m_colors);
}

void XScenePyramid::drawBackground(QPainter* painter, const QRectF&)
{
	if (!m_pBuilder || !m_pImgData)
		return;

	painter->beginNativePainting();

	m_pBuilder->DrawTexture(true);

	painter->endNativePainting();
}

void XScenePyramid::HandleMouseEvent(QMouseEvent *event)
{
	if (m_pRectItem)
		m_pRectItem->HandleMouseEvent(event);
}