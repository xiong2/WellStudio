#ifndef XWIZARDFRACTUREAVO_H
#define XWIZARDFRACTUREAVO_H

#include <QWizard>
#include "xguiplus_global.h"

class CXBaseParameter;
class CXObject;
class CXParameterFractureAVO;

/**
*	@class	 CXWizardFractureAVO in the file "kewizardfractureavo.h"
*	@brief	 The class provide a wizard for AVO fracture analysis
*	@author	Yong Shu
*	@date	 9/26/2016
*/
class XGUIPLUS_EXPORT CXWizardFractureAVO : public QWizard
{
	Q_OBJECT

public:
	///@brief CXWizardFractureAVO and destructor
	CXWizardFractureAVO(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardFractureAVO();

	private slots:
	void slotPageChanged(int);

private:
	CXParameterFractureAVO* m_pPara;
};


#endif // KEWIZARDFRACTUREAVO_H
