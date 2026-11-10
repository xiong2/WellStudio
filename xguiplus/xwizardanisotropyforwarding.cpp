#pragma warning (push, 0)
#include "xwizardanisotropyforwarding.h"
#include "xparameteranisotropyforwarding.h"
#include "xpageseismicforwardingone.h"
#include "xpageseismicforwardingtwo.h"
#include "xpageseismicforwardingthree.h"
#include "xglobal.h"
#include "xprocessfactory.h"
#include <cassert>

#pragma warning pop


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardAnisotropyForwarding)
EAnisotrpicForwarding
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardAnisotropyForwarding)

CXWizardAnisotropyForwarding::CXWizardAnisotropyForwarding(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameterAnisotropyForwarding* pForwardingPara = dynamic_cast<CXParameterAnisotropyForwarding*>(pPara);
	assert(pForwardingPara);

	CXPageSeismicForwardingOne* pPageOne = new CXPageSeismicForwardingOne(pForwardingPara);
	CXPageSeismicForwardingTwo* pPageTwo = new CXPageSeismicForwardingTwo(pForwardingPara);
	CXPageSeismicForwardingThree* pPageThree = new CXPageSeismicForwardingThree(pForwardingPara);

	setPage(1, pPageOne);
	setPage(2, pPageTwo);
	setPage(3, pPageThree);

	setWizardStyle(QWizard::ModernStyle);
	resize(740, 450);
}

CXWizardAnisotropyForwarding::~CXWizardAnisotropyForwarding()
{

}

void CXWizardAnisotropyForwarding::slotPageChanged(int index)
{
	QString strWindowTitle;
	switch (index)
	{
	case 1:
		strWindowTitle = "Anisotropy Forwarding: Select Data Volumes and Angles";
		break;
	case 2:
		strWindowTitle = "Anisotropy Forwarding: Select Wavelets";
		break;
	case 3:
		strWindowTitle = "Anisotropy Forwarding: Set Output Range";
		break;
	default:
		break;
	}

	this->setWindowTitle(strWindowTitle);
}
