#ifndef XRANDOMLINEITEM_H
#define XRANDOMLINEITEM_H

#include "xabstractitem.h"
#include <vector>

using std::vector;

class CX2DSectionWindow;

class CXRandomLineItem : public CXAbstractItem
{
public:
	CXRandomLineItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
	~CXRandomLineItem(void);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const;

protected:
	virtual void _UpdateData();

private:
	vector<double> m_vecDataRatio;

	int m_nLineWidth;
};

#endif // KERANDOMLINEITEM_H
