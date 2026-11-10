#include "xlfmgeometry.h"
#include <cassert>
#include <QtCore/QFile>

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xregulardatareader.h"
#include "xfunctiontemplate.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXLFMGeometry)
EXLowFrequencyModel
END_REGISTER_OBJECT_TO_FACTORY(CXLFMGeometry)

CXLFMGeometry::CXLFMGeometry()
{
	_Init();
	m_nK = 0;
}

CXLFMGeometry::CXLFMGeometry(const QUuid& uuidSurveyID, const CXSeismicUTMTool& utm, int nK, const QString& strName)
	:m_utm(utm), m_uuidSurveyID(uuidSurveyID), m_nK(nK), CXObject(strName)
{
	_Init();

}

CXLFMGeometry::~CXLFMGeometry()
{
	if (m_pReader)
	{
		delete m_pReader;
		m_pReader = NULL;
	}
}

void CXLFMGeometry::_Init()
{
	SetObjectType(EXLowFrequencyModel);
	SetIconName("ResGeometryModel.png");
	m_pReader = NULL;
}

CXSeismicUTMTool& CXLFMGeometry::GetUTM()
{
	return m_utm;
}

CXRegularDataReader<float>* CXLFMGeometry::_GetReader()
{
	if (m_pReader)
		return m_pReader;

	m_pReader = new CXRegularDataReader<float>(this->GetDataFileName(), m_nK, m_utm.GetNI(), m_utm.GetNJ());
	if (!m_pReader->Open())
	{
		delete m_pReader;
		m_pReader = NULL;
	}

	return m_pReader;
}

bool CXLFMGeometry::ReadOneSlice(int iIndex, float* pBuffer)
{
	if (!pBuffer)
		return false;

	if (!IsBound(iIndex, 0, m_nK - 1))
		return false;

	if (!_GetReader())
		return false;

	return m_pReader->ReadUSection(iIndex, pBuffer);
}

bool CXLFMGeometry::ReadOneSection(int iIndex, float* pBuffer)
{
	if (!pBuffer)
		return false;

	int nI = m_utm.GetNI();
	if (!IsBound(iIndex, 0, nI - 1))
		return false;

	if (!_GetReader())
		return false;

	return m_pReader->ReadVSection(iIndex, pBuffer);
}

bool CXLFMGeometry::SerializeData(CXArchive& ar)
{
	m_utm.SerializeData(ar);

	if (ar.IsSaving())
	{
		ar << m_uuidSurveyID;
		ar << m_nK;

		int nIndexNum = (int)m_vecHorizonIndex.size();
		ar << nIndexNum;
		for (int i = 0; i < nIndexNum; ++i)
		{
			ar << m_vecHorizonIndex[i];
		}

		ar << m_strListZoneName;
	}
	else
	{
		ar >> m_uuidSurveyID;
		ar >> m_nK;

		int nIndexNum;
		ar >> nIndexNum;
		m_vecHorizonIndex.resize(nIndexNum);
		for (int i = 0; i < nIndexNum; ++i)
		{
			ar >> m_vecHorizonIndex[i];
		}

		ar >> m_strListZoneName;
	}

	return true;
}

void CXLFMGeometry::_SetSelfDimension()
{
	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	m_utm.GetDimensionRange(dXMin, dXMax, dYMin, dYMax);

	GetDataRange(dZMin, dZMax);

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

QStringList CXLFMGeometry::GetDescription()
{
	QStringList list;
	QString sZones = m_strListZoneName[0] + "(" + QString::number(m_vecHorizonIndex[0] + 1) + "~" + QString::number(m_vecHorizonIndex[1] + 1) + ")";
	for(int i = 1; i < m_strListZoneName.size(); i++)
	{
		sZones = sZones + "， " + m_strListZoneName[i] + "(" + QString::number(m_vecHorizonIndex[i] + 1) + "~" + QString::number(m_vecHorizonIndex[i + 1] + 1) + ")";
	}

	list << "Number of Inlines: " << QString::number(m_utm.GetNI())
		<< "Number of Crosslines: " << QString::number(m_utm.GetNJ())
		<< "Number of Total Slices: " << QString::number(m_nK)
		<< "Number of Zones: " << QString::number(m_strListZoneName.size())
		<< "Zones are: " << sZones;

	return list;
}

