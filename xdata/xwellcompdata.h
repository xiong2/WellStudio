 #if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif 

#if !defined(AFX_KEWellCompData_H_)
#define AFX_KEWellCompData_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <QColor>
#include <QList>
#include "xdata_global.h"
#include "xobject.h"

class CXWell;
class CXWellCurve;
/**
  \brief 交会图与曲线显示窗口交互时使用的临时数据类,用来显示相对应的数据选择
 */
class XDATA_EXPORT CXWellCompData : public CXObject
{
public:
	CXWellCompData();
	virtual ~CXWellCompData();

	void SetID(void*);
	void* GetID();
	static QList<CXWellCompData*> g_lstAllData;


	/**  设置一段范围为选定或非选定  */
	void       SetChooseDepth(double Dst,double Ded,int choose); 

	void SetType(int type) { m_type = type; }///type = 0,wellcurve ,1 crossplot, 2 histgram, ...
	const int GetType() { return m_type; }

	/**  index与int*  m_pData的值相对应  index<12,设置颜色,
	* 如果没有定义index,则默认添加新颜色
	*/ 
	void  SetColor(QColor cr,int index = -1); 
	/**  返回相对应的颜色,如果index错误则返回Qt::black  */
	QColor GetColor(int index); 
	int GetColorCount();
	/**  返回当前的depth  */
	double       GetDepth(int index); 
	/**  由深度返回index  */
	int         GetIndex(double depth); 

	int*      GetData();
	int       GetData(int index);
	int       GetCount();
	virtual bool SerializeData(CXArchive& ar);

	/**  由相对应的pTrack创建原始数据  */
	bool       CreateDataByTrack(CXWellCurve* pTrack);
private:		
	QList<QColor> m_lstColor;//记录颜色类型---默认只支持10种颜色
	void* m_id;
	int       m_nCount;
	int*      m_pCompData; //0为没选择,其余为选择
	
	double     m_start;    //顶深
	double     m_stop;     //底深
	double     m_step;     //间隔值

	int m_type;
};

#endif // !defined(AFX_RLCOMPDATA_H__D836E261_3734_45F4_BF23_108C9BA09F97__INCLUDED_)
