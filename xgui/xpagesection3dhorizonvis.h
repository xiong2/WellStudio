#ifndef XPAGESECTION3DHORIZONVIS_H
#define XPAGESECTION3DHORIZONVIS_H

#include "xbasepropertypage.h"
#include "ui_xpagesection3dhorizonvis.h"

class CXViewInfo3DHorizon;
class CXViewInfoObject;
class CXPageSection3DHorizonVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageSection3DHorizonVis(QWidget *parent, CXViewInfoObject *pViewInfo);
	~CXPageSection3DHorizonVis();

	virtual void Apply() override;
	virtual void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _Init();

private:
	Ui::CXPageSection3DHorizonVis m_ui;
	CXViewInfo3DHorizon* m_pViewInfo;
};

#endif // KEPAGESECTION3DHORIZONVIS_H
