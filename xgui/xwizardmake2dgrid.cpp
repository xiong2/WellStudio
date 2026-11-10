#pragma warning (push, 0)
#include "xwizardmake2dgrid.h"

#include <assert.h>

#include "xparametermake2dgrid.h"
#include "xwelltops.h"
#include "xglobal.h"
#include "xpageselectwelltopsformation.h"
#include "xpageedit2dgrid.h"
#include "xpageinterpolation.h"
#include "xprocessfactory.h"

#pragma warning pop

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardMake2DGrid)
EMake2DGRid
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXWizardMake2DGrid)


CXWizardMake2DGrid::CXWizardMake2DGrid(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QWizard(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWizardStyle(QWizard::ClassicStyle);

	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(slotPageChanged(int)));

	CXParameterMake2DGrid *pParaMake2dGrid = dynamic_cast<CXParameterMake2DGrid*>(pPara);
	assert(pParaMake2dGrid && pParentObj);

	CXWellTops *pWellTops = dynamic_cast<CXWellTops*>(pParentObj);
	if (pWellTops)
	{
		CXPageSelectWellTopsFormation *pWellTopsPage = new CXPageSelectWellTopsFormation(pParaMake2dGrid, pParentObj);
		CXPageEdit2DGrid *pEdit2DGrid = new CXPageEdit2DGrid(pParaMake2dGrid, pParentObj);
		CXPageInterpolation *pInterpolation = new CXPageInterpolation(pParaMake2dGrid, pParentObj);

		this->setPage(0, pWellTopsPage);
		this->setPage(1, pEdit2DGrid);
		this->setPage(2, pInterpolation);
	}
	else
	{
		pParaMake2dGrid->SetHorizonNameList(QStringList(pParentObj->GetObjectName()));
		CXPageEdit2DGrid *pEdit2DGrid = new CXPageEdit2DGrid(pParaMake2dGrid, pParentObj);
		CXPageInterpolation *pInterpolation = new CXPageInterpolation(pParaMake2dGrid, pParentObj);

		this->setPage(0, pEdit2DGrid);
		this->setPage(1, pInterpolation);
	}
	

	this->setMinimumSize(600, 500);
}

CXWizardMake2DGrid::~CXWizardMake2DGrid()
{
}

void CXWizardMake2DGrid::slotPageChanged(int pageIndex)
{
	switch (pageIndex)
	{
	case -1:
		emit close();
		break;
	case 0:
		if(::UsingChinese())
			setWindowTitle(GetTr("制作2D网格: 选择层位数据 - 步骤1/3"));
		else
			setWindowTitle(GetTr("Make 2D Grid: Select Formation - Step 1 of 4"));
		break;
	case 1:
		if(::UsingChinese())
			setWindowTitle(GetTr("制作2D网格: 调整网格范围 - 步骤2/3"));
		else
			setWindowTitle(GetTr("Make 2D Grid: Edit Grid Geometry - Step 3 of 4"));
		break;
	case 2:
		if(::UsingChinese())
			setWindowTitle(GetTr("制作2D网格: 选择插值方法 - 步骤3/3"));
		else
			setWindowTitle(GetTr("Make 2D Grid: Select Interpolation Method  - Step 4 of 4"));
		break;
	default:
		assert(!"can not reach this page.");
	}
}

