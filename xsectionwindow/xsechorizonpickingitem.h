#ifndef _KESECHORIZONPICKINGITEM_H__
#define _KESECHORIZONPICKINGITEM_H__

#include <qvector.h>
#include "xabstractitem.h"

class CX3DHorizon;
class CXSectionScene;

enum ESecHorizonPickingMode
{
	eSecHorizonManual,
	eSecHorizonSemiAuto,
	eSecHorizonAuto,
	eSecHorizonErase,
};

class CXSecHorizonPickingItem : public CXAbstractItem
{
public:
	CXSecHorizonPickingItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
	~CXSecHorizonPickingItem(void);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const
	{
		return scene()->sceneRect();
	}

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene();

	virtual void HandleMouseEvent(QMouseEvent *, EXMouseEventType);

	void SetHorizonPickingMode(ESecHorizonPickingMode eMode)
	{
		m_eMode = eMode;
	}

protected:
	virtual void _UpdateData();

	void _leftButtonPressed(QMouseEvent *);
	void _middleButtonPressed();
	void _leftButtonDoubleClicked(QMouseEvent *);
	void _buttonRelease();
	void _mouseMoving(QMouseEvent *);

	void _saveBackHorizonData();

	int m_iSTrace;
	int m_iTraceInc;
	QVector<float>				m_vecZ;

	ESecHorizonPickingMode		m_eMode;
	CXSectionScene*			m_pScene;
	CX3DHorizon*				m_pHorizon;

	QVector<QPointF>	m_vecPoints;
	QLineF				m_rubberyLine;
	QPainterPath		m_Path;
	QVector<QPointF>	m_vecIntPoints;
};

#endif