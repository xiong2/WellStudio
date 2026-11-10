#ifndef XDLGEXTRACTHORIZONATT_H
#define XDLGEXTRACTHORIZONATT_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgextracthorizonatt.h"

using std::vector;

class CXBaseParameter;
class CXObject;
class CXParameterExtractHorizonAtt;
class CX3DHorizon;

/**
*	@class	 CXDlgExtractHorizonAtt in the file "kedlgextracthorizonatt.h"
*	@brief	 The class provide a dialog for extracting horizon attributes
*	@author	Yong Shu
*	@date	 9/28/2016
*/

class XGUIPLUS_EXPORT CXDlgExtractHorizonAtt : public QDialog
{
	Q_OBJECT

public:
	CXDlgExtractHorizonAtt(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXDlgExtractHorizonAtt();

	virtual void accept();

private slots:
	void slotAddDV();
	void slotRemoveDV();
	void slotMethodChange(int);


private:
	void _Init();
	void _Calc();
	void _CalcMinMax(int& zMin, int& zMax);

private:
	Ui::DlgExtractHorizonAtt m_ui;

	CXParameterExtractHorizonAtt* m_pPara;

	CX3DHorizon* m_p3DHorizon;
};


#endif // KEDLGEXTRACTHORIZONATT_H
