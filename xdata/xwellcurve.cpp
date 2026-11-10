#include <QVector3D>
#include "xwellcurve.h"
#include "xtemplate.h"
#include "xglobal.h"
#include "xdbio.h"
#include "xobjectfactory.h"
#include "xwell.h"
#include "xutility.h"
#include "xcubicspline.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellCurve)
EXWellCurve
END_REGISTER_OBJECT_TO_FACTORY(CXWellCurve)

CXWellCurve::CXWellCurve(QString sName) : CXObject(sName)
{
	this->SetObjectType(EXWellCurve);

	m_dStep = 0.;
}

CXWellCurve::~CXWellCurve()
{
}

void CXWellCurve::ResetData(double fStart, double dStep, unsigned int iNumPoints, double*pData)
{
	_LoadBaseData();

	if (m_pBaseData)
		delete m_pBaseData;

	m_dStart = fStart;
	m_dStep = dStep;
	m_nSamplingNum = iNumPoints;
	m_pBaseData = pData;

	SetModifiedFlag();
}

bool reSampleCurve(int nSrcQty, double *pSrcX, double *pSrcY, int nTarQty, double *pTarX, double *pTarY, double fInvalidData)
{
	int SrcIndex = 0; int TarIndex = 0;
	while (pTarX[TarIndex] < pSrcX[SrcIndex])//处理头部
	{
		pTarY[TarIndex] = fInvalidData;
		TarIndex++;
	}
	double preSrcData = fInvalidData;
	for (; TarIndex < nTarQty; TarIndex++)
	{
		if (SrcIndex + 1 >= nSrcQty)
		{
			break;
		}
		while (SrcIndex + 1 < nSrcQty && pTarX[TarIndex] >= pSrcX[SrcIndex + 1])//定位
		{
			SrcIndex++;
		}
		if (SrcIndex + 1 >= nSrcQty)
		{
			break;
		}

		if (fabs(pTarX[TarIndex] - pSrcX[SrcIndex]) < M_FEPS)
		{
			pTarY[TarIndex] = pSrcY[SrcIndex];
			continue;
		}
		else if (fabs(pTarX[TarIndex] - pSrcX[SrcIndex + 1]) < M_FEPS)
		{
			pTarY[TarIndex] = pSrcY[SrcIndex + 1];
			continue;
		}

		if (pSrcY[SrcIndex] == fInvalidData
			|| pSrcY[SrcIndex + 1] == fInvalidData)
		{
			pTarY[TarIndex] = fInvalidData;
			continue;
		}
		pTarY[TarIndex] = pSrcY[SrcIndex] + (pSrcY[SrcIndex + 1] - pSrcY[SrcIndex])* (pTarX[TarIndex] - pSrcX[SrcIndex]) / (pSrcX[SrcIndex + 1] - pSrcX[SrcIndex]);

	}
	for (; TarIndex < nTarQty; TarIndex++)//处理尾部
	{
		pTarY[TarIndex] = fInvalidData;
	}
	return true;
}
void CXWellCurve::ResetDataByResample(double fStart, double dStep, unsigned int iNumPoints, double*pData)
{
	CXWell* pWell = dynamic_cast<CXWell*>(GetParent());
	if (!pWell)
	{
		return;
	}
	double dWellStart, dWellEnd, dWellStep;
	pWell->GetDepthRange(dWellStart, dWellEnd);
	dWellStep = pWell->GetWellStep();
	int newCount = (dWellEnd - dWellStart) / dWellStep + 1.9;
	double* newData = new double[newCount];
	// 		if (pCurve->GetStep() == m_dStep)//间隔相同的地方
	// 		{
	// 			pCurve->GetData(newData, m_dStart, newCount);		
	// 		}
	// 		else//间隔不同
	{
		double* intsDataTime = NULL;//第一次插值数据
		double* srcDataTime = NULL;//第一次插值数据
								   //unsigned intsCount = (pCurve->GetStop() - pCurve->GetStart()) / m_dStep + 1.9;//第一次重采样个数
								   //if (!intsDataTime)

		int z;
		intsDataTime = new double[newCount];
		for (z = 0; z < newCount; z++)
		{
			intsDataTime[z] = z*dWellStep + dWellStart;
		}
		int oldCount = iNumPoints;
		srcDataTime = new double[oldCount];
		double oldstep = dStep;
		double oldstart = fStart;
		for (z = 0; z < oldCount; z++)
		{
			srcDataTime[z] = z*oldstep + oldstart;
		}

		double* intsData = new double[newCount];

		//重采样
		reSampleCurve(iNumPoints, srcDataTime, pData
			, newCount, intsDataTime, intsData
			, g_dInvalidData);

		delete intsDataTime;
		delete srcDataTime;


		this->ResetData(dWellStart, dWellStep, newCount, intsData);
		this->GetData(newData, dWellStart, newCount);
	}
	if (this->GetObjectName().toLower() == "depth")
	{
		for (int z = 0; z < newCount; z++)
		{
			newData[z] = dWellStart + z*dWellStep;
		}
	}
	this->ResetData(dWellStart, dWellStep, newCount, newData);
}

