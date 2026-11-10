#ifndef _CXPAGEATTRIBUTES_H__
#define _CXPAGEATTRIBUTES_H__

#include <QWizardPage>

#include "xgui_global.h"

#include "xdef.h"
#include "xunit.h"

class QTableWidget;
class CXASCIIFile;

class XGUI_EXPORT CXPageAttributes : public QWizardPage
{
	Q_OBJECT
public:
	CXPageAttributes(CXASCIIFile* pASCIIFile, QWidget *parent = 0);

	virtual void initializePage();

	bool validatePage();

protected:

	void guessDataType(QStringList& sListAttributes, QList<int>& iDataType, QList<int>& iUnitType);

	QTableWidget*		m_pTable;
	CXASCIIFile*		m_pASCIIFile;

private slots:
	void slotDataTypeChanged(int);
	void slotUnitTypeChanged(int);
};

#endif