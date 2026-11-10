#pragma warning (push,0)
#include "xguiplusutil.h"

#include "xseismicdatavolume.h"
#include "xdlgremovefootprint.h"
#include "xparameterremovefootprint.h"
#include "xglobal.h"
#include "xbaseconsole.h"

#pragma warning(pop)


void NGuiPlusUtil::RemoveFootprint(CXSeismicDataVolume* pDV)
{
	if (!pDV)
		return;

	auto para = new CXParameterRemoveFootprint;

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	auto pdlg = new CXDlgRemoveFootprint(para, pDV, pParentWidget);
	pdlg->show();
}