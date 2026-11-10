#include "gsfaultprocess.h"
#include "xfunctiontemplate.h"
#include "xmathmacro.h"
#include "xutmtool.h"
#include "gsutilities.h"
#include "xglobal.h"
#include "xproject.h"
#include <exception>
#include <cassert>
#include <algorithm>
#include <QDebug>
#include <QPolygonF>

GSFaultInterpStick::GSFaultInterpStick(std::vector<XPoint>::const_iterator beg, std::vector<XPoint>::const_iterator end)
{
	int count = std::distance(beg, end);
	if (count < 2)
		throw std::invalid_argument("too few points.");

	auto bak = std::prev(end);
	double zMin = beg->z;
	double zMax = bak->z;
	double dz = (zMax - zMin) / m_nInterpNum;

	if (dz < M_TOL_DOUBLE)
		throw std::invalid_argument("too dense points");

	m_vecInterpPoints.reserve(m_nInterpNum);
	m_vecInterpPoints.push_back(*beg);

	int idx = 0;
	for (int i = 1; i < m_nInterpNum - 1; ++i)
	{
		double z = zMin + i * dz;
		while (z < zMax && idx < count - 1 && z >= std::next(beg, idx)->z)
			++idx;

		double r = (z - std::next(beg, idx - 1)->z) / (std::next(beg, idx)->z - std::next(beg, idx - 1)->z);
		assert(0.0 <= r && r <= 1.0);
		assert(0 <= idx && idx < count);

		XPoint interpPoint = XGeom::Lerp(*std::next(beg, idx - 1), *std::next(beg, idx), r);
		assert(IsEqualDouble(interpPoint.z, z, M_TOL_DOUBLE));

		m_vecInterpPoints.push_back(interpPoint);
	}
	m_vecInterpPoints.push_back(*bak);
}

double GSFaultInterpStick::GetDipAngle()
{
	if (std::isnan(m_dipAngle))
	{
		XRMA rma;
		const XPoint& p0 = m_vecInterpPoints.front();

		for (auto&& p : m_vecInterpPoints)
		{
			double x = XGeom::Distance(XVec2d(p0.x, p0.y), XVec2d(p.x, p.y));
			double y = p.z - p0.z;
			rma.Add(x, y);
		}
		rma.Solve();
		m_dipAngle = rma.Line().Angle();
	}
	return m_dipAngle;
}

std::vector<XPoint>::const_iterator GSFaultInterpStick::begin() const
{
	return m_vecInterpPoints.cbegin();
}

std::vector<XPoint>::const_iterator GSFaultInterpStick::end() const
{
	return m_vecInterpPoints.cend();
}

std::vector<XPoint>::iterator GSFaultInterpStick::begin()
{
	return m_vecInterpPoints.begin();
}

std::vector<XPoint>::iterator GSFaultInterpStick::end()
{
	return m_vecInterpPoints.end();
}

std::vector<XPoint>::const_reverse_iterator GSFaultInterpStick::rbegin() const
{
	return m_vecInterpPoints.crbegin();
}

std::vector<XPoint>::const_reverse_iterator GSFaultInterpStick::rend() const
{
	return m_vecInterpPoints.crend();
}

std::vector<XPoint>::reverse_iterator GSFaultInterpStick::rbegin()
{
	return m_vecInterpPoints.rbegin();
}

std::vector<XPoint>::reverse_iterator GSFaultInterpStick::rend()
{
	return m_vecInterpPoints.rend();
}

GSHorizonFault::GSHorizonFault(CXUTMTool & utm, float * pHorzData, GSFaultInterpStick & faultStick)
	: m_utm(utm), m_pHorzData(pHorzData), m_faultInterpStick(faultStick)
{
	determineSectionType();
	buildSectionLeftAndRightLine();
}

GSFaultTrace GSHorizonFault::GetFaultTrace(double dFaultTol)
{
	if (m_ft.IsNull())
	{
		calcThrows(dFaultTol);
	}

	return m_ft;
}

