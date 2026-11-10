#ifndef _CXDLGEXPORTLAS_H__
#define _CXDLGEXPORTLAS_H__

#include "xgui_global.h"
#include "ui_xexportlas.h"

class CXObject;

class XGUI_EXPORT CXDlgExportLAS: public QDialog
{
	Q_OBJECT
public:
	CXDlgExportLAS(CXObject *pObj, QWidget *parent = 0);
	~CXDlgExportLAS();

	void accept();

protected:
	Ui::ExportLAS ui;

	CXObject	*m_pObject;

	void exportLas();
	void exportPath();

protected slots:
	void slotSelectCurves();
	void slotSelectFile();
};

#endif