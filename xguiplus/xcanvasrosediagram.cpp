#include <QPainter>
#include <QtMath>
#include <qmessagebox.h>
#include "xcanvasrosediagram.h"
#include "xseismicirregularreader.h"
#include "xwaitcursor.h"
#include "xcolormap.h"

#define MARGIN 20

CXCanvasRoseDiagram::CXCanvasRoseDiagram(QWidget *parent)
	: QFrame(parent)
{
	m_gridColor = QColor("green");
	m_roseColor.setRgb(210, 127, 111, 153);
	m_strColormap = "greyscale";

	m_iNumRose = 0;
	m_iNumBins = 0;
	m_iStartRose = -5;
	m_iEndRose = 355;
	m_pTotalQuant = NULL;
	m_pRoseQuant = NULL;
	m_pBinQuant = NULL;
}

CXCanvasRoseDiagram::~CXCanvasRoseDiagram()
{
	if (m_pTotalQuant)
	{
		delete[]m_pTotalQuant;
		delete[]m_pRoseQuant;
		delete[]m_pBinQuant;
	}
}

void CXCanvasRoseDiagram::Refresh(unsigned int iNumRose, int iStartRose, int iEndRose, unsigned int iNumBin)
{
	CXWaitCursor cursor;
	m_iNumRose = iNumRose;
	m_iNumBins = iNumBin;
	m_iStartRose = iStartRose;
	m_iEndRose = iEndRose;

	if (m_pTotalQuant)
	{
		delete[]m_pTotalQuant;
		delete[]m_pRoseQuant;
		delete[]m_pBinQuant;

		m_pTotalQuant = NULL;
	}

	char *pBuffer = m_pReader->GetBuffer();
	int iMaxFold = m_pReader->GetMaxFold();
	unsigned short iMinOffset = m_pReader->GetMinOffset();
	unsigned short iMaxOffset = m_pReader->GetMaxOffset();
	float fOffsetStep = 1. * (iMaxOffset - iMinOffset) / m_iNumBins;
	float fRoseStep = 1. * (m_iEndRose - m_iStartRose) / m_iNumRose;

	if (fOffsetStep == 0.)
	{
		QMessageBox::warning(NULL, "Rose Diagram", "The seismic data contains only one offset, can not show it's rose diagram.");
		return;
	}
	else if (fRoseStep == 0.)
	{
		QMessageBox::warning(NULL, "Rose Diagram", "The seismic data contains only one azimuth, can not show it's rose diagram.");
		return;
	}

	m_pTotalQuant = new unsigned int[m_iNumBins * m_iNumRose];
	memset(m_pTotalQuant, 0, sizeof(int) * m_iNumBins * m_iNumRose);
	m_pRoseQuant = new unsigned int[m_iNumRose];
	memset(m_pRoseQuant, 0, sizeof(int) * m_iNumRose);
	m_pBinQuant = new unsigned int[m_iNumBins];
	memset(m_pBinQuant, 0, sizeof(int) * m_iNumBins);
	m_iMaxTotal = m_iMaxRose = m_iMaxBin = 0;

	//	Full fill the bins.
	int i, j, iGatherSize = 10 + 4 * iMaxFold;
	for (i = 0; i < m_iNumGather; i++)
	{
		short *pSh = (short *)(pBuffer + i * iGatherSize);
		for (j = 0; j < pSh[4]; j++)
		{
			int iRoseID = (int)((pSh[5 + j * 2 + 1] - m_iStartRose - 0.1) / fRoseStep);
			int iBinID = (int)((pSh[5 + j * 2] - iMinOffset - 0.1) / fOffsetStep);

			if (iRoseID >= m_iNumRose)
				continue;

			m_pTotalQuant[iRoseID * m_iNumBins + iBinID]++;
		}
	}

	//	Statistics along rose.
	for (i = 0; i < m_iNumRose; i++)
	{
		for (j = 0; j < m_iNumBins; j++)
		{
			m_pRoseQuant[i] += m_pTotalQuant[i * m_iNumBins + j];
			m_iMaxTotal = m_iMaxTotal > m_pTotalQuant[i * m_iNumBins + j] ? m_iMaxTotal : m_pTotalQuant[i * m_iNumBins + j];
		}

		m_iMaxRose = m_iMaxRose > m_pRoseQuant[i] ? m_iMaxRose : m_pRoseQuant[i];
	}

	//	Statistics  along bin.
	for (j = 0; j < m_iNumBins; j++)
	{
		for (i = 0; i < m_iNumRose; i++)
		{
			m_pBinQuant[j] += m_pTotalQuant[i * m_iNumBins + j];
		}

		m_iMaxBin = m_iMaxBin > m_pBinQuant[j] ? m_iMaxBin : m_pBinQuant[j];
	}

	update();
}

