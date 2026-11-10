#include "x3dhorizon.h"

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xutility.h"
#include "xfunctiontemplate.h"
#include "gscompressionpulse.h"
#include "gsthreadutminterpolation.h"
#include "xdlgcalculatingprogress.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX3DHorizon)
EX3DHorizon,
EX3DHorizonAtt,
EXGS3DHorizonTWT,
EXGS3DHorizonDepth,
EXGS3DHorizonIso,
EXGS3DHorizonAtt
END_REGISTER_OBJECT_TO_FACTORY(CX3DHorizon)

CX3DHorizon::CX3DHorizon(): m_grid(*this)
{
}

CX3DHorizon::CX3DHorizon(const QUuid& uuidSurvey, const CXSeismicUTMTool& utm, const QString& strName)
	:m_uuidSurvey(uuidSurvey), CX3DSurface(utm, strName), m_grid(*this)
{
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&utm));
	SetIconName("Horizon.png");
	SetObjectType(EX3DHorizon);
}

CX3DHorizon::CX3DHorizon(const CX3DHorizon& other)
	:CX3DSurface(other), m_grid(*this)
{
	m_utm = other.m_utm;
	m_uuidSurvey = other.m_uuidSurvey;

	SetIconName(other.GetIconName());
	SetObjectType(other.GetObjectType());

	SetPulse(other.m_iPulse);
	SetHorizonType(other.m_eHType);
	SetBaseSHDirection(other.m_iSHDir);
	SetPorePressure(other.m_fPorePressure);
	SetHydroGradient(other.m_fHydroGradient);
	SetLithoGradient(other.m_fLithoGradient);
	SetIntervalVelocity(other.m_fIntervalVelocity);
	SetUsedByPP(other.m_bUsedByPP);
	SetColor(other.GetColor());

	SetDeletableFlag(false);
}

CX3DHorizon::~CX3DHorizon()
{
}

bool CX3DHorizon::SerializeData(CXArchive& ar)
{
	if (!CX3DSurface::SerializeData(ar))
		return false;

	int iTmp;
	if (ar.IsSaving())
	{
		iTmp = (int)m_eHType;
		ar << m_uuidSurvey;
		ar << m_iPulse;
		ar << m_iSHDir;
		ar << m_fIntervalVelocity;
		ar << m_fHydroGradient;
		ar << m_fLithoGradient;
		ar << m_fPorePressure;
		ar << m_bUsedByPP;
		ar << m_topHID;
		ar << m_bottomHID;
		ar << iTmp;
	}
	else
	{
		ar >> m_uuidSurvey;
		ar >> m_iPulse;
		ar >> m_iSHDir;
		ar >> m_fIntervalVelocity;
		ar >> m_fHydroGradient;
		ar >> m_fLithoGradient;
		ar >> m_fPorePressure;
		ar >> m_bUsedByPP;
		ar >> m_topHID;
		ar >> m_bottomHID;
		ar >> iTmp;

		m_eHType = (EHorizonType)iTmp;
	}

	m_utm.SerializeData(ar);

	return true;

}

void CX3DHorizon::SetObjectType(EXObjectType eObjType)
{
	IKEIO::SetObjectType(eObjType);

	if (eObjType == EX3DHorizon || eObjType == EX3DHorizonAtt)
	{
		SetIconName("Horizon.png");
	}
	else if (eObjType == EXGS3DHorizonTWT)
	{
		SetDeletableFlag(false);
		SetIconName("Horizon2.png");
	}
	else if (eObjType == EXGS3DHorizonDepth)
	{
		SetDeletableFlag(false);
		SetIconName("Horizon3.png");
	}
	else if (eObjType == EXGS3DHorizonIso)
	{
		SetDeletableFlag(false);
		SetIconName("Horizon4.png");
	}
	else if (eObjType == EXGS3DHorizonAtt)
	{
		SetDeletableFlag(true);
		SetIconName("Horizon4.png");
	}
}

QString CX3DHorizon::GetTypeString()
{
	if (this == nullptr)
		return QString();

	EXObjectType eObjType = GetObjectType();

	if (eObjType == EX3DHorizon)
		return "3-D Horizon";
	else if(eObjType == EX3DHorizonAtt)
		return "3-D Horizon Attribute";
	else if (eObjType == EXGS3DHorizonTWT)
		return "3-D Horizon TWT";
	else if (eObjType == EXGS3DHorizonDepth)
		return "3-D Horizon Depth";
	else if (eObjType == EXGS3DHorizonIso)
		return "Isopach Map";
	else if (eObjType == EXGS3DHorizonAtt)
		return "Attribute Map";
	else
		return "error type";
}

