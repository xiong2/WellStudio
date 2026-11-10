#include "xwellpath.h"
#include "xobjectfactory.h"
#include "xlinearitymap.h"
#include "xwell.h"
#include "xwelltd.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellPath)
EXWellPath
END_REGISTER_OBJECT_TO_FACTORY(CXWellPath)

CXWellPath::CXWellPath()
{
	m_pMdData = NULL;
	m_pTWT = NULL;
}

CXWellPath::CXWellPath(double dX, double dY, double dZ)
{
	SetObjectType(EXWellPath);
	SetObjectName("Well Path");
	m_pMdData = NULL;
	m_pTWT = NULL;
	m_nSamplingNum	= 6;
	m_pBaseData = new double[6];
	m_pBaseData[0] = m_pBaseData[3] = dX;
	m_pBaseData[1] = m_pBaseData[4] = dY;
	m_pBaseData[2] = m_pBaseData[5] = dZ;
	m_pBaseData[5] += 10000.;

	SetNodeFlag(false);

	//	Need re-calculate the dimension.
	SetNeedCalcDimension();
}

CXWellPath::~CXWellPath()
{
	if(m_pMdData)
		delete[] m_pMdData;
	if (m_pTWT)
		delete[]m_pTWT;
}

void CXWellPath::GetWellPosition(double& dX, double& dY)
{
	_LoadBaseData();
	dX = m_pBaseData[0];
	dY = m_pBaseData[1];
}

//	set the X, Y coordinate of the well.
void CXWellPath::SetWellPosition(double dX, double dY)
{
	_LoadBaseData();
	double devX = m_pBaseData[0] - dX;
	double devY = m_pBaseData[1] - dY;
	int nCount = m_nSamplingNum / 3;
	for (unsigned int i = 0; i < nCount; i++)
	{
		m_pBaseData[i * 3] = m_pBaseData[i * 3] - devX;
		m_pBaseData[i * 3 + 1] = m_pBaseData[i * 3 + 1] - devY;
	}
	//	Need re-calculate the dimension.
	SetNeedCalcDimension();

	//data modified flag
	this->SetModifiedFlag();
}

void CXWellPath::ResetData(double* pData, unsigned int iNumber, double *pMDData)
{
	_LoadBaseData();
	if(m_pMdData)
		delete[] m_pMdData;
	m_pMdData = NULL;

	if (m_pTWT)
		delete[]m_pTWT;
	m_pTWT = NULL;

	//	Free the data if exist.
	if (m_pBaseData != pData)
		delete[]m_pBaseData;

	m_pBaseData = pData;
	m_nSamplingNum = iNumber;
	m_pMdData = pMDData;

	//	Need re-calculate the dimension.
	SetNeedCalcDimension();

	//data modified flag
	this->SetModifiedFlag();
}

double * CXWellPath::GetMdData()
{
	if (m_pMdData != NULL)
	{
		return m_pMdData;
	}
	_LoadBaseData();

	int nCount = m_nSamplingNum/3;
	m_pMdData = new double[nCount];

	double dKB = ((CXWell *)GetParent())->GetKB();
	double dLength = qAbs(m_pBaseData[2] + dKB);
	m_pMdData[0] = dLength;

	for(unsigned int i = 0; i <nCount -1 ; i ++)
	{
		double dX = m_pBaseData[3 * i];
		double dY = m_pBaseData[3 * i + 1];
		double dZ = m_pBaseData[3 * i + 2];

		double dX1 = m_pBaseData[3 * (i + 1)];
		double dY1 = m_pBaseData[3 * (i + 1) + 1];
		double dZ1 = m_pBaseData[3 * (i + 1) + 2];

		double dTmpX = (dX1 - dX) * (dX1 - dX);
		double dTmpY = (dY1 - dY) * (dY1 - dY);
		double dTmpZ = (dZ1 - dZ) * (dZ1 - dZ);

		double dMD = sqrt(dTmpX+ dTmpY + dTmpZ);
		dLength += dMD;	
		m_pMdData[i+1] = dLength;
	}

	return m_pMdData;
}

double* CXWellPath::GetTWTData()
{
	if (m_pTWT)
		return m_pTWT;

	CXWell *pWell = dynamic_cast<CXWell *>(GetParent());
	CXWellTD *pWTD = pWell->GetWellTD();
	if(!pWTD)
		return m_pTWT;

	int nCount = m_nSamplingNum / 3;
	m_pTWT = new double[nCount];
	for (unsigned int i = 0; i < nCount - 1; i++)
	{
		m_pTWT[i] = pWTD->GetAValue(m_pBaseData[3 * i + 2]);
	}
	
	return m_pTWT;
}

//	Get top and bottom depth (SSTVD)
void CXWellPath::GetDepth(double& dTopDepth, double& dBottomDepth)
{
	_LoadBaseData();
	dTopDepth = m_pBaseData[2];
	dBottomDepth = m_pBaseData[m_nSamplingNum - 1];
}

