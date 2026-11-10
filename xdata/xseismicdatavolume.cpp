#include "xseismicdatavolume.h"

#include <vector>
#include <QFile>
#include <qfileinfo.h>
#include <qvector.h>

#include "xglobal.h"
#include "xproject.h"
#include "xobjectfactory.h"
#include "xregulardatareader.h"
#include "xseismicrandomsection.h"
#include "xseismicirregularreader.h"
#include "xseismicsection.h"
#include "xeventconsole.h"
#include "xutility.h"
#include "xfunctiontemplate.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXSeismicDataVolume)
EXSeismicDataVolume
END_REGISTER_OBJECT_TO_FACTORY(CXSeismicDataVolume)

CXSeismicDataVolume::CXSeismicDataVolume()
{
	m_pTraceReader = NULL;
	m_pSliceReader = NULL;

	m_iMaxFold = 1;
	m_fStartOffset = 0.;
	m_fOffsetStep = 0.;
}

CXSeismicDataVolume::CXSeismicDataVolume (const CXSeismicUTMTool& utm, double dSamplingStart, double dSamplingEnd, double dSamplingRate, 
	const QString& strName, int iMaxFold, float fStartOffset, float fOffsetStep, bool bAzimuth)
	:CXSeismicObject(dSamplingStart, dSamplingEnd, dSamplingRate, strName)
{
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&utm));

	if (bAzimuth)
		SetIconName("Prestack5D.png");
	else if (iMaxFold > 1)
		SetIconName("Prestack3D.png");
	else 
		SetIconName("SeismicDataVolume.png");

	SetObjectType(EXSeismicDataVolume);

	m_iMaxFold = iMaxFold;
	m_fStartOffset = fStartOffset;
	m_fOffsetStep = fOffsetStep;

	m_pTraceReader = NULL;
	m_pSliceReader = NULL;
}

CXSeismicDataVolume::CXSeismicDataVolume(const CXSeismicDataVolume& other)
	:CXSeismicObject(other)
{
	m_pTraceReader = NULL;
	m_pSliceReader = NULL;
}

CXSeismicDataVolume::~CXSeismicDataVolume()
{
	if (m_pTraceReader)
		delete m_pTraceReader;

	if (m_pSliceReader)
		delete m_pSliceReader;

	if (m_pIrregularReader)
		delete m_pIrregularReader;
}

QString CXSeismicDataVolume::GetTypeString()
{
	if (IsAzimuth())
		return "Prestack Azimuth 3D Seismic Volume";
	else if (IsIrregular())
		return "Prestack 3D Seismic Gather with Irregular Offsets";
	else if (IsPrestack())
		return "Prestack 3D Seismic Gather";
	else
		return "Poststack 3D Seismic Volume";
}

unsigned int CXSeismicDataVolume::GetTraceNumber()
{
	return m_utm.GetNI() * m_utm.GetNJ();
}

int CXSeismicDataVolume::GetInlineQty()
{
	return m_utm.GetNI();
}

int CXSeismicDataVolume::GetXlineQty()
{
	return m_utm.GetNJ();
}

int CXSeismicDataVolume::GetInlineTraceQty(int iXline)
{
	if (IsIrregular())
	{
		CXSeismicIrregularReader *pTInfo = GetIrregularReader();
		if (pTInfo)
			return pTInfo->GetInlineTraceQty(iXline);
		else
			return 0;
	}
	else
		return m_utm.GetNI() * m_iMaxFold;
}

int CXSeismicDataVolume::GetXlineTraceQty(int iInline)
{
	if (IsIrregular())
	{
		CXSeismicIrregularReader *pTInfo = GetIrregularReader();
		if (pTInfo)
			return pTInfo->GetXlineTraceQty(iInline);
		else
			return 0;
	}
	else
		return m_utm.GetNJ() * m_iMaxFold;
}

