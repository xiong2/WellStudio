#include <qfiledialog.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qvalidator.h>
#include "xdlgupdatesgy.h"
#include "xsegyloadparameters.h"
#include "xdataconvertor.h"

XDlgUpdateSGY::XDlgUpdateSGY(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	ui.lineEdit_2->setValidator(new QIntValidator(10001, 99999, this));

	connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(slotBrowse()));
}

XDlgUpdateSGY::~XDlgUpdateSGY()
{
	if (m_pPara)
		delete m_pPara;
}

void XDlgUpdateSGY::slotBrowse()
{
	QString sPath = QFileDialog::getExistingDirectory();

	if (!sPath.isEmpty())
	{
		ui.lineEdit->setText(sPath);
		ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
	}
	else
	{
		ui.lineEdit->clear();
		ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	}
}

void XDlgUpdateSGY::accept()
{
	QStringList sListFile, sListFilter;
	sListFilter << "FFID-*.sgy";
	QString sPath = ui.lineEdit->text();
	QDir qDir(sPath);
	sListFile = qDir.entryList(sListFilter);

	if (sListFile.isEmpty())
	{
		QMessageBox::warning(NULL, "Update SEGY file", "No SEGY files in this directory!");
		return;
	}

	int iID = ui.lineEdit_2->text().toInt();
	QStringList sListF;
	sListF << sPath + "/" + sListFile[0];
	if (m_pPara)
		delete m_pPara;
	m_pPara = new CXSEGYLoadParameters(sListF);

	foreach(QString sFile, sListFile)
	{
		convertOneFile(sPath, sFile, iID);
		iID++;
	}

	QDialog::accept();
}

void XDlgUpdateSGY::convertOneFile(QString sPath, QString sFile, int iID)
{
	QDir qDir(sPath);
	int iTraceNum = m_pPara->GetTraceNumber();
	int iTraceLen = m_pPara->GetTraceLength() + 240;

	QFile qFile(sPath + "/" + sFile);
	if (!qFile.open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(NULL, "Update SEGY file", "Can not open " + sFile + " to convert!");
		return;
	}

	int iVal = iID;
	Reverse(iVal);
	for (int i = 0; i < iTraceNum; i++)
	{
		qFile.seek( 3600 + i * iTraceLen + 8);
		qFile.write((char *)(&iVal), 4);
	}

	qFile.close();

	QString sNew = "00000";
	QString sID = QString::number(iID);
	int iLen = sID.length();
	sNew.replace(5 - iLen, iLen, sID);
	QString sNFile = sFile;
	sNFile.replace(5, 5, sNew);

	qDir.rename(sFile, sNFile);
}