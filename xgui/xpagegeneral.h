#ifndef XGENERALPAGE_H
#define XGENERALPAGE_H

#include <qcombobox.h>
#include "ui_xpagegeneral.h"
#include "xbasepropertypage.h"

class CXObject;
class CXPageGeneral : public CXBasePropertyPage
{
	Q_OBJECT
public:
	CXPageGeneral(QWidget *parent,CXObject *pObject);
	~CXPageGeneral();

	CXButtonColorEdit* GetObjColorButton();

	virtual void Apply();

protected:
	void initGeneralInfo();
	void initDescription();

	Ui_CXPageGeneral m_ui;
	CXObject *m_pObject;

	QComboBox *m_pCMBTemplate;

private:
	void _SetSpecificWidget();

private slots:
	void slotSetColor(QColor);
};

#endif // RFGENERALPAGE_H
