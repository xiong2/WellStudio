#include "xwelltd.h"
#include "xobjectfactory.h"
#include "xlinearitymap.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xwell.h"
#include "xmathmacro.h"
#include "x3dsurvey.h"
#include "xproject.h"
#include "xglobal.h"
#include <cassert>
#include "xutility.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellTD)
EXWellTD
END_REGISTER_OBJECT_TO_FACTORY(CXWellTD)

CXWellTD::CXWellTD()
{
	SetObjectType(EXWellTD);
	m_nSamplingNum	= 0;
	m_pBaseData = NULL;

	SetNodeFlag(false);
}

CXWellTD::~CXWellTD()
{
}

//	Populate the data. Depth array (z) followed by TWT array.
void CXWellTD::ResetData(double* pData, unsigned int iNumber)
{
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

double CXWellTD::GetAValue(double dIVal, bool bFromZToT)
{
	int i, iNum = m_nSamplingNum / 2;

	if (iNum == 0)
		return g_dInvalidData;

	_LoadBaseData();

	double *pZ = m_pBaseData;
	double *pTWT = m_pBaseData + iNum;
	if (!bFromZToT)
	{
		pZ = pTWT;
		pTWT = m_pBaseData;
	}

	for (i = 0; i < iNum; i++)
	{
		if(dIVal < pZ[i])
			break;
	}

	if (i == 0)
	{
		//	Above the 1st point.
		return pTWT[0] - (pZ[0] - dIVal) * (pTWT[1] - pTWT[0]) / (pZ[1] - pZ[0]);
	}
	else
	{
		//	To ensure it works while byond the last point.
		if (i < iNum)
			i++;

		return pTWT[i - 1] + (pTWT[i - 1] - pTWT[i - 2]) * (dIVal - pZ[i - 1]) / (pZ[i - 1] - pZ[i - 2]);
	}
}