void CXCanvasRoseDiagram::paintEvent(QPaintEvent *)
{
	int iWidth = width();
	int iHeight = height();
	m_iRadius = qMin(iWidth, iHeight) / 2 - 3 * MARGIN;

	m_qOriPoint.setX(iWidth / 2);
	m_qOriPoint.setY(iHeight / 2);

	//	Background.
	QPainter painter(this);
	painter.fillRect(MARGIN, MARGIN, iWidth - 2 * MARGIN, iHeight - 2 * MARGIN, QColor(240, 240, 255));

	if (m_bBins && m_pTotalQuant)
		drawBins();

	drawBackground();

	//	Check whether data is ready.
	if (!m_pTotalQuant)
		return;

	if (m_bGrid)
		drawGrid();

	if (m_bRose)
		drawRose();

	if (m_bHisto)
		drawHisto();
}

void CXCanvasRoseDiagram::drawBackground()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	//	Axes.
	painter.save();
	painter.setPen(m_gridColor);
	painter.drawLine(m_qOriPoint.x() - m_iRadius - MARGIN, m_qOriPoint.y(), m_qOriPoint.x() + m_iRadius + MARGIN + 1, m_qOriPoint.y());
	painter.drawLine(m_qOriPoint.x(), m_qOriPoint.y() - m_iRadius - MARGIN, m_qOriPoint.x(), m_qOriPoint.y() + m_iRadius + MARGIN + 1);

	painter.drawText(m_qOriPoint.x() - 5, m_qOriPoint.y() - m_iRadius - MARGIN - 5, "90");
	painter.drawText(m_qOriPoint.x() + m_iRadius + MARGIN + 5, m_qOriPoint.y() + 3, "E");
	painter.drawText(m_qOriPoint.x() - 10, m_qOriPoint.y() + m_iRadius + MARGIN + 15, "270");
	painter.drawText(m_qOriPoint.x() - m_iRadius - MARGIN - 25, m_qOriPoint.y() + 3, "180");

	painter.drawEllipse(m_qOriPoint.x() - m_iRadius, m_qOriPoint.y() - m_iRadius, 2 * m_iRadius + 1, 2 * m_iRadius + 1);
	//QPolygon arrow;
	//painter.setBrush(QBrush(m_gridColor));
	//arrow << QPoint(m_qOriPoint.x(), m_qOriPoint.y() - m_iRadius - MARGIN)
	//	<< QPoint(m_qOriPoint.x() + 4, m_qOriPoint.y() - m_iRadius - MARGIN + 15)
	//	<< QPoint(m_qOriPoint.x() - 4, m_qOriPoint.y() - m_iRadius - MARGIN + 15);
	//painter.drawConvexPolygon(arrow);
	painter.restore();
}

void CXCanvasRoseDiagram::drawGrid()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.save();
	QPen pen(Qt::DashLine);
	QColor gridColor(m_gridColor);
	gridColor.setAlpha(128);
	pen.setColor(gridColor);
	painter.setPen(pen);

	//	Draw concentric circles first.
	int i;
	float fStep = 1. * m_iRadius / m_iNumBins;
	for (i = 1; i < m_iNumBins; i++)
	{
		painter.drawEllipse(m_qOriPoint.x() - i * fStep, m_qOriPoint.y() - i * fStep, 2 * i * fStep + 1, 2 * i * fStep + 1);
	}

	for (i = 1; i < 12; i++)
	{
		if (i % 3 == 0)
			continue;

		QPoint endPoint((int)(m_qOriPoint.x() + cos(M_PI * i / 6) * m_iRadius), (int)(m_qOriPoint.y() + sin(M_PI * i / 6) * m_iRadius));
		painter.drawLine(m_qOriPoint, endPoint);
	}

	painter.restore();
}

