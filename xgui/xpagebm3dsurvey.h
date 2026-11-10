#ifndef XPAGEBM3DSURVEY_H
#define XPAGEBM3DSURVEY_H

#include "xbasepropertypage.h"
#include "ui_xpagebm3dsurvey.h"

class CXViewInfo3DSurvey;
class CXViewInfoObject;
class CXPageBM3DSurvey : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageBM3DSurvey(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageBM3DSurvey();

	void Apply() override;
	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _Init();

private:
	Ui::CXPageBM3DSurvey m_ui;
	CXViewInfo3DSurvey* m_pViewInfo;
};

#endif // KEPAGEBM3DSURVEY_H
