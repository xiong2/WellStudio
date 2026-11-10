#include "xmathmacro.h"
#include "gsstructure.h"
#include "gsgeometry.h"
#include "xgeometry.h"
#include "xobjectfactory.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSStructure)
EXGSStructure
END_REGISTER_OBJECT_TO_FACTORY(GSStructure)

GSStructure::GSStructure(int iType, QPointF end0, QPointF end1, double dMag, double dRFrac, double dFaultLength, double dLWRatio)
{
	SetObjectType(EXGSStructure);

	m_iType = iType;
	m_end0 = end0;
	m_end1 = end1;

	m_bIntersected = false;
	m_iMagState = MAG_NULL;
	m_iMagStateAdj = MAG_NULL;
	m_dMagnitude = dMag;
	m_dReverseFraction = dRFrac;
	m_dFaultLength = dFaultLength;
	m_dLWRatio = dLWRatio;

	m_boundaryPolygon = GSGeom::CreateCapsule(m_end0, m_end1, 4000, getLengthWidthRatio());
	_SetSelfDimension();
}

GSStructure::GSStructure(QPointF p, double dLength, double dAzimuth, double dLengthToWidth)
{
	SetObjectType(EXGSStructure);

	m_iType = 3;
	    
	double dAng = dAzimuth * M_PI / 180;
	m_end0.setX(p.x() + dLength * sin(dAng) / 2);
	m_end0.setY(p.y() + dLength * cos(dAng) / 2);
	m_end1.setX(p.x() - dLength * sin(dAng) / 2);
	m_end1.setY(p.y() - dLength * cos(dAng) / 2);
		
	m_dLWRatio = dLengthToWidth;

	m_boundaryPolygon = GSGeom::CreateCapsule(m_end0, m_end1, dLength / (dLengthToWidth * 2));
	_SetSelfDimension();
}

void GSStructure::AdjustBoundaryPolygon(double dRatio, double dRadius)
{
	m_boundaryPolygon = GSGeom::CreateCapsule(m_end0, m_end1, dRadius, dRatio);
	_SetSelfDimension();
}

int GSStructure::getAboveState()
{
	return m_iMagState + 1 > MAG_REVERSE ? MAG_REVERSE : m_iMagState + 1;
}

int GSStructure::getBelowState()
{
	if (m_iType == 2 && m_iFaultType == 3 && m_iMagState == MAG_ESS)
		return MAG_ESS;

	return m_iMagState - 1 > MAG_NORMAL ? m_iMagState - 1 : MAG_NORMAL;
}

bool GSStructure::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_bIntersected;
		ar << m_iType;
		ar << m_iMagState;
		ar << m_iMagStateAdj;
		ar << m_end0;
		ar << m_end1;
		ar << m_dMagnitude;
		ar << m_dReverseFraction;
		ar << m_dFaultLength;
		ar << m_dLWRatio;
		ar << m_boundaryPolygon;
		ar << m_dSHAzi;
		ar << m_dSH;
		ar << m_dSh;
		ar << m_dSV;
		ar << m_dPp;
	}
	else
	{
		ar >> m_bIntersected;
		ar >> m_iType;
		ar >> m_iMagState;
		ar >> m_iMagStateAdj;
		ar >> m_end0;
		ar >> m_end1;
		ar >> m_dMagnitude;
		ar >> m_dReverseFraction;
		ar >> m_dFaultLength;
		ar >> m_dLWRatio;
		ar >> m_boundaryPolygon;
		ar >> m_dSHAzi;
		ar >> m_dSH;
		ar >> m_dSh;
		ar >> m_dSV;
		ar >> m_dPp;
	}

	return true;
}

