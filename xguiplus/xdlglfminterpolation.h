#ifndef XDLGLFMINTERPOLATION_H
#define XDLGLFMINTERPOLATION_H


#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlglfinterpolation.h"

class CXBaseParameter;
class CXObject;
class CXParameterLFMInterpolation;
class CXLFMGeometry;

/**
*	@class	 CXDlgLFMInterpolation in the file "kedlglfminterpolation.h"
*	@brief	 The class provide a wizard to build low frequency model
*	@author	Yong Shu
*	@date	 11/26/2015
*/

class XGUIPLUS_EXPORT CXDlgLFMInterpolation : public QDialog
{
	Q_OBJECT

public:
	CXDlgLFMInterpolation(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXDlgLFMInterpolation();

	virtual void accept();

private slots:
	void slotMethod(int);

	void slotPower();
	void slotSampleNum();
	void slotRadius();

	void slotSill();
	void slotNugget();
	void slotMajorRange();
	void slotMinorRange();
	void slotAzimuth();

private:
	void _Init();


private:
	Ui::DlgLFMInterpolation m_ui;

	CXParameterLFMInterpolation* m_pPara;

	CXLFMGeometry* m_pLFM;
};

#endif // KEDLGLFMINTERPOLATION_H
