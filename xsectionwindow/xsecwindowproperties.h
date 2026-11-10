#ifndef XSECWINDOWPROPERTIES_H
#define XSECWINDOWPROPERTIES_H

#include <QDialog>
#include "ui_xpagesecwindowvis.h"

class CXWindowInfoSection;
class CXSecWindowProperties : public QDialog
{
	Q_OBJECT
public:
    CXSecWindowProperties(QWidget *parent, CXWindowInfoSection *pViewInfo);
	~CXSecWindowProperties(void);

protected slots:
	void slotContensChanged(int);	
	void OnApply();

protected:
	void _InitUI();

	float getDPI(bool bHorizontal);

	Ui_PageSectionWindowVis m_UI;
    CXWindowInfoSection *m_pWindowViewInfo;
};

#endif // KESECWINDOWPROPERTIES_H