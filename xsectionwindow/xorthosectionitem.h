#ifndef _CXORTHOSECTIONITEM_H__
#define _CXORTHOSECTIONITEM_H__

#include "xabstractitem.h"
class CXSectionScene;
class CXSeismicSection;

class CXOrthoSectionItem : public CXAbstractItem
{
public:
	CXOrthoSectionItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
	~CXOrthoSectionItem(void);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const;

	virtual void HandleMouseEvent(QMouseEvent *, EXMouseEventType);

protected:
	virtual void _UpdateData();

	void _leftButtonPressed(QMouseEvent *);
	void _buttonRelease();
	void _mouseMoving(QMouseEvent *);

	QVector<QUuid>	m_vecSectionID;
	QVector<double>	m_vecSectionRatio;
	
	int	m_iDraggingIndex = -1;
};

#endif