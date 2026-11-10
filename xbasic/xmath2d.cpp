#include <cfloat>
#include <QVector2D>
#include "xmath2d.h"

float NXMath2D::PointToSegment(QPointF point, QLineF segment)
{
	QVector2D v = QVector2D(segment.p2()) - QVector2D(segment.p1());
	QVector2D w = QVector2D(point) - QVector2D(segment.p1());

    auto c1 = QVector2D::dotProduct(v, w);
    if (c1 <= 0)
    {
		if (fabs(c1 - 0.f) < FLT_EPSILON)
		{
			return QVector2D(point).distanceToPoint(QVector2D(segment.p1()));
		}
		else
		{
			return INFINITE_MAX;
		}
	}

    auto c2 = QVector2D::dotProduct(v, v);
    if (c2 <= c1)
    {
		if (fabs(c2 - c1) < FLT_EPSILON)
		{
			return QVector2D(point).distanceToPoint(QVector2D(segment.p2()));
		}
		else
		{
			return INFINITE_MAX;
		}
	}

	float b = c1 / c2;
	QPointF projection = (QVector2D(segment.p1()) + b * v).toPointF();
    return QVector2D(point).distanceToPoint(QVector2D(projection));
}

float NXMath2D::PointProjectionOnSegment(QPointF point, QLineF segment)
{
	// [p1 + x * (p2 - p1) - p] * (p2 - p1) = 0

	QVector2D v = QVector2D(segment.p2()) - QVector2D(segment.p1());

	float productPV = QVector2D::dotProduct(QVector2D(point), v);
	float productP1V = QVector2D::dotProduct(QVector2D(segment.p1()), v);
	float productVV = QVector2D::dotProduct(v, v);

	return (productPV - productP1V) / productVV;
}
