#ifndef XDLGAVOCSSIADVANCED_H
#define XDLGAVOCSSIADVANCED_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgavocssiadvanced.h"

class CXBaseParameter;
class CXObject;
class CXParameter3TermInversion;

/**
*	@class	 CXDlgAVOCSSIAdvanced in the file "kedlgavocssiadvanced.h"
*	@brief	 The class provide a dialog for avo cssi advanced settings
*	@author	Yong Shu
*	@date	 6/15/2016
*/

class XGUIPLUS_EXPORT CXDlgAVOCSSIAdvanced : public QDialog
{
	Q_OBJECT

public:
	CXDlgAVOCSSIAdvanced(CXBaseParameter* pPara, CXObject* pParentObj=NULL, QWidget *parent = NULL);
	~CXDlgAVOCSSIAdvanced();

	virtual void accept();

private:
	void _Init();
	void _InitAngle();

private:
	Ui::DlgAVOCSSIAdvanced m_ui;

	CXParameter3TermInversion* m_pPara;
};

#endif // KEDLGAVOCSSIADVANCED_H
