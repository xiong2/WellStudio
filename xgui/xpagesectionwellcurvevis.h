#ifndef XPAGESECTIONWELLCURVEVIS_H
#define XPAGESECTIONWELLCURVEVIS_H

#include "xbasepropertypage.h"
#include "ui_xpagesectionwellcurvevis.h"

/*!
 * @class	CXPageSectionWellCurveVis in kepagesectionwellcurvevis.h
 * @brief	The class define well curves property page for section window.
 * @author	pezy
 * @date	2016-11-14
 * @see		
 */

class CXViewInfoObject;
class CXViewInfoWellCurve;

class CXPageSectionWellCurveVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageSectionWellCurveVis(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageSectionWellCurveVis();

	void Apply() override;
	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _InitUI();

private slots:
	void slotFilterTypeChanged(int type);

private:
	Ui::CXPageSectionWellCurveVis m_ui;
	CXViewInfoWellCurve *m_pViewInfo;
};

#endif // KEPAGESECTIONWELLCURVEVIS_H
