#include <qfile.h>
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xgeometry.h"
#include "gsstressmap.h"
#include "gsstructure.h"
#include "gscompressionpulse.h"
#include "gsstressparameters.h"
#include "xdlgcalculatingprogress.h"
#include "x3dhorizon.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSStressMap)
EXGSStressMap
END_REGISTER_OBJECT_TO_FACTORY(GSStressMap)

GSStressMap::GSStressMap()
{
	m_pDataInMem = NULL;
}

GSStressMap::GSStressMap(const CXSeismicUTMTool& utm, const QString& strName, GSStressParameters *pParas) : CXObject(strName)
{
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&utm));
	
	if(pParas)
		m_paras.Copy(pParas);

	SetIconName("Stress.png");
	SetObjectType(EXGSStressMap);

	m_pDataInMem = NULL;
}

GSStressMap::GSStressMap(GSStressMap *pOtherMap, QString sName) : CXObject(sName)
{
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&pOtherMap->GetUTM()));
	SetIconName(pOtherMap->GetIconName());
	SetObjectType(pOtherMap->GetObjectType());
	m_paras.Copy(&(pOtherMap->m_paras));

	int iSize = 2 * m_utm.GetNI() * m_utm.GetNJ();
	m_pDataInMem = new float[iSize];
	float *pData = pOtherMap->GetData();
	memcpy(m_pDataInMem, pData, 4 * iSize);
}

GSStressMap::~GSStressMap()
{
	if (m_pDataInMem)
	{
		delete[]m_pDataInMem;
		m_pDataInMem = NULL;
	}
}

bool GSStressMap::SerializeData(CXArchive& ar)
{
	m_paras.SerializeData(ar);
	return m_utm.SerializeData(ar);
}

float* GSStressMap::GetData()
{
	if (!m_pDataInMem)
		LoadData();

	if (!m_pDataInMem)
	{
		//	The former half is magtitude and the later is direction.
		int nSize = 2 * m_utm.GetNI()*m_utm.GetNJ();
		m_pDataInMem = new float[nSize];

		for (int i = 0; i < nSize; ++i)
			m_pDataInMem[i] = g_dInvalidData;
	}

	return m_pDataInMem;
}

float* GSStressMap::_GetHistogramData(int& nDataNum, bool& bDeleted)
{
	if (!m_pDataInMem)
		LoadData();

	bDeleted = false;
	if (!m_pDataInMem)
	{
		nDataNum = 0;
		return NULL;
	}
	else
	{
		nDataNum = m_utm.GetNI()*m_utm.GetNJ();
		return  m_pDataInMem;
	}
}

void GSStressMap::_SetSelfDimension()
{
	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	m_utm.GetDimensionRange(dXMin, dXMax, dYMin, dYMax);

	GetDataRange(dZMin, dZMax);

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

void GSStressMap::_WriteData()
{
	if (!m_pDataInMem)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	int nSize = 2 * m_utm.GetNI()*m_utm.GetNJ();
	qFile.write((char*)m_pDataInMem, sizeof(float)*nSize);

}
void GSStressMap::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	int nSize = 2 * m_utm.GetNI()*m_utm.GetNJ();
	if (!m_pDataInMem)
	{
		m_pDataInMem = new float[nSize];
	}

	qFile.read((char*)m_pDataInMem, sizeof(float)*nSize);
}

QString GSStressMap::GetTypeString()
{
	return "Stress Map";
}

QStringList GSStressMap::GetDescription()
{
	QStringList strList;

	if (m_paras.m_bFaults)
		strList << "Used faults data" << "Yes";
	else
		strList << "Used faults data" << "No";

	for (int i = 0; i < 3; i++)
	{
		if (m_paras.m_iAnti[i] == 0)
			continue;

		QString sStructure = "anticline", sShape = "Shape" + QString::number(i + 1);
		if (m_paras.m_iAnti[i] == 2)
			sStructure = "syncline";
		strList << sShape + " tracks" << sStructure;
		strList << sStructure + " correlation" << QString::number(m_paras.m_dCThreshold[i]);
		strList << "Mininum " + sStructure + " length" << QString::number(m_paras.m_dLThreshold[i]);
		strList << "Mininum " + sStructure + " height" << QString::number(m_paras.m_dTHeight[i]);
		strList << "Maximum searching radius" << QString::number(m_paras.m_dSRadius[i]);
	}

	strList << "Contains anticline/syncline number" << QString::number(GetChildren(EXGSAnticline).size());
	strList << "Contains merged structures number" << QString::number(GetChildren(EXGSStructure).size());

	strList << "Number in I direction" << QString::number(m_utm.GetNI());
	strList << "Step in I direction" << QString::number(m_utm.GetIInterval(), 'g', 4);
	strList << "Number in J direction" << QString::number(m_utm.GetNJ());
	strList << "Step in J direction" << QString::number(m_utm.GetJInterval(), 'g', 4);

	return strList;
}

