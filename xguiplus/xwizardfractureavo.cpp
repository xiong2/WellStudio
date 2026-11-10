#pragma warning (push, 0)
#include "xwizardfractureavo.h"
#include <assert.h>
#include "xpagefractureavoone.h"
#include "xpagefractureavotwo.h"
#include "xparameterfractureavo.h"
#include "xglobal.h"
#include "xprocessfactory.h"
#include "xseismicdatavolume.h"

#pragma warning pop


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardFractureAVO)
EFractureAnalysisAVO
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardFractureAVO)

CXWizardFractureAVO::CXWizardFractureAVO(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameterFractureAVO* pFracPara = dynamic_cast<CXParameterFractureAVO*>(pPara);
	assert(pFracPara);
	m_pPara = pFracPara;

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (pDV && pDV->IsAzimuth())
	{		
		pFracPara->SetAzimuthDVID(pDV->GetObjectID());
	}
	else
	{
		QWizardPage* pPageOne = new CXPageFractureAVOOne(pFracPara);
		setPage(1, pPageOne);
	}
	
	QWizardPage* pPageTwo = new CXPageFractureAVOTwo(pFracPara);
	
	setPage(2, pPageTwo);

	setWizardStyle(QWizard::ModernStyle);
	resize(700, 450);
}

CXWizardFractureAVO::~CXWizardFractureAVO()
{

}

void CXWizardFractureAVO::slotPageChanged(int index)
{
	QString strPreName = "AVAz Analysis : ";
	QString strWindowTitle;
	switch (index)
	{
	case 1:
		strWindowTitle = strPreName + "Seismic Data";
		break;
	case 2:
		strWindowTitle = strPreName + "Parameters and Range";
		break;
	default:
		break;
	}

	this->setWindowTitle(strWindowTitle);
}