int CXSeismicDataVolume::GetSectionTraceQty(CXSeismicSection *pSection)
{
	if (IsIrregular())
	{
		CXSeismicIrregularReader *pTInfo = GetIrregularReader();
		if (pTInfo)
			return pTInfo->GetSectionTraceQty(pSection);
		else
			return 0;
	}
	else
	{
		bool bChanged = false;
		int iSTrace, iETrace;
		pSection->GetSectionRange(iSTrace, iETrace);
		if (pSection->GetSectionType() == eInlineSection)
		{
			if (iSTrace == -1 || iETrace == -1)
			{
				pSection->SetSectionRange(m_utm.GetFirstCrossline(), m_utm.GetLastCrossline());
				return m_utm.GetNJ() * m_iMaxFold;
			}

			if (iSTrace < m_utm.GetFirstCrossline())
			{
				iSTrace = m_utm.GetFirstCrossline();
				bChanged = true;
			}
			if (iETrace > m_utm.GetLastCrossline())
			{
				iETrace = m_utm.GetLastCrossline();
				bChanged = true;
			}

			if (bChanged)
			{
				pSection->SetSectionRange(iSTrace, iETrace);

				CXProcessEvent processEvent;
				pSection->AddEvent(EDataChanged);
			}

			int i, j1, j2;
			m_utm.LineToIJ(pSection->GetSectionNumber(), iSTrace, i, j1);
			m_utm.LineToIJ(pSection->GetSectionNumber(), iETrace, i, j2);

			return (j2 - j1 + 1) * m_iMaxFold;
		}
		else if (pSection->GetSectionType() == eCrosslineSection)
		{
			if (iSTrace == -1 || iETrace == -1 || iSTrace == iETrace)
			{
				pSection->SetSectionRange(m_utm.GetFirstInline(), m_utm.GetLastInline());
				return m_utm.GetNI() * m_iMaxFold;
			}

			if (iSTrace < m_utm.GetFirstInline())
			{
				iSTrace = m_utm.GetFirstInline();
				bChanged = true;
			}
			if (iETrace > m_utm.GetLastInline())
			{
				iETrace = m_utm.GetLastInline();
				bChanged = true;
			}

			if (bChanged)
			{
				pSection->SetSectionRange(iSTrace, iETrace);

				CXProcessEvent processEvent;
				pSection->AddEvent(EDataChanged);
			}

			int i1, i2, j;
			m_utm.LineToIJ(iSTrace, pSection->GetSectionNumber(), i1, j);
			m_utm.LineToIJ(iETrace, pSection->GetSectionNumber(), i2, j);

			return (i2 - i1 + 1) * m_iMaxFold;
		}

		return 0;
	}
}

int CXSeismicDataVolume::GetRandomSectionTraceQty(CXSeismicRandomSection *pRSection)
{
	if (!IsIrregular())
	{
		return pRSection->GetTraceNum() * m_iMaxFold;
	}
	else
	{
		CXSeismicIrregularReader *pIrrReader = GetIrregularReader();
		std::vector<int> vecInline, vecXline;
		pRSection->GetLineNumbers(vecInline, vecXline);

		return pIrrReader->GetRandomSectionTraceQty(vecInline, vecXline);
	}
}

qint64 CXSeismicDataVolume::GetTotalTraceQty()
{
	QFileInfo qFI(GetTraceFileName());
	qint64 iSize = qFI.size();

	return iSize / (4 * this->GetSamplingQty());
}

QString CXSeismicDataVolume::GetSliceFileName()
{
	QString strFileName = ::GetProject()->GetProjectDataPath() + this->GetObjectID().toString() + ".sli";
	return strFileName;
}

QString CXSeismicDataVolume::GetBrickFileName()
{
	QString strFileName = ::GetProject()->GetProjectDataPath() + this->GetObjectID().toString() + ".bri";
	return strFileName;
}

bool CXSeismicDataVolume::HasTraceFile()
{
	return QFile::exists(GetTraceFileName());
}

