#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <qmainwindow.h>
#include <quuid.h>
#include <QMdiSubWindow>
#include "ui_mainwindow.h"


#define MAX_RECENTPROJECTS 5

class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~CMainWindow();

	///	While there's a valid current project, enable all actions.
	void EnableActions(bool bEnable = true);

	///	Whether using MDI.
	bool IsMDI();

protected:
	Ui::MainWindowClass ui;

	QAction*	m_pSeperator;
	QAction*	m_pRecentProjects[MAX_RECENTPROJECTS];

private slots:
	//! @brief	File
	void slotNewProject();
	void slotOpenProject();
	void slotSaveProject();
	void slotProjectProperties();
	//! @brief	I/O
	void slotImportFromFiles();
	void slotImportWavelet();
	void slotCreateSeismicWorkArea();
	//! @brief	View
	void slotCreateView();
	void slotActiveView(QMdiSubWindow *);
	void slotSwitchWindowStyle();
	//! @brief	Tools
	void slotTool();
	void slotHelp();
	void slotFAQ();

	//	GSM
	void slotGSM();
	void slotGSMWindow();

	// inversion
	void slotAVOInversion();
	void slotCSSI();
	void slotAVOCSSI();

private:
	void _Init();

	void updateRecentProjectsMenu();
	void addRecentProject(QString);
	void refreshRecentProject();
};

#endif // XMAINWINDOW_H
