#ifndef XPAGEFORMATIONVISONSEC_H
#define XPAGEFORMATIONVISONSEC_H

#include "xbasepropertypage.h"
#include "ui_xpageformationvisonsec.h"

class CXViewInfoObject;
class CXViewInfo3DWellTopFormation;

class CXPageFormationVisOnSec : public CXBasePropertyPage
{
	Q_OBJECT
public:
    CXPageFormationVisOnSec(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageFormationVisOnSec(void);
	virtual void Apply();

	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton);

private slots:
	void slotTransChanged(int nValue);
private:
	void _InitUi();
private:
	Ui_PageFormationVisOnSec m_UI;
    CXViewInfo3DWellTopFormation *m_pViewInfo;
};

#endif // KEPAGEFORMATIONVISONSEC_H