#ifndef XWIZARDBUILDLFM_H
#define XWIZARDBUILDLFM_H

#include <QWizard>
#include "xguiplus_global.h"

class CXBaseParameter;
class CXObject;

/**
*	@class	 CXWizardBuildLFM in the file "kewizardbuildlfm.h"
*	@brief	 The class provide a wizard to create framework of low frequency model
*	@author	Yong Shu
*	@date	 11/17/2015
*/
class XGUIPLUS_EXPORT CXWizardBuildLFM : public QWizard
{
	Q_OBJECT

public:
	///@brief Constructor and destructor
	CXWizardBuildLFM(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardBuildLFM();

private slots:
	void slotPageChanged(int);
};

#endif // KEWIZARDBUILDLFM_H