bool CXSeismicDataVolume::HasSliceFile()
{
	return QFile::exists(GetSliceFileName());
}

bool CXSeismicDataVolume::HasBrickFile()
{
	return QFile::exists(GetBrickFileName());
}

bool CXSeismicDataVolume::_GetTraceReader()
{
	if (m_pTraceReader)
		return true;

	if (!HasTraceFile())
		return false;

	int nI = GetInlineQty();
	int nJ = GetXlineQty();
	int nK = GetSamplingQty();

	m_pTraceReader = new CXRegularDataReader<float>(GetTraceFileName(), nI, nJ, nK, m_iMaxFold);
	if (!m_pTraceReader->Open())
	{
		delete m_pTraceReader;
		m_pTraceReader = NULL;
		return false;
	}
	else
	{
		return true;
	}
}

bool CXSeismicDataVolume::_GetSliceReader()
{
	//	Prestack volume does not support slice so far.
	if (m_iMaxFold > 1)
		return false;

	if (m_pSliceReader)
		return true;

	if (!HasSliceFile())
		return false;

	int nI = GetInlineQty();
	int nJ = GetXlineQty();
	int nK = GetSamplingQty();

	m_pSliceReader = new CXRegularDataReader<float>(GetSliceFileName(), nK, nI, nJ);
	if (!m_pSliceReader->Open())
	{
		delete m_pSliceReader;
		m_pSliceReader = NULL;
		return false;
	}
	else
	{
		return true;
	}
}

bool CXSeismicDataVolume::ReadInline(int iInlineNumber, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	if (IsIrregular())
	{
		if (!pTraceInfo)
			return false;

		return GetIrregularReader()->ReadInline(this, iInlineNumber, pBuffer, pTraceInfo);
	}
	else
	{
		int iInlineIndex, iTmp;
		m_utm.LineToIJ(iInlineNumber, 0, iInlineIndex, iTmp);

		int nJ = GetInlineQty();
		if (iInlineIndex < 0 || iInlineIndex >= nJ)
			return false;

		if (!pBuffer)
			return false;

		if (!_GetTraceReader())
			return false;

		return m_pTraceReader->ReadUSection(iInlineIndex, pBuffer);
	}

}
bool CXSeismicDataVolume::ReadXline(int iXlineNumber, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	if (IsIrregular())
	{
		if (!pTraceInfo)
			return false;

		return GetIrregularReader()->ReadXline(this, iXlineNumber, pBuffer, pTraceInfo);
	}
	else
	{
		int iXlineIndex, iTmp;
		m_utm.LineToIJ(0, iXlineNumber, iTmp, iXlineIndex);

		int nJ = GetXlineQty();
		if (iXlineIndex < 0 || iXlineIndex >= nJ)
			return false;

		if (!pBuffer)
			return false;

		if (!_GetTraceReader())
			return false;

		return m_pTraceReader->ReadVSection(iXlineIndex, pBuffer);
	}
}

bool CXSeismicDataVolume::ReadSlice(double dZValue, float* pBuffer)
{
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	this->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	int iSliceIndex = static_cast<int>((dZValue - dSamplingStart) / dSamplingRate + 0.01);

	int nK = GetSamplingQty();
	if (iSliceIndex < 0 || iSliceIndex >= nK)
		return false;

	if (!pBuffer)
		return false;

	if (!_GetSliceReader())
		return false;

	return m_pSliceReader->ReadUSection(iSliceIndex, pBuffer);
}

