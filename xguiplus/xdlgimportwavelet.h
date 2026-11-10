#ifndef XDLGIMPORTWAVELET_H
#define XDLGIMPORTWAVELET_H

#include "xguiplus_global.h"
#include "ui_xdlgcssinversion.h"
#include "ui_xdlgimportwavelet.h"
#include <qstringlist.h>


class XGUIPLUS_EXPORT CXDlgImportWavelet : public QWidget
{
	Q_OBJECT
public:
	CXDlgImportWavelet(QWidget* parent = 0);
	~CXDlgImportWavelet();

	QStringList m_listLines;

public slots:
	void slotOnSelect();
	void slotViewFile();
	void slotOnImport();
	void slotOnCancel();

private:
	Ui::CDlgRLImportWavelet m_ui;
};
#endif // XDLGIMPORTWAVELET_H
