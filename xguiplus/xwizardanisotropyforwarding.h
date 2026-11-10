#ifndef XWIZARDANISOTROPYFORWARDING_H
#define XWIZARDANISOTROPYFORWARDING_H

#include <QWizard>
#include "xguiplus_global.h"

class CXBaseParameter;
class CXObject;

/**
*	@class	 CXWizardAnisotropyForwarding in the file "kewizardanisotropyforwarding.h"
*	@brief	 The class provide a wizard for seismic anisotropy forwarding
*	@author	Yong Shu
*	@date	 1/9/2017
*/
class XGUIPLUS_EXPORT CXWizardAnisotropyForwarding : public QWizard
{
	Q_OBJECT

public:
	///@brief Constructor and destructor
	CXWizardAnisotropyForwarding(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardAnisotropyForwarding();

private slots:
	void slotPageChanged(int);
};

#endif // KEWIZARDANISOTROPYFORWARDING_H
