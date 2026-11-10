#ifndef XDLGPCAFILTERING_H
#define XDLGPCAFILTERING_H


#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgpcalfiltering.h"

class CXBaseParameter;
class CXObject;
class CXParameterPCAFiltering;
class CXSeismicDataVolume;

/**
*	@class	 CXDlgPCAFiltering in the file "kedlgpcafiltering.h"
*	@brief	 The class provide a wizard for PCA filtering
*	@author	Yong Shu
*	@date	 6/8/2016
*/

class XGUIPLUS_EXPORT CXDlgPCAFiltering : public QDialog
{
	Q_OBJECT

public:
	CXDlgPCAFiltering(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXDlgPCAFiltering();

private slots:

	virtual void accept();

private:
	void _Init();

private:
	Ui::DlgPCAFiltering m_ui;

	CXParameterPCAFiltering* m_pPara;

	CXSeismicDataVolume* m_pDV;
};

#endif // KEDLGPCAFILTERING_H
