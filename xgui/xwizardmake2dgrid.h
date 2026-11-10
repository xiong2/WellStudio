#ifndef XWIZARDMAKE2DGRID_H
#define XWIZARDMAKE2DGRID_H

#include <QWizard>
#include "xgui_global.h"

///@brief	a framework for wizards to make 2D grid
///@author	pezy
///@date	May. 19th, 2014
///@see	

class CXBaseParameter;
class CXObject;

class XGUI_EXPORT CXWizardMake2DGrid : public QWizard
{
	Q_OBJECT

public:
	CXWizardMake2DGrid(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardMake2DGrid();

private slots:
	void slotPageChanged(int pageIndex);
	
};

#endif // RLWIZARDMAKE2DGRID_H