void CXWellCurve::GetDepthRange(double& fStart, double& fEnd)
{
	fStart = m_dStart;
	fEnd = m_dStart + (m_nSamplingNum - 1) * m_dStep;
}

double* CXWellCurve::GetData()
{
	_LoadBaseData();
	return m_pBaseData;
}

void CXWellCurve::GetData(double dStartDepth, double dEndDepth, vector<double> &vec)
{
	_LoadBaseData();
	if (!m_pBaseData || m_dStep == 0.) return;

	double dEnd = m_dStart + (m_nSamplingNum - 1) * m_dStep;
	if (dEndDepth < m_dStart || dStartDepth > dEnd) return;

	dStartDepth = qMax(dStartDepth, m_dStart);
	dEndDepth = qMin(dEndDepth, dEnd);

	int iStartIDX = (dStartDepth - m_dStart) / m_dStep;
	int iNumPoint = (dEndDepth - dStartDepth) / m_dStep;

	for (int i = 0; i < iNumPoint; ++i)
	{
		vec.push_back(m_pBaseData[iStartIDX + i]);
	}
}

//	Copy the data to the given pointer (space already allocated), INVALID value be used if beyond the data range.
bool CXWellCurve::GetData(double* pData, double dStartDepth, unsigned int iNumPoints)
{
	_LoadBaseData();
	if (!pData || !m_pBaseData || m_dStep == 0.)
		return false;

	int i, iSouStartIDX = 0, iDesStartIDX = 0, iActureNumPoints = iNumPoints;

	//	First fill all the array by invalid value.
	for (i = 0; i < iNumPoints; i++)
		pData[i] = ::g_dInvalidData;

	if (dStartDepth < m_dStart)
	{
		iDesStartIDX = (m_dStart - dStartDepth) / m_dStep;
		iActureNumPoints -= iDesStartIDX;

		if (iActureNumPoints > m_nSamplingNum)
			iActureNumPoints = m_nSamplingNum;
	}
	else
	{
		iSouStartIDX = (dStartDepth - m_dStart) / m_dStep;

		if (iActureNumPoints > m_nSamplingNum - iSouStartIDX)
			iActureNumPoints = m_nSamplingNum - iSouStartIDX;
	}

	for (i = 0; i < iActureNumPoints; i++)
	{
		pData[i + iDesStartIDX] = m_pBaseData[i + iSouStartIDX];
	}

	return true;
}

bool CXWellCurve::GetDataByResample(float *pData, double dStartDepth, double dStartStep, unsigned int iNumPoints)
{
	_LoadBaseData();
	if (!pData || !m_pBaseData || m_dStep == 0.)
		return false;



	double dWellStart, dWellEnd, dWellStep;
	dWellStart = dStartDepth;
	dWellStep = dStartStep;
	int newCount = iNumPoints;
	float* newData = pData;//new double[newCount];
	// 		if (pCurve->GetStep() == m_dStep)//间隔相同的地方
	// 		{
	// 			pCurve->GetData(newData, m_dStart, newCount);		
	// 		}
	// 		else//间隔不同

	double* intsDataTime = NULL;//第一次插值数据
	double* srcDataTime = NULL;//第一次插值数据
							   //unsigned intsCount = (pCurve->GetStop() - pCurve->GetStart()) / m_dStep + 1.9;//第一次重采样个数
							   //if (!intsDataTime)
	{
		int z;
		intsDataTime = new double[newCount];
		for (z = 0; z < newCount; z++)
		{
			intsDataTime[z] = z*dWellStep + dWellStart;
		}
		int oldCount = iNumPoints;
		srcDataTime = new double[oldCount];
		double oldstep = m_dStep;
		double oldstart = m_dStart;
		for (z = 0; z < oldCount; z++)
		{
			srcDataTime[z] = z*oldstep + oldstart;
		}
	}
	double* intsData = new double[newCount];

	//重采样
	reSampleCurve(iNumPoints, srcDataTime, intsData
		, newCount, intsDataTime, intsData
		, g_dInvalidData);
	for (int i = 0; i < newCount; i++)
	{
		newData[i] = intsData[i];
	}
	if (intsDataTime)
	{
		delete[]intsDataTime;
		delete[]srcDataTime;
	}

	return true;
}


