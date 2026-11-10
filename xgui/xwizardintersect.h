#ifndef XWIZARDINTERSECT_H
#define XWIZARDINTERSECT_H

#include <QWizard>
#include "xgui_global.h"

///@brief	a framework for wizards to calculate intersection between well and 3-D surface
///@author	pezy
///@date	Jun. 9th, 2014
///@see	

class CXBaseParameter;
class CXObject;

class XGUI_EXPORT CXWizardIntersect : public QWizard
{
	Q_OBJECT

public:
	CXWizardIntersect(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent=NULL);
	~CXWizardIntersect();

private slots:
	void slotPageChanged(int pageIndex);
	
};

#endif // RLWIZARDINTERSECT_H
