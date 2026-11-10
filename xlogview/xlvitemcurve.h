#pragma once
#include <qgraphicsitem.h>
#include <quuid.h>
#include "xlogview_global.h"

class CXViewInfoObject;
class CXViewInfoLPCurve;
class CXLVWindowInfo;
class CXLVScene;

class CXLVItemCurve : public QGraphicsRectItem
{
public:
	CXLVItemCurve(CXLVScene *, QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsRectItem *parent);

	QUuid GetObjectID()
	{
		return m_objectID;
	}

	bool GetValue(qreal y, qreal& dDepth, qreal& dValue);

	void Configure();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	void drawHeader(QPainter *);
	void drawGrid(QPainter *);
	void drawCurve(QPainter *);

	QUuid					m_objectID;
	CXLVScene*				m_pScene;
	CXLVWindowInfo*			m_pWinInfo;
	CXViewInfoLPCurve*		m_pViewInfo;

	double					m_dStart;
	double					m_dStop;
	QPolygonF				m_polyline;
	QVector<QPolygonF>		m_vecFFPolygon;
	QVector<QPolygonF>		m_vecFTPolygon;
};