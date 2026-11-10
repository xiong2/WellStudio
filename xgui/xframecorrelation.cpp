#include <qpainter.h>
#include "xframecorrelation.h"

void CXFrameCorrelation::Populate(int iHalfWin, double dStep, float *pData)
{
	m_iHalfWin = (int)(iHalfWin * dStep);
	int iWin = iHalfWin * 2;

	m_poly.clear();
	m_rect = this->rect();
	m_rect.adjust(30, 40, -20, -20);

	m_poly << QPointF(m_rect.x(), m_rect.top() + (1 - pData[0]) * m_rect.height() / 2);
	m_fMaxCor = pData[0];
	m_fMaxPos = 0 - dStep * iHalfWin;
	m_dPos = m_rect.x();
	m_fZeroCor = pData[iHalfWin];
	for (int i = 1; i <= iWin; i++)
	{
		if (pData[i] > m_fMaxCor)
		{
			m_fMaxCor = pData[i];
			m_fMaxPos = dStep * (i - m_iHalfWin);
			m_dPos = m_rect.x() + m_rect.width() * i / iWin;
		}

		m_poly << QPointF(m_rect.x() + m_rect.width() * i / iWin, m_rect.top() + (1 - pData[i]) * m_rect.height() / 2);
	}

	update();
}

void CXFrameCorrelation::adjustCurve()
{
	QRect rect = this->rect();
	rect.adjust(30, 40, -20, -20);

	if (qAbs(rect.width() - m_rect.width()) > 5 || qAbs(rect.height() - m_rect.height()) > 5)
	{
		float fH = 1. * rect.width() / m_rect.width();
		float fV = 1. * rect.height() / m_rect.height();

		for (int i = 0; i < m_poly.size(); i++)
		{
			m_poly[i].setX((m_poly[i].x() - 30) * fH + 30);
			m_poly[i].setY((m_poly[i].y() - 40) * fV + 40);
		}

		m_dPos = (m_dPos - 30) * fH + 30;
		m_rect = rect;
	}
}

void CXFrameCorrelation::paintEvent(QPaintEvent *)
{
	showGrid();

	if (m_poly.isEmpty())
		return;

	adjustCurve();

	QPainter painter(this);
	painter.setPen(QPen(Qt::blue, 2));
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPolyline(m_poly);

	painter.setPen("black");
	QRect rect = this->rect();

	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);

	QString sDir = " ms up";
	if (m_fMaxPos > 0)
		sDir = " ms down";
	QString str1 = "Zero lag Coeff. = " + QString::number(m_fZeroCor);
	QString str2 = "Max Coeff. = " + QString::number(m_fMaxCor) + " at time shift " + QString::number(qAbs(m_fMaxPos)) + sDir;
	painter.drawText(rect.x(), 0, rect.width(), 15, Qt::AlignCenter, str1);
	painter.drawText(rect.x(), 15, rect.width(), 20, Qt::AlignCenter, str2);

	painter.setPen("red");
	rect.adjust(30, 40, -20, -20);
	painter.drawLine(m_dPos, rect.top(), m_dPos, rect.bottom());
}

void CXFrameCorrelation::showGrid()
{
	QPainter painter(this);
	painter.setPen("grey");
	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);

	QRect rect = this->rect();
	rect.adjust(30, 40, -20, -20);
	painter.drawRect(rect);

	painter.drawLine(rect.x(), rect.y() + rect.height() / 2, rect.right(), rect.y() + rect.height() / 2);

	int i, iNum = (m_poly.size() - 1);
	QStringList sList;
	sList << "-" + QString::number(m_iHalfWin) << "-" + QString::number(m_iHalfWin / 2) << "0" << QString::number(m_iHalfWin / 2) << QString::number(m_iHalfWin);
	for (i = 0; i <= 4; i++)
	{
		painter.drawLine(rect.x() + i * rect.width() / 4, rect.y(), rect.x() + i * rect.width() / 4, rect.bottom() + 5);
		painter.drawText(rect.x() + i * rect.width() / 4 -  15, rect.bottom() + 5, 30, 20, Qt::AlignCenter, sList[i]);
	}

	sList.clear();
	sList << "-1.0" << "0" << "1.0";
	for (i = 0; i <= 2; i++)
	{
		painter.drawText(rect.x() - 25, rect.bottom() - i * rect.height() / 2 - 5, 20, 20, Qt::AlignRight, sList[i]);
	}
	painter.drawLine(rect.x(), rect.y() + rect.height() / 2, rect.right(), rect.y() + rect.height() / 2);
}