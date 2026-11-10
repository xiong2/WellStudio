#ifndef XPAGE3DWELLCURVEVIS_H
#define XPAGE3DWELLCURVEVIS_H

#include "xbasepropertypage.h"
#include "ui_xpage3dwellcurvevis.h"

/*!
 * @class	CXPageSectionWellCurveVis in kepagesectionwellcurvevis.h
 * @brief	The class define well curves property page for section window.
 * @author	pezy
 * @date	2016-11-14
 * @see		
 */

class CXViewInfoWellCurve;
class CXViewInfoObject;

class CXPage3DWellCurveVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPage3DWellCurveVis(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPage3DWellCurveVis();

	void Apply() override;
	void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _InitUI();

private:
	Ui::CXPage3DWellCurveVis m_ui;
	CXViewInfoWellCurve *m_pViewInfo;
};

#endif // KEPAGE3DWELLCURVEVIS_H
