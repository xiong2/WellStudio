#ifndef X2DSEISMICSECTIONVISPAGE_H
#define X2DSEISMICSECTIONVISPAGE_H

#include "ui_x2dseismiclinevispage.h"
#include "xbasepropertypage.h"
#include "xviewinfo2dseismicline.h"

class CX2DSeismicLineVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CX2DSeismicLineVisPage(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CX2DSeismicLineVisPage();

	virtual void Apply() override;

private:
	void _Init();
	void _InitData();
	void _InitNameFontSize();

	Ui::CX2DSeismicLineVisPage m_ui;
	CXViewInfo2DSeismicLine* m_pViewInfo;
};

#endif // KE2DSEISMICSECTIONVISPAGE_H
