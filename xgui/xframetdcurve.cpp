#include <qpainter.h>
#include "xframetdcurve.h"

#define MARGIN 30

CXFrameTDCurve::CXFrameTDCurve(QWidget *parent) : QFrame(parent)
{
}

CXFrameTDCurve::~CXFrameTDCurve()
{
}

void CXFrameTDCurve::Populate(double* pData, int iNum)
{
	m_pDData = pData;
	m_pTData = pData + iNum;
	m_iNum = iNum;

	update();
}

void CXFrameTDCurve::paintEvent(QPaintEvent *)
{
	if (m_iNum == 0)
		return;

	drawAnno();
	drawCurve();
}

void CXFrameTDCurve::drawAnno()
{
	int i;
	qreal x, y;
	QPainter painter(this);
	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);
	painter.setPen("gray");

	QRect rect = this->rect().adjusted(2 * MARGIN, 2 * MARGIN, -10, 0);

	QVector<QPointF> vecPoints;
	int iMaxD = ((int)(m_pDData[m_iNum - 1] / 100) + 1) * 100;
	m_dVScale = 1. * rect.height() / iMaxD;
	for (i = 0; i <= iMaxD; i += 500)
	{
		y = rect.top() + i * m_dVScale;
		vecPoints << QPointF(rect.left() - 10, y) << QPointF(rect.right(), y);

		painter.drawText(rect.x() - 55, y - 10, 40, 20, Qt::AlignRight, QString::number(i));
	}

	int iMaxT = ((int)(m_pTData[m_iNum - 1] / 100) + 1) * 100;
	m_dHScale = 1. * rect.width() / iMaxT;
	for (i = 0; i <= iMaxT; i += 250)
	{
		x = rect.left() + i * m_dHScale;
		vecPoints << QPointF(x, rect.top() - 10) << QPointF(x, rect.bottom());

		painter.drawText(x - 20, rect.top() - 30, 40, 20, Qt::AlignCenter, QString::number(i));
	}

	painter.drawLines(vecPoints);

	painter.drawText(5, rect.top() + 10, 40, 20, Qt::AlignLeft, "TVDSS");
	painter.drawText(rect.left() + 10, rect.top() - 40, 40, 20, Qt::AlignLeft, "Time");
}

void CXFrameTDCurve::drawCurve()
{
	qreal x, y;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::blue, 2));

	QPainterPath qPath;
	qPath.moveTo(2 * MARGIN, 2 * MARGIN);
	for (int i = 0; i < m_iNum; i++)
		qPath.lineTo(2 * MARGIN + m_pTData[i] * m_dHScale, 2 * MARGIN + m_pDData[i] * m_dVScale);

	painter.drawPath(qPath);
}