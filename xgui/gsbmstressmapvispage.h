#ifndef GSPAGEBMVISSTRESSMAP_H
#define GSPAGEBMVISSTRESSMAP_H

#include "xgui_global.h"
#include "xbasepropertypage.h"
#include "ui_gsbmstressmapvispage.h"

class CXViewInfoObject;
class GSStressMapViewInfo;

class XGUI_EXPORT GSBMStressMapVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	GSBMStressMapVisPage(CXViewInfoObject* pViewInfo, QWidget *parent = 0);
	~GSBMStressMapVisPage();

	virtual void Apply() override;

private:
	Ui::GSBMStressMapVisPage ui;
	GSStressMapViewInfo* m_pViewInfo = nullptr;
};

#endif // GSPAGEBMVISSTRESSMAP_H