QUuid GSStressMap::GetSurveyID()
{
	CXObject *pParent = this->GetParent();
	while (pParent)
	{
		if (pParent->GetObjectType() == EX3DSurvey)
			return pParent->GetObjectID();

		pParent = pParent->GetParent();
	}

	return QUuid();
}

QVector<double> GSStressMap::CalculateStressInsideCapsules()
{
	double dStep = m_utm.GetIInterval() / 5;

	QVector<double> points;

	int i, j;
	double dX, dY, dAngle, dPreAngle = 999., dMag, dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	const QList<CXObject*>& listCapsule = GetChildren(EXGSStructure);
	for (CXObject* pObj : listCapsule)
	{
		GSStructure* pCapsule = dynamic_cast<GSStructure*>(pObj);
		Q_ASSERT(pCapsule);

		bool bReverse = pCapsule->GetType() == STRUCTURE_REVERSE_FAULT && pCapsule->GetMagState() == MAG_REVERSE;
		pCapsule->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
		for (dX = dXMin + 1; dX < dXMax; dX += dStep)
		{
			for (dY = dYMin + 1; dY < dYMax; dY += dStep)
			{
				if (pCapsule->GetBoundaryPolygon().containsPoint(QPointF(dX, dY), Qt::WindingFill))
				{
					dMag = pCapsule->GetStressMagtitude();

					if (bReverse
						|| pCapsule->GetAdjMagState() == MAG_NORMAL
						|| pCapsule->GetAdjMagState() == MAG_ESS)
					{
						QPolygonF polygon = pCapsule->GetBoundaryPolygon();

						QPointF p1 = polygon[0];
						for (j = 1; j < polygon.size(); j++)
						{
							QPointF p2 = polygon[j];
							XLine2d line(p1.x(), p1.y(), p2.x(), p2.y());
							if (XGeom::Distance(XVec2d(dX, dY), line) < 9 * dStep)
							{
								break;
							}

							p1 = p2;
						}

						if (j < polygon.size())
						{
							if (bReverse)
							{
								dMag = gStressMagRange[MAG_REVERSE].m_fSHMagLower;
							}
							else if (pCapsule->GetAdjMagState() == MAG_NORMAL)
							{
								dMag = gStressMagRange[MAG_NORMAL].Upper();
							}
							else
							{
								dMag = gStressMagRange[MAG_ESS].m_fSHMagLower;
							}
						}
					}

					if ((pCapsule->GetType() == STRUCTURE_REVERSE_FAULT && pCapsule->GetMagState() == MAG_CSS)
						|| (pCapsule->GetType() == STRUCTURE_NORMAL_FAULT && pCapsule->GetMagState() == MAG_ESS)
						|| (pCapsule->GetMagState() != pCapsule->GetAdjMagState())
						|| (pCapsule->GetType() == STRUCTURE_NORMAL_FAULT && pCapsule->GetMagState() == MAG_NORMAL))
					{
						dAngle = g_dInvalidData;
					}
					else
					{
						dAngle = pCapsule->GetSlope() + 90;
						if (dPreAngle == 999.)
							dPreAngle = dAngle;
						if (qAbs(dPreAngle - dAngle) > 90)
						{
							if (dAngle > 90)
								dAngle -= 90;
							else
								dAngle += 90;
						}
						dPreAngle = dAngle;
					}

					points << dX << dY << dMag << dAngle;
				}
			}
		}
	}

	double dAdj;
	for (CXObject* pObj : listCapsule)
	{
		GSStructure* pCapsule = dynamic_cast<GSStructure*>(pObj);
		Q_ASSERT(pCapsule);
		QPolygonF polygon = pCapsule->GetBoundaryPolygon();
		dAngle = g_dInvalidData;

		if (pCapsule->GetType() == STRUCTURE_REVERSE_FAULT && pCapsule->GetAdjMagState() == MAG_REVERSE)
		{
			dMag = gStressMagRange[MAG_REVERSE].m_fSHMagLower - 0.005;
			dAdj = 0.022;
		}
		else if (pCapsule->GetAdjMagState() == MAG_NORMAL)
		{
			dMag = gStressMagRange[MAG_NORMAL].Upper() + 0.005;
			dAdj = 0.;
		}
		else if (pCapsule->GetAdjMagState() == MAG_ESS)
		{
			dMag = gStressMagRange[MAG_ESS].m_fSHMagLower - 0.005;
			dAdj = 0.;
		}
		else
			continue;

		QPointF p1 = polygon[0], p2;
		points << p1.x() << p1.y() << dMag << dAngle;

		double dLen, dInc, dDelta;
		XLine2d line;
		for (j = 1; j < polygon.size(); j++)
		{
			p2 = polygon[j];
			dLen = XGeom::Distance(XVec2d(p1.x(), p1.y()), XVec2d(p2.x(), p2.y()));
			line = XLine2d(p1.x(), p1.y(), p2.x(), p2.y());

			if (dLen > dStep)
			{
				dInc = dStep / dLen;
				for (dDelta = dInc; dDelta < 1; dDelta += dInc)
				{
					dX = p1.x() * (1 - dDelta) + p2.x() * dDelta;
					dY = p1.y() * (1 - dDelta) + p2.y() * dDelta;
					points << dX << dY << dMag << dAngle;

					XVec2d xp = line.PointPerp(dDelta * dLen, dStep / (-2));
					points << xp[0] << xp[1] << dMag << dAngle;
					xp = line.PointPerp(dDelta * dLen, dStep / (-4));
					points << xp[0] << xp[1] << dMag << dAngle;
				}
			}

			points << p2.x() << p2.y() << dMag << dAngle;

			XVec2d xp = line.PointPerp(dLen, dStep / (-2));
			points << xp[0] << xp[1] << dMag - dAdj << dAngle;
			xp = line.PointPerp(dLen, dStep / (-4));
			points << xp[0] << xp[1] << dMag - dAdj << dAngle;

			p1 = p2;
		}
	}

	return points;
}

