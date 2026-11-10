#ifndef XGLOBALCOORDTRANSFORM_H
#define XGLOBALCOORDTRANSFORM_H

#include "xdata_global.h"
#include <array>
#include <QUuid>
#include <QPoint>
#include <QRectF>

#define HALFSIZE 125

/**
@class  CXGlobalCoordTransform provided in the file "xglobalcoordtransform.h"
@brief  The class provides the global coordinate transform for objects.
@author pezy
@date   2018-03-21
@sa
*/
class XDATA_EXPORT CXGlobalCoordTransform
{
public:
	bool IsInitialized() const;
	void Init(const QUuid& objId);

	std::array<float, 3> World2Local(const std::array<double, 3>& world) const;
	std::array<double, 3> Local2World(const std::array<float, 3>& local) const;

	QPointF World2Local(const QPointF& world) const;
	QPointF Local2World(const QPointF& local) const;

private:
	double m_dXOffset = 0.;
	double m_dYOffset = 0.;
	double m_dZOffset = 0.;
	bool m_isInitialized = false;
};

#endif // XGLOBALCOORDTRANSFORM_H