QStringList CX3DHorizon::GetDescription()
{
	QStringList strList;

	if(::UsingChinese())
	{
		strList<<GetTr("主测线方向数目")<<QString::number(m_utm.GetNI());
		strList<<GetTr("主测线方向步长")<<QString::number(m_utm.GetIInterval());
		strList<<GetTr("联络测线方向数目")<<QString::number(m_utm.GetNJ());
		strList<<GetTr("联络测线方向步长")<<QString::number(m_utm.GetJInterval());
	}
	else
	{
		strList<<"Number in inline direction"<<QString::number(m_utm.GetNI());
		strList<<"Step in inline direction"<<QString::number(m_utm.GetIInterval());
		strList<<"Number in crossline direction"<<QString::number(m_utm.GetNJ());
		strList<<"Step in crossline direction"<<QString::number(m_utm.GetJInterval());
	}

	EXObjectType eObjType = GetObjectType();
	QStringList sListType;
	sListType << "Conformable" << "Unconformable" << "Erosional" << "Basement";

	if (eObjType == EXGS3DHorizonTWT)
	{
		strList << "Interval velocity (m/s)" << QString::number(m_fIntervalVelocity);
		strList << "Compression pulse" << GSCompressionPulse::GetOnePulse(m_iPulse);
		strList << "Horizon type" << sListType[m_eHType];
	}
	else if (eObjType == EXGS3DHorizonDepth)
	{
		strList << "Compression pulse" << GSCompressionPulse::GetOnePulse(m_iPulse);
		strList << "Horizon type" << sListType[m_eHType];
	}
	else if (eObjType == EXGS3DHorizonIso)
	{
		CXObject *pTObj = GetObjectByID(m_topHID);
		CXObject *pBObj = GetObjectByID(m_bottomHID);

		if (pTObj && pBObj)
		{
			strList << "Top horizon" << pTObj->GetObjectName();
			strList << "Bottom horizon" << pBObj->GetObjectName();
		}
		else
			strList << "Top or bottom horizons" << "Unknown";
	}

	return strList;
}

CX3DHorizon * CX3DHorizon::GetGeometryObject()
{
	if (this == nullptr)
		return nullptr;

	if (this->GetObjectType() == EX3DHorizon
		|| this->GetObjectType() == EXGS3DHorizonTWT || this->GetObjectType() == EXGS3DHorizonDepth
		|| this->GetObjectType() == EXGS3DHorizonIso || this->GetObjectType() == EXGS3DHorizonAtt)
		return this;
	else if (this->GetObjectType() == EX3DHorizonAtt)
	{
		return dynamic_cast<CX3DHorizon*>(this->GetAncient(EX3DHorizon));
	}
	else
		return nullptr;
}

