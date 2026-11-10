#ifndef XPARAPAGEAVOCSSINVERSION_H
#define XPARAPAGEAVOCSSINVERSION_H

#include <QWidget>
#include "xguiplus_global.h"
#include "ui_xparapageavoinversion.h"

class CXBaseParameter;
class CXObject;
class CXParameter3TermInversion;

/**
*	@class	 CXParaPageAVOCSSInversion in the file "keparapageavocssinversion.h"
*	@brief	 The class provide a parameter page
*	@author	Yong Shu
*	@date	 5/4/2016
*/

class XGUIPLUS_EXPORT CXParaPageAVOCSSInversion : public QWidget
{
	Q_OBJECT
public:
	CXParaPageAVOCSSInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget* parent=NULL);
	~CXParaPageAVOCSSInversion();

private:
	void _Init();

private:
	Ui::ParaPageAvoInversion m_ui;

	CXParameter3TermInversion* m_pPara;

	CXObject* m_pObject;
	
};

#endif // KEPARAPAGEAVOCSSINVERSION_H
