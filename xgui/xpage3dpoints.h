#ifndef XPAGE3DPOINTS_H
#define XPAGE3DPOINTS_H

#include "xbasepropertypage.h"
#include "ui_xpage3dpoints.h"
#include "xviewinfo3dpoints.h"

class CXPage3DPoints : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPage3DPoints(CXViewInfoObject* pViewInfo, QWidget *parent = 0);
	~CXPage3DPoints();

	void Apply() override;

	//@Brief: As the object color changed, we should notice the visualization page, and then update color buttons.
	void SetObjectColorBuddyButton(CXButtonColorEdit*) override;

private:
	Ui::CXPage3DPoints ui;
	CXViewInfo3DPoints* m_pViewInfo = nullptr;
};

#endif // XPAGE3DPOINTS_H
