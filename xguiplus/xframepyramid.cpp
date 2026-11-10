#include <qpainter.h>
#include "xframepyramid.h"

CXFramePyramid::CXFramePyramid(QWidget *parent) : QFrame(parent)
{
}

void CXFramePyramid::paintEvent(QPaintEvent *)
{
	drawAnno();
}

void CXFramePyramid::drawAnno()
{
	QPainter painter(this);
	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);
	painter.setPen("gray");
	QRect rect = this->rect().adjusted(50, 50, -20, -20);
	painter.drawRect(rect);
}