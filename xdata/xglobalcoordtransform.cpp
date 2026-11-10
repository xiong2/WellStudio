#include "xglobalcoordtransform.h"
#include "xglobal.h"
#include "xobject.h"

bool CXGlobalCoordTransform::IsInitialized() const
{
    return m_isInitialized;
}

void CXGlobalCoordTransform::Init(const QUuid& objId)
{
    CXObject* pObj = ::GetObjectByID(objId);
    if (!pObj)
        return;

    double xmin, xmax, ymin, ymax, zmin, zmax;
    pObj->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);

    std::vector<double> vecDimension{ xmin, xmax, ymin, ymax, zmin, zmax };
    if (std::any_of(vecDimension.begin(), vecDimension.end(), [](double d) { return d == g_dInvalidData; }))
        return;

    m_dXOffset = (xmin + xmax) / 2.;
    m_dYOffset = (ymin + ymax) / 2.;
    m_dZOffset = (zmin + zmax) / 2.;

    m_isInitialized = true;
}

std::array<float, 3> CXGlobalCoordTransform::World2Local(const std::array<double, 3>& world) const
{
	return std::array<float, 3>{static_cast<float>(world.at(0) - m_dXOffset), -static_cast<float>(world.at(1) - m_dYOffset), -static_cast<float>(world.at(2) - m_dZOffset)};
}

std::array<double, 3> CXGlobalCoordTransform::Local2World(const std::array<float, 3>& local) const
{
	return std::array<double, 3>{local.at(0) + m_dXOffset, -local.at(1) + m_dYOffset, -local.at(2) + m_dZOffset};
}

QPointF CXGlobalCoordTransform::World2Local(const QPointF& world) const
{
    return QPointF(world.x() - m_dXOffset, -(world.y() - m_dYOffset));
}

QPointF CXGlobalCoordTransform::Local2World(const QPointF& local) const
{
    return QPointF(local.x() + m_dXOffset, -local.y() + m_dYOffset);
}
