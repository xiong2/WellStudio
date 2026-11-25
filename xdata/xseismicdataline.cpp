#include <QFile>
#include "xseismicdataline.h"
#include "x2dseismicline.h"
#include "xseismicrandomsection.h"
#include "xseismicsection.h"
#include "xseismicirregularreader.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xeventconsole.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXSeismicDataLine)
EXSeismicDataLine
END_REGISTER_OBJECT_TO_FACTORY(CXSeismicDataLine)

CXSeismicDataLine::CXSeismicDataLine()
{
	SetIconName("SeismicLine.png");
	SetObjectType(EXSeismicDataLine);

	m_pDataInMem		= NULL;
	m_refID				= QUuid();
}

CXSeismicDataLine::CXSeismicDataLine(CXObject *pRefObj, double dSamplingStart, double dSamplingEnd, double dSamplingRate, const QString& strName)
: CXSeismicObject(dSamplingStart, dSamplingEnd, dSamplingRate, strName)
{
	SetIconName("SeismicLine.png");
	SetObjectType(EXSeismicDataLine);

	m_pDataInMem = NULL;
	m_refID = pRefObj->GetObjectID();
	CXSeismicRandomSection *pRSection = dynamic_cast<CXSeismicRandomSection *>(pRefObj);
	if (pRSection)
	{
		m_utm.Copy(&(pRSection->GetUTM()));
	}
}

CXSeismicDataLine::CXSeismicDataLine(CXSeismicUTMTool utm, double dSamplingStart, double dSamplingEnd, double dSamplingRate, const QString& strName)
	: CXSeismicObject(dSamplingStart, dSamplingEnd, dSamplingRate, strName)
{
	SetIconName("SeismicLine.png");
	SetObjectType(EXSeismicDataLine);

	m_pDataInMem = NULL;
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&utm));
	m_refID = QUuid();
}

CXSeismicDataLine::~CXSeismicDataLine()
{
	_freeMemory();
}

QString CXSeismicDataLine::GetTypeString()
{
	EXSectionType eType = GetDataLineType();
	if (eType == eInlineSection)
		return u8"三维主测线地震数据";
	else if (eType == eCrosslineSection)
		return u8"三维联络测线地震数据";
	else if (eType == eRandomSection)
		return u8"三维任意线地震数据";
	else if (eType == e2DSection)
		return u8"二维地震数据";
	else
		return "";
}

unsigned int CXSeismicDataLine::GetTraceNumber()
{
	if (m_refID.isNull())
	{
		if (m_utm.GetNI() > 1)
			return m_utm.GetNI() * GetMaxFold();
		else
			return m_utm.GetNJ() * GetMaxFold();
	}
	else
	{
		CXObject *pRefObj = ::GetObjectByID(m_refID);
		CX2DSeismicLine *pLine = dynamic_cast<CX2DSeismicLine *>(pRefObj);
		if (pLine)
		{
			return pLine->GetTraceNumber();
		}
		CXSeismicRandomSection *pRSection = dynamic_cast<CXSeismicRandomSection *>(pRefObj);
		if (pRSection)
		{
			return pRSection->GetTraceNum();
		}
	}

	return 0;
}

EXSectionType CXSeismicDataLine::GetDataLineType()
{
	if (m_refID.isNull())
	{
		if (m_utm.GetNI() > 1)
			return eCrosslineSection;
		else
			return eInlineSection;
	}
	else
	{
		CXObject *pRefObj = ::GetObjectByID(m_refID);
		CX2DSeismicLine *pLine = dynamic_cast<CX2DSeismicLine *>(pRefObj);
		if (pLine)
		{
			return e2DSection;
		}
		CXSeismicRandomSection *pRSection = dynamic_cast<CXSeismicRandomSection *>(pRefObj);
		if (pRSection)
		{
			return eRandomSection;
		}
	}
	return eRandomSection;
}

int CXSeismicDataLine::GetLineNumber()
{
	if (m_refID.isNull())
	{
		if (m_utm.GetNI() > 1)
			return m_utm.GetFirstCrossline();
		else
			return m_utm.GetFirstInline();
	}
	else
	{
		return 0;
	}
}

int CXSeismicDataLine::GetSectionTraceQty(CXSeismicSection *pSection)
{
	//	2D line or random section do not support this feature.
	if (!m_refID.isNull())
		return 0;

	if (pSection->GetSectionType() != GetDataLineType())
		return 0;

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

CXObject* CXSeismicDataLine::GetGeometryObject()
{
	if (!m_refID.isNull())
		return ::GetObjectByID(m_refID);
	else
	//	It's really a stupid design that if no attached geometry, return itself, though itself is not a geometry!
		return this;
}

QStringList CXSeismicDataLine::GetDescription()
{
	QStringList sListDes;

	sListDes << u8"地震道数目" << QString::number(GetTraceNumber());
	sListDes << u8"起始时间" << QString::number(m_dSamplingStart);
	sListDes << u8"终止时间" << QString::number(m_dSamplingEnd);
	sListDes << u8"样点数目" << QString::number(GetSamplingQty());
	sListDes << u8"采样间隔" << QString::number(m_dSamplingRate);

	return sListDes;
}

float* CXSeismicDataLine::GetData()
{
	if (!m_pDataInMem)
		LoadData();

	return m_pDataInMem;
}

bool CXSeismicDataLine::SerializeData(CXArchive &ar)
{
	CXSeismicObject::SerializeData(ar);

	if (ar.IsSaving())
	{
		ar << m_refID;
	}
	else
	{
		ar >> m_refID;
	}

	return true;
}

void CXSeismicDataLine::_SetSelfDimension()
{
	//double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	//CXObject *pLine = GetGeometryObject();
	//
	//if (!pLine)
	//	return;

	//pLine->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

	//_SetDimension(dXMin, dXMax, dYMin, dYMax, m_dSamplingStart, m_dSamplingEnd);
}

void CXSeismicDataLine::_WriteData()
{
	if (!m_pDataInMem)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	qFile.write((char*)m_pDataInMem, sizeof(float) * GetSamplingQty() * GetTraceNumber());
}

void CXSeismicDataLine::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	_freeMemory();

	unsigned int nSize = GetSamplingQty() * GetTraceNumber();
	m_pDataInMem = new float[nSize];

	qFile.read((char*)m_pDataInMem, sizeof(float) * nSize);
}