void CX3DHorizon::GetFractureInfo(const QUuid & uuidDensity, const QUuid & uuidAzimuth, int ndX, int ndY, float fMinThreshold, float fMaxThreshold, vector<float>& vecDensity, vector<float>& vecAzimth, vector<float>& vecColor)
{
	CX3DHorizon* pDenSur = dynamic_cast<CX3DHorizon*>(::GetObjectByID(uuidDensity));
	CX3DHorizon* pAziSur = dynamic_cast<CX3DHorizon*>(::GetObjectByID(uuidAzimuth));

	if (!pDenSur || !pAziSur)
		return;

	CXSeismicUTMTool utm = pDenSur->GetUTM();
	if (!pAziSur->GetUTM().Equals(&utm))
		return;

	int nI = utm.GetNI();
	int nJ = utm.GetNJ();

	float fInvalid = ::g_dInvalidData;
	float fInvEPS = ::GetEPSofInvalidData(fInvalid);

	std::vector<float> vecHorDen(nI*nJ), vecHorAzi(nI*nJ);
	memcpy(&vecHorDen[0], pDenSur->GetData(), sizeof(float)*nI*nJ);
	memcpy(&vecHorAzi[0], pAziSur->GetData(), sizeof(float)*nI*nJ);

	// filtering
	//NXUtility::FilterTwoData(nI, nJ, &vecHorDen[0], &vecHorAzi[0], 3, 3, ::g_dInvalidData);

	int iDI = qMax(1, ndY);
	int iDJ = qMax(1, ndX);

	int nFraNI = nI / iDI;
	int nFraNJ = nJ / iDJ;

	if (nFraNI < 1 || nFraNJ < 1)
		return;

	vecDensity.resize(nFraNI*nFraNJ, fInvalid);
	vecAzimth.resize(nFraNI*nFraNJ, fInvalid);
	vecColor.resize(nFraNI*nFraNJ, fInvalid);

	std::vector<QPair<int, int> > vecIndex(nFraNI*nFraNJ);

	int iMin, iMax, jMin, jMax;
	for (int iI = 0; iI < nFraNI; ++iI)
	{
		iMin = iI*iDI;
		iMax = iMin + iDI - 1;
		for (int iJ = 0; iJ < nFraNJ; ++iJ)
		{
			jMin = iJ*iDJ;
			jMax = jMin + iDJ - 1;

			int iPos = -1, jPos = -1;
			float fMaxValue = M_FLT_NEGATIVEMAX;
			int count = 0;
			for (int i = iMin; i <= iMax; ++i)
			{
				for (int j = jMin; j <= jMax; ++j)
				{
					if (qAbs(vecHorDen[i*nJ + j] - fInvalid) < fInvEPS ||
						qAbs(vecHorAzi[i*nJ + j] - fInvalid) < fInvEPS)
						continue;

					//vecIndex[count++] = qMakePair(i, j);

					if (qAbs(vecHorDen[i*nJ + j]) > fMaxValue)
					{
						fMaxValue = qAbs(vecHorDen[i*nJ + j]);
						iPos = i;
						jPos = j;
					}
				}
			}

			if (iPos != -1)
			{

				vecDensity[iI*nFraNJ + iJ] = qAbs(vecHorDen[iPos*nJ + jPos]);
				vecAzimth[iI*nFraNJ + iJ] = vecHorAzi[iPos*nJ + jPos];
				vecColor[iI*nFraNJ + iJ] = vecHorDen[iPos*nJ + jPos];

			}

			if (count != 0)
			{
				//double dSumX(0), dSumY(0);
				//double dAni, dAZi;
				//for (int i = 0; i < count; ++i)
				//{
				//	dAni = qAbs(vecHorDen[vecIndex[i].first*nJ + vecIndex[i].second]);
				//	dAZi = vecHorAzi[vecIndex[i].first*nJ + vecIndex[i].second] * M_RAD;
				//	dSumX += dAni*cos(dAZi);
				//	dSumY += dAni*sin(dAZi);
				//}

				//dSumX /= count;
				//dSumY /= count;

				//dAni = sqrt(SQR(dSumX) + SQR(dSumY));
				//dAZi = -atan2(dSumY, dSumX)*M_DEG;
				//if (dAZi < 0)
				//	dAZi += 360;

				//vecDensity[iI*nFraNJ + iJ] = dAni;
				//vecAzimth[iI*nFraNJ + iJ] = dAZi;

				//vecDensity[iI*nFraNJ + iJ] = vecHorDen[iPos*nJ + jPos];
				//vecAzimth[iI*nFraNJ + iJ] = vecHorAzi[iPos*nJ + jPos];
			}
		}
	}

	// post-processing
	int nSize = nFraNI*nFraNJ;
	std::vector<float> vecTmp(nSize);
	int iCount = 0;
	for (int i = 0; i < nSize; ++i)
	{
		if (qAbs(vecDensity[i] - fInvalid) > fInvEPS)
		{
			vecTmp[iCount++] = vecDensity[i];
		}
	}
	if (iCount == 0)
		return;

	int kmin = static_cast<int>(iCount*fMinThreshold);
	int kmax = qMin((int)vecTmp.size() - 1, static_cast<int>(iCount*fMaxThreshold));
	
	float fminValue = NXUtility::Select(&vecTmp[0], iCount, kmin);
	float fmaxValue = NXUtility::Select(&vecTmp[0], iCount, kmax);

	float fHalfLength = sqrt(SQR(qMax(1, iDI - 1)*utm.GetIInterval()) + SQR(qMax(1,iDJ - 1)*utm.GetJInterval())) / 2.f;

	for (int i = 0; i < nSize; ++i)
	{
		if (qAbs(vecDensity[i] - fInvalid) < fInvEPS)
			continue;

		if (vecDensity[i] < fminValue)
			vecDensity[i] = 0;
		else if (vecDensity[i] > fmaxValue)
			vecDensity[i] = fHalfLength;
		else
		{
			vecDensity[i] = fHalfLength / (fmaxValue - fminValue)*(vecDensity[i] - fminValue);
		}
	}
}


//	Resample to the new UTM and interpolate the data.
void CX3DHorizon::Resample(CXSeismicUTMTool* pUTM)
{
	if (!m_pDataInMem)
		LoadData();

	auto pThread = std::make_unique<GSThreadUTMInterpolation>(*pUTM, m_pDataInMem, m_utm);
	pThread->LockRead(this);
	pThread->SetObjectName(GetObjectName());

	auto pProgress = new CXDlgCalculatingProgress(pThread.get());
	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		const std::vector<float>& vecData = pThread->GetResult();
		m_utm = *pUTM;
		CX3DSurface::m_utm.Copy(pUTM);
		delete m_pDataInMem;
		m_pDataInMem = new float[m_utm.GetNI() * m_utm.GetNJ()];
		memcpy(m_pDataInMem, &vecData[0], vecData.size() * sizeof(float));
		SetModifiedFlag();
	}

	pThread->UnlockRead(this);
}

//	Resample to the new UTM and interpolate the data.
void CX3DHorizon::Resample(float fBinSize)
{
	if (!m_pDataInMem)
		LoadData();

	CXSeismicUTMTool utm = CXSeismicUTMTool(m_utm);
	utm.ChangeCellSize(fBinSize);

	auto pThread = std::make_unique<GSThreadUTMInterpolation>(utm, m_pDataInMem, m_utm, 1);
	pThread->LockRead(this);
	pThread->SetObjectName(GetObjectName());

	auto pProgress = new CXDlgCalculatingProgress(pThread.get());
	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		const std::vector<float>& vecData = pThread->GetResult();
		m_utm = utm;
		delete m_pDataInMem;
		m_pDataInMem = new float[m_utm.GetNI() * m_utm.GetNJ()];
		memcpy(m_pDataInMem, &vecData[0], vecData.size() * sizeof(float));
		SetModifiedFlag();
	}

	pThread->UnlockRead(this);
}