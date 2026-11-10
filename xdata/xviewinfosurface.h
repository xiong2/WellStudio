#ifndef XVIEWINFOSURFACE_H
#define XVIEWINFOSURFACE_H

#include "xdata_global.h"
#include "xviewinfoobject.h"
#include "xrange.h"

/*!
 *	@brief	The class provides data structure for view info of 3-D surfaces
 *	@author	pezy
 *	@date	2016-05-04
 *	@see	
 */

class XDATA_EXPORT CXViewInfoSurface : public CXViewInfoObject
{
public:
	CXViewInfoSurface();
	~CXViewInfoSurface();

	void SetViewObjectID(const QUuid& objID) override;

	const QMap<CXRange<float>, QColor>& GetDiscreteContourFillColor() const { return m_rangeColor; }
	void ClearDiscreteContourFillColor() { m_rangeColor.clear(); }
	void AddDiscreteContourFillColor(float fMin, float fMax, const QColor& color);

	X_PROPERTY(int, DisplayMode) // 0-point, 1-surface, 2-frac

	X_PROPERTY(QColor, PointColor)
	X_PROPERTY(int, PointColorType)
	X_PROPERTY(int, PointSize)

	X_PROPERTY(bool, ReverseColormap)
	X_PROPERTY(float, MaxLevel)
	X_PROPERTY(float, MinLevel)
	X_PROPERTY(float, IncLevel)

	X_PROPERTY(QColor, FillColor)
	X_PROPERTY(int, FillColorType)
	X_PROPERTY(QString, DiscreteFillColorName)
	
	X_PROPERTY(float, ContourStart)
	X_PROPERTY(float, ContourEnd)
	X_PROPERTY(float, ContourInc)
	X_PROPERTY(bool, ContourVisible)

	X_PROPERTY(int, MajorColorType)
	X_PROPERTY(QColor, MajorContourColor)
	X_PROPERTY(int, MajorLineWeight)
	X_PROPERTY(int, MajorLineStyle)
	X_PROPERTY(int, MajorLineInterval)

	X_PROPERTY(int, MinorColorType)
	X_PROPERTY(QColor, MinorContourColor)
	X_PROPERTY(int, MinorLineWeight)
	X_PROPERTY(int, MinorLineStyle)

	X_PROPERTY(QUuid, FracAzimuth)
	X_PROPERTY(QUuid, FracDensity)
	X_PROPERTY(int, FracDX)
	X_PROPERTY(int, FracDY)
	X_PROPERTY(float, FracScale)
	X_PROPERTY(float, FracMinThreshold)
	X_PROPERTY(float, FracMaxThreshold)
	X_PROPERTY(QColor, FracColor)
	X_PROPERTY(int, FracColorType)
	X_PROPERTY(int, FracWidth)
	X_PROPERTY(int, FracHeight)
	X_PROPERTY(float, FracOffset)
	
	///@brief visualization page for Section window.
	X_PROPERTY(bool, SectionLineUseObjColor)
	X_PROPERTY(QColor, SectionLineColor)
	X_PROPERTY(int, SectionLineWidth)

	X_PROPERTY(bool, SectionAnnotationUseObjColor)
	X_PROPERTY(QColor, SectionAnnotationColor)
	X_PROPERTY(QColor, SectionAnnotationBackgroundColor)
	X_PROPERTY(int, SectionAnnotationSize)

	X_PROPERTY(int, SectionIntersectionPointSize)

	X_PROPERTY(bool, SectionAnnotationLeftVisible)
	X_PROPERTY(bool, SectionAnnotationRightVisible)
	X_PROPERTY(bool, SectionAnnotationBackgroundVisible)

private:
	QMap<CXRange<float>, QColor> m_rangeColor;
};

#endif // KEVIEWINFOSURFACE_H
