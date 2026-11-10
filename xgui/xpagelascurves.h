#ifndef _CXPAGELASCURVES_H__
#define _CXPAGELASCURVES_H__
#include "xgui_global.h"

#include <QWizardPage>
#include <qlist.h>
#include "ui_xpagelascurves.h"

class CXLasWisFile;

///@brief	A page to parse LAS curves.
///@author	Xiong Xiong
///@date	May, 2013
///@see		
class XGUI_EXPORT CXPageLASCurves : public QWizardPage
{
	Q_OBJECT
public:
	CXPageLASCurves(QList<CXLasWisFile *> listLASFile, QStringList& sListMatchedWells, bool bLas = true, QWidget *parent = 0);

	///	Reimplement super class' function.
	void initializePage();
	
	bool validatePage();

protected:
	Ui::PageLASCurves ui;

	QList<CXLasWisFile *>		m_listLASFile;		//	Hold the list of LAS file.
	QStringList&			m_sListMatchedWells;

	bool m_bSelectAll;
	bool m_bLAS;

private slots:
	void slotSelectAll();
	void slotRefreshPreview(int);		//	Preview other files.
	void slotChangeTemplate(int);			//	User change the template mannually.
};

#endif