#ifndef XDLGIMPORT2DSEGY_H
#define XDLGIMPORT2DSEGY_H

#include <QDialog>
#include "xgui_global.h"
#include "ui_xdlgimport2dsegy.h"

class CXSEGYLoadParameters;

class XGUI_EXPORT CXDlgImport2DSEGY : public QDialog
{
	Q_OBJECT

public:
	CXDlgImport2DSEGY(QStringList sListFiles, QWidget *parent = 0);
	~CXDlgImport2DSEGY();

	QList<CXSEGYLoadParameters*> GetParameters() { return m_listParameters; }

	QString Get2DSurveyName();

	
public slots:
	virtual void accept();

protected slots:
	void slotViewVolumeHeader();
	void slotViewLineHeader();
	void slotSetTraceHeader();
	void slotSetDataFormat();

	void slotItemClicked();
	void slotAddFiles();
	void slotRemoveFile();

private:
	Ui::CXDlgImport2DSEGY ui;

	void initializeTab();

	QStringList							m_sListSEGYFiles;		

	QList<CXSEGYLoadParameters *>		m_listParameters;
};

#endif // KEDLGIMPORT2DSEGY_H