void GSHorizonFault::calcThrows(double dFaultTol)
{
	if (eRandomline == m_secType || m_vecSecPoints.empty())
		return;

	// Delete any points that are too close to the fault trace
	QPolygonF fpoly = buildFaultTracePolygon(dFaultTol);

	double ox = m_faultInterpStick.begin()->x;
	double oy = std::prev(m_faultInterpStick.end())->y;
	double oidx = m_vecSecPoints.front().stn;

	std::vector<GSSectionPoint> vecHorzSecPoints;
	int iDataSize = m_utm.GetNI() * m_utm.GetNJ();
	for (auto&& p : m_vecSecPoints)
	{
		int stn = qRound(p.stn);
		int horzIdx = (eInline == m_secType) ? (m_lineNo * m_utm.GetNJ() + stn) : (stn * m_utm.GetNJ() + m_lineNo);

		if(horzIdx < 0 || horzIdx >= iDataSize)
			continue;
		double z = m_pHorzData[horzIdx];
		if (z == M_FINVALID)
			continue;

		double x, y;
		if (eInline == m_secType)
			m_utm.IJToXY(m_lineNo, stn, x, y);
		else
			m_utm.IJToXY(stn, m_lineNo, x, y);
		double dist = XGeom::Distance(XVec2d(ox, oy), XVec2d(x, y));
		if (p.stn < oidx)
			dist *= -1;
		if (fpoly.containsPoint(QPointF(dist, z), Qt::WindingFill))
			m_pHorzData[horzIdx] = M_FINVALID;
		else
			vecHorzSecPoints.emplace_back(stn, z);
	}

	if (vecHorzSecPoints.empty())
		return;

	// Loop for each horizon line segment
	for (auto hp1 = vecHorzSecPoints.cbegin(), hp2 = std::next(hp1); hp2 != vecHorzSecPoints.cend(); ++hp1, ++hp2)
	{
		// Loop for each fault trace segment
		for (auto fp1 = m_vecSecPoints.cbegin(), fp2 = std::next(fp1); fp2 != m_vecSecPoints.cend(); ++fp1, ++fp2)
		{
			if (XGeom::IntersectionTwoSegments(XVec2d(hp1->stn, hp1->z), XVec2d(hp2->stn, hp2->z), XVec2d(fp1->stn, fp1->z), XVec2d(fp2->stn, fp2->z)))
			{
				GSFaultTrace ft;

				ft.m_p1 = zInterp(hp1->z);
				ft.m_p2 = zInterp(hp2->z);

				// Are the points too far away from the intersection?
				if (isThePointsTooFarAwayFromIntersection(*hp1, *hp2, ft))
					break;

				// If vertical, sep a bit
				if (IsEqualDouble(ft.m_p1.x(), ft.m_p2.x(), M_TOL_DOUBLE) && IsEqualDouble(ft.m_p1.y(), ft.m_p2.y(), M_TOL_DOUBLE))
				{
					XVec2d p1 = getHorzLocByStn(hp1->stn);
					XVec2d p2 = getHorzLocByStn(hp2->stn);
					ft.m_p1.rx() -= (p2.x() - p1.x()) / 100;
					ft.m_p1.ry() -= (p2.y() - p1.y()) / 100;
					ft.m_p2.rx() += (p2.x() - p1.x()) / 100;
					ft.m_p2.ry() += (p2.y() - p1.y()) / 100;
				}

				float stn1 = getFaultStickPointStn(ft.m_p1.x(), ft.m_p1.y());
				float stn2 = getFaultStickPointStn(ft.m_p2.x(), ft.m_p2.y());

				if (fabs(hp1->z - hp2->z) < M_TOL_DOUBLE)
					ft.m_type = GSFaultTrace::eZero;
				else if (fabs(stn1 - stn2) < M_TOL_DOUBLE)
					ft.m_type = GSFaultTrace::eVertical;
				else if (stn1 > stn2)
					ft.m_type = GSFaultTrace::eReverse;
				else
					ft.m_type = GSFaultTrace::eNormal;

				m_ft = ft;
			}
		}
	}

}

