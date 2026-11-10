#ifndef GSBMITEMROSEDIAGRAM_H
#define GSBMITEMROSEDIAGRAM_H

#include <memory>
#include <QGraphicsItem>

class CXObject;
class GSRoseDiagram;
class GSRoseDiagramViewInfo;
class CXGlobalCoordTransform;

class GSBMItemRoseDiagram : public QGraphicsItem
{
public:
	GSBMItemRoseDiagram(CXObject *, const CXGlobalCoordTransform& coordTrans, GSRoseDiagramViewInfo *, QGraphicsItem* parent = Q_NULLPTR);

	QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

private:
	const CXGlobalCoordTransform& m_coordTrans;
	GSRoseDiagramViewInfo*	m_pViewInfo;
	GSRoseDiagram*			m_pRoseDiagram;
};

#endif