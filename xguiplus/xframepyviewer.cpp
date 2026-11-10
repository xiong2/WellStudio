#include <qpainter.h>
#include "xframepyviewer.h"

XFramePyViewer::XFramePyViewer(QWidget *parent) : QFrame(parent)
{
}

int XFramePyViewer::SetVar(double *pVar)
{
	m_pVar = pVar;

	m_dMin = pVar[0];
	m_dMax = pVar[0];
	m_iMax = 0;

	for (int i = 1; i < 360; i++)
	{
		if (m_dMin > pVar[i])
			m_dMin = pVar[i];
		if (m_dMax < pVar[i])
		{
			m_dMax = pVar[i];
			m_iMax = i;
		}
	}

	return m_iMax;
}

void XFramePyViewer::paintEvent(QPaintEvent *)
{
	if (m_pVar)
		drawVar();
	else if (m_image.isNull())
		return;

	QPainter painter(this);
	painter.drawImage(rect(), m_image);
}

void XFramePyViewer::drawVar()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QRect rect = this->rect();

	painter.drawLine(rect.x() + 10, rect.bottom() - 30, rect.right() - 10, rect.bottom() - 30);
	painter.drawLine(rect.x() + 10, rect.top() + 5, rect.x() + 10, rect.bottom() - 30);

	int i, x, y;
	for (i = 0; i < 5; i++)
	{
		QString sAng = QString::number(i * 90);
		x = rect.x() + i * (rect.width() - 20) / 4;
		painter.drawText(x, rect.bottom() - 25, 20, 20, Qt::AlignCenter, sAng);
		painter.drawLine(x + 10, rect.bottom() - 30, x + 10, rect.bottom() - 28);
	}

	QPainterPath path;
	double dSpan = m_dMax - m_dMin;
	double dScale = (rect.height() - 40.) / dSpan;
	y = rect.bottom() - 30 - (m_pVar[0] - m_dMin) * dScale;
	path.moveTo(rect.x() + 10, y);

	for (i = 1; i < 360; i++)
	{
		x = rect.x() + 10 + i * (rect.width() - 20.) / 360;
		y = rect.bottom() - 32 - (m_pVar[i] - m_dMin) * dScale;
		path.lineTo(x, y);
	}
	painter.setPen("blue");
	painter.drawPath(path);

	painter.setPen("red");
	x = rect.x() + 10 + m_iMax * (rect.width() - 20.) / 360;
	painter.drawLine(x, rect.bottom() - 25, x, rect.top() + 2);
	painter.drawText(x, rect.bottom() - 50, 20, 20, Qt::AlignCenter, QString::number(m_iMax));

	int iMax2 = m_iMax;
	if (iMax2 < 180)
		iMax2 += 180;
	else
		iMax2 -= 180;
	x = rect.x() + 10 + iMax2 * (rect.width() - 20.) / 360;
	painter.drawLine(x, rect.bottom() - 25, x, rect.top() + 2);
	painter.drawText(x, rect.bottom() - 50, 20, 20, Qt::AlignCenter, QString::number(iMax2));
}