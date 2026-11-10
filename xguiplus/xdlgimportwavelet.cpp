#include "xdlgimportwavelet.h"
#include <qfiledialog.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <QMessageBox>
#include "xglobal.h"
#include "xwavelet.h"


CXDlgImportWavelet::CXDlgImportWavelet(QWidget* parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);	
	setAttribute(Qt::WA_DeleteOnClose);

	connect(m_ui.m_pBtnSelect, SIGNAL(clicked()), this, SLOT(slotOnSelect()));
	connect(m_ui.m_pBtnImport, SIGNAL(clicked()), this, SLOT(slotOnImport()));
	connect(m_ui.m_pBtnCancel, SIGNAL(clicked()), this, SLOT(slotOnCancel()));
}


CXDlgImportWavelet::~CXDlgImportWavelet()
{
}

void CXDlgImportWavelet::slotOnSelect()
{
	QString strFile = QFileDialog::getOpenFileName(this, tr("All Files (*)"));
	if (strFile.isEmpty())
		return;

	m_ui.m_pEdtFileName->setText(strFile);
	slotViewFile();

	m_ui.m_pEdtName->setDisabled(false);
	m_ui.m_pEdtLineToSkip->setDisabled(false);
	m_ui.m_pEdtSampleCount->setDisabled(false);
	m_ui.m_pEdtStep->setDisabled(false);
	m_ui.m_pEdtTimeZero->setDisabled(false);
	m_ui.m_pBtnImport->setDisabled(false);

	QFileInfo qFI(strFile);
	QString sWName = qFI.baseName();
	CXObject *pWaveletFolder = ::GetRootObjectFolder(EXWaveletFolder);
	sWName = pWaveletFolder->GetUnallocatedName(sWName);
	m_ui.m_pEdtName->setText(sWName);

}

void CXDlgImportWavelet::slotViewFile()
{
	QString strFile = m_ui.m_pEdtFileName->text();

	
	QFile qFile(strFile);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	QTextStream stream(&qFile);
	qint64 iLine = 1;
	m_listLines.clear();
	QString strAllText;

	while (!stream.atEnd())
	{
		QString strLine = stream.readLine();
		m_listLines.append(strLine);
		strAllText += QString::number(iLine) + ":\t" + strLine + "\n";

		iLine++;
	}
	qFile.close();

	m_ui.m_pTextBrowser->setText(strAllText);
	m_ui.m_pTextBrowser->setWindowTitle(strFile);
	m_ui.m_pTextBrowser->show();
}

void CXDlgImportWavelet::slotOnImport()
{
	QString strName = m_ui.m_pEdtName->text();
	if (strName.isEmpty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter a valid wavelet name.");
		return;
	}


	int indexSkip = m_ui.m_pEdtLineToSkip->text().toInt();
	int indexZeor = m_ui.m_pEdtTimeZero->text().toInt();
	float step = m_ui.m_pEdtStep->text().toFloat();
	if (step <= 0)
	{
		QMessageBox::warning(this, ::g_strProductName, "The sampling rate has to be greater than 0.");
		return;
	}
	QList<double> lstData;
	bool bok;
	double data;
	int i;
	for (i = indexSkip; i < m_listLines.count(); i++)
	{
		data = m_listLines[i].toDouble(&bok);
		if (bok)
		{
			lstData.append(data);
		}
	}
	if (lstData.count() < 3)
	{
		QMessageBox::warning(this, ::g_strProductName, "There is no enough data to import.");
		return;
	}
	if (indexZeor <= 0 || indexZeor >= lstData.count())
	{
		QMessageBox::warning(this, ::g_strProductName, "Zero position has to be specified correctly.");
		return;
	}


	int zCount = lstData.count() - indexZeor;
	// padding zero at the beginning or end
	if (zCount < indexZeor)
	{
		zCount = indexZeor - 1 - zCount;
		for (int i = 0; i < zCount; i++)
		{
			lstData.append(0);
		}
	}
	else {
		zCount = indexZeor - zCount + 1;
		for (int i = 0; i < zCount; i++)
		{
			lstData.prepend(0);
		}
	}

	double* pData = new double[lstData.count()];
	for (i = 0; i < lstData.count(); i++)
	{
		pData[i] = lstData[i];
	}

	CXWavelet* pWavelet = new CXWavelet(strName);
	pWavelet->ResetData(-step * (lstData.count() / 2), step, lstData.count(), pData);
	pWavelet->SetNeedCalcDimension();
	CXObject *pWaveletFolder = ::GetRootObjectFolder(EXWaveletFolder);
	if (pWaveletFolder != NULL)
	{
		pWavelet->SetObjectName(pWaveletFolder->GetUnallocatedName(strName));
		pWaveletFolder->AddChild(pWavelet);
	}

	AddObjectEvent(pWavelet);

	close();
}

void CXDlgImportWavelet::slotOnCancel()
{
	close();
}