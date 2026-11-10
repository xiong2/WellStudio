#pragma warning (push, 0)
#include "xwizard3termavoinversion.h"
#include <assert.h>
#include "xpage3termavoinversionone.h"
#include "xpage3termavoinversiononeext.h"
#include "xpage3termavoinversiontwo.h"
#include "xpage3termavoinversionthree.h"
#include "xparameter3terminversion.h"
#include "xglobal.h"
#include "xprocessfactory.h"
#include "xseismicdatavolume.h"

#pragma warning pop


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizard3TermAvoInversion)
EAVOInversion,
EAVOSSInversion
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizard3TermAvoInversion)

CXWizard3TermAvoInversion::CXWizard3TermAvoInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameter3TermInversion* pInversionPara = dynamic_cast<CXParameter3TermInversion*>(pPara);
	assert(pInversionPara);
	m_pPara = pInversionPara;

	QWizardPage* pPageOne = NULL;
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (pDV && pDV->IsPrestack())
	{
		pPageOne = new CXPage3TermAVOInversionOne(pInversionPara);
	}
	else
	{
		pPageOne = new CXPage3TermAVOInversionOneExt(pInversionPara);
	}


	CXPage3TermAVOInversionTwo* pPageTwo = new CXPage3TermAVOInversionTwo(pInversionPara);
	CXPage3TermAVOInversionThree* pPageThree = new CXPage3TermAVOInversionThree(pInversionPara);

	setPage(1, pPageOne);
	setPage(2, pPageTwo);
	setPage(3, pPageThree);

	setWizardStyle(QWizard::ModernStyle);
	resize(700, 450);
}

CXWizard3TermAvoInversion::~CXWizard3TermAvoInversion()
{

}

void CXWizard3TermAvoInversion::slotPageChanged(int index)
{
	QString strPreName;
	if (m_pPara->GetObjectType() == EAVOSSInversion)
		strPreName = "Prestack AVO Sparse Spike Inversion : ";
	else
		strPreName = "Prestack AVO Inversion : ";

	QString strWindowTitle;
	switch (index)
	{
	case 1:
		strWindowTitle = strPreName + "Seismic Data and Wavelets";
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
