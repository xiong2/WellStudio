 #if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif 

#if !defined(AFX_KEWellComp_H_)
#define AFX_KEWellComp_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <QColor>
#include <QList>
#include <QMap>
#include "xdata_global.h"
#include "xobject.h"

class CXWell;
class CXWellCompData;
/**
  \brief 交会图与曲线显示窗口交互时使用的临时数据类,用来显示相对应的数据选择
 */
class XDATA_EXPORT CXWellComp : public CXObject
{
public:
	CXWellComp();
	virtual ~CXWellComp();

	///@brief Get well CXWellCompData instance.
	CXWellCompData* GetWellCompData(void* pWindow, bool bCreate = false);
	static void ReomveAllCompData(void* pWindow);
	void ReomveWellCompData(void* pWindow);
	void ReomveAllWellCompData();

	QList<CXWellCompData*> GetAllData();
	QMap<void*, CXWellCompData*>& GetCompMap() { return m_mapCompData; };
private:
	QMap<void*, CXWellCompData*> m_mapCompData;//void* is widget pointer,
};

#endif // !defined(AFX_RLCOMPDATA_H__D836E261_3734_45F4_BF23_108C9BA09F97__INCLUDED_)
