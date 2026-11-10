#ifndef _GSITEMFAULTPOLYGONS_H__
#define _GSITEMFAULTPOLYGONS_H__

#include <QGraphicsRectItem>
#include <qlist.h>

class GS3DHorizonFaultTraces;
class CXGlobalCoordTransform;

class GSItemFaultPolygons : public QGraphicsRectItem
{
public:
	GSItemFaultPolygons(QList<GS3DHorizonFaultTraces *>, CXGlobalCoordTransform *, bool bShowName = true, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	bool	m_bShowName;

	QList<GS3DHorizonFaultTraces *>	m_listFTs;
	CXGlobalCoordTransform *m_pCoordTransform;
};

#endif