bool CXSeismicDataVolume::ReadRandomSection(CXSeismicRandomSection* pRandomSec, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	if (!pRandomSec)
		return false;

	if (!pBuffer)
		return false;

	if (IsIrregular())
	{
		if (!pTraceInfo)
			return false;

		std::vector<int> vecInline, vecXline;
		pRandomSec->GetLineNumbers(vecInline, vecXline);
		return GetIrregularReader()->ReadRandomSection(this, vecInline, vecXline, pBuffer, pTraceInfo);
	}
	else
	{
		if (!_GetTraceReader())
			return false;

		std::vector<int> vecInline, vecXline;
		pRandomSec->GetLineNumbers(vecInline, vecXline);
		if (vecInline.empty() || vecXline.empty())
			return false;

		int nK = GetSamplingQty();
		//int nTraceNum = (int) vecInline.size();
		int iI, iJ;
		for (int i = 0; i < vecInline.size(); ++i)
		{
			float* pTraceData = pBuffer + i * nK * m_iMaxFold;
			if (!m_utm.LineToIJ(vecInline[i], vecXline[i], iI, iJ))
			{
				std::fill(pTraceData, pTraceData + nK * m_iMaxFold, 0.f);
			}
			else
			{
				if (!m_pTraceReader->ReadUVTrace(iI, iJ, pTraceData))
					return false;
			}
		}
	}

	return true;
}

QStringList CXSeismicDataVolume::GetDescription()
{
	QStringList strList;

	int iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc;
	m_utm.GetLineNumRange(iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc);

	//if(::UsingChinese())
	//{
	//	strList<<GetTr("主测线范围")<<QString::number(iFirstInline) + " ~ " + QString::number(iLastInline);
	//	strList<<GetTr("主测线步长")<<QString::number(iInlineInc);
	//	strList<<GetTr("主测线数")<<QString::number(m_utm.GetNI());
	//	strList<<GetTr("联络测线范围")<<QString::number(iFirstCrossline) + " ~ " + QString::number(iLastCrossline);
	//	strList<<GetTr("联络测线步长")<<QString::number(iCrosslineInc);
	//	strList<<GetTr("联络测线数")<<QString::number(m_utm.GetNJ());

	//	strList<<GetTr("起始深度")<<QString::number(m_dSamplingStart);
	//	strList<<GetTr("终止深度")<<QString::number(m_dSamplingEnd);
	//	strList<<GetTr("采样间隔")<<QString::number(m_dSamplingRate);
	//	strList<<GetTr("样点数")<<QString::number(GetSamplingQty());
	//}
	//else
	//{
	strList<<"Inline range:"<<QString::number(iFirstInline) + " ~ " + QString::number(iLastInline);
	strList<<"Inline step:"<<QString::number(iInlineInc);
	strList<<"Inline number:"<<QString::number(m_utm.GetNI());
	strList<<"Crossline range:"<<QString::number(iFirstCrossline) + " ~ " + QString::number(iLastCrossline);
	strList<<"Crossline step:"<<QString::number(iCrosslineInc);
	strList<<"Crossline number:"<<QString::number(m_utm.GetNJ());

	if (m_iMaxFold > 1)
	{
		if (m_fOffsetStep > 0.)
		{
			strList << "Number of offsets of each CDP:" << QString::number(m_iMaxFold);
			strList << "Nearest offset:" << QString::number(m_fStartOffset);
			strList << "Farest offset:" << QString::number(m_fStartOffset + (m_iMaxFold - 1) * m_fOffsetStep);
			strList << "Offset step:" << QString::number(m_fOffsetStep);

		}
		else 
		{
			CXSeismicIrregularReader* pReader = GetIrregularReader();
			strList << "Whether contains irregular offsets:" << "Irregular";
			strList << "Maximum fold:" << QString::number(m_iMaxFold);
			strList << "Nearest offset:" << QString::number(pReader->GetMinOffset());
			strList << "Farest offset:" << QString::number(pReader->GetMaxOffset());

			if (IsAzimuth())
			{
				strList << "Minimum azimuth:" << QString::number(pReader->GetMinAzimuth());
				strList << "Maximum azimuth:" << QString::number(pReader->GetMaxAzimuth());
			}
		}
	}

	strList<<"Start Z:"<<QString::number(m_dSamplingStart);
	strList<<"End Z:"<<QString::number(m_dSamplingEnd);
	strList<<"Sample interval:"<<QString::number(m_dSamplingRate);
	strList<<"Sample number:"<<QString::number(GetSamplingQty());
	//}

	return strList;
}

