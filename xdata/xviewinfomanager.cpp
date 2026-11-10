#include "xviewinfomanager.h"
#include <cassert>
#include "xobjectfactory.h"
#include "xviewinfoobject.h"
#include "xglobal.h"
#include "xobject.h"

CXViewInfoManager::CXViewInfoManager()
{
}


CXViewInfoManager::~CXViewInfoManager()
{
	_ClearMap();
}

CXViewInfoObject* CXViewInfoManager::GetDefaultViewInfoByID(const QUuid& uuid)
{
	CXViewInfoObject* pViewInfo = m_mapIDToViewInfo.value(uuid);
	if (!pViewInfo)
	{
		pViewInfo = new CXViewInfoObject;
		m_mapIDToViewInfo.insert(uuid, pViewInfo);

		// Set default min/max value from percentile (1%, 99%)
		auto pObj = ::GetObjectByID(uuid);
		if (pObj && pObj->HasHistogram())
		{
			double dMin, dMax;
			::GetObjectMinMaxByPercentile(dMin, dMax, 1., 99., pObj);

			pViewInfo->SetDisplayDataMin(dMin);
			pViewInfo->SetDisplayDataMax(dMax);
		}
	}
	return pViewInfo;
}

void CXViewInfoManager::_ClearMap()
{
	// Parameter
	QMap<QUuid, CXViewInfoObject*>::iterator it;
	for (it = m_mapIDToViewInfo.begin(); it != m_mapIDToViewInfo.end(); ++it)
	{
		CXViewInfoObject* pViewInfo = it.value();
		delete pViewInfo;
	}
	m_mapIDToViewInfo.clear();
}

void CXViewInfoManager::RemoveOneViewInfo(const QUuid& ObjID)
{
	CXViewInfoObject* pViewInfo = m_mapIDToViewInfo.value(ObjID, NULL);
	if (pViewInfo)
	{
		delete pViewInfo;
		m_mapIDToViewInfo.remove(ObjID);
	}
}

bool CXViewInfoManager::SerializeData(CXArchive & ar)
{
	if (ar.IsSaving())
	{
		int nCount = m_mapIDToViewInfo.size();
		ar << nCount;

		QMap<QUuid, CXViewInfoObject*>::iterator it;
		for (it = m_mapIDToViewInfo.begin(); it != m_mapIDToViewInfo.end(); ++it)
		{
			QUuid ObjID = it.key();
			CXViewInfoObject* pViewInfo = it.value();
			assert(pViewInfo);

			ar << ObjID.toString();
			pViewInfo->Serialize(ar.IsSaving());
		}
	}
	else
	{
		_ClearMap();

		int nCount;
		ar >> nCount;

		QString strObjID;
		int nType;
		EXObjectType eType;

		for (int i = 0; i < nCount; ++i)
		{
			ar >> strObjID;

			CXViewInfoObject* pViewInfo = new CXViewInfoObject;

			pViewInfo->Serialize(ar.IsSaving());

			m_mapIDToViewInfo.insert(QUuid(strObjID), pViewInfo);
		}
	}

	return true;
}
