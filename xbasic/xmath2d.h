#ifndef XMATH2D_H
#define XMATH2D_H

#include "xbasic_global.h"
#include <QPointF>
#include <QLineF>

/*!
 * @namespace	NXMath2D provided in the file "xsmath2d.h"
 * @brief		The namespace provides basic 2d math operator.(Qt Style)
 *
 * @author		Pezy
 * @date		2015-10-14
 * @see			NXUtility
 */

#define INFINITE_MAX 99999

namespace NXMath2D
{
	///	@brief	Return the distance a point to a segment.
	///	If the point's projection not fall on the segment, return infinite big value.
	float XBASIC_EXPORT PointToSegment(QPointF point, QLineF segment);

	///	@brief	Return the projective point of a point on a segment, represented by ratio to the segment start end. 
	float XBASIC_EXPORT PointProjectionOnSegment(QPointF point, QLineF segment);
}

#endif // KEMATH2D_H
