#include "x2dpolygon.h"
#include "xobjectfactory.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX2DPolygon)
EX2DPolygon,
EXFaultPolygon
END_REGISTER_OBJECT_TO_FACTORY(CX2DPolygon)


CX2DPolygon::CX2DPolygon()
{

}
CX2DPolygon::CX2DPolygon(QString strName, EXObjectType eType): CXObject(strName)
{
	SetObjectType(eType);
	m_pBaseData = NULL;

	if(eType == EX2DPolygon)
		SetIconName("Polygon.png");
	else
		SetIconName("FaultPolygon.png");
}

QString CX2DPolygon::GetTypeString()
{
	if (GetObjectType() == EX2DPolygon)
		return "Polygon";
	else
		return "Fault Polygon";
}

void CX2DPolygon::ResetData(double* pData, unsigned int iNumber)
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
void CX2DPolygon::ResetData(unsigned int index,double xValue,double yValue)
{
	_LoadBaseData();

	if (m_pBaseData)
	{
		m_pBaseData[index * 2] = xValue;
		m_pBaseData[index * 2 + 1] = yValue;
	}
	SetModifiedFlag();
	SetNeedCalcDimension();
}

QStringList CX2DPolygon::GetDescription()
{
	QStringList strListDesc;

	strListDesc<<"Vertices number is:"<<QString::number(m_nSamplingNum / 2);

	return strListDesc;
}

void CX2DPolygon::_SetSelfDimension()
{
	if(m_nSamplingNum < 2)
		return;

	_LoadBaseData();

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	dXMin = dXMax = m_pBaseData[0];
	dYMin = dYMax = m_pBaseData[1];
	dZMin = dZMax = 0.;

	for(unsigned int i = 2; i < m_nSamplingNum; i += 2)
	{
		dXMin = dXMin < m_pBaseData[i] ? dXMin : m_pBaseData[i];
		dXMax = dXMax > m_pBaseData[i] ? dXMax : m_pBaseData[i];
		dYMin = dYMin < m_pBaseData[i + 1] ? dYMin : m_pBaseData[i + 1];
		dYMax = dYMax > m_pBaseData[i + 1] ? dYMax : m_pBaseData[i + 1];
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}