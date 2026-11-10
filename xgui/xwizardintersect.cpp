#pragma warning (push, 0)
#include "xwizardintersect.h"

#include <assert.h>

#include "xparameterwellhorzionintersect.h"
#include "xwelltops.h"
#include "xglobal.h"
#include "xprocessfactory.h"

#include "xpageselectformation.h"
#include "xpageselectrock.h"
#pragma warning pop

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardIntersect)
EWellHorizonIntersect
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardIntersect)

CXWizardIntersect::CXWizardIntersect(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWizardStyle(QWizard::ClassicStyle);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameterWellHorzionIntersect *pParaWellHorzionIntersect = dynamic_cast<CXParameterWellHorzionIntersect*>(pPara);
	assert(pParaWellHorzionIntersect);

	CXPageSelectFormation *pPageSelectFormation = new CXPageSelectFormation(pParaWellHorzionIntersect);
	CXPageSelectRock *pPageSelectRock = new CXPageSelectRock(pParaWellHorzionIntersect);

	this->setPage(0, pPageSelectFormation);
	this->setPage(1, pPageSelectRock);

	this->setMinimumSize(600, 500);
}

CXWizardIntersect::~CXWizardIntersect()
{

}

void CXWizardIntersect::slotPageChanged(int pageIndex)
{
	switch (pageIndex)
	{
	case -1:
		emit close();
		break;
	case 0:
		setWindowTitle(GetTr("Intersect well profile with 3-D horizon - Step 1 of 2"));
		break;
	case 1:
		setWindowTitle(GetTr("Intersect well profile with 3-D horizon - Step 2 of 2"));
		break;	
	default:
		assert(!"can not reach this page.");
	}
}