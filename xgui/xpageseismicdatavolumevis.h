#ifndef XPAGESEISMICDATAVOLUMEVIS_H
#define XPAGESEISMICDATAVOLUMEVIS_H

/*!
 *	@brief	Seismic data volume visualization page for base map or 3D window
 *	@author	pezy
 *	@date	2016-06-15
 */

#include "xbasepropertypage.h"
#include "ui_xpageseismicdatavolumevis.h"
class CXViewInfoObject;
class CXViewInfoSeismicDV;

class CXPageSeismicDataVolumeVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageSeismicDataVolumeVis(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageSeismicDataVolumeVis();

	void Apply() override;
	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _Init();

private:
	Ui::CXPageSeismicDataVolumeVis m_ui;
	CXViewInfoSeismicDV* m_pViewInfo;
};

#endif // KEPAGESEISMICDATAVOLUMEVIS_H
