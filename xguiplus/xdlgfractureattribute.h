#ifndef XDLGFRACTUREATTRIBUTE_H
#define XDLGFRACTUREATTRIBUTE_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgfractureattribute.h"

class CXBaseParameter;
class CXObject;
class CXParameterFractureAttribute;
class CXSeismicDataVolume;

/**
*	@class	 CXDlgFractureAttribute in the file "kedlgfractureattribute.h"
*	@brief	 The class provide a dialog for fracture attribute
*	@author	Yong Shu
*	@date	 12/28/2016
*/

class XGUIPLUS_EXPORT CXDlgFractureAttribute : public QDialog
{
	Q_OBJECT

public:
	CXDlgFractureAttribute(CXBaseParameter* pPara, CXObject* pParentObj = NULL, QWidget *parent = NULL);
	~CXDlgFractureAttribute();

	virtual void accept();

private:
	void _Init();
	void _SetDV(CXSeismicDataVolume* pDV);
	void _SetRange();

private slots:
	void slotSelectDV();
	void slotSelectLFM();
	void slotSelectFilter();


private:
	Ui::DlgFractureAttribute m_ui;

	CXParameterFractureAttribute* m_pPara;

	CXSeismicDataVolume* m_pDV;
};

#endif // KEDLGFRACTUREATTRIBUTE_H
