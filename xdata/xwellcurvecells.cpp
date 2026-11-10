#include "xwellcurvecells.h"
#include "xwellcurve.h"
#include "xobjectfactory.h"
#include "xwellcells.h"
#include "xglobal.h"

#include <numeric>

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellCurveCells)
EXWellCurveCells
END_REGISTER_OBJECT_TO_FACTORY(CXWellCurveCells)

CXWellCurveCells::CXWellCurveCells(CXWellCells *pWellCells, CXWellCurve *pCurve)
{
	SetObjectType(EXWellCurveCells);

	m_curveID = pCurve->GetObjectID();
	m_wellID = pWellCells->GetWellID();

	SetObjectName(pCurve->GetObjectName() + "_" + pWellCells->GetObjectName());
	SetIconName(pWellCells->GetIconName());
}

CXWellCurveCells* CXWellCurveCells::CreateWellCurveCells(CXWellCells *pWellCells, CXWellCurve *pWellCurve)
{
	CXWellCurveCells *pWellCurveCells = new CXWellCurveCells(pWellCells, pWellCurve);

	QList<double>& listValue = pWellCurveCells->GetValueList();

	// Calculate here.
	const QList<double> listMD = pWellCells->GetMDList();
	
	for (int i=0; i<listMD.size(); i+=2)
	{
		std::vector<double> vecValue;
		//qDebug() << listMD[i] << " ~ " << listMD[i+1];
		pWellCurve->GetData(listMD[i], listMD[i+1], vecValue);
		if (vecValue.empty()) listValue << ::g_dInvalidData;
		else listValue << std::accumulate(vecValue.cbegin(), vecValue.cend(), 0.0) / vecValue.size();
	}

	// check invalid data
	
	// head
	if (listValue.front() == ::g_dInvalidData)
	{
		QList<double>::iterator iter = listValue.begin() + 1; 
		while (*iter == ::g_dInvalidData)
			++iter;
		std::fill(listValue.begin(), iter, *iter);
	}

	// back
	if (listValue.back() == ::g_dInvalidData)
	{
		QList<double>::iterator iter = listValue.end() - 2;
		while (*iter == ::g_dInvalidData)
			--iter;
		std::fill(iter+1, listValue.end(), *iter);
	}

	// middle
	for (int i=0; i<listValue.size(); ++i)
	{
		if (listValue[i] == ::g_dInvalidData)
		{
			int j = i+1;
			while (listValue[j] == ::g_dInvalidData)
				++j;
			double dPreMD = (listMD[2*i-2] + listMD[2*i-1]) / 2;
			double dCurMD = (listMD[2*i]   + listMD[2*i+1]) / 2;
			double dNxtMD = (listMD[2*j]   + listMD[2*j+1]) / 2;

			double dPercent = (dCurMD - dPreMD) / (dNxtMD - dPreMD);
			listValue[i] = dPercent * listValue[j] + (1 - dPercent) * listValue[i-1];
		}
	}

	if (listValue.isEmpty() || listValue.size() != pWellCells->GetCellList().size())
	{
		delete pWellCurveCells;
		pWellCurveCells = NULL;
	}

	return pWellCurveCells;
}

bool CXWellCurveCells::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_curveID;
		ar << m_wellID;
		ar << m_listValues.size();
		foreach (double dValue, m_listValues)
			ar << dValue;
	}
	else
	{
		ar >> m_curveID;
		ar >> m_wellID;
		int iSize = 0;
		ar >> iSize;
		for (int i=0; i<iSize; ++i)
		{
			double dValue;
			ar >> dValue;
			m_listValues << dValue;
		}
	}

	return true;
}