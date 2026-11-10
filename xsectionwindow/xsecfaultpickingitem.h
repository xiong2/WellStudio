#ifndef _KESECFAULTPICKINGITEM_H__
#define _KESECFAULTPICKINGITEM_H__

#include "xabstractitem.h"

class CXFaultStick;
class CXSectionScene;

enum ESecFaultStatus
{
	eSecFaultNull,
	eSecFaultPicking,
	eSecFaultMovingNode,
};

class CXSecFaultPickingItem : public CXAbstractItem
{
public:
	CXSecFaultPickingItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
	~CXSecFaultPickingItem(void);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const
	{
		return m_boundRect;
	}

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene();

	virtual void HandleMouseEvent(QMouseEvent *, EXMouseEventType);

	void FaultStickAssign(QUuid sourceFaultID, QUuid destFaultID);

protected:
	virtual void _UpdateData();

	void _updateActiveStick();

	void _leftButtonPressed(QMouseEvent *);
	void _middleButtonPressed(QMouseEvent *);
	void _buttonRelease();
	void _mouseMoving(QMouseEvent *);
	void _leftButtonDoubleClicked(QMouseEvent *);
	void _middleButtonDoubleClicked(QMouseEvent *);

	bool _pressOnStick(QPoint);
	bool _pressOnActiveNode(QPoint);
	bool _pressOnActiveEnd(QPoint);

	QList<CXFaultStick *>	m_listSticks;
	CXFaultStick*			m_pActiveStick;

	int						m_activeNode;
	QPolygonF				m_activeDataLine;
	QPolygonF				m_activeDrawLine;
	QLineF					m_rubberyLine;
	QList<QPolygonF>		m_listDataLines;
	QList<QPolygonF>		m_listDrawLines;
	QList<QPointF>			m_listDataPoints;
	QList<QPointF>			m_listDrawPoints;
	QList<CXFaultStick *>	m_listIntersectSticks;

	ESecFaultStatus			m_eStatus;
	QRectF					m_boundRect;
	CXSectionScene*		m_pScene;

private:

};

#endif