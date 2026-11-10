#include "xcurvecells.h"
#include "xwellcurvealias.h"
#include "xobjectfactory.h"
#include "xwellcondition.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellcurvecells.h"
#include "xwellcells.h"

#include <cassert>

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXCurveCells)
EXCurveCells
END_REGISTER_OBJECT_TO_FACTORY(CXCurveCells)

CXCurveCells::CXCurveCells()
{
}

CXCurveCells::CXCurveCells(CXWellCurveAlias *pCurveAlias)
{
	SetObjectType(EXCurveCells);

	m_curveAliasID = pCurveAlias->GetObjectID();

	SetObjectName(pCurveAlias->GetObjectName());
	SetIconName(pCurveAlias->GetIconName());
}

void CXCurveCells::CalculateCurve(CXWellCondition *pWellCondition)
{
	assert(pWellCondition);
	QList<CXWell *> listWells = pWellCondition->GetCalculatedWells();
	if (listWells.empty()) return;

	_LoadBaseData();
	if (m_pBaseData)
	{
		delete[] m_pBaseData;
		m_pBaseData = nullptr;
	}

	QList<double> listValue;

	foreach (CXWell *pWell, listWells)
	{
		QList<CXObject *> listCurve = pWell->GetChildren(EXWellCurve);
		if (listCurve.empty())
		{
			CXObject *pChild = pWellCondition->GetChild(pWell->GetObjectName(), EXWellCells);
			if (pChild)
			{
				CXWellCells *pWellCells = dynamic_cast<CXWellCells*>(pChild);
				assert(pWellCells);
				QList<double> listInvalid;
				for (int i=0; i<pWellCells->GetCellList().size(); ++i)
					listInvalid << ::g_dInvalidData;
				listValue.append(listInvalid);
			}
		}

		foreach (CXObject *pChild, listCurve)
		{
			CXWellCurve *pCurve = dynamic_cast<CXWellCurve *>(pChild);
			if (pCurve->GetAliasID() == m_curveAliasID)
			{
				CalculateOneCurve(pCurve, pWellCondition, listValue);
			}
		}
	}

	m_nSamplingNum = listValue.size();
	m_pBaseData = new double[m_nSamplingNum];
	for (int i=0; i<m_nSamplingNum; ++i)
		m_pBaseData[i] = listValue[i];
}

void CXCurveCells::CalculateOneCurve(CXWellCurve *pCurve, CXWellCondition *pWellCondition, QList<double> &listValue)
{
	QList<CXObject *> listWellCurveCells = GetChildren(EXWellCurveCells);
	foreach (CXObject *pObj, listWellCurveCells)
	{
		CXWellCurveCells *pWellCurveCells = dynamic_cast<CXWellCurveCells *>(pObj);
		if (pWellCurveCells && pWellCurveCells->GetWellCurveId() == pCurve->GetObjectID())
		{
			RemoveOneChild(pWellCurveCells);
			delete pWellCurveCells;
			break;
		}
	}

	// Calculate the WellCurveCells
	QList<CXObject *> listWellCells = pWellCondition->GetChildren(EXWellCells);

	foreach (CXObject *pChild, listWellCells)
	{
		CXWellCells *pWellCells = dynamic_cast<CXWellCells *>(pChild);
		if (pWellCells && pWellCells->GetWellID() == pCurve->GetParent()->GetObjectID())
		{
			CXWellCurveCells *pWellCurveCells = CXWellCurveCells::CreateWellCurveCells(pWellCells, pCurve);
			if (pWellCurveCells)
			{
				pWellCurveCells->SetNodeFlag(false);
				AddChild(pWellCurveCells);
				QList<double> listCurveCellsValue = pWellCurveCells->GetValueList();
				listValue.append(listCurveCellsValue);
			}
		}
	}
}

CXObject* CXCurveCells::GetGeometryObject()
{
	CXWellCondition *pWellCondition = dynamic_cast<CXWellCondition*>(GetParent());
	if (pWellCondition)
		return pWellCondition;
	
    return nullptr;
}

QStringList CXCurveCells::GetDescription()
{
	QStringList strListDesc;

	CXWellCondition *pWellCondition = dynamic_cast<CXWellCondition*>(GetParent());
	if (!pWellCondition)
		return strListDesc;

	QList<CXWell*> listWell = pWellCondition->GetCalculatedWells();
	strListDesc << GetTr("Computed well count") << QString::number(listWell.size());

	return strListDesc;
}

bool CXCurveCells::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
		ar << m_curveAliasID;
	else
		ar >> m_curveAliasID;

	return true;
}

float * CXCurveCells::_GetHistogramData(int & nDataNum, bool & bDeleted)
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