void CXWellPath::_SetSelfDimension()
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
bool CXWellPath::MapAttrPointToCoord(double dMD, QVector3D & coord0)
{
	CXPoint3 coord;
	bool b = MapAttrPointToCoord(dMD, coord);
	coord0.setX(coord.x);
	coord0.setY(coord.y);
	coord0.setZ(coord.z);
	return b;
}

bool CXWellPath::MapAttrPointToCoord(double dMD, CXPoint3 & coord)
{
	// ensure have two point and ePathCol
	unsigned int nNumber(0);
	this->GetData(nNumber);
	nNumber /= 3;
	if(nNumber <2)
		return false;
	// get index	
	double * pMdData = GetMdData();
	int nIndex (-1);
	if( nIndex < 0 || nIndex >= nNumber )
	{
		double *pFind= std::lower_bound( pMdData,pMdData + nNumber ,dMD );
		nIndex = static_cast<int>( std::distance( pMdData,pFind ) );
		nIndex =  ( nIndex >=nNumber  ? nNumber-1 : nIndex );
	}

	_LoadBaseData();

	if( fabs( pMdData[ nIndex ] - dMD ) < 1.0e-3 )
	{
		//in the well path MD array if pMD[nIndex] value equal dMd, return correspond x, y and z value
		coord.x = (m_pBaseData[3 * nIndex + 0]);
		coord.y = (m_pBaseData[3 * nIndex + 1]);
		coord.z = (m_pBaseData[3 * nIndex + 2]);
	}
	else  
	{
		// insert the value by Linear
		int nPreIndex = nIndex - 1;
		nPreIndex = nPreIndex < 0 ? 0 : nPreIndex;
		CXLinearityMap mapX(pMdData[nPreIndex], pMdData[nIndex], m_pBaseData[3 * nPreIndex + 0], m_pBaseData[3 * nIndex + 0]);
		CXLinearityMap mapY(pMdData[nPreIndex], pMdData[nIndex], m_pBaseData[3 * nPreIndex + 1], m_pBaseData[3 * nIndex + 1]);
		CXLinearityMap mapZ(pMdData[nPreIndex], pMdData[nIndex], m_pBaseData[3 * nPreIndex + 2], m_pBaseData[3 * nIndex + 2]);

		coord.x = (mapX.GetOutputValue(dMD));
		coord.y = (mapY.GetOutputValue(dMD));
		coord.z = (mapZ.GetOutputValue(dMD));
	}

	return true;
}

double CXWellPath::Md2Tvd(const float &fMD)
{
	unsigned int iNumber;
	double *pData = GetData(iNumber);
	iNumber /= 3;
	double *pMDData = GetMdData();

	if (fMD < pMDData[0])
	{
		return (fMD - pMDData[0]) * (pData[5] - pData[2]) / (pMDData[1] - pMDData[0]) + pData[2];
	}
	else if (fMD > pMDData[iNumber - 1])
	{
		return (fMD - pMDData[iNumber - 2]) * (pData[3 * iNumber - 1] - pData[3 * iNumber - 4]) / (pMDData[iNumber - 1] - pMDData[iNumber - 2]) + pData[3 * iNumber - 4];
	}
	else
	{
		for (int i = 1; i < iNumber; i++)
		{
			if (fMD < pMDData[i])
			{
				return (fMD - pMDData[i - 1]) * (pData[3 * i + 2] - pData[3 * i - 1]) / (pMDData[i] - pMDData[i - 1]) + pData[3 * i - 1];
			}
		}
	}

	return -999.25;
}

void CXWellPath::CleanTWTData()
{
	if (m_pTWT)
	{
		delete[]m_pTWT;
		m_pTWT = NULL;
	}
}

double CXWellPath::Tvd2Md(const float &depth)
{
	unsigned int iNumber;
	double *pData = GetData(iNumber);
	iNumber /= 3;
	double *pMDData = GetMdData();

	if (depth < pData[2])
	{
		return (depth - pData[2]) * (pMDData[1] - pMDData[0]) / (pData[5] - pData[2]) + pMDData[0];
	}
	else if (depth > pData[3 * iNumber - 1])
	{
		return (depth - pData[3 * iNumber - 4]) * (pMDData[iNumber - 1] - pMDData[iNumber - 2]) / (pData[3 * iNumber - 1] - pData[3 * iNumber - 4]) + pMDData[iNumber - 2];
	}
	else
	{
		for (int i = 1; i < iNumber; i++)
		{
			if (depth < pData[3 * i + 2])
			{
				return (depth - pData[3 * i - 1]) * (pMDData[i] - pMDData[i - 1]) / (pData[3 * i + 2] - pData[3 * i - 1]) + pMDData[i - 1];
			}
		}
	}

	return depth;
}