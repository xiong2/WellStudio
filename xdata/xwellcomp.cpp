
#include "xwellcomp.h"
#include "xwellcompdata.h"
#include "xobjectfactory.h"
#include "xwellcurve.h"
#include "xwell.h"
#include <math.h>
#ifndef MAX
#define	MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define	MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellComp)
EXWellComp
END_REGISTER_OBJECT_TO_FACTORY(CXWellComp)

CXWellComp::CXWellComp()
{
	SetObjectType(EXWellComp);
	SetObjectName("Well Comp");
	SetNodeFlag(false);
}

CXWellComp::~CXWellComp()
{
}
CXWellCompData* CXWellComp::GetWellCompData(void* pWindow, bool bCreate)
{
	if (m_mapCompData.contains(pWindow))
	{
		if (CXWellCompData::g_lstAllData.contains(m_mapCompData[pWindow])==false)//已经被删除的,要删除
		{
			m_mapCompData.remove(pWindow);
			//ReomveWellCompData(pWindow);
		}
	}
	if (m_mapCompData.contains(pWindow) == false)
	{
		if (bCreate)
		{
			CXWell* pWell = dynamic_cast<CXWell*>(GetParent());
			if (!pWell)
			{
				return NULL;
			}
			QList<CXWellCurve*> lst = pWell->getCurveList();
			if (lst.count()>0)
			{
				//ReomveAllCompData(NULL);
				

				CXWellCompData* pCompData = new CXWellCompData();
				pCompData->SetID(pWindow);
				AddChild(pCompData);
				pCompData->CreateDataByTrack(lst.first());
				m_mapCompData[pWindow] = pCompData;
				return pCompData;
			}
		}
		return NULL;
	}
	return m_mapCompData[pWindow];
}

#include <qmessagebox.h>
void CXWellComp::ReomveAllCompData(void* pWindow)
{
	for (int i = CXWellCompData::g_lstAllData.count() - 1; i >= 0; i--)
	{
		if (CXWellCompData::g_lstAllData[i]->GetID() == pWindow)
		{
	//	QMessageBox::warning(NULL, "", "start" + QString::number(i));
			if (CXWellCompData::g_lstAllData[i]->GetParent())
			{
				CXWellCompData::g_lstAllData[i]->GetParent()->RemoveOneChild(CXWellCompData::g_lstAllData[i]);
			}
			delete CXWellCompData::g_lstAllData[i];
		//	QMessageBox::warning(NULL, "", "delete" + QString::number(i));
			//CXWellCompData::g_lstAllData.removeAt(i);
		}
		//QMessageBox::warning(NULL, "", "end" + QString::number(i));
	}
}

void CXWellComp::ReomveWellCompData(void* pWindow)
{
	if (m_mapCompData.contains(pWindow))
	{
		RemoveOneChild(m_mapCompData[pWindow]);
		delete m_mapCompData[pWindow];
		m_mapCompData.remove(pWindow);
	}
}
void CXWellComp::ReomveAllWellCompData()
{
	QMap<void*, CXWellCompData*>::iterator it;
	for (it = m_mapCompData.begin(); it != m_mapCompData.end(); ++it)
	{
		RemoveOneChild(it.value());
		delete (it.value());
	}
	m_mapCompData.clear();
}

bool lstCXWellCompDataLessThan( CXWellCompData* p1, CXWellCompData* p2)
{
	return p1->GetType() < p2->GetType();
}
QList<CXWellCompData*> CXWellComp::GetAllData()
{
	QList<CXWellCompData*> lst;

	QMap<void*, CXWellCompData*>::iterator it;
	for (it = m_mapCompData.begin(); it != m_mapCompData.end(); ++it)
	{
		lst.append(it.value());
	}


	qSort(lst.begin(), lst.end(), lstCXWellCompDataLessThan);


	return lst;
}