#ifndef XWIZARD3TERMAVOINVERSION_H
#define XWIZARD3TERMAVOINVERSION_H


#include <QWizard>
#include "xguiplus_global.h"

class CXBaseParameter;
class CXObject;
class CXParameter3TermInversion;

/**
*	@class	 CXWizard3TermAvoInversion in the file "kewizard3termavoinversion.h"
*	@brief	 The class provide a wizard to make 
*	@author	Yong Shu
*	@date	 12/14/2015
*/
class XGUIPLUS_EXPORT CXWizard3TermAvoInversion : public QWizard
{
	Q_OBJECT

public:
	///@brief Constructor and destructor
	CXWizard3TermAvoInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizard3TermAvoInversion();

private slots:
	void slotPageChanged(int);

private:
	CXParameter3TermInversion* m_pPara;
};


#endif // KEWIZARD3TERMAVOINVERSION_H