void CXSeismicDataLine::_freeMemory()
{
	if (m_pDataInMem)
		delete[]m_pDataInMem;

	m_pDataInMem = NULL;
}

QUuid CXSeismicDataLine::GetSurveyID()
{
	CXObject* pParentObj = this->GetParent();

	QUuid surveyID;

	while (pParentObj)
	{
		if (pParentObj->GetObjectType() == EX2DSurvey || pParentObj->GetObjectType() == EX3DSurvey)
		{
			surveyID = pParentObj->GetObjectID();
			break;
		}

		pParentObj = pParentObj->GetParent();
	}

	return surveyID;
}


CXSeismicIrregularReader* CXSeismicDataLine::GetIrregularReader()
{
	if (!IsIrregular())
		return NULL;

	if (!m_pIrregularReader)
	{
		m_pIrregularReader = new CXSeismicIrregularReader(m_iMaxFold, &m_utm, GetTraceInfoFileName(), GetTraceNumber());
	}

	return m_pIrregularReader;
}

bool CXSeismicDataLine::ReadSection(CXSeismicSection *pSection, float* pBuffer, SKETraceInfo* pTraceInfo)
{
	if (pSection->GetSectionType() != GetDataLineType()
		|| pSection->GetSectionNumber() != GetLineNumber())
		return false;

	if (IsIrregular())
	{
		if (!pTraceInfo)
			return false;

		int iSTrace, iETrace;
		pSection->GetSectionRange(iSTrace, iETrace);
		if (pSection->GetSectionType() == eInlineSection)
			return GetIrregularReader()->ReadInline(this, GetLineNumber(), iSTrace, iETrace,
				m_dSamplingStart, m_dSamplingEnd, pBuffer, pTraceInfo);
		else if (pSection->GetSectionType() == eCrosslineSection)
			return GetIrregularReader()->ReadXline(this, GetLineNumber(), iSTrace, iETrace,
				m_dSamplingStart, m_dSamplingEnd, pBuffer, pTraceInfo);
	}

	int iSTrace, iETrace;
	pSection->GetSectionRange(iSTrace, iETrace);

	QFile qFile(GetTraceFileName());
	if (!qFile.open(QIODevice::ReadOnly))
		return false;

	if (iSTrace == -1 || iETrace == -1)
	{
		//	Whole line.
		qFile.read((char *)pBuffer, sizeof(float) * GetTraceNumber() * GetSamplingQty());
	}
	else
	{
		//	Part line.
		int ij, iSIDX, iEIDX;
		if (m_utm.GetNI() > 1)
		{
			m_utm.LineToIJ(iSTrace, m_utm.GetFirstCrossline(), iSIDX, ij);
			m_utm.LineToIJ(iETrace, m_utm.GetFirstCrossline(), iEIDX, ij);
		}
		else
		{
			m_utm.LineToIJ(m_utm.GetFirstInline(), iSTrace, ij, iSIDX);
			m_utm.LineToIJ(m_utm.GetFirstInline(), iETrace, ij, iEIDX);
		}

		qFile.seek(sizeof(float) * iSIDX * GetMaxFold() * GetSamplingQty());
		qFile.read((char *)pBuffer, sizeof(float) * (iEIDX - iSIDX + 1) * GetMaxFold() * GetSamplingQty());
	}

	qFile.close();
	return true;
}

bool CXSeismicDataLine::ResetLine(double dSZ, double dEZ, double dZStep, float fRatio)
{
	if (dSZ < m_dSamplingStart || dEZ > m_dSamplingEnd || dZStep < m_dSamplingRate)
		return false;

	if (!m_pDataInMem)
		LoadData();

	int i, j, nTrace = GetTraceNumber();
	int nSample = GetSamplingQty();
	int nNSample = (dEZ - dSZ) / dZStep + 1;
	int iTOffset = (dSZ - m_dSamplingStart) / m_dSamplingRate;
	float *pBuff = new float[nTrace * nSample];

	if (dZStep == m_dSamplingRate)
	{
		for (i = 0; i < nTrace; i++)
			memcpy(pBuff + i * nNSample, m_pDataInMem + i * nSample + iTOffset, 4 * nNSample);
	}
	else
	{
		int n = dZStep / m_dSamplingRate;
		for (i = 0; i < nTrace; i++)
			for (j = 0; j < nNSample; j++)
				pBuff[i * nNSample + j] = m_pDataInMem[i * nSample + iTOffset + j * n];
	}

	if (fRatio != 1.)
	{
		int nSize = nTrace * nSample;
		for (i = 0; i < nSize; i++)
			pBuff[i] *= fRatio;
	}

	delete[]m_pDataInMem;
	m_dSamplingStart = dSZ;
	m_dSamplingEnd = dEZ;
	m_dSamplingRate = dZStep;
	m_pDataInMem = pBuff;

	_WriteData();

	SetNeedCalcDimension();

	return true;
}