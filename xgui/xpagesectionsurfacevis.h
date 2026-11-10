#ifndef XPAGE2DSURFACEVIS_H
#define XPAGE2DSURFACEVIS_H

#include "xbasepropertypage.h"
#include "ui_xpagesectionsurfacevis.h"

/*!
 *	@brief	surface viewinfo page on section window.
 *	@author	pezy
 *	@date	2016-05-05
 */

class CXViewInfoObject;
class CXViewInfoSurface;
class CXObject;

class CXPageSectionSurfaceVis : public CXBasePropertyPage
{
	Q_OBJECT
public:
	CXPageSectionSurfaceVis(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageSectionSurfaceVis(void);

	virtual void Apply();
	virtual void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private slots:
	void slotEnabledAnn();
private:
	void _InitUi();

private:
	Ui_SurfaceVisPage m_ui;
	CXViewInfoSurface *m_pViewInfo;
};

#endif // KEPAGE2DSURFACEVIS_H
