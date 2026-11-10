#include "xfracturepatch.h"
#include "xobjectfactory.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXFracturePatch)
EXFracturePatch
END_REGISTER_OBJECT_TO_FACTORY(CXFracturePatch)

CXFracturePatch::CXFracturePatch(QString sName) : CXObject(sName)
{
	SetObjectType(EXFracturePatch);
	SetIconName("FracturePatch.png");
}

CXFracturePatch::~CXFracturePatch()
{
}

QStringList CXFracturePatch::GetDescription()
{
	QStringList sList;

	int iNum = m_sListProperties.size() + 12;
	sList << "Fracure Patches amount" << QString::number(m_nSamplingNum / iNum);
	sList << "Patches properties" << m_sListProperties.join(", ");

	return sList;
}

bool CXFracturePatch::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_sListProperties;
	}
	else
	{
		ar >> m_sListProperties;
	}

	return true;
}

void CXFracturePatch::ResetData(QStringList sListPro, double* pData, unsigned int iNumber)
{
	m_sListProperties = sListPro;

	_LoadBaseData();

	//	Free the data if exist.
	if (m_pBaseData != nullptr && m_pBaseData != pData)
		delete[]m_pBaseData;

	m_pBaseData = pData;
	m_nSamplingNum = iNumber;

	//	Need re-calculate the dimension.
	SetNeedCalcDimension();

	//data modified flag
	this->SetModifiedFlag();
}

void CXFracturePatch::_SetSelfDimension()
{
	int nProp = m_sListProperties.size();
	int nPatch = m_nSamplingNum / (nProp + 12);
	if (nPatch < 1)
		return;

	_LoadBaseData();
	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	dXMin = dXMax = m_pBaseData[nProp];
	dYMin = dYMax = m_pBaseData[nProp + 1];
	dZMin = dZMax = m_pBaseData[nProp + 2];

	int i, j, iIDX;
	for (i = 0; i < nPatch; i++)
	{
		iIDX = i * (nProp + 12) + nProp;
		for (j = 0; j < 4; j++)
		{
			dXMin = dXMin < m_pBaseData[iIDX + 3 * j] ? dXMin : m_pBaseData[iIDX + 3 * j];
			dXMax = dXMax > m_pBaseData[iIDX + 3 * j] ? dXMax : m_pBaseData[iIDX + 3 * j];
			dYMin = dYMin < m_pBaseData[iIDX + 3 * j + 1] ? dYMin : m_pBaseData[iIDX + 3 * j + 1];
			dYMax = dYMax > m_pBaseData[iIDX + 3 * j + 1] ? dYMax : m_pBaseData[iIDX + 3 * j + 1];
			dZMin = dZMin < m_pBaseData[iIDX + 3 * j + 2] ? dZMin : m_pBaseData[iIDX + 3 * j + 2];
			dZMax = dZMax > m_pBaseData[iIDX + 3 * j + 2] ? dZMax : m_pBaseData[iIDX + 3 * j + 2];
		}
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}