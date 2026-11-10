#include "xlfmattribute.h"
#include "xlfmgeometry.h"
#include <cassert>
#include <QtCore/QFile>

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xregulardatareader.h"
#include "xfunctiontemplate.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXLFMAttribute)
EXLFMAttribute
END_REGISTER_OBJECT_TO_FACTORY(CXLFMAttribute)

CXLFMAttribute::CXLFMAttribute()
{
	_Init();
	m_nI = 0;
	m_nJ = 0;
	m_nK = 0;
}

CXLFMAttribute::CXLFMAttribute(CXLFMGeometry* pLFMGeo, const QString& strName)
	: CXObject(strName)
{
	_Init();

	m_uuidLFM = pLFMGeo->GetObjectID();
	m_nI = pLFMGeo->GetUTM().GetNI();
	m_nJ = pLFMGeo->GetUTM().GetNJ();
	m_nK = pLFMGeo->GetNK();

}

CXLFMAttribute::~CXLFMAttribute()
{
	if (m_pReader)
	{
		delete m_pReader;
		m_pReader = NULL;
	}
}

void CXLFMAttribute::_Init()
{
	SetObjectType(EXLFMAttribute);
	SetIconName("ResPropertyModel.png");
	m_pReader = NULL;
}


CXRegularDataReader<float>* CXLFMAttribute::_GetReader()
{
	if (m_pReader)
		return m_pReader;

	m_pReader = new CXRegularDataReader<float>(this->GetDataFileName(), m_nK, m_nI, m_nJ);
	if (!m_pReader->Open())
	{
		delete m_pReader;
		m_pReader = NULL;
	}

	return m_pReader;
}

CXLFMGeometry* CXLFMAttribute::GetLFM()
{
	return dynamic_cast<CXLFMGeometry*>(::GetObjectByID(m_uuidLFM));
}

bool CXLFMAttribute::ReadOneSlice(int iIndex, float* pBuffer)
{
	if (!pBuffer)
		return false;

	if (!IsBound(iIndex, 0, m_nK - 1))
		return false;

	if (!_GetReader())
		return false;

	return m_pReader->ReadUSection(iIndex, pBuffer);
}

bool CXLFMAttribute::ReadOneSection(int iIndex, float* pBuffer)
{
	if (!pBuffer)
		return false;

	if (!IsBound(iIndex, 0, m_nI - 1))
		return false;

	if (!_GetReader())
		return false;

	return m_pReader->ReadVSection(iIndex, pBuffer);
}

bool CXLFMAttribute::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_uuidLFM;

		ar << m_nI;
		ar << m_nJ;
		ar << m_nK;
	}
	else
	{
		ar >> m_uuidLFM;

		ar >> m_nI;
		ar >> m_nJ;
		ar >> m_nK;
	}

	return true;
}

bool CXLFMAttribute::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	if (!GetLFM())
		return false;
	else
		return GetLFM()->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

}

QStringList CXLFMAttribute::GetDescription()
{
	QStringList list;
	list << "Number of Inlines: " << QString::number(m_nI)
		<< "Number of Crosslines: " << QString::number(m_nJ)
		<< "Number of Slices: " << QString::number(m_nK);

	return list;
}

CXObject* CXLFMAttribute::GetGeometryObject()
{
    return GetLFM();
}