#include "xseismicobject.h"
#include "xproject.h"
#include "xglobal.h"
#include "xseismicirregularreader.h"

CXSeismicObject::CXSeismicObject()
{
	m_iMaxFold = 1;
	m_fStartOffset = 0.;
	m_fOffsetStep = 0.;

	m_pIrregularReader = NULL;
}

CXSeismicObject::CXSeismicObject(double dSamplingStart, double dSamplingEnd, double dSamplingRate, const QString& strName)
	:CXObject(strName)
{
	m_dSamplingStart	= dSamplingStart;
	m_dSamplingEnd		= dSamplingEnd;
	m_dSamplingRate		= dSamplingRate;

	m_iMaxFold = 1;
	m_fStartOffset = 0.;
	m_fOffsetStep = 0.;

	m_pIrregularReader = NULL;
}

CXSeismicObject::CXSeismicObject(const CXSeismicObject& other)
	:CXObject(other)
{
	m_dSamplingStart = other.m_dSamplingStart;
	m_dSamplingEnd = other.m_dSamplingEnd;
	m_dSamplingRate = other.m_dSamplingRate;

	m_iMaxFold = other.m_iMaxFold;;
	m_fStartOffset = other.m_fStartOffset;
	m_fOffsetStep = other.m_fOffsetStep;

	m_utm = other.m_utm;

	m_pIrregularReader = NULL;
}

CXSeismicObject::~CXSeismicObject()
{
}

int CXSeismicObject::GetSamplingQty()
{
	int nK = static_cast<int>((qAbs(m_dSamplingEnd - m_dSamplingStart) + 0.01*m_dSamplingRate) / m_dSamplingRate + 1);
	return nK;
}

void CXSeismicObject::ShiftStartSamplingTo(double dStartZ)
{
	if (qAbs(dStartZ - m_dSamplingStart) < M_DEPS)
		return;

	m_dSamplingEnd += (dStartZ - m_dSamplingStart);
	m_dSamplingStart = dStartZ;

	SetNeedCalcDimension();
}

void CXSeismicObject::GetSamplingRange(double& dStartZ, double& dStopZ, double& dStep)
{
	dStartZ		= m_dSamplingStart;
	dStopZ		= m_dSamplingEnd;
	dStep		= m_dSamplingRate;
}

bool CXSeismicObject::SerializeData(CXArchive &ar)
{
	if (ar.IsSaving())
	{
		ar << m_dSamplingStart;
		ar << m_dSamplingEnd;
		ar << m_dSamplingRate;

		m_utm.SerializeData(ar);

		ar << m_iMaxFold;
		ar << m_fStartOffset;
		ar << m_fOffsetStep;
	}
	else
	{
		ar >> m_dSamplingStart;
		ar >> m_dSamplingEnd;
		ar >> m_dSamplingRate;

		m_utm.SerializeData(ar);

		ar >> m_iMaxFold;
		ar >> m_fStartOffset;
		ar >> m_fOffsetStep;
	}

	return true;
}

QString CXSeismicObject::GetTraceFileName()
{
	QString strFileName = ::GetProject()->GetProjectDataPath() + this->GetObjectID().toString() + ".tra";
	return strFileName;
}

QString CXSeismicObject::GetTraceInfoFileName()
{
	QString strFileName = "";
	if (m_iMaxFold > 1 && m_fOffsetStep == 0.)
		strFileName = ::GetProject()->GetProjectDataPath() + this->GetObjectID().toString() + ".inf";
	return strFileName;
}


bool CXSeismicObject::IsAzimuth()
{
	if (!IsIrregular())
		return false;

	CXSeismicIrregularReader* pIReader = GetIrregularReader();
	return pIReader->IsAzimuthVolume();
}