void CXCanvasRoseDiagram::drawRose()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QColor frameColor = m_roseColor;
	frameColor.setAlpha(255);
	QPen pen(frameColor, 2);

	painter.save();

	int iAngleStep = 16 * (m_iEndRose - m_iStartRose) / m_iNumRose;
		
	for (int i = 0; i < m_iNumRose; i++)
	{
		int iRadius = (int)(1. * m_iRadius * m_pRoseQuant[i] / m_iMaxRose);
		if (iRadius < 1)
			continue;
		//int iAngle = (90 - (int)(m_iStartRose + 1. * (m_iEndRose - m_iStartRose) * i / m_iNumRose)) * 16;
		int iAngle = (int)((m_iStartRose + 1. * (m_iEndRose - m_iStartRose) * i / m_iNumRose) * 16);

		painter.setPen(pen);
		painter.setBrush(Qt::NoBrush);
		painter.drawPie(m_qOriPoint.x() - iRadius, m_qOriPoint.y() - iRadius, 2 * iRadius + 1, 2 * iRadius + 1, iAngle, iAngleStep);

		painter.setPen(m_roseColor);
		painter.setBrush(QBrush(m_roseColor));
		painter.drawPie(m_qOriPoint.x() - iRadius, m_qOriPoint.y() - iRadius, 2 * iRadius + 1, 2 * iRadius + 1, iAngle, iAngleStep);
	}

	painter.restore();
}

void CXCanvasRoseDiagram::drawBins()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.save();
	CXColormap *pColormap = CXColormap::GetColormap(m_strColormap);
	float fRoseStep = 1. * (m_iEndRose - m_iStartRose) / m_iNumRose;
	painter.setPen(Qt::NoPen);

	int i, j;
	for (i = 0; i < m_iNumRose; i++)
	{
		for (j = 0; j < m_iNumBins; j++)
		{
			unsigned short iColorIDX = m_pTotalQuant[i * m_iNumBins + j] * (pColormap->GetColorNum() - 1) / m_iMaxTotal;
			int iSRadius = j * m_iRadius / m_iNumBins, iLRadius = (j + 1) * m_iRadius / m_iNumBins;
			//qreal fSAngle = 90 - m_iStartRose - 1. * (m_iEndRose - m_iStartRose) * i / m_iNumRose;
			qreal fSAngle = m_iStartRose + 1. * (m_iEndRose - m_iStartRose) * i / m_iNumRose;
			QPainterPath path(m_qOriPoint + QPointF(iSRadius * cos(fSAngle * M_PI / 180), (-1) * iSRadius * sin(fSAngle * M_PI / 180)));
			path.arcTo(m_qOriPoint.x() - iSRadius, m_qOriPoint.y() - iSRadius, 2 * iSRadius + 1, 2 * iSRadius + 1, fSAngle, fRoseStep);
			path.arcTo(m_qOriPoint.x() - iLRadius, m_qOriPoint.y() - iLRadius, 2 * iLRadius + 1, 2 * iLRadius + 1, fSAngle + fRoseStep, -fRoseStep);
			path.closeSubpath();
			painter.setBrush(QBrush(pColormap->GetColorAt(iColorIDX)));
			painter.drawPath(path);
		}
	}

	painter.restore();
}

void CXCanvasRoseDiagram::drawHisto()
{
	int iTWidth = 140;
	int iTHeight = 80;
	int iTLX = width() - 2 * MARGIN - iTWidth;
	int iTLY = height() - 2 * MARGIN - iTHeight;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.save();
	CXColormap *pColormap = CXColormap::GetColormap(m_strColormap);

	for (int i = 0; i < m_iNumBins; i++)
	{
		unsigned short iColorIDX = m_pBinQuant[i] * (pColormap->GetColorNum() - 1) / m_iMaxBin;
		int iHeight = iTHeight * m_pBinQuant[i] / m_iMaxBin;
		painter.setBrush(QBrush(pColormap->GetColorAt(iColorIDX)));
		painter.drawRect(iTLX +  i * iTWidth / m_iNumBins, iTLY + iTHeight - iHeight, iTWidth / m_iNumBins, iHeight);
	}

	QString sLLabel = QString::number(m_pReader->GetMinOffset()) + "m";
	QString sRLabel = QString::number(m_pReader->GetMaxOffset()) + "m";
	painter.drawText(iTLX - 15, iTLY + iTHeight + 15, sLLabel);
	painter.drawText(iTLX + iTWidth - 20, iTLY + iTHeight + 15, sRLabel);

	painter.restore();
}