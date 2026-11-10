#pragma warning (push, 0)
#include "xwizardfractureinversion.h"
#include <assert.h>
#include "xpage3termavoinversiontwo.h"
#include "xpage3termavoinversionthree.h"
#include "xpagefractureinversion.h"
#include "xparameter3terminversion.h"
#include "xglobal.h"
#include "xprocessfactory.h"
#include "xseismicdatavolume.h"

#pragma warning pop


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardFractureInversion)
EAnisotropyInversion
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardFractureInversion)

CXWizardFractureInversion::CXWizardFractureInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameter3TermInversion* pFracInv = dynamic_cast<CXParameter3TermInversion*>(pPara);
	assert(pFracInv);
	m_pPara = pFracInv;

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (pDV && pDV->IsIrregular() && pDV->IsAzimuth())
	{
		m_pPara->SetPrestackDVID(pDV->GetObjectID());
	}

	QWizardPage* pPage1 = new CXPageFractureInversion(m_pPara);
	QWizardPage* pPage2 = new CXPage3TermAVOInversionTwo(m_pPara);
	QWizardPage* pPage3 = new CXPage3TermAVOInversionThree(m_pPara);

	setPage(1, pPage1);
	setPage(2, pPage2);
	setPage(3, pPage3);

	setWizardStyle(QWizard::ModernStyle);
	resize(700, 600);
}

CXWizardFractureInversion::~CXWizardFractureInversion()
{

}

void CXWizardFractureInversion::slotPageChanged(int index)
{
	QString strPreName = "Seismic Anisotropy Inversion : ";
	QString strWindowTitle;
	switch (index)
	{
	case 1:
		strWindowTitle = strPreName + "Azimuth, Incidence Angle and Wavelets";
		break;
	case 2:
		strWindowTitle = strPreName + "Impedance Volumes and Parameters";
		break;
	case 3:
		strWindowTitle = strPreName + "Data Range and Output Options";
		break;
	default:
		break;
	}

	this->setWindowTitle(strWindowTitle);
}

