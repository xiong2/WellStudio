#ifndef GSBMITEMDEFINEROSE_H
#define GSBMITEMDEFINEROSE_H

#include <memory>
#include <QGraphicsItem>

class CXObject;
class CXGlobalCoordTransform;
class GSBasemapScene;

class GSBMItemDefineRose : public QGraphicsItem
{
public:
	GSBMItemDefineRose(GSBasemapScene *pScene, const CXGlobalCoordTransform& coordTrans, double dRadius, QGraphicsItem* parent = Q_NULLPTR);

	QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

	void SetCentre(QPointF point);

	void SetRadius(double dRadius);

	void SetMode(int iMode);

	QPointF GetCentre()
	{
		return m_pointCentre;
	}

	double GetRadius()
	{
		return m_dRadius;
	}

	int GetMode()
	{
		return m_iMode;
	}

private:
	GSBasemapScene*	m_pScene;
	const CXGlobalCoordTransform& m_coordTrans;

	int			m_iMode;	//	0: circle;	1: polygon.
	double		m_dRadius;
	QPointF		m_pointCentre;
	QPolygonF	m_boundaryPolygon;
};

#endif