void CXSeismicDataVolume::_SetSelfDimension()
{
	double x[4], y[4];

	m_utm.IJToXY (0, 0, x[0], y[0]);
	m_utm.IJToXY (0, m_utm.GetNJ()-1, x[1], y[1]);
	m_utm.IJToXY (m_utm.GetNI()-1, m_utm.GetNJ()-1, x[2], y[2]);
	m_utm.IJToXY (m_utm.GetNI()-1, 0, x[3], y[3]);

	double dXMin = qMin (qMin (x[0], x[1]), qMin(x[2], x[3]));
	double dXMax = qMax (qMax (x[0], x[1]), qMax(x[2], x[3]));
	double dYMin = qMin (qMin (y[0], y[1]), qMin(y[2], y[3]));
	double dYMax = qMax (qMax (y[0], y[1]), qMax(y[2], y[3]));

	_SetDimension(dXMin, dXMax, dYMin, dYMax, m_dSamplingStart, m_dSamplingEnd);
}

QUuid CXSeismicDataVolume::GetSurveyID()
{
	CXObject* pParentObj = this->GetParent();

	QUuid surveyID;

	while (pParentObj)
	{
		if (pParentObj->GetObjectType() == EX3DSurvey)
		{
			surveyID =  pParentObj->GetObjectID();
			break;
		}

		pParentObj = pParentObj->GetParent();
	}

	return surveyID;	
}

float CXSeismicDataVolume::GetMaxValue()
{
	double dMin, dMax;
	GetDataRange(dMin, dMax);
	return qMax(qAbs(dMin), qAbs(dMax));
}

void CXSeismicDataVolume::_ConvertNumToIndex(int iInlineNum, int iXlineNum, double dSampling, int& iInline, int& iXline, int& iSamling)
{
	m_utm.LineToIJ(iInlineNum, iXlineNum, iInline, iXline);

	iSamling = static_cast<int>((qAbs(dSampling - m_dSamplingStart) + 0.01*m_dSamplingRate)/m_dSamplingRate);
}

bool CXSeismicDataVolume::ReadSection(CXSeismicSection *pSection, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	double dSZ, dEZ, dZStep;
	this->GetSamplingRange(dSZ, dEZ, dZStep);
	int iSTrace, iETrace;
	pSection->GetSectionRange(iSTrace, iETrace);

	if (iSTrace == -1 || iETrace == -1)
	{
		if (pSection->GetSectionType() == eInlineSection)
		{
			return ReadInline(pSection->GetSectionNumber(), pBuffer, pTraceInfo);
		}
		else if (pSection->GetSectionType() == eCrosslineSection)
		{
			return ReadXline(pSection->GetSectionNumber(), pBuffer, pTraceInfo);
		}
	}
	else
	{
		if (pSection->GetSectionType() == eInlineSection)
		{
			return ReadInline(pSection->GetSectionNumber(), iSTrace, iETrace, dSZ, dEZ, pBuffer, pTraceInfo);
		}
		else if (pSection->GetSectionType() == eCrosslineSection)
		{
			return ReadXline(pSection->GetSectionNumber(), iSTrace, iETrace, dSZ, dEZ, pBuffer, pTraceInfo);
		}
	}

	return false;
}

