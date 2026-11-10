#ifndef XFAULTSTICKSVISSEC_H
#define XFAULTSTICKSVISSEC_H

#include "xbasepropertypage.h"
#include "ui_xfaultsticksvispagesec.h"

class CXViewInfoObject;
class CXViewInfo3DFaultSticks;

class CXFaultSticksVisSec : public CXBasePropertyPage
{
	Q_OBJECT
public:
	CXFaultSticksVisSec(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXFaultSticksVisSec(void);

	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton);

	virtual void Apply();
private:
	void _initUI();
private:
	Ui_RLFaultSticksVisPageSec m_Ui;
	CXViewInfo3DFaultSticks *m_pViewInfo;
};

#endif // KEFAULTSTICKSVISSEC_H