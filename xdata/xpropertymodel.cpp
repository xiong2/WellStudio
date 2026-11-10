#include "xpropertymodel.h"
#include "xgridmodel.h"
#include "xobjectfactory.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXPropertyModel)
EXPropertyModel
END_REGISTER_OBJECT_TO_FACTORY(CXPropertyModel)

CXPropertyModel::CXPropertyModel()
{
	m_pBaseData = NULL;
}

CXPropertyModel::CXPropertyModel(QString strName): CXObject(strName)
{
	SetObjectType(EXPropertyModel);
	SetIconName("ResPropertyModel.png");

	m_pBaseData = NULL;
}

CXPropertyModel::~CXPropertyModel()
{
}

///	Reset data, so far only used by importing procedure.
void CXPropertyModel::ResetData(unsigned int iNum, double *pData)
{
	_LoadBaseData();
	if (m_pBaseData)
		delete m_pBaseData;

	m_nSamplingNum	= iNum;
	m_pBaseData = pData;

	SetModifiedFlag();
}
	
CXGridModel* CXPropertyModel::GetGridModel()
{
	CXObject *pParent = GetParent();
	if(pParent)
	{
		QList<CXObject*> listChildren = pParent->GetChildren(EXGridModel);
		if (listChildren.empty())
			return NULL;
		else
		{
			return dynamic_cast<CXGridModel*>(listChildren.front());
		}
	}
	else
	{
		return NULL;
	}
}


bool CXPropertyModel::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	CXGridModel *pGridModel = GetGridModel();
	if(pGridModel)
	{
		return pGridModel->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	}	

	return false;
}

CXObject* CXPropertyModel::GetGeometryObject()
{
	return GetGridModel();
}


QStringList CXPropertyModel::GetDescription()
{
	QStringList strListDesc;

	CXGridModel *pGridModel = GetGridModel();
	if(!pGridModel)
		return strListDesc;

	unsigned int nI, nJ, nK;
	pGridModel->GetIJKDimentionInfo(nI, nJ, nK);
	strListDesc<<GetTr(" I 方向网格数目")<<QString::number(nI);
	strListDesc<<GetTr(" J 方向网格数目")<<QString::number(nJ);
	strListDesc<<GetTr(" K 方向网格数目")<<QString::number(nK);
	strListDesc<<GetTr("总网格数目")<<QString::number(nK * nI * nJ);
	strListDesc<<GetTr("有效网格数目")<<QString::number(m_nSamplingNum);
	strListDesc<<GetTr("有效网格比例（%）")<<QString::number(m_nSamplingNum * 100 / (nK * nI * nJ));
			
	return strListDesc;
}

float * CXPropertyModel::_GetHistogramData(int & nDataNum, bool & bDeleted)
{
	nDataNum = m_nSamplingNum;
	bDeleted = true;
	if (nDataNum < 1)
		return nullptr;

	_LoadBaseData();
	float* pData = new float[m_nSamplingNum];
	for (int i = 0; i < m_nSamplingNum; ++i)
		pData[i] = (float)m_pBaseData[i];

	return pData;
}