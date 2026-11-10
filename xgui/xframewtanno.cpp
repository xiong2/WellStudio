#include <qpainter.h>
#include "xframewtanno.h"
#include "xseismicdatavolume.h"
#include "xwelltd.h"

#define MARGIN 0

CXFrameWTAnno::CXFrameWTAnno(QWidget *parent) : QFrame(parent)
{
}

CXFrameWTAnno::~CXFrameWTAnno()
{
}

void CXFrameWTAnno::paintEvent(QPaintEvent *)
{
	if (!m_pDV || !m_pTD)
		return;

	double dZS, dZE, dZStep, fVScale = 1.;
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);

	QPainter painter(this);
	painter.setPen("black");
	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);

	QRect rect = this->rect();
	int x = rect.right() - MARGIN;

	int iS;
	if (m_iType == 0)
	{
		//	Time anno.
		iS = ((int)(dZS / 20)) * 20;
		for (int iZ = iS; iZ < dZE; iZ += 20)
		{
			if (iZ <= dZS)
				continue;

			int y = (iZ - dZS) * fVScale;
			if ((int)(iZ - iS) % 100 == 0)
			{
				painter.drawLine(QPoint(x, y), QPoint(x - 10, y));
				painter.drawText(0, y - 10, 35, 20, Qt::AlignRight, QString::number(iZ));
			}
			else
			{
				painter.drawLine(QPoint(x, y), QPoint(x - 5, y));
			}
		}
	}
	else if(m_iType == 3)
	{
		//	SSTVD
		x = rect.left();
		double dDS = m_pTD->GetAValue(dZS, false);
		double dDE = m_pTD->GetAValue(dZE, false);
		iS = ((int)(dDS / 20)) * 20;
		for (int iD = iS; iD < dDE; iD += 20)
		{
			if (iD <= dDS)
				continue;

			int y = (int)m_pTD->GetAValue((double)iD);
			y = (y - dZS) * fVScale;
			if ((int)(iD - iS) % 100 == 0)
			{
				painter.drawLine(QPoint(x, y), QPoint(x + 10, y));
				painter.drawText(x + 15, y - 10, 35, 20, Qt::AlignLeft, QString::number(iD));
			}
			else
			{
				painter.drawLine(QPoint(x, y), QPoint(x + 5, y));
			}
		}
	}
}