XVec2d GSHorizonFault::getHorzLocByStn(int stn)
{
	double x, y;
	if (eInline == m_secType)
	{
		m_utm.IJToXY(m_lineNo, stn, x, y);
	}
	else
	{
		m_utm.IJToXY(stn, m_lineNo, x, y);
	}

	return XVec2d(x, y);
}

float GSHorizonFault::getFaultStickPointStn(double x, double y)
{
    float fI, fJ;
    m_utm.XYToIJ(x, y, fI, fJ);
    return (eInline == m_secType) ? fJ : fI;
}

void GSHorizonFault::determineSectionType()
{
	float firstI, firstJ, lastI, lastJ;
	const auto& firstPoint = *m_faultInterpStick.begin();
	const auto& lastPoint = *std::prev(m_faultInterpStick.end());

	m_utm.XYToIJ(firstPoint.x, firstPoint.y, firstI, firstJ);
	m_utm.XYToIJ(lastPoint.x, lastPoint.y, lastI, lastJ);

	if(qRound(firstI) != qRound(lastI) && qRound(firstJ) != qRound(lastJ))
	{
		m_secType = eRandomline;
	}
	else if (qAbs(firstI - lastI) > qAbs(firstJ - lastJ))
	{
		m_lineNo = qRound(firstJ);
		m_secType = eCrossline;
	}
	else
	{
		m_lineNo = qRound(firstI);
		m_secType = eInline;
	}
}

void GSHorizonFault::buildSectionLeftAndRightLine()
{
	m_vecSecPoints.clear();

	for (auto&& p : m_faultInterpStick)
	{
		float fI, fJ;
		if (!m_utm.XYToIJ(p.x, p.y, fI, fJ))
		{
			fI = qBound(0.f, fI, (float)(m_utm.GetNI() - 1));
			fJ = qBound(0.f, fJ, (float)(m_utm.GetNJ() - 1));
		}

		if (eInline == m_secType)
		{
			m_vecSecPoints.emplace_back(fJ, p.z);
		}
		else if (eCrossline == m_secType)
		{
			m_vecSecPoints.emplace_back(fI, p.z);
		}
	}

	if (m_vecSecPoints.empty())
		return;

	XLine2d line(m_vecSecPoints.front().stn, m_vecSecPoints.front().z, m_vecSecPoints.back().stn, m_vecSecPoints.back().z);

	double ttMin = std::numeric_limits<double>::max();
	double tMin = std::numeric_limits<double>::max();
	double ttMax = std::numeric_limits<double>::min();
	double tMax = std::numeric_limits<double>::min();

	for (auto&& p : m_vecSecPoints)
	{
		double t = line.TforXY(p.stn, p.z);
		double tt = XGeom::Distance(XVec2d(p.stn, p.z), line);

		tMin = std::min(tMin, t);
		tMax = std::max(tMax, t);

		ttMin = std::min(ttMin, tt);
		ttMax = std::max(ttMax, tt);
	}

	XVec2d left = line.PointPerp(tMin, ttMin);
	XVec2d right = line.PointPerp(tMin, ttMax);
	XVec2d dir = line.Direction();

	m_leftLine = XLine2d(left, dir);
	m_rightLine = XLine2d(right, dir);
}

