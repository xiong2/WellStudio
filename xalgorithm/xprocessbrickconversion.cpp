#pragma warning( push ,0 )
#include "xprocessbrickconversion.h"
#include "xthreadtracetobrick.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "xseismicdatavolume.h"
#pragma warning( pop )

BEGIN_REGISTER_PROCESS_TO_FACTORY(CGmProcessBrickConversion)
ETraceToBrick
END_REGISTER_RPOCESS_TO_FACTORY(CGmProcessBrickConversion)


CGmProcessBrickConversion::CGmProcessBrickConversion()
{
}

CGmProcessBrickConversion::~CGmProcessBrickConversion()
{
}

void CGmProcessBrickConversion::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (!pDV)
		return;

	m_pThread = new CXThreadTraceToBrick(pDV);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CGmProcessBrickConversion::slotFinishedComputing()
{
	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}
