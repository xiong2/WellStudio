#ifndef XDLGSEISMICFILTERING_H
#define XDLGSEISMICFILTERING_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgseismicfiltering.h"

class CXBaseParameter;
class CXObject;
class CXParameterSeismicFiltering;
class QButtonGroup;

/**
*	@class	 CXDlgSeismicFiltering in the file "kedlgseismicfiltering.h"
*	@brief	 The class provide a wizard for seismic filtering
*	@author	Yong Shu
*	@date	 5/18/2016
*/

class XGUIPLUS_EXPORT CXDlgSeismicFiltering : public QDialog
{
	Q_OBJECT

public:
	CXDlgSeismicFiltering(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXDlgSeismicFiltering();

	virtual void accept();

private slots:
	void slotFilteringMethod(int);

private:
	void _SetWidget(bool bShowLow, bool bShowHigh);

private:
	Ui::DlgSeismicFiltering m_ui;

	CXParameterSeismicFiltering* m_pPara;

	QButtonGroup* m_PBottonGroup;
};

#endif // KEDLGSEISMICFILTERING_H
