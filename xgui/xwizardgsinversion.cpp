#include "xwizardgsinversion.h"
#include "xprocessfactory.h"
#include "xparametersgsinversion.h"
#include "xpagegsinversion1.h"
#include "xpagegsinversion2.h"
#include "xobject.h"

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardGSInversion)
EGSInversion
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardGSInversion)

CXWizardGSInversion::CXWizardGSInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent) : QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWizardStyle(QWizard::ClassicStyle);

	CXParametersGSInversion *pGSIPara = dynamic_cast<CXParametersGSInversion*>(pPara);
	pGSIPara->SetSMID(pParentObj->GetObjectID());
	CXPageGSInversion1 *pPage0 = new CXPageGSInversion1(pGSIPara);
	CXPageGSInversion2 *pPage1 = new CXPageGSInversion2(pGSIPara);

	this->setPage(0, pPage0);
	this->setPage(1, pPage1);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	this->setMinimumSize(980, 500);
}

CXWizardGSInversion::~CXWizardGSInversion()
{

}

void CXWizardGSInversion::slotPageChanged(int iPageID)
{
	switch (iPageID)
	{
	case -1:
		emit close();
		break;
	case 0:
		setWindowTitle("Defining structrue model and wells - Step 1 of 2");
		break;
	case 1:
		setWindowTitle("Adjusting Pdf/Value - Step 2 of 2");
		break;
	default:
		break;
	}
}