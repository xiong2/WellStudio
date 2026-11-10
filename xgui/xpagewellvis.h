#ifndef XPAGEWELLVIS_H
#define XPAGEWELLVIS_H

#include "xbasepropertypage.h"
#include "ui_xpagewellvis.h"

class CXViewInfoObject;
class CXViewInfoWellPath;

class CXPageWellVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageWellVis(QWidget *parent, CXViewInfoObject * pWellViewInfo);
	~CXPageWellVis();

	void Apply() override;
	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _Init();

private:
	Ui::CXPageWellVis m_ui;
	CXViewInfoWellPath* m_pViewInfo;
};

#endif // KEPAGEWELLVIS_H