bool CXSeismicDataVolume::ReadInline(int iInlineNum, int iXlineMinNum, int iXlineMaxNum, double dStart, double dEnd, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	if (!pBuffer)
		return false;

	if (IsIrregular())
	{
		if (!pTraceInfo)
			return false;

		return GetIrregularReader()->ReadInline(this, iInlineNum, iXlineMinNum, iXlineMaxNum, dStart, dEnd, pBuffer, pTraceInfo);
	}
	else
	{
		if (!_GetTraceReader())
			return false;

		int iInlineMin, iInlineMax, iXlineMin, iXlineMax, iSamplingMin, iSamplingMax;
		_ConvertNumToIndex(iInlineNum, iXlineMinNum, dStart, iInlineMin, iXlineMin, iSamplingMin);
		_ConvertNumToIndex(iInlineNum, iXlineMaxNum, dEnd, iInlineMax, iXlineMax, iSamplingMax);

		if (iXlineMin > iXlineMax)
			qSwap(iXlineMin, iXlineMax);
		if (iSamplingMin > iSamplingMax)
			qSwap(iSamplingMin, iSamplingMax);

		return m_pTraceReader->ReadPartialUSection(iInlineMin, iXlineMin, iXlineMax, iSamplingMin, iSamplingMax, pBuffer);
	}
}

bool CXSeismicDataVolume::ReadXline(int iXlineNum, int iInlineMinNum, int iInlineMaxNum, double dStart, double dEnd, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	if (!pBuffer)
		return false;

	if (IsIrregular())
	{
		if (!pTraceInfo)
			return false;

		return GetIrregularReader()->ReadXline(this, iXlineNum, iInlineMinNum, iInlineMaxNum, dStart, dEnd, pBuffer, pTraceInfo);
	}
	else
	{
		if (!_GetTraceReader())
			return false;

		int iInlineMin, iInlineMax, iXlineMin, iXlineMax, iSamplingMin, iSamplingMax;
		_ConvertNumToIndex(iInlineMinNum, iXlineNum, dStart, iInlineMin, iXlineMin, iSamplingMin);
		_ConvertNumToIndex(iInlineMaxNum, iXlineNum, dEnd, iInlineMax, iXlineMax, iSamplingMax);

		if (iInlineMin > iInlineMax)
			qSwap(iInlineMin, iInlineMax);
		if (iSamplingMin > iSamplingMax)
			qSwap(iSamplingMin, iSamplingMax);

		return m_pTraceReader->ReadPartialVSection(iXlineMin, iInlineMin, iInlineMax, iSamplingMin, iSamplingMax, pBuffer);
	}
}
bool CXSeismicDataVolume::ReadSlice(double dSampling, int iInlineMinNum, int iInlineMaxNum, int iXlineMinNum, int iXlineMaxNum, float* pBuffer)
{
	if (!pBuffer)
		return false;

	if (!_GetSliceReader())
		return false;

	int iInlineMin, iInlineMax, iXlineMin, iXlineMax, iSamplingMin, iSamplingMax;
	_ConvertNumToIndex(iInlineMinNum, iXlineMinNum, dSampling, iInlineMin, iXlineMin, iSamplingMin);
	_ConvertNumToIndex(iInlineMaxNum, iXlineMaxNum, dSampling, iInlineMax, iXlineMax, iSamplingMax);

	if (iInlineMin > iInlineMax)
		qSwap(iInlineMin, iInlineMax);
	if (iXlineMin > iXlineMax)
		qSwap(iXlineMin, iXlineMax);

	return m_pSliceReader->ReadPartialUSection(iSamplingMin, iInlineMin, iInlineMax, iXlineMin, iXlineMax, pBuffer);
}

bool CXSeismicDataVolume::IsSameSizeWith(CXSeismicDataVolume* pOther)
{
	if (!m_utm.Equals(&pOther->GetUTM()))
		return false;

	double dSamplingStart, dSamplingEnd, dSamplingRate, dSamplingStart2, dSamplingEnd2, dSamplingRate2;
	GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	pOther->GetSamplingRange(dSamplingStart2, dSamplingEnd2, dSamplingRate2);

	if (!qFuzzyCompare(dSamplingStart, dSamplingStart2) ||
		!qFuzzyCompare(dSamplingEnd, dSamplingEnd2) ||
		!qFuzzyCompare(dSamplingRate, dSamplingRate2))
		return false;

	if (m_iMaxFold != pOther->m_iMaxFold)
		return false;

	return true;
}

