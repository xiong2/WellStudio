#ifndef XWELLCONDITIONVISPAGE_H
#define XWELLCONDITIONVISPAGE_H

#include "xbasepropertypage.h"
#include "xgui_global.h"

namespace Ui {class CXWellConditionVisPage;};

///@brief	The class provides a visualization page for WellCondition of Reservoirmodel
///@author	Pezy
///@date	Feb. 2th, 2015
///@see		CXBasePropertyPage
///@see     CXWellCondition

class CXViewInfoObject;
class CXViewInfoWellCondition;

class XGUI_EXPORT CXWellConditionVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXWellConditionVisPage(QWidget *parent, CXViewInfoObject *pViewInfo);
	~CXWellConditionVisPage();

	virtual void Apply();

private:
	void _Init();
	void _InitData();
	
private slots:
	void _SelectAllWellItems();
	void _DisSelectAllWellItems();

private:
	Ui::CXWellConditionVisPage *m_pUi;
    CXViewInfoWellCondition *m_pViewInfo;
};

#endif // RLWELLCONDITIONVISPAGE_H