QString CXWellCurve::GetIconName() const
{
	CXTemplate *pTemplate = CXTemplate::GetTemplate(GetTemplateID());
	if (pTemplate)
		return pTemplate->GetIcon();
	else
		return CXObject::GetIconName();
}

QString CXWellCurve::GetUnit()
{
	CXTemplate *pTemplate = CXTemplate::GetTemplate(GetTemplateID());
	if (pTemplate)
		return pTemplate->GetUnit();
	else
		return "";
}

QStringList CXWellCurve::GetDescription()
{
	QStringList strListDesc;
	CXTemplate *pTemplate = CXTemplate::GetTemplate(GetTemplateID());

	if (::UsingChinese())
	{
		strListDesc << GetTr("样点数目") << QString::number(m_nSamplingNum / 3);
		strListDesc << GetTr("模板名称") << pTemplate->GetName();
		strListDesc << GetTr("单位") << pTemplate->GetUnit();
	}
	else
	{
		strListDesc << "Sample number is" << QString::number(m_nSamplingNum / 3);
		strListDesc << "Template Name" << pTemplate->GetName();
		strListDesc << "Unit" << pTemplate->GetUnit();
	}

	return strListDesc;
}

bool CXWellCurve::SerializeData(CXArchive& ar)
{
	int flags0 = 201510;
	int flags1;
	if (ar.IsSaving())
	{
		ar << flags0
			<< m_unit;
	}
	else
	{
		ar >> flags1
			>> m_unit;
	}

	return true;
}
unsigned int CXWellCurve::GetTemplateID() const
{
	//	Find the alias object.
	CXObject *pAlias = ::GetObjectByID(m_aliasID);

	if (pAlias)
		return pAlias->GetTemplateID();
	else
	{
		//	Should not run here!
		return CXObject::GetTemplateID();
	}
}

bool CXWellCurve::Serialize(bool bSave)
{
	// base object
	if (!CXObject::Serialize(bSave))
		return false;

	QString strTable = "wellcurve";

	// save
	if (bSave)
	{
		QStringList strFieldList;
		strFieldList << "ID";
		strFieldList << "AliasID";
		strFieldList << "Start";
		strFieldList << "Step";
		strFieldList << "PairValue";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());
		vtList.append(m_aliasID.toString());
		vtList.append(m_dStart);
		vtList.append(m_dStep);

		// curve alias
		QStringList listPair;
		for (int i = 0; i < m_lstTableData.size(); ++i)
		{
			listPair.append(QString::number(m_lstTableData.at(i).first, 'f', 8));
			listPair.append(QString::number(m_lstTableData.at(i).second, 'f', 8));
		}
		vtList.append(listPair.join('\r'));

		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	}
	else
	{
		QStringList strFieldList;
		strFieldList << "AliasID";
		strFieldList << "Start";
		strFieldList << "Step";
		strFieldList << "PairValue";

		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if (query.first())
		{
			int nIndex = -1;

			m_aliasID = query.value(++nIndex).toString();
			m_dStart = query.value(++nIndex).toDouble();
			m_dStep = query.value(++nIndex).toDouble();

			QString listPair = query.value(++nIndex).toString();
			QStringList strListPair = listPair.split("\r");
			m_lstTableData.clear();
			for (int i = 0; i < strListPair.size() / 2; ++i)
			{
				double dVOne = strListPair[2 * i].toDouble();
				double dVTwo = strListPair[2 * i + 1].toDouble();

				m_lstTableData.append(qMakePair(dVOne, dVTwo));
			}
		}

		return true;
	}
}



