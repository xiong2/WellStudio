#include "gsanticline.h"
#include "x3dhorizon.h"
#include "gsgeometry.h"
#include "xgeometry.h"
#include "xobjectfactory.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSAnticline)
EXGSAnticline
END_REGISTER_OBJECT_TO_FACTORY(GSAnticline)

GSAnticline::GSAnticline(QPointF end0, QPointF end1, double dRmaR, double dLength, bool bAnticline)
{
	SetObjectType(EXGSAnticline);

	m_bAnticline = bAnticline;
	m_end0 = end0;
	m_end1 = end1;
	m_fVolume = -1.;
	m_dRmaR = dRmaR;
	m_dLength = dLength;
}

bool GSAnticline::SerializeData(CXArchive& ar)
{
	int iTmp;
	if (ar.IsSaving())
	{
		ar << m_bAnticline;
		ar << m_end0;
		ar << m_end1;
		ar << m_fVolume;
		ar << m_dRmaR;
		ar << m_dLength;
	}
	else
	{
		ar >> m_bAnticline;
		ar >> m_end0;
		ar >> m_end1;
		ar >> m_fVolume;
		ar >> m_dRmaR;
		ar >> m_dLength;
	}

	return true;
}

QPolygonF GSAnticline::GetBoundaryPolygon()
{
	return GSGeom::CreateCapsule(m_end0, m_end1, 4000, 5);
}

void GSAnticline::_SetSelfDimension()
{
	double dXMin = m_end0.x(), dXMax = m_end1.x();
	if (dXMin > dXMax)
	{
		dXMin = dXMax;
		dXMax = m_end0.x();
	}

	double dYMin = m_end0.y(), dYMax = m_end1.y();
	if (dYMin > dYMax)
	{
		dYMin = dYMax;
		dYMax = m_end0.y();
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, g_dInvalidData, g_dInvalidData);
}

float GSAnticline::GetVolume(CX3DHorizon *pIsoHor)
{
	//	Already be calculated?
	if (m_fVolume > 0)
		return m_fVolume;

	//	Data from the isopach.
	CXSeismicUTMTool utm = pIsoHor->GetUTM();
	float *pData = pIsoHor->GetData();
	int m, n, i, j, nJ = utm.GetNJ();

	//	t1 - t0 is the length of the capsule, and r is the radius of the capsule end, or the half width. 
	XLine2d line2D(m_end0.x(), m_end0.y(), m_end1.x(), m_end1.y());
	double t0 = line2D.TforXY(m_end0.x(), m_end0.y());
	double t1 = line2D.TforXY(m_end1.x(), m_end1.y());
	if (t0 > t1) std::swap(t0, t1);
	double r = (t1 - t0) / 5;
	r = r > 2000 ? 2000 : r;

	//	Now adjust t0, t1 to the end of the long axis of the capsule.
	t0 += r;
	t1 -= r;

	//	Step along the long axis.
	double dHDelta = (t1 - t0) / 32;

	//	Step perpendicular to the long axis.
	double dVDelta = r / 16;

	//	Now loop along the long axis and its perpendicular line to accumulate the volume.
	float zMin, zMax;
	m_fVolume = 0.;
	for (double t = t0; t <= t1; t += dHDelta)
	{
		utm.XYToIJ(line2D.XforT(t), line2D.YforT(t), i, j);
		zMin = zMax = pData[i * nJ + j];

		//	m == 0, left side;	m == 1, right side.
		for (m = 0; m <= 1; m++)
		{
			dVDelta = qAbs(dVDelta) * (2 * m - 1);
			for (n = 1; n < 16; n++)
			{
				XVec2d point = line2D.PointPerp(t, n * dVDelta);
				if (utm.XYToIJ(point.x(), point.y(), i, j))
				{
					zMin = qMin(zMin, pData[i * nJ + j]);
					zMax = qMax(zMax, pData[i * nJ + j]);
				}
			}
		}

		m_fVolume += (zMax - zMin) * 32;
	}

	return m_fVolume;
}