#ifndef CXPAGETIMESLICEVISBM_H
#define CXPAGETIMESLICEVISBM_H

#include "xbasepropertypage.h"
#include "ui_xpagetimeslicevis.h"
#include "xdef.h"

/*!
 *	@brief	Timeslice property page on basemap.
 *	@author	pezy
 *	@date	2016-09-29
 *	@see
 */

class CXViewInfoObject;
class CXViewInfoTimeSlice;
class CXObject;

class CXPageTimeSliceVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageTimeSliceVis(QWidget *parent, CXViewInfoObject* pViewInfo, CXObject* pObj, EXWindowType typeWin);
	~CXPageTimeSliceVis();

	virtual void Apply() override;
	virtual void SetObjectColorBuddyButton(CXButtonColorEdit* pButton) override;

private:
	void _Init();
	void _InitForSectionWindow();
	void _InitForBaseMapWindow();
	void _InitFor3DWindow();
	void _InitAttributeList(QComboBox* pCbbAzi, QComboBox* pCbbDen);
	void _ApplyForSectionWindow();
	void _ApplyForBaseMapWindow();
	void _ApplyFor3DWindow();

private:
	Ui::CXPageTimeSliceVis m_ui;

	CXViewInfoTimeSlice* m_pViewInfo;
	CXObject* m_pObj;
	EXWindowType m_typeWin;
};

#endif // CXPAGETIMESLICEVISBM_H
