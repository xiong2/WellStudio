#include "xobjectfactory.h"
#include "gsfrg.h"
#include "x3dsurvey.h"
#include "x3dhorizon.h"
#include "xfaultsticks.h"
#include "gs3dhorizonfaulttraces.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSFRG)
EXGSFRG
END_REGISTER_OBJECT_TO_FACTORY(GSFRG)

GSFRG::GSFRG(CX3DSurvey *pSurvey, CXFaultSticks *pFault)
{
	SetObjectName("Fault Seal Graph");
	SetObjectType(EXGSFRG);
	SetIconName("FRG.png");

	double dCX, dCY, dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	CXSeismicUTMTool utm = pSurvey->GetUTM();
	pFault->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	dCX = (dXMin + dXMax) / 2;
	dCY = (dYMin + dYMax) / 2;
	int i, j, ti, tj, k, nJ = utm.GetNJ();
	utm.XYToIJ(dCX, dCY, ti, tj);

	int dipArray[] = {0, 15, 25, 32, 38, 45, 52, 60, 66, 72, 76, 85, 90};
	double deArray[] = {100, 95, 85, 80, 70, 62, 55, 42, 35, 28, 20, 9, 5};
	double nfdpct[] = {00, 10, 13, 20, 29, 30, 40, 43, 48, 60, 70, 80, 88, 90, 93, 95, 100};
	double nfdd[] = {90, 82, 80, 76, 72, 69, 62, 60, 57, 48, 40, 30, 20, 18, 15, 10, 0};

	QList<CXObject *> listH = pSurvey->GetChildren(EXGS3DHorizonDepth, true);
	foreach(CXObject *pObj, listH)
	{
		CX3DHorizon *pH = (CX3DHorizon *)pObj;
		float *pData = pH->GetData();

		CXObject *pHF = pObj->GetChild(pFault->GetObjectName(), EXGSFaultTraces);
		if (!pHF)
		{
			m_vecDepth << pData[ti * nJ + tj];
			m_vecRP << g_dInvalidData;
			m_vecDE << g_dInvalidData;
			m_vecAV << g_dInvalidData;
			m_vecFD << g_dInvalidData;
		}
		else
		{
			GS3DHorizonFaultTraces *pHFT = (GS3DHorizonFaultTraces *)pHF;
			pHFT->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
			dCX = (dXMin + dXMax) / 2;
			dCY = (dYMin + dYMax) / 2;
			utm.XYToIJ(dCX, dCY, i, j);

			int iDip = pHFT->Dip();
			for(k = 0; k < 13; k++)
				if(iDip <= dipArray[k])
					break;
			double dPer = pHFT->ReversePercent();
			double dPct = deArray[k];
			for(k = 0; k < 17; k++)
				if(dPct <= nfdpct[k])
					break;

			m_vecDepth << pData[i * nJ + j];
			m_vecRP << dPer;
			m_vecDE << dPct;
			m_vecAV << (dPer + dPct) / 2;
			m_vecFD << (90.0 - nfdd[k]) * 100.0 / 90.0;
		}
	}

	dZMin = m_vecDepth.first();
	dZMax = m_vecDepth.last();

    _SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

bool GSFRG::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_vecDepth;
		ar << m_vecRP;
		ar << m_vecDE;
		ar << m_vecAV;
		ar << m_vecFD;
	}
	else
	{
		ar >> m_vecDepth;
		ar >> m_vecRP;
		ar >> m_vecDE;
		ar >> m_vecAV;
		ar >> m_vecFD;
	}

	return true;
}

QString GSFRG::GetTypeString()
{
	return "Fault Seal Graph";
}

QStringList GSFRG::GetDescription()
{
	QStringList sList;

	sList << "Traverse horizons number" << QString::number(GetTraverseHorizonNum());

	return sList;
}

int GSFRG::GetTraverseHorizonNum()
{
	int iCount = 0;
	foreach(double dVal, m_vecRP)
	{
		if(dVal != g_dInvalidData)
			iCount++;
	}

	return iCount;
}