#include <qpainter.h>
#include "xframewtcorner.h"

CXFrameWTCorner::CXFrameWTCorner(QWidget *parent) : QFrame(parent)
{
}

CXFrameWTCorner::~CXFrameWTCorner()
{
}

void CXFrameWTCorner::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setPen("black");
	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);
	QRect rect = this->rect();

	if (m_bShowTWT)
	{
		painter.drawText(0, rect.bottom() - 45, rect.width(), 20, Qt::AlignCenter, "Time");
		painter.drawText(0, rect.bottom() - 25, rect.width(), 20, Qt::AlignCenter, "(ms)");
	}
	else
	{
		painter.drawText(0, rect.bottom() - 45, rect.width(), 20, Qt::AlignCenter, "TVDSS");
		painter.drawText(0, rect.bottom() - 25, rect.width(), 20, Qt::AlignCenter, "(m)");
	}
}