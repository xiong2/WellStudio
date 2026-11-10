#ifndef XDLGNEWOBJECT_H
#define XDLGNEWOBJECT_H

#include "xobjecttype.h"
#include "xbasedialog.h"
#include "ui_xdlgnewobject.h"

class CX3DSurvey;

class CXDlgNewObject : public CXBaseDialog
{
	Q_OBJECT

public:
	CXDlgNewObject(CX3DSurvey *, EXObjectType, QWidget *parent = 0);
	~CXDlgNewObject();

	virtual void OnOK();

private:
	void _init();

	CX3DSurvey*			m_pSurvey;
	EXObjectType			m_eObjType;
	Ui::CXDlgNewObject		ui;
};

#endif // KEDLGNEWOBJECT_H
