#include "xpagegsinversion2.h"
#include "xparametersgsinversion.h"

CXPageGSInversion2::CXPageGSInversion2(CXParametersGSInversion *pPara, QWidget *parent)
	: QWizardPage(parent)
{
	ui.setupUi(this);
	m_pPara = pPara;

	initGUI();
}

CXPageGSInversion2::~CXPageGSInversion2()
{

}

void CXPageGSInversion2::initGUI()
{
}
