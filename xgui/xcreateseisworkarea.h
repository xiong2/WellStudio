#ifndef XCREATESEISWORKAREA_H
#define XCREATESEISWORKAREA_H

#include "xbasedialog.h"
#include "xseismicutmtool.h"
#include "ui_xdlgcreateseisworkarea.h"
#include "xgui_global.h"

class XGUI_EXPORT CXCreateSeisWorkArea : public CXBaseDialog
{
	Q_OBJECT
public:
	CXCreateSeisWorkArea(QWidget *parent);
	~CXCreateSeisWorkArea(void);

private:
	virtual void OnOK();

	Ui_CreateSeisWorkArea	m_Ui;
	CXSeismicUTMTool		m_utm;

private slots:
	void slotPreView();
	void slotPreViewEnabled();
	void slotSave();
	void slotLoad();
};

#endif // KECREATESEISWORKAREA_H