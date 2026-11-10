#pragma once

#include "xgui_global.h"
#include "xbasepropertypage.h"
#include "ui_gsbmrosediagramvispage.h"

class CXViewInfoObject;
class GSRoseDiagramViewInfo;

class XGUI_EXPORT GSBMRoseDiagramVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	GSBMRoseDiagramVisPage(CXViewInfoObject *, QWidget * parent = Q_NULLPTR);
	~GSBMRoseDiagramVisPage();

	void Apply() override;

private:
	Ui::GSBMRoseDiagramVisPage ui;

	GSRoseDiagramViewInfo*	m_pViewInfo;
};
