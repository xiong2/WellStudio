#include <qmessagebox.h>
#include <qdir.h>
#include <QSettings>
#include <qfiledialog.h>
#include "xdlgnewproject.h"
#include "xproject.h"

CXDlgNewProject::CXDlgNewProject(QWidget *parent): QDialog(parent)
{
	m_pProject = NULL;

	ui.setupUi(this);
	ui.okButton->setDefault(true);
	QString strFilePath ;
	QSettings settings("XStudio", "Project Dir" );
	settings.beginGroup("Project");
	strFilePath = settings.value("Project Dir").toString();

	if(strFilePath.isEmpty())
		ui.lineEditDirectory->setText(QDir::currentPath());
	else
		ui.lineEditDirectory->setText(strFilePath);

	_InitProjectName();

	connect(ui.pushButtonBrowse, SIGNAL(clicked()), this, SLOT(slotSelectDir()));
}

void CXDlgNewProject::_InitProjectName()
{
	QString sProj = ui.lineEditName->text();
	QDir dir(ui.lineEditDirectory->text());
	QString strSuffix = ".rdb";
	QStringList strNameFilters;
	strNameFilters.append("*"+strSuffix);
	QStringList listFileName = dir.entryList(strNameFilters,QDir::Files);
	
	if (listFileName.contains(sProj + strSuffix, Qt::CaseInsensitive))
	{
		int i=2;
		sProj += QString::number(i);
		while (listFileName.contains(sProj + strSuffix, Qt::CaseInsensitive))
		{
			sProj = ui.lineEditName->text() + QString::number(++i);
		}
	}
	ui.lineEditName->setText(sProj);
}

bool CXDlgNewProject::checkName(QString sProj)
{
	if (sProj.isEmpty())
	{
		QMessageBox::critical(NULL, "Project Name", "Project name can not be empty!");
		return false;
	}

	for (int i = 0; i < sProj.length(); i++)
	{
		QChar ch = sProj.at(i);
		if (!ch.isLetterOrNumber() && ch != "+"
			&& ch != "-" && ch != "_")
		{
			QMessageBox::critical(NULL, "Project Name", "Project name can not contain special character!");
			return false;
		}
	}

	return true;
}

void CXDlgNewProject::accept()
{
	QString sProject = ui.lineEditName->text();
	if (!checkName(sProject))
		return;
	
	//	Need to check whether the project name already exist here.
	QString sDir = ui.lineEditDirectory->text();
	QDir qDir(sDir);
	if(!qDir.exists())
	{
		if(!qDir.mkdir(sDir))
		{
			QMessageBox::critical(NULL, "Wrong Directory", "Can not create the project directory!");
			return;
		}
	}

	//	Create the project now, but how to set other parameters?
	m_pProject = new CXProject(sProject, sDir, ui.radioButtonM->isChecked(), ui.textEditComments->toPlainText());
	if (!m_pProject->InitNewProject())
	{
		delete m_pProject;
		m_pProject = NULL;
		return;
	}

	QDialog::accept();
}

void CXDlgNewProject::slotSelectDir()
{
	QString strFilePath ;
	QSettings settings("XStudio", "Project Dir" );
	settings.beginGroup("Project");
	strFilePath = settings.value("Project Dir").toString();
	if(strFilePath.isEmpty())
	{
		strFilePath = QFileDialog::getExistingDirectory(NULL, "Select Project Directory");
		if (strFilePath == "")
			return;

		ui.lineEditDirectory->setText(strFilePath);
	}
	else
	{
		strFilePath = QFileDialog::getExistingDirectory(NULL, "Select Project Directory", strFilePath);
		if (strFilePath == "")
			return;

		ui.lineEditDirectory->setText(strFilePath);
	}

	settings.setValue("Project Dir", strFilePath);
	settings.endGroup();

	_InitProjectName();
}