void CXSeismicDataVolume::GetAllDVWithSameSize(QList<CXObject *>& listDV)
{
	CXObject *pSurvey = ::GetObjectByID(GetSurveyID());
	Q_ASSERT(pSurvey);

	QList<CXObject *> listChildren = pSurvey->GetChildren(EXSeismicDataVolume, true);
	foreach(CXObject *pObj, listChildren)
	{
		CXSeismicDataVolume *pDV = (CXSeismicDataVolume *)pObj;
		if (IsSameSizeWith(pDV))
		{
			listDV << (CXObject *)pDV;
		}
	}
}

CXSeismicIrregularReader* CXSeismicDataVolume::GetIrregularReader()
{
	if (!IsIrregular())
		return NULL;

	if (!m_pIrregularReader)
	{
		m_pIrregularReader = new CXSeismicIrregularReader(m_iMaxFold, &m_utm, GetTraceInfoFileName());
	}

	return m_pIrregularReader;
}

void CXSeismicDataVolume::GetFoldMap(unsigned short *pFoldMap)
{
	if (!pFoldMap)
		return;

	if (IsIrregular())
	{
		//	Irregular volume, use trace info to get the fold map.
		CXSeismicIrregularReader *pIReader = GetIrregularReader();
		if (pIReader)
			pIReader->GetFoldMap(pFoldMap);
	}
	else
	{
		int iMapSize = m_utm.GetNI() * m_utm.GetNJ();
		for (int i = 0; i < iMapSize; i++)
		{
			pFoldMap[i] = m_iMaxFold;
		}
	}
}

///@brief	Get the trace number of the specified CDP.
int CXSeismicDataVolume::GetTraceNumberAt(int iInline, int iXline)
{
	if (!IsIrregular())
		return m_iMaxFold;

	CXSeismicIrregularReader *pIReader = GetIrregularReader();
	return pIReader->GetTraceNumberAt(iInline, iXline);
}

///@brief	Get the trace data and offset/azimuth info of the specified CDP.
///			The space of pData should be pre-allocated and mananged by the caller.
bool CXSeismicDataVolume::GetTraceDataAt(int iInline, int iXline, float *pData, QVector<float>& vecOffsetAziPair)
{
	if (IsIrregular())
	{
		CXSeismicIrregularReader *pIReader = GetIrregularReader();
		return pIReader->GetTraceDataAt(this, iInline, iXline, pData, vecOffsetAziPair);
	}
	else
	{
		if (!_GetTraceReader())
			return false;

		int i, j;
		m_utm.LineToIJ(iInline, iXline, i, j);
		if (!m_pTraceReader->ReadPartialUSection(i, j, j, 0, GetSamplingQty() - 1, pData))
			return false;

		if (!IsPrestack())
		{
			vecOffsetAziPair << 0. << 0.;
		}
		else
		{
			for (i = 0; i < m_iMaxFold; i++)
				vecOffsetAziPair << m_fStartOffset + i * m_fOffsetStep << 0.;
		}
	}

	return true;
}

void CXSeismicDataVolume::GetOffset(int iInline, int iXline, vector<int>& vecOffset)
{
	if (IsIrregular())
	{
		CXSeismicIrregularReader *pIReader = GetIrregularReader();
		return pIReader->GetOffset(iInline, iXline, vecOffset);
	}
	else
	{
		int i, j;
		if (!m_utm.LineToIJ(iInline, iXline, i, j))
			return;

		if (!IsPrestack())
		{
			vecOffset.push_back(0);
		}
		else
		{
			for (i = 0; i < m_iMaxFold; i++)
				vecOffset.push_back(m_fStartOffset + i * m_fOffsetStep);
		}
	}
}

