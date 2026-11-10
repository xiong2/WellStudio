#ifndef GSBMSECTIONVISPAGE_H
#define GSBMSECTIONVISPAGE_H

#include "xgui_global.h"
#include "xbasepropertypage.h"
#include "ui_gsbmsectionvispage.h"

class GSSectionViewInfo;
class CXViewInfoObject;

class XGUI_EXPORT GSBMSectionVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	GSBMSectionVisPage(CXViewInfoObject* pViewInfo, QWidget *parent = 0);
	~GSBMSectionVisPage();

	void Apply() override;

private:
	Ui::GSBMSectionVisPage ui;
	GSSectionViewInfo* m_pViewInfo = nullptr;
};

#endif // GSBMSECTIONVISPAGE_H
