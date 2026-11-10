#ifndef _CXPAGEASCIIFILE_H__
#define _CXPAGEASCIIFILE_H__

#include "xgui_global.h"

#include <QWizardPage>
#include "ui_xpageasciifile.h"
#include "xdef.h"

class CXASCIIFile;

///@brief	A page to represent an ASCII file.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XGUI_EXPORT CXPageASCIIFile : public QWizardPage
{
	Q_OBJECT
public:
	CXPageASCIIFile(CXASCIIFile *pASCIIFile, QWidget *parent = 0);

	///	Overwrite the inherit feature.
	virtual void initializePage();
		
	bool validatePage();

protected:
	Ui::PageASCIIFileClass ui;
	
	CXASCIIFile*			m_pASCIIFile;
	QStringList				m_sListPreviewContent;			//	Preview content.

	//	Refresh the preview content.
	bool refreshPreviewContent();

	//	Refresh the preivew table.
	bool refreshPreviewTable();

	//	To avoid nested calling, may temperarily block some signal.
	void blockSomeSignals(bool bBlock);

private slots:
	void slotDelimiterChanged();
	void slotPreviewLineNumberChanged();
	void slotPreviewColumnResized(int nColumn, int nOldWidth, int nNewWidth);
	void slotRefreshColumnNames();
};

#endif