QPolygonF GSHorizonFault::buildFaultTracePolygon(double dFaultTol)
{
	QPolygonF fpoly;
	
	const XPoint& op = *m_faultInterpStick.begin();
	float oidx = m_vecSecPoints.front().stn;

	// Build the left side
	for (auto iter = m_faultInterpStick.begin(); iter != m_faultInterpStick.end(); ++iter)
	{
		double dist = XGeom::Distance(XVec2d(op.x, op.y), XVec2d(iter->x, iter->y));
		if (std::next(m_vecSecPoints.begin(), std::distance(m_faultInterpStick.begin(), iter))->stn < oidx)
			dist *= -1;
		dist -= dFaultTol;
		fpoly << QPointF(dist, iter->z);
	}

	// Build the right side
	for (auto iter = m_faultInterpStick.rbegin(); iter != m_faultInterpStick.rend(); ++iter)
	{
		double dist = XGeom::Distance(XVec2d(op.x, op.y), XVec2d(iter->x, iter->y));
		if (std::next(m_vecSecPoints.rbegin(), std::distance(m_faultInterpStick.rbegin(), iter))->stn < oidx)
			dist *= -1;
		dist += dFaultTol;
		fpoly << QPointF(dist, iter->z);
	}

	return fpoly;
}

XPoint GSHorizonFault::zInterp(double z, bool bSetZ)
{
	XPoint ret;

	auto begn = m_faultInterpStick.begin();
	auto last = std::prev(m_faultInterpStick.end());

	if (z < begn->z)
		ret = *begn;
	else if (z > last->z)
		ret = *last;
	else
	{
		for (auto p0 = begn, p1 = std::next(p0); p1 != m_faultInterpStick.end(); ++p0, ++p1)
		{
			if (p0->z <= z && z < p1->z)
			{
				double r = (z - p0->z) / (p1->z - p0->z);
				ret = XGeom::Lerp(*p0, *p1, r);
				break;
			}
		}
	}
	
	if (bSetZ)
		ret.z = z;
	return ret;
}

bool GSHorizonFault::sectionPointIsLeft(double idx, double z)
{
	if (XGeom::Distance(XVec2d(idx, z), m_leftLine) <= 0.0) // left of left line
		return true;

	if (XGeom::Distance(XVec2d(idx, z), m_rightLine) > 0.0) // right of right line
		return false;

	std::vector<XVec2d> polygon;
	for (auto&& secPoint : m_vecSecPoints)
	{
		polygon.emplace_back(secPoint.stn, secPoint.z);
	}
	polygon.push_back(polygon.front()); // close to the start.

	return XGeom::Distance(XVec2d(idx, z), polygon) <= 0;
}

bool GSHorizonFault::isThePointsTooFarAwayFromIntersection(const GSSectionPoint& hp1, const GSSectionPoint& hp2, const GSFaultTrace& ft)
{
    int cellSize = qRound(::GetProject()->GetCellSize());
	double xyTol = 5.0 * cellSize / 2.0;

	return XGeom::Distance(getHorzLocByStn((int)hp1.stn), ft.m_p1.ToVec2()) > xyTol || XGeom::Distance(getHorzLocByStn((int)hp2.stn), ft.m_p2.ToVec2()) > xyTol;
}

void NGSFault::SortFaultTrace(std::vector<GSFaultTrace>* vecTraces)
{
	double dXMin = std::numeric_limits<double>::max();
	double dYMin = std::numeric_limits<double>::max();
	for (auto&& trace : *vecTraces)
	{
		dXMin = std::min({ dXMin, trace.m_p1.x(), trace.m_p2.x() });
		dYMin = std::min({ dYMin, trace.m_p1.y(), trace.m_p2.y() });
	}

	// sort into RMA order
	XRMA rma;
	for (auto&& trace : *vecTraces)
	{
		const QPointF& p = trace.CentrePoint();
		rma.Add(p.x() - dXMin, p.y() - dYMin);
	}
	rma.Solve();

	std::sort(vecTraces->begin(), vecTraces->end(), [&rma, dXMin, dYMin](const GSFaultTrace& ft1, const GSFaultTrace& ft2)
	{
		const QPointF& p1 = ft1.CentrePoint();
		const QPointF& p2 = ft2.CentrePoint();

		return rma.Line().TforXY(p1.x() - dXMin, p1.y() - dYMin) < rma.Line().TforXY(p2.x() - dXMin, p2.y() - dYMin);
	});
}