double GSStructure::getLengthWidthRatio()
{
	if (m_dLWRatio == -1.)
	{
		if (m_iType == 2)
		{
			//	Faults.
			if (m_dMagnitude < THROW_CUTOFF_R20)
				return 20.;
			else if (m_dMagnitude < THROW_CUTOFF_R15)
				return 15.;
			else if (m_dMagnitude < THROW_CUTOFF_R10)
				return 10.;
			else
				return 5.;
		}
		else
			return 5.;
	}
	else
		return m_dLWRatio;
}

double GSStructure::GetLength()
{
	return sqrt((m_end0.x() - m_end1.x()) * (m_end0.x() - m_end1.x()) + (m_end0.y() - m_end1.y()) * (m_end0.y() - m_end1.y()));
}

bool GSStructure::GreaterThan(GSStructure *pOther)
{
	if ((m_iType != pOther->m_iType) && (m_iType > 1 || pOther->m_iType > 1))
	{
		//	Not the same and at least one capsule is a fault.
		return m_iType > pOther->m_iType;
	}

	return GSGeom::PolygonArea(m_boundaryPolygon) > GSGeom::PolygonArea(pOther->m_boundaryPolygon);
}

double GSStructure::GetStressAzimuth()
{
	double dAng = GetSlope();

	if (m_iType == 1 || m_iType == 2)
	{
		if (m_iType == 1)
		{
			dAng += 90;
		}
		else if (m_iType == 2)
		{
			if(m_iFaultType == 1)
				dAng += 40;
			else if(m_iFaultType == 2)
				dAng -= 40;
			else if(m_iFaultType == 3)
				dAng += 90;
		}

		if(dAng > 90)
			dAng -= 180;
	}
	else if (m_iType == 3)
	{
		if(m_dSHAzi == g_dInvalidData)
			return m_dSHAzi;

		dAng = 90 - m_dSHAzi;
	}

	return dAng;
}

double GSStructure::GetSlope()
{
	if (m_end0.x() == m_end1.x())
		return 90;
	else
		return 180 * atan((m_end0.y() - m_end1.y()) / (m_end0.x() - m_end1.x())) / M_PI;
}

const QPolygonF& GSStructure::GetBoundaryPolygon() const
{
	return m_boundaryPolygon;
}

void GSStructure::GetBigBoundary(QPolygonF& bigBoundary)
{
	double dDX = m_end1.x() - m_end0.x();
	double dDY = m_end1.y() - m_end0.y();

	QPointF p0, p1;
	p0.setX(m_end0.x() - dDX / 5);
	p0.setY(m_end0.y() - dDY / 5);
	p1.setX(m_end1.x() + dDX / 5);
	p1.setY(m_end1.y() + dDY / 5);

	double dLen = 1.4 * sqrt(dDX * dDX + dDY * dDY);

	if(m_iType == 3)
		bigBoundary = GSGeom::CreateCapsule(p0, p1, dLen / (m_dLWRatio * 2));
	else
		bigBoundary = GSGeom::CreateCapsule(p0, p1, 4000, getLengthWidthRatio());
}

bool GSStructure::MergeWith(GSStructure *pOther, double dOverlapThreshold, double dAngleThreshold)
{
	if (qAbs(GetSlope() - pOther->GetSlope()) > dAngleThreshold)
		return false;

	bool bCanMerge = false;
	if (m_iType == pOther->m_iType)
	{
		if (m_iType == STRUCTURE_REVERSE_FAULT)
		{
			//	if(m_mag_type_adj == NULL) ...
			//	if(m_mag_type_adj == NULL) ...

		}
		else
		{
			bCanMerge = true;
		}

	}

	QPolygonF intPolygon = m_boundaryPolygon.intersected(pOther->m_boundaryPolygon);
	if (intPolygon.isEmpty())
		return false;

	//if (GSGeom::PolygonArea(intPolygon) / GSGeom::PolygonArea(m_boundaryPolygon) < dOverlapThreshold)
	//	return false;

	m_boundaryPolygon = GSGeom::ConvexHull(m_boundaryPolygon + pOther->m_boundaryPolygon);

	_SetSelfDimension();
	return true;
}

bool GSStructure::HasNabour(QList<GSStructure *>& listStr, double dDis)
{
	dDis *= dDis;
	foreach(GSStructure *pStr, listStr)
	{
		if (pStr == this)
			continue;

		if (BoundarySquareDistance(pStr) < dDis)
			return true;
	}

	return false;
}

double GSStructure::BoundarySquareDistance(GSStructure *pStr)
{
	double dMin = 999999. * 999999.;
	foreach(QPointF p1, m_boundaryPolygon)
	{
		foreach(QPointF p2, pStr->m_boundaryPolygon)
		{
			double dDis = (p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y());
			dMin = qMin(dDis, dMin);
		}
	}

	return dMin;
}

void GSStructure::SubtractBoundaryPolygon(GSStructure *pOther)
{
	m_boundaryPolygon = m_boundaryPolygon.subtracted(pOther->m_boundaryPolygon);
	_SetSelfDimension();
}

void GSStructure::_SetSelfDimension()
{
	QRectF rect = m_boundaryPolygon.boundingRect();

	_SetDimension(rect.left(), rect.right(), rect.top(), rect.bottom(), g_dInvalidData, g_dInvalidData);
}

void GSStructure::Grouping(QList<GSStructure *>& listStr)
{
	int i;
	QList<GSStructure *> listNextLevelStr;
	while (1)
	{
		GSStructure *pStr = NULL;
		for(i = 0; i < listStr.size(); i++)
		{
			if(this == listStr[i])
				continue;

			if (!m_boundaryPolygon.intersected(listStr[i]->m_boundaryPolygon).isEmpty())
			{
				pStr = listStr[i];
				listStr.removeAt(i);
				break;
			}
		}

		if (pStr)
		{
			int iState = getAboveState();
			if (GreaterThan(pStr))
				iState = getBelowState();
			pStr->SetMagState(iState);

			listNextLevelStr << pStr;
		}
		else
			break;
	}

	foreach(GSStructure *pStr, listNextLevelStr)
	{
		pStr->Grouping(listNextLevelStr);
	}
}

double GSStructure::GetStressMagtitude()
{
	if (m_iType == 3)
	{
		return m_dSH;
	}
	//else if (m_iType == STRUCTURE_SPE_FAULT)
	//{
	//	return gStressMagRange[m_iMagState].m_fSHMag;
	//}
	else if ( m_iType == 2 && m_iMagStateAdj == MAG_REVERSE)
	{
		if (m_dMagnitude < THROW_CUTOFF_R20)
		{
			return gStressMagRange[MAG_REVERSE].m_fSHMagLower * 0.95 + gStressMagRange[MAG_REVERSE].m_fSHMag *0.05;
		}
		else if (m_dMagnitude < THROW_CUTOFF_R15)
		{
			return gStressMagRange[MAG_REVERSE].m_fSHMag;
		}
		else if (m_dMagnitude < THROW_CUTOFF_R10)
		{
			return gStressMagRange[MAG_REVERSE].m_fSHMag * 0.5 + gStressMagRange[MAG_REVERSE].Upper() *0.5;
		}
		else
			return gStressMagRange[MAG_REVERSE].Upper();
	}
	else
		return gStressMagRange[m_iMagStateAdj].m_fSHMag;
}

GSStructure* GSStructure::FindHigherStructure(QList<GSStructure *> listStr, double dAngle)
{
	GSStructure *pFStr = NULL;
	foreach(GSStructure *pStr, listStr)
	{
		if (pStr == this)
			continue;

		if (pStr->GetType() != STRUCTURE_SYNCLINE && pStr->GetType() != STRUCTURE_ANTICLINE)
			continue;

		if (qAbs(GetSlope() - pStr->GetSlope()) > dAngle)
			continue;

		if (!pFStr || pStr->GetStressMagtitude() > pFStr->GetStressMagtitude())
			pFStr = pStr;
	}

	return pFStr;
}