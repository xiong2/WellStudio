#ifndef XPAGEBM2DPOLYGON_H
#define XPAGEBM2DPOLYGON_H

#include "xbasepropertypage.h"
namespace Ui {class CXPageBM2DPolygon;};
class CXViewInfo2DPolygon;
class CXViewInfoObject;

class CXPageBM2DPolygon : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageBM2DPolygon(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageBM2DPolygon();

	void Apply() override;
	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _Init();

private:
	Ui::CXPageBM2DPolygon *m_ui;
	CXViewInfo2DPolygon* m_pViewInfo;
};

#endif // KEPAGEBM2DPOLYGON_H
