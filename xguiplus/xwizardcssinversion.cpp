#pragma warning (push, 0)
#include "xwizardcssinversion.h"
#include <assert.h>
#include "xpagecssinversionone.h"
#include "xpagecssinversiontwo.h"
#include "xparametercssinversion.h"
#include "xglobal.h"
#include "xprocessfactory.h"
#include "xseismicdatavolume.h"

#pragma warning pop


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardCSSInversion)
ECSSInversion
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardCSSInversion)

CXWizardCSSInversion::CXWizardCSSInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameterCSSInversion* pInversionPara = dynamic_cast<CXParameterCSSInversion*>(pPara);
	assert(pInversionPara);

	QWizardPage* pPageOne = new CXPageCSSInversionOne(pInversionPara);
	QWizardPage* pPageTwo = new CXPageCSSInversionTwo(pInversionPara);

	setPage(1, pPageOne);
	setPage(2, pPageTwo);

	setWizardStyle(QWizard::ModernStyle);
	resize(700, 450);
}

CXWizardCSSInversion::~CXWizardCSSInversion()
{

}

void CXWizardCSSInversion::slotPageChanged(int index)
{
	QString strWindowTitle;
	switch (index)
	{
	case 1:
		strWindowTitle = "Constrained Sparse-Spike Inversion: Seismic Data and Wavelets";
		break;
	case 2:
		strWindowTitle = "Constrained Sparse-Spike Inversion: Data Range";
		break;
	default:
		break;
	}

	this->setWindowTitle(strWindowTitle);
}

