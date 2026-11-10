#ifndef GSSECSECTIONVISPAGE_H
#define GSSECSECTIONVISPAGE_H

#include "xgui_global.h"
#include "xbasepropertypage.h"
#include "ui_gssecsectionvispage.h"

class GSSectionViewInfo;
class CXViewInfoObject;

class XGUI_EXPORT GSSecSectionVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	GSSecSectionVisPage(CXViewInfoObject* pViewInfo, QWidget *parent = 0);
	~GSSecSectionVisPage();

	void Apply() override;

private:
	Ui::GSSecSectionVisPage ui;
	GSSectionViewInfo* m_pViewInfo = nullptr;
};

#endif // GSBMSECTIONVISPAGE_H