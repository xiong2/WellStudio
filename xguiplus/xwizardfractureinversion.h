#ifndef XWIZARDFRACTUREINVERSION_H
#define XWIZARDFRACTUREINVERSION_H


#include <QWizard>
#include "xguiplus_global.h"

class CXBaseParameter;
class CXObject;
class CXParameter3TermInversion;

/**
*	@class	 CXWizardFractureInversion in the file "kewizardfractureinversion.h"
*	@brief	 The class provide a wizard for facture inversion
*	@author	Yong Shu
*	@date	 12/19/2016
*/
class XGUIPLUS_EXPORT CXWizardFractureInversion : public QWizard
{
	Q_OBJECT

public:
	///@brief CXWizardFractureAVO and destructor
	CXWizardFractureInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardFractureInversion();

	private slots:
	void slotPageChanged(int);

private:
	CXParameter3TermInversion* m_pPara;
};


#endif // KEWIZARDFRACTUREINVERSION_H