void CXSeismicDataVolume::GetFractureInfo(const QUuid & uuidDensity, const QUuid & uuidAzimuth, double dSliceNum, int ndX, int ndY, float fMinThreshold, float fMaxThreshold, vector<float>& vecDensity, vector<float>& vecAzimth, vector<float>& vecColor)
{
	CXSeismicDataVolume* pDenDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(uuidDensity));
	CXSeismicDataVolume* pAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(uuidAzimuth));

	if (!pDenDV || !pAziDV)
		return;

	CXSeismicUTMTool utm = pDenDV->GetUTM();
	if (!pAziDV->GetUTM().Equals(&utm))
		return;

	int nI = utm.GetNI();
	int nJ = utm.GetNJ();

	float fInvalid = ::g_dInvalidData;
	float fInvEPS = ::GetEPSofInvalidData(fInvalid);

	vector<float> vecDen(nI*nJ), vecAzi(nI*nJ);
	if (!pDenDV->ReadSlice(dSliceNum, &vecDen[0]) ||
		!pAziDV->ReadSlice(dSliceNum, &vecAzi[0]))
		return;

	// filtering
	NXUtility::FilterTwoData(nI, nJ, &vecDen[0], &vecAzi[0], 3, 3, ::g_dInvalidData);

	int iDI = qMax(1, ndY);
	int iDJ = qMax(1, ndX);

	int nFraNI = nI / iDI;
	int nFraNJ = nJ / iDJ;

	if (nFraNI < 1 || nFraNJ < 1)
		return;

	vecDensity.resize(nFraNI*nFraNJ, fInvalid);
	vecAzimth.resize(nFraNI*nFraNJ, fInvalid);
	vecColor.resize(nFraNI*nFraNJ, fInvalid);

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
			for (int i = iMin; i <= iMax; ++i)
			{
				for (int j = jMin; j <= jMax; ++j)
				{
					if (qAbs(vecDen[i*nJ + j] - fInvalid) < fInvEPS ||
						qAbs(vecAzi[i*nJ + j] - fInvalid) < fInvEPS)
						continue;

					if (vecDen[i*nJ + j] > fMaxValue)
					{
						fMaxValue = vecDen[i*nJ + j];
						iPos = i;
						jPos = j;
					}

				}
			}

			if (iPos != -1)
			{
				vecDensity[iI*nFraNJ + iJ] = qAbs(vecDen[iPos*nJ + jPos]);
				vecAzimth[iI*nFraNJ + iJ] = vecAzi[iPos*nJ + jPos];
				vecColor[iI*nFraNJ + iJ] = vecDen[iPos*nJ + jPos];
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
	int kmax = qMin((int)vecTmp.size()-1, static_cast<int>(iCount*fMaxThreshold));

	float fminValue = NXUtility::Select(&vecTmp[0], iCount, kmin);
	float fmaxValue = NXUtility::Select(&vecTmp[0], iCount, kmax);

	float fHalfLength = sqrt(SQR(qMax(1, iDI - 1)*utm.GetIInterval()) + SQR(qMax(1, iDJ - 1)*utm.GetJInterval())) / 2.f;

	for (int i = 0; i < nSize; ++i)
	{
		if (qAbs(vecDensity[i] - fInvalid) < fInvEPS)
			continue;

		if (vecDensity[i] < fminValue )
			vecDensity[i] = 0.f;
		else if (vecDensity[i] > fmaxValue)
			vecDensity[i] = fHalfLength;
		else
		{
			vecDensity[i] = fHalfLength / (fmaxValue - fminValue)*(vecDensity[i] - fminValue);
		}
	}
}

bool CXSeismicDataVolume::ContainsAzimuthOnly()
{
	if (!GetIrregularReader())
		return false;
	else
		return GetIrregularReader()->ContainsAzimuthOnly();
}