#ifndef _CXSHOWTEMPLATES_H__
#define _CXSHOWTEMPLATES_H__

#include "xgui_global.h"

#include <qmainwindow.h>
#include <QtSql>
#include "ui_xshowtemplates.h"

class XGUI_EXPORT CXShowTemplates : public QMainWindow
{
	Q_OBJECT

public:
	CXShowTemplates(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~CXShowTemplates();

private:
	void _InitContinuousModel();
	void _InitDiscreteModel();

	void _NewContinuousTemplate();
	void _NewDiscreteTemplate();

private:
	Ui::ShowTemplatesClass ui;

	QSqlTableModel*		m_pContinuousModel;
	QSqlTableModel*		m_pDiscreteModel;
	bool				m_bShowingMetric;			//	Showing metric or imperial.
	bool				m_bDirty;					//	Whether need to save.

private slots:
	void closeWindow();
	void setDirty();					//	Indicate the data dirty.
	void reset();						//	Refresh the GUI by data from DB and abort any changing.
	void saveToDB();					//	Save to DB.
	void newTemplate();					//	Create a new template.
	void switchUnitSys();				//	Switch between metirc and imperial unit system.
	void slotSetCurrentDiscreteModelIndex(const QModelIndex& index);
	void slotNewDiscreteProperty();
	void slotDelDiscreteProperty();
	void slotDiscretePropertyChanged();
	void slotDeleteTemplate();
};

#endif // CXShowTemplates_H
