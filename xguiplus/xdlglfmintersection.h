#ifndef XDLGLFMINTERSECTION_H
#define XDLGLFMINTERSECTION_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlglfmintersection.h"

class CXBaseParameter;
class CXObject;
class CXParameterLFMIntersecton;
class CXLFMGeometry;

/**
*	@class	 CXDlgLFMIntersection in the file "kedlglfmintersection.h"
*	@brief	 The class provide a wizard to build the upscaling geometry
*	@author	Yong Shu
*	@date	 11/17/2015
*/

class XGUIPLUS_EXPORT CXDlgLFMIntersection : public QDialog
{
	Q_OBJECT

public:
	CXDlgLFMIntersection(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent=NULL);
	~CXDlgLFMIntersection();

	virtual void accept();

private:
	void _Init();

private slots:
	void slotAddAll();
	void slotRemoveAll();

private:
	Ui::CXDlgLFMIntersection m_ui;

	CXParameterLFMIntersecton* m_pPara;

	CXLFMGeometry* m_pLFM;
};

#endif // KEDLGLFMINTERSECTION_H
