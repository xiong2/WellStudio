#ifndef XWELLVISUALIZATIONPAGE_H_H
#define XWELLVISUALIZATIONPAGE_H_H

#include "ui_xpagewellvis3d.h"
#include "xbasepropertypage.h"

class CXViewInfoObject;
class CXViewInfoWellPath;
class CXButtonColorEdit;

class CXPageWellVis3D :public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageWellVis3D(QWidget *parent, CXViewInfoObject * pWellViewInfo);
	~CXPageWellVis3D();

	virtual void Apply();

	virtual void SetObjectColorBuddyButton(CXButtonColorEdit* pButton);

private:
	void _InitUIState();

private:
	Ui::CXPageWellVis3D m_page;
	CXViewInfoWellPath *m_pViewInfo;
};
#endif