#ifndef XWIZARDCSSINVERSION_H
#define XWIZARDCSSINVERSION_H

#include <QWizard>
#include "xguiplus_global.h"

class CXBaseParameter;
class CXObject;

/**
*	@class	 CXWizardCSSInversion in the file "kewizardcssinversion.h"
*	@brief	 The class provide a wizard to make
*	@author	Yong Shu
*	@date	 1/15/2016
*/
class XGUIPLUS_EXPORT CXWizardCSSInversion : public QWizard
{
	Q_OBJECT

public:
	///@brief Constructor and destructor
	CXWizardCSSInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardCSSInversion();

	private slots:
	void slotPageChanged(int);
};

#endif // KEWIZARDCSSINVERSION_H
