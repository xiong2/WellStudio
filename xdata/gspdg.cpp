#include "xobjectfactory.h"
#include "gspdg.h"
#include "x3dsurvey.h"
#include "x3dhorizon.h"
#include "gsstressmap.h"
#include "gsdef.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSPDG)
EXGSPDG
END_REGISTER_OBJECT_TO_FACTORY(GSPDG)

GSPDG::GSPDG()
{

}

//	Created from a map.
GSPDG::GSPDG(CX3DSurvey *pSurvey, const QString& sName, QPointF point) : CXObject(sName)
{
	SetIconName("PDG.png");
	SetObjectType(EXGSPDG);
	m_trajectory << point;

	calculateStressPoints(pSurvey);
}

//	Created from a section.
GSPDG::GSPDG(GSSection *, const QString& sName, QPolygonF) : CXObject(sName)
{
	SetIconName("PDG.png");
	SetObjectType(EXGSPDG);
}

GSPDG::~GSPDG()
{

}

bool GSPDG::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_refID;
		ar << m_listHID;
		ar << m_trajectory;
		ar << m_vecStressPoints;
	}
	else
	{
		ar >> m_refID;
		ar >> m_listHID;
		ar >> m_trajectory;
		ar >> m_vecStressPoints;
	}

	return true;
}

QString GSPDG::GetTypeString()
{
	return "Pressure-Depth Graph";
}

QStringList GSPDG::GetDescription()
{
	QStringList sList;
	sList << "Traverse horizons number" << QString::number(m_listHID.size());

	return sList;
}

void GSPDG::calculateStressPoints(CX3DSurvey *pSurvey)
{
	m_listHID.clear();
	m_vecStressPoints.clear();

	//	6 values for each point: horizon IDX, depth, Pp, Sv, SH, Sh.
	QList<CXObject *> listFolder = pSurvey->GetChildren(EXGSFolderHorizon, true);
	int i, j, iCount = 0;
	float fPreZ = 0., fPrePp = 0., fPreSv = 0;
	foreach(CXObject *pFolder, listFolder)
	{
		QList<CXObject *> listH = pFolder->GetChildren(EXGS3DHorizonDepth);
		QList<CXObject *> listS = pFolder->GetChildren(EXGSStressMap);

		if (listH.isEmpty() || listS.isEmpty())
			continue;

		CX3DHorizon *pHor = (CX3DHorizon *)listH.first();
		GSStressMap *pMap = (GSStressMap *)listS.last();

		m_listHID << pHor->GetObjectID();

		//	Horizon IDX.
		m_vecStressPoints << (float)iCount;

		//	Depth.
		CXSeismicUTMTool zutm = pHor->GetUTM();
		zutm.XYToIJ(m_trajectory[0].x(), m_trajectory[0].y(), i, j);
		float *pZData = pHor->GetData();
		float z = pZData[i * zutm.GetNJ() + j];
		m_vecStressPoints << z;

		//	Pp
		float fPp = (fPrePp + (z - fPreZ) * pHor->GetHydroGradient() / 1000.);
		m_vecStressPoints << fPp;

		//	Sv
		float fSv = (fPreSv + (z - fPreZ) * pHor->GetLithoGradient() / 1000.);
		m_vecStressPoints << fSv;

		//	SH
		CXSeismicUTMTool sutm = pMap->GetUTM();
		sutm.XYToIJ(m_trajectory[0].x(), m_trajectory[0].y(), i, j);
		float *pSData = pMap->GetData();
		float SH = pSData[i * sutm.GetNJ() + j];
		m_vecStressPoints << SH;

		//	Sh
		m_vecStressPoints << gSHToSh(SH);

		iCount++;
		fPreZ = z;
		fPrePp = fPp;
		fPreSv = fSv;
	}

	//	The last horizon does not contain stress map, but we still need it as the end point.
	QList<CXObject *> listH = listFolder.last()->GetChildren(EXGS3DHorizonDepth);
	CX3DHorizon *pHor = (CX3DHorizon *)listH.first();

	float fLastSH = m_vecStressPoints[m_vecStressPoints.size() - 2];
	float fLastSh = m_vecStressPoints[m_vecStressPoints.size() - 1];

	//	Horizon IDX.
	m_vecStressPoints << -1.;

	//	Depth.
	CXSeismicUTMTool zutm = pHor->GetUTM();
	zutm.XYToIJ(m_trajectory[0].x(), m_trajectory[0].y(), i, j);
	float *pZData = pHor->GetData();
	float z = pZData[i * zutm.GetNJ() + j];
	m_vecStressPoints << z;

	//	Pp
	float fPp = (fPrePp + (z - fPreZ) * pHor->GetHydroGradient() / 1000.);
	m_vecStressPoints << fPp;

	//	Sv
	float fSv = (fPreSv + (z - fPreZ) * pHor->GetLithoGradient() / 1000.);
	m_vecStressPoints << fSv;

	m_vecStressPoints << fLastSH << fLastSh;
}

void GSPDG::_SetSelfDimension()
{
	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	dXMin = m_trajectory[0].x();
	dXMax = m_trajectory[0].x();
	dYMin = m_trajectory[0].y();
	dYMax = m_trajectory[0].y();

	foreach(QPointF point, m_trajectory)
	{
		dXMin = dXMin < point.x() ? dXMin : point.x();
		dXMax = dXMax > point.x() ? dXMax : point.x();
		dYMin = dYMin < point.y() ? dYMin : point.y();
		dYMax = dYMax > point.y() ? dYMax : point.y();
	}

	dZMin = m_vecStressPoints[1];
	dZMax = m_vecStressPoints[1];
	for (int i = 1; i < m_vecStressPoints.size(); i += 6)
	{
		dZMin = dZMin < m_vecStressPoints[i] ? dZMin : m_vecStressPoints[i];
		dZMax = dZMax > m_vecStressPoints[i] ? dZMax : m_vecStressPoints[i];
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

