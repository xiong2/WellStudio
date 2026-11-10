#pragma warning (push, 0)
#include "xwizardbuildlfm.h"
#include <assert.h>
#include "xpagebuildlfmone.h"
#include "xpagebuildlfmtwo.h"
#include "xpagebuildlfmthree.h"
#include "xparameterbuildlfm.h"
#include "xglobal.h"
#include "xprocessfactory.h"

#pragma warning pop


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardBuildLFM)
EBuildLowFreuqencyModel
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardBuildLFM)

CXWizardBuildLFM::CXWizardBuildLFM(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameterBuildLFM* pLFMPara = dynamic_cast<CXParameterBuildLFM*>(pPara);
	assert(pPara);

	CXPageBuildLFMOne* pPageOne = new CXPageBuildLFMOne(pLFMPara);
	CXPageBuildLFMTwo* pPageTwo = new CXPageBuildLFMTwo(pLFMPara);
	CXPageBuildLFMThree* pPageThree = new CXPageBuildLFMThree(pLFMPara);

	setPage(1, pPageOne);
	setPage(2, pPageTwo);
	setPage(3, pPageThree);

	setWizardStyle(QWizard::ModernStyle);
	resize(640, 420);
}

CXWizardBuildLFM::~CXWizardBuildLFM()
{

}

void CXWizardBuildLFM::slotPageChanged(int index)
{
	QString strWindowTitle;
	switch (index)
	{
	case 1:
		strWindowTitle = "Build Framework of Low Frequency Model: Select 3-D Horizons";
		break;
	case 2:
		strWindowTitle = "Build Framework of Low Frequency Model: Set Data Range";
		break;
	case 3:
		strWindowTitle = "Build Framework of Low Frequency Model: Choose Parameters";
		break;
	default:
		break;		
	}

	this->setWindowTitle(strWindowTitle);
}
