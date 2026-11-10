#include "x3dpoints.h"
#include "xobjectfactory.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX3DPoints)
EX3DPoints
END_REGISTER_OBJECT_TO_FACTORY(CX3DPoints)

CX3DPoints::CX3DPoints(QString strName): CXObject(strName)
{
	SetObjectType(EX3DPoints);
	m_pBaseData = NULL;

	SetIconName("Points.png");
}

void CX3DPoints::ResetData(double* pData, unsigned int iNumber)
{
	_LoadBaseData();

	//	Free the data if exist.
	if (m_pBaseData)
		delete[]m_pBaseData;

	m_pBaseData = pData;
	m_nSamplingNum = iNumber;

	SetModifiedFlag();
	SetNeedCalcDimension();
}

QStringList CX3DPoints::GetDescription()
{
	QStringList strListDesc;

	if(::UsingChinese())
	{
		strListDesc<<GetTr("¶¥µãÊýÄ¿")<<QString::number(m_nSamplingNum / 3);
	}
	else
	{
		strListDesc<<"Points number is"<<QString::number(m_nSamplingNum / 3);
	}

	return strListDesc;
}

void CX3DPoints::_SetSelfDimension()
{
	if(m_nSamplingNum < 3)
		return;

	_LoadBaseData();

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	dXMin = dXMax = m_pBaseData[0];
	dYMin = dYMax = m_pBaseData[1];
	dZMin = dZMax = m_pBaseData[2];

	for(unsigned int i = 3; i < m_nSamplingNum; i += 3)
	{
		dXMin = dXMin < m_pBaseData[i] ? dXMin : m_pBaseData[i];
		dXMax = dXMax > m_pBaseData[i] ? dXMax : m_pBaseData[i];
		dYMin = dYMin < m_pBaseData[i + 1] ? dYMin : m_pBaseData[i + 1];
		dYMax = dYMax > m_pBaseData[i + 1] ? dYMax : m_pBaseData[i + 1];
		dZMin = dZMin < m_pBaseData[i + 2] ? dZMin : m_pBaseData[i + 2];
		dZMax = dZMax > m_pBaseData[i + 2] ? dZMax : m_pBaseData[i + 2];
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}