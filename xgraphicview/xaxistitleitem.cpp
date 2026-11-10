#include "xaxistitleitem.h"
#include <qpainter.h>
#include <qfont.h>
#include "xscene.h"

CXAxisTitleItem::CXAxisTitleItem(QString sName, QGraphicsItem *parent): QGraphicsItem(parent)
{
	m_sName = sName;
}

void CXAxisTitleItem::Populate(bool bHorizontal, bool bTopLeft)
{
	m_bHorizontal	= bHorizontal;
	m_bTopLeft		= bTopLeft;
}

QRectF CXAxisTitleItem::boundingRect() const
{
	return QRectF(0, 0, scene()->width(), scene()->height());
}

void CXAxisTitleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	CXScene *pScene = (CXScene *)scene();
	qreal height = pScene->GetCanvasHeight();
	qreal width = pScene->GetCanvasWidth();

	if(m_bHorizontal)
	{
		painter->save();
		painter->setFont(QFont("Times", 16));
		if(m_bTopLeft)
		{
			painter->drawText(QRectF(0, -40, pScene->GetCanvasWidth(), 50), Qt::AlignHCenter, m_sName);
		}
		else
		{
			painter->drawText(QRectF(0, pScene->GetCanvasHeight() - 30, pScene->GetCanvasWidth(), 30), Qt::AlignHCenter, m_sName);
		}
		painter->restore();
	}
	else
	{
		painter->save();
		painter->setFont(QFont("Times", 16));
		
		if(m_bTopLeft)
		{
			painter->translate(15, pScene->GetCanvasHeight());
			painter->rotate(-90);
		}
		else
		{
			painter->translate(pScene->GetCanvasWidth() + 60, 20);
			painter->rotate(90);
		}
		painter->drawText(QRectF(0, 0, pScene->GetCanvasHeight(), 50), Qt::AlignHCenter, m_sName);
		painter->restore();
	}
}