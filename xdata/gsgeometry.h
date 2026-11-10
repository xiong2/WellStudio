#pragma once

#include <QPolygon>
#include <QPoint>
#include "xdata_global.h"

namespace GSGeom
{
	XDATA_EXPORT QPolygonF CreateCapsule(QPointF p0, QPointF p1, double dMaxRadius, double dLengthToWidth = 1.);

	XDATA_EXPORT double PolygonArea(const QPolygonF& polygon);
	XDATA_EXPORT QPolygonF ConvexHull(const QVector<QPointF>& points);
	XDATA_EXPORT QPointF PolygonCentroid(const QPolygonF& polygon);

	enum EMarkerType {eAnticline, eSyncline, eStressArrow};
	XDATA_EXPORT QPolygonF CreateMarker(EMarkerType type, QPointF center, double dSize, double dAngleDegress);
}