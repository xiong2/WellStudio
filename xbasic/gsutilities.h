#pragma once
#include <QColor>
#include <QPointF>
#include "xgeometry.h"
#include "xbasic_global.h"

namespace GSUtil
{
	XBASIC_EXPORT QColor GetKellyColor(int index);
	XBASIC_EXPORT XVec2d ToVec(const QPointF& p);
	XBASIC_EXPORT QPointF ToPoint(const XVec3d& vec);
	XBASIC_EXPORT XLine2d MakeLine(const QPointF& p1, const QPointF& p2);
}