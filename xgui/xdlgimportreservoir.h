#ifndef _CXDLGIMPORTRESERVOIR_H__
#define _CXDLGIMPORTRESERVOIR_H__

#include "xgui_global.h"
#include "ui_xdlgimportReservoir.h"
#include <QDialog>

class CXImportReservoirThread;

class XGUI_EXPORT CXDlgImportReservoir :public QDialog 
{
	Q_OBJECT
public:
	CXDlgImportReservoir(QString sFile, QWidget *parent = NULL);
	~CXDlgImportReservoir();

protected slots:
	void slotScan();
	void slotSelectAll();
	void slotDeselectAll();
	virtual void accept();

protected:
	Ui::ImportReservoir			ui;

	QString						m_sFileName;
	CXImportReservoirThread*	m_pThread;
};

#endif