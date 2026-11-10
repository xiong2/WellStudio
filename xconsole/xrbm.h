#ifndef XRBM_H
#define XRBM_H

#include "xconsole_global.h"
#include <qobject.h>
#include "xobjecttype.h"

class QMenu;
class CXObject;

class XCONSOLE_EXPORT CXRBM : public QObject
{
	Q_OBJECT

public:
	CXRBM(QMenu& menu, CXObject* pObj);
	~CXRBM();

	void AddAction();
	void AddDeleteAction();

public slots:
	void slotSpreadsheet();
	void slotCalculator();
	void slotImport();
	void slotExport();

	void slotWireframe();
	void slotTraceBPolygons();

	void slotFilter();
	void slotIntegration();
	void slotBiot();
	void slotSh();

	void slotTDCalculate();
	void slotWellTie();

	void slotDelete();
	void slotDeleteContent();
	void slotRename();
	void slotProperties();

	void slotCreateSection();
	void slotCreateFlatHorizon();

	void slotWellCondition();
	void slotWellConditionUpscale();

	void slotExtractFaultPillars();
	void slotAutoConnectFaults();

	void slotRoseDiagram();

	void slotGeneral();

	// general slots for workflow
	void slotCalculateModal();
	void slotCalculateNonModal();
	void slotCalculateOnly();

	void slotShowDebugInfo();
	void slotShowInSectionWindow();

	void slotCalSurfaceSlope();

	void slotRemovefp();

private:
	void _AddDefaultAction();
	void _DeleteObj(CXObject* pObj);

	void slotMakeFaultSticksAccordingToSurvey();

private:
	QMenu& m_menu;

	CXObject* m_pObject;
};

#endif // RLRBM_H
