#include "gscursoritem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "xglobalcoordtransform.h"

GSCursorItem::GSCursorItem(const CXGlobalCoordTransform& coordTrans, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_coordTrans(coordTrans)
{
    setZValue(10);
}

GSCursorItem::~GSCursorItem()
{
}

QRectF GSCursorItem::boundingRect() const
{
    return m_crossPath.boundingRect();
}

void GSCursorItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_crossPath.isEmpty())
        return;

	painter->setPen(QPen(Qt::white, getRealPixelSize(2)));
	painter->drawPath(m_crossPath);
}

void GSCursorItem::UpdatePosition(double dx, double dy)
{
	m_crossPath = QPainterPath();
	if (!m_coordTrans.IsInitialized())
		return;

	QPointF localPos = m_coordTrans.World2Local(QPointF(dx, dy));

	m_crossPath.moveTo(localPos - QPointF(getRealPixelSize(8), 0.0));
	m_crossPath.lineTo(localPos + QPointF(getRealPixelSize(8), 0.0));
	m_crossPath.moveTo(localPos - QPointF(0.0, getRealPixelSize(8)));
	m_crossPath.lineTo(localPos + QPointF(0.0, getRealPixelSize(8)));

    update();
}

void GSCursorItem::Clear()
{
	m_crossPath = QPainterPath();
	update();
}

double GSCursorItem::getRealPixelSize(int size) const
{
    if (!scene() || scene()->views().isEmpty())
        return size;

    QGraphicsView* pView = scene()->views().front();

    QPolygonF scenePolygon = pView->mapToScene(QRect(QPoint(0, 0), QSize(size, size)));
    return QLineF(scenePolygon.at(0), scenePolygon.at(1)).length();
}