bool CXWellCurve::IsValid(double v)
{
	return fabs(v - g_dInvalidData) > 1;
}
void CXWellCurve::SetData(int index, double& value) //set data ,for rocklab
{
	_LoadBaseData();
	m_pBaseData[index] = value;
}
double CXWellCurve::GetDepth(int index)
{
	return m_dStart + m_dStep*index;
}
double CXWellCurve::GetData(int index)
{
	_LoadBaseData();
	return m_pBaseData[index];
}

int CXWellCurve::GetIndex(float depth)//由深度返回index
{
	if (m_dStart > depth)
	{
		return 0;
	}
	if (depth - (float)m_nSamplingNum* m_dStep - m_dStart > 0.01)
	{
		return m_nSamplingNum - 1;
	}
	if (m_dStart - depth > 0.01 || depth - (float)m_nSamplingNum* m_dStep - m_dStart > 0.01)
		return -1;
	int   index = (depth - m_dStart)*1000.f / (m_dStep*1000.f);
	float dep, amin, temp, ix;
	for (int i = index - 1; i <= index + 1; i++)
	{
		dep = GetDepth(i);
		if (i == index - 1)
		{
			amin = fabs(depth - dep);
			ix = i;
		}
		else
		{
			temp = fabs(depth - dep);
			if (temp < amin)
			{
				amin = temp;
				ix = i;
			}
		}
	}
	return qBound(0, (int)ix, (int)m_nSamplingNum - 1);
}


void CXWellCurve::GetDepthRange(float& fStart, float& fEnd)
{
	fStart = m_dStart;
	fEnd = m_dStart + (m_nSamplingNum - 1) * m_dStep;
}

bool CXWellCurve::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	CXObject* pWell = GetAncient(EXWell);
	if (!pWell)
		return false;

	QList<CXObject*> listObj = pWell->GetChildren(EXWellPath);
	if (listObj.isEmpty())
		return false;
	else
	{
		return listObj.front()->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	}
}

void CXWellCurve::GetValidRange(double& dStart, double& dStop)
{
	_LoadBaseData();
	dStart = -999;
	dStop = -999;
	int i;
	for (i = 0; i < m_nSamplingNum; i++)
	{
		if (m_pBaseData[i] != g_dInvalidData)
		{
			dStart = m_dStart + (i - 1) * m_dStep;
			break;
		}
	}
	for (i = m_nSamplingNum - 1; i >= 0; i++)
	{
		if (m_pBaseData[i] != g_dInvalidData)
		{
			dStop = m_dStart + (i - 1) * m_dStep;
			break;
		}
	}
}

QList<QPair<double, double> >	CXWellCurve::GetTableData()
{
	return m_lstTableData;
}

bool lstTableDataLessThan(const QPair<double, double> p1, const QPair<double, double> p2)
{
	return p1.first < p2.first;
}
void CXWellCurve::SetTableData(QList<QPair<double, double> >		lstTableData)
{
	_LoadBaseData();

	SetModifiedFlag();
	m_lstTableData = lstTableData;
	if (m_lstTableData.count() <= 1)
	{
		return;
	}
	qSort(m_lstTableData.begin(), m_lstTableData.end(), lstTableDataLessThan);
	int indexOfTable = 0;
	double curData = g_dInvalidData;
	for (int i = 0; i < m_nSamplingNum; i++)
	{
		//两种情况1.在当前位置的上面，2.在当前位置的下面。3或者当前位置最低了
		if (indexOfTable < m_lstTableData.count() && GetDepth(i) < m_lstTableData[indexOfTable].first)
		{
			m_pBaseData[i] = curData;
		}
		else if (indexOfTable < m_lstTableData.count() - 1 && GetDepth(i) >= m_lstTableData[indexOfTable].first)
		{
			m_pBaseData[i] = curData = m_lstTableData[indexOfTable].second;
			indexOfTable++;
		}
		else {
			m_pBaseData[i] = g_dInvalidData;
		}
	}
	this->SetNeedCalculateHistogram();
}

float * CXWellCurve::_GetHistogramData(int & nDataNum, bool & bDeleted)
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