QVector<double> GSStressMap::CalculateStressInsideCapsulesMethod2()
{
	double dStep = m_utm.GetIInterval() / 5;

	QVector<double> points;

	int i, j;
	double dX, dY, dAngle, dPreAngle = 999., dMag, dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	const QList<CXObject*>& listCapsule = GetChildren(EXGSStructure);

	QPolygonF totalWPolygon;
	for (CXObject* pObj : listCapsule)
	{
		GSStructure* pCapsule = dynamic_cast<GSStructure*>(pObj);
		Q_ASSERT(pCapsule);

		if(pCapsule->GetType() != 3)
			continue;

		QPolygonF wellPolygon;
		pCapsule->GetBigBoundary(wellPolygon);
		totalWPolygon = totalWPolygon.united(wellPolygon);
	}

	for (CXObject* pObj : listCapsule)
	{
		GSStructure* pCapsule = dynamic_cast<GSStructure*>(pObj);
		Q_ASSERT(pCapsule);

		bool bWellStructure = (pCapsule->GetType() == 3);
		pCapsule->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
		for (dX = dXMin; dX <= dXMax; dX += dStep)
		{
			for (dY = dYMin; dY <= dYMax; dY += dStep)
			{
				if (!bWellStructure)
				{
					//	Then check whether it locates in any well polygons.
					if(totalWPolygon.containsPoint(QPointF(dX, dY), Qt::WindingFill))
						continue;
				}

				if (pCapsule->GetBoundaryPolygon().containsPoint(QPointF(dX, dY), Qt::WindingFill))
				{
					dMag = pCapsule->GetStressMagtitude();

					dAngle = pCapsule->GetStressAzimuth();

					points << dX << dY << dMag << dAngle;
				}
			}
		}
	}

	return points;
}

bool GSStressMap::IsInsideNormalStructure(double x, double y)
{
	for (auto pObj : GetChildren(EXGSStructure))
	{
		auto pStructure = dynamic_cast<GSStructure*>(pObj);
		if (!pStructure || pStructure->GetMagState() != MAG_NORMAL)
			continue;

		const QPolygonF& boundaryPolygon = pStructure->GetBoundaryPolygon();
		if (boundaryPolygon.containsPoint(QPointF(x, y), Qt::WindingFill))
			return true;
	}

	return false;
}

bool GSStressMap::IsInsideReverseStructure(double x, double y)
{
	for (auto pObj : GetChildren(EXGSStructure))
	{
		auto pStructure = dynamic_cast<GSStructure*>(pObj);
		if (!pStructure || pStructure->GetMagState() != MAG_REVERSE)
			continue;

		const QPolygonF& boundaryPolygon = pStructure->GetBoundaryPolygon();
		if (boundaryPolygon.containsPoint(QPointF(x, y), Qt::WindingFill))
			return true;
	}

	return false;
}

CX3DHorizon* GSStressMap::CreateKh()
{
	CX3DHorizon *pKh = NULL;

	float *pData = GetData();
	if (!pData)
		return pKh;

	QString sHName = "Kh from " + GetObjectName();
	sHName = GetParent()->GetUnallocatedName(sHName);
	pKh = new CX3DHorizon(GetSurveyID(), GetUTM(), sHName);
	pKh->SetObjectType(EXGS3DHorizonAtt);
	pKh->SetModifiedFlag();

	float *pKData = pKh->GetData();
	memcpy(pKData, pData, sizeof(float) * GetUTM().GetNI() * GetUTM().GetNJ());

	return pKh;
}