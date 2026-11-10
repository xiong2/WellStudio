#ifndef CXDLGKRIGINGINTERPOLATION_H_H
#define CXDLGKRIGINGINTERPOLATION_H_H
#include "xbasedialog.h"

#include "ui_xdlgkriginginterpolation.h"

class CXObject;
class CXBaseParameter;
class CXParameterMakeRevInterpolation;

class CXDlgKrigingInterpolation:public CXBaseDialog
{
	Q_OBJECT
public:
	CXDlgKrigingInterpolation(CXBaseParameter *pPara ,CXObject* pObj,QWidget *parent);
	~CXDlgKrigingInterpolation();

	void InitDlg();
	virtual void  OnOK();
public slots:
	void slotShowParameter(int selectedIndex);
private:

	Ui::CXKrigingInterpolationDialog m_ui;
	CXObject *m_pObj;
	CXParameterMakeRevInterpolation *m_pPara;
};


#endif