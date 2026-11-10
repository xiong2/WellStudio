#ifndef _CXAXISTITLEITEM_H__
#define _CXAXISTITLEITEM_H__

#include <qgraphicsitem.h>
#include "xgraphicview_global.h"

class XGRAPHICVIEW_EXPORT CXAxisTitleItem: public QGraphicsItem
{
public:
	CXAxisTitleItem(QString sName, QGraphicsItem *parent = 0);

	void Populate(bool bHorizontal, bool bTopLeft);

	QRectF boundingRect() const;

	QString GetName()
	{
		return m_sName;
	}

	void SetName(QString sName)
	{
		m_sName = sName;
	}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	QString		m_sName;
	bool		m_bHorizontal;		//	Horizontal or vertical axis?
	bool		m_bTopLeft;			//	On the top (horizontal) or on the left (vertical) axis?
};

#endif