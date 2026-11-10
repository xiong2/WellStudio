#include <qsettings.h>
#include <qtextstream.h>
#include <QFile>
#include <qcombobox.h>
#include <qmessagebox.h>
#include "xpageasciifile.h"
#include "xasciifile.h"
#include "xglobal.h"

CXPageASCIIFile::CXPageASCIIFile(CXASCIIFile *pASCIIFile, QWidget *pParent): QWizardPage(pParent)
{
	ui.setupUi(this);

	ui.tableWidgetPreview->horizontalHeader()->hide();
	ui.tableWidgetPreHeader->setRowCount(1);

    QStringList sListColName;
	sListColName << tr("Column Name");
   
	ui.tableWidgetPreHeader->setVerticalHeaderLabels(sListColName);
    QHeaderView * pHeader1=ui.tableWidgetPreview->verticalHeader () ;
    QHeaderView * pHeader2=ui.tableWidgetPreHeader->verticalHeader () ;
    pHeader1->setMinimumWidth(pHeader2->sizeHint().width());

	//	Delimiter changed.
	connect(ui.checkBoxAllowBlank, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxColon, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxComma, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxDOther, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxDQ, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxQOther, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxSemiColon, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxSpace, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxSQ, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.checkBoxTab, SIGNAL(clicked()), this, SLOT(slotDelimiterChanged()));
	connect(ui.lineEditDOther, SIGNAL(editingFinished()), this, SLOT(slotDelimiterChanged()));
	connect(ui.lineEditQOther, SIGNAL(editingFinished()), this, SLOT(slotDelimiterChanged()));

	//	Name from changed.
	connect(ui.radioButtonAuto, SIGNAL(clicked()), this, SLOT(slotRefreshColumnNames()));
	connect(ui.radioButtonLastUsed, SIGNAL(clicked()), this, SLOT(slotRefreshColumnNames()));
	connect(ui.spinBoxNameLine, SIGNAL(valueChanged(int)), this, SLOT(slotRefreshColumnNames()));

	//	Header column should has the same width with preview table column's width.
	connect(ui.tableWidgetPreHeader->horizontalHeader(), SIGNAL(sectionResized(int,int,int)),
        this, SLOT(slotPreviewColumnResized(int,int,int)));

	//	Header's horizontal scroll bar synchronized that of the preivew table.
    connect((QObject *)ui.tableWidgetPreview->horizontalScrollBar(), SIGNAL(valueChanged(int)),
        (QObject *)ui.tableWidgetPreHeader->horizontalScrollBar(), SLOT(setValue(int)));

	m_pASCIIFile = pASCIIFile;
	
	blockSomeSignals(false);
}

void CXPageASCIIFile::blockSomeSignals(bool bBlock)
{
	if(bBlock)
	{
		disconnect(ui.spinBoxNameLine, SIGNAL(valueChanged()), this, SLOT(slotRefreshColumnNames()));
		disconnect(ui.spinBoxPrivewNumber, SIGNAL(valueChanged(int)), this, SLOT(slotPreviewLineNumberChanged()));
	}
	else
	{
		connect(ui.spinBoxNameLine, SIGNAL(valueChanged(int)), this, SLOT(slotRefreshColumnNames()));
		connect(ui.spinBoxPrivewNumber, SIGNAL(valueChanged(int)), this, SLOT(slotPreviewLineNumberChanged()));
	}
}

//	Populate the GUI with the file information.
void CXPageASCIIFile::initializePage()
{	
	//	File information.
	ui.lineEditFileName->setText(m_pASCIIFile->GetFileName());
	ui.lineEditLineNumber->setText(QString::number(m_pASCIIFile->GetLineNumber()));
	ui.lineEditInvalid->setText(QString::number(m_pASCIIFile->GetInvalid()));

	//	Import range.
	ui.lineEditFromLine->setText(QString::number(m_pASCIIFile->GetImportFrom()));
	if(m_pASCIIFile->GetImportTo() == m_pASCIIFile->GetLineNumber())
		ui.lineEditToLine->setText("EOF");
	else
		ui.lineEditToLine->setText(QString::number(m_pASCIIFile->GetImportTo()));

	//	Delimiter.
	QStringList sListDelimiter = m_pASCIIFile->GetDelimiter()->GetAllStandardDelimiters();
	if(sListDelimiter.contains(","))
		ui.checkBoxComma->setChecked(true);
	if(sListDelimiter.contains(";"))
		ui.checkBoxSemiColon->setChecked(true);
	if(sListDelimiter.contains(":"))
		ui.checkBoxColon->setChecked(true);
	if(sListDelimiter.contains("\t"))
		ui.checkBoxTab->setChecked(true);
	if(sListDelimiter.contains(" "))
		ui.checkBoxSpace->setChecked(true);
	
	QString sUserDefinedDelimiter = m_pASCIIFile->GetDelimiter()->GetUserDefinedDelimiter();
	if(sUserDefinedDelimiter != "")
	{
		ui.checkBoxDOther->setChecked(true);
		ui.lineEditDOther->setText(sUserDefinedDelimiter);
		ui.lineEditDOther->setEnabled(true);
	}
	else
	{
		ui.lineEditDOther->setEnabled(false);
	}

	//	Quotes.
	bool bDoubleQuotes, bSingleQuotes, bUserDefinedQuotes;
	QString sUserDefinedQuotes = m_pASCIIFile->GetDelimiter()->GetUsingQuotes(bDoubleQuotes, bSingleQuotes, bUserDefinedQuotes);
	ui.checkBoxDQ->setChecked(bDoubleQuotes);
	ui.checkBoxSQ->setChecked(bSingleQuotes);
	ui.checkBoxQOther->setChecked(bUserDefinedQuotes);
	ui.lineEditQOther->setText(sUserDefinedQuotes);
	ui.lineEditQOther->setEnabled(bUserDefinedQuotes);

	if(m_pASCIIFile->GetDelimiter()->IsAllowBlankItem())
		ui.checkBoxAllowBlank->setChecked(true);
	else
		ui.checkBoxAllowBlank->setChecked(false);

	//	Column name.
	ui.radioButtonLastUsed->setChecked(false);
	ui.spinBoxNameLine->setEnabled(true);
	
	ui.spinBoxNameLine->setMaximum(m_pASCIIFile->GetLineNumber());

	//	Preview content.
	ui.spinBoxPrivewNumber->setValue(m_pASCIIFile->GetPreviewLineNumber());
	ui.spinBoxPrivewNumber->setMaximum(m_pASCIIFile->GetLineNumber());

	//	Read the preview content.
	m_sListPreviewContent.clear();
	refreshPreviewContent();

	//	Refresh the priew table.
	refreshPreviewTable();
	
	//	Try to use saved informatoin refresh the columns.
	slotRefreshColumnNames();
}

bool CXPageASCIIFile::refreshPreviewContent()
{
	//	May be no need to read again?
	if(m_sListPreviewContent.size() >= m_pASCIIFile->GetPreviewLineNumber())
	{
		//	Just abort the last lines.
		while(m_sListPreviewContent.size() > m_pASCIIFile->GetPreviewLineNumber())
		{
			m_sListPreviewContent.removeLast();
		}

		return true;
	}

	m_sListPreviewContent.clear();

	QFile qFile(m_pASCIIFile->GetFileName());
	if(!qFile.open(QIODevice::ReadOnly))
		return false;

	//	A loop to read the preview content.
	unsigned int iCount = 0;
	QTextStream stream(&qFile);
	while(!stream.atEnd())
	{
		QString sLine = stream.readLine();
		m_sListPreviewContent<<sLine;
		iCount++;

		if(iCount >= m_pASCIIFile->GetPreviewLineNumber())
			break;
	}

	return true;
}

bool CXPageASCIIFile::refreshPreviewTable()
{
	int i, j;
	QList<QStringList> listSListPre;

	//	Split the preview content.
	unsigned int iMaxColumn = 0;
	for(i = 0; i < m_sListPreviewContent.size(); i++)
	{
		QStringList sList = m_pASCIIFile->GetDelimiter()->GetSplittedString(m_sListPreviewContent.at(i));
		if(iMaxColumn < sList.size())
			iMaxColumn = sList.size();
		listSListPre<<sList;
	}

	//	Set the column name and number.
	ui.tableWidgetPreHeader->setColumnCount(iMaxColumn);
	for(j = 0; j < iMaxColumn; j++)
	{
		QComboBox *pComboBox = new QComboBox;
		pComboBox->addItems(m_pASCIIFile->GetColumnCandidates());
		ui.tableWidgetPreHeader->setCellWidget(0, j, pComboBox);
	}

	//	Populate the content.
	QStringList sListRowLabel;
	ui.tableWidgetPreview->setRowCount(m_sListPreviewContent.size());
	ui.tableWidgetPreview->setColumnCount(iMaxColumn);
	for(i = 0; i < m_sListPreviewContent.size(); i++)
	{
		QStringList sList = listSListPre.at(i);
		for(j = 0; j < sList.size(); j++)
		{
			ui.tableWidgetPreview->setItem(i, j, new QTableWidgetItem(sList.at(j)));
		}

		//	Erase others
		for(;j < iMaxColumn; j++)
		{
			ui.tableWidgetPreview->setItem(i, j, new QTableWidgetItem(""));
		}

		sListRowLabel<<QString::number(i + 1);
	}
    ui.tableWidgetPreview->setVerticalHeaderLabels(sListRowLabel);

	return true;
}

void CXPageASCIIFile::slotPreviewColumnResized(int nColumn, int nOldWidth, int nNewWidth)
{
	ui.tableWidgetPreview->setColumnWidth(nColumn, nNewWidth);
}

void CXPageASCIIFile::slotDelimiterChanged()
{
	//	5 standard delimiters.
	m_pASCIIFile->GetDelimiter()->UpdateDelimiter(":", ui.checkBoxColon->isChecked());
	m_pASCIIFile->GetDelimiter()->UpdateDelimiter(";", ui.checkBoxSemiColon->isChecked());
	m_pASCIIFile->GetDelimiter()->UpdateDelimiter(" ", ui.checkBoxSpace->isChecked());
	m_pASCIIFile->GetDelimiter()->UpdateDelimiter("\t", ui.checkBoxTab->isChecked());
	m_pASCIIFile->GetDelimiter()->UpdateDelimiter(",", ui.checkBoxComma->isChecked());

	//	User define delimiter
	if(ui.checkBoxDOther->isChecked())
	{
		ui.lineEditDOther->setEnabled(true);
		m_pASCIIFile->GetDelimiter()->ChangeUserDefinedDelimiter(ui.lineEditDOther->text());
	}
	else
	{
		ui.lineEditDOther->setEnabled(false);
		m_pASCIIFile->GetDelimiter()->ChangeUserDefinedDelimiter("");
	}

	//	Quote
	m_pASCIIFile->GetDelimiter()->UseDoubleQuotes(ui.checkBoxDQ->isChecked());
	m_pASCIIFile->GetDelimiter()->UseSingleQuotes(ui.checkBoxSQ->isChecked());

	m_pASCIIFile->GetDelimiter()->UseUserDefinedQuotes(ui.checkBoxQOther->isChecked());
	m_pASCIIFile->GetDelimiter()->UseUserDefinedQuotes(ui.lineEditQOther->text());
	ui.lineEditQOther->setEnabled(ui.checkBoxQOther->isChecked());

	//	Allow blank item?
	m_pASCIIFile->GetDelimiter()->AllowBlankItem(ui.checkBoxAllowBlank->isChecked());

	//	All delimiters refreshed, reset the preview and column names.
	refreshPreviewTable();
	slotRefreshColumnNames();
}

void CXPageASCIIFile::slotPreviewLineNumberChanged()
{
	blockSomeSignals(true);

	int iLineNumber = ui.spinBoxPrivewNumber->value();

	//	Can not exced the file line number.
	if(iLineNumber > m_pASCIIFile->GetLineNumber())
	{
		iLineNumber = m_pASCIIFile->GetLineNumber();
		ui.spinBoxPrivewNumber->setValue(iLineNumber);
	}

	if(iLineNumber != m_pASCIIFile->GetPreviewLineNumber())
	{
		m_pASCIIFile->SetPreviewLineNumber(iLineNumber);

		//	Refresh.
		refreshPreviewContent();
		refreshPreviewTable();
	}

	//	Should the name line need update?
	int iNameLine = m_pASCIIFile->GetNameLine();
	if(iNameLine > iLineNumber)
	{
		iNameLine = iLineNumber;

		m_pASCIIFile->SetNameLine(iNameLine);
		ui.spinBoxNameLine->setValue(iNameLine);

		slotRefreshColumnNames();
	}

	blockSomeSignals(false);
}

void CXPageASCIIFile::slotRefreshColumnNames()
{
	blockSomeSignals(true);

	if(ui.radioButtonLastUsed->isChecked())
	{
		ui.spinBoxNameLine->setEnabled(false);

		//	Try to load column information from settings.
		int iType = m_pASCIIFile->GetFileType();
		QString sType = QString::number(iType);
		QSettings settings("XStudio", "ImportASCIIFile");
		QStringList sListColumns = settings.value(sType).toStringList();

		int i, iColumnNumber = ui.tableWidgetPreHeader->columnCount();
		if(iColumnNumber > sListColumns.size())
			iColumnNumber = sListColumns.size();

		for(i = 0; i < iColumnNumber; i++)
		{
			QComboBox *pComboBox = dynamic_cast<QComboBox *>(ui.tableWidgetPreHeader->cellWidget(0, i));
			if(!pComboBox)
				continue;
	
			int iIDX = pComboBox->findText(sListColumns.at(i));
			if(iIDX != -1)
				pComboBox->setCurrentIndex(iIDX);
		}
	}
	else
	{
		ui.spinBoxNameLine->setEnabled(true);
		if(ui.spinBoxNameLine->value() > m_pASCIIFile->GetPreviewLineNumber())
		{
			ui.spinBoxNameLine->setValue(m_pASCIIFile->GetPreviewLineNumber());
		}
		m_pASCIIFile->SetNameLine(ui.spinBoxNameLine->value());

		QStringList sListColumn = m_pASCIIFile->GuessColumnName();
		QStringList sListCandidates = m_pASCIIFile->GetColumnCandidates();
		if (sListCandidates.size() == 0)
		{
			int iColumnSize = sListColumn.size();
			if (iColumnSize > ui.tableWidgetPreHeader->columnCount())
				iColumnSize = ui.tableWidgetPreHeader->columnCount();

			for (int i = 0; i < iColumnSize; i++)
			{
				QComboBox *pComboBox = dynamic_cast<QComboBox *>(ui.tableWidgetPreHeader->cellWidget(0, i));
				if (!pComboBox)
					continue;

				pComboBox->clear();
				pComboBox->addItem(sListColumn[i]);
				pComboBox->addItem("Do not import");
				pComboBox->setCurrentIndex(0);
			}
		}
	}

	blockSomeSignals(false);
}

bool CXPageASCIIFile::validatePage()
{
	//	Check the chosen columns.
	QStringList& sListChosenColumn = m_pASCIIFile->GetChosenColumns();
	sListChosenColumn.clear();
		
	QStringList& sListAttributes = m_pASCIIFile->GetAttributes();
	sListAttributes.clear();

	int iLineTo, iLineFrom = ui.lineEditFromLine->text().toInt();

	// Set invalid data.
	bool bRes = true;
	float fInv = ui.lineEditInvalid->text().toFloat(&bRes);
	if (bRes)
		m_pASCIIFile->SetInvalid(fInv);

	if(ui.lineEditToLine->text() == "EOF")
	{
		iLineTo = m_pASCIIFile->GetLineNumber();
		m_pASCIIFile->ImportToFileEnd(true);
	}
	else
	{
		iLineTo = ui.lineEditToLine->text().toInt();
		m_pASCIIFile->ImportToFileEnd(false);
	}

	if(iLineFrom < 1 || iLineFrom > iLineTo || iLineTo > m_pASCIIFile->GetLineNumber())
	{
//  		if(::UsingChinese())
// 			QMessageBox::warning(NULL, GetTr("加载ASCII文件"), GetTr("加载范围错误！"));
// 		else
			QMessageBox::warning(NULL, tr("Importing ASCII Files"), tr("Import range error!"));
		return false;
	}
	m_pASCIIFile->SetImportFrom(iLineFrom);
	m_pASCIIFile->SetImportTo(iLineTo);

	int i, iColumnNumber = ui.tableWidgetPreHeader->columnCount();
	for(i = 0; i < iColumnNumber; i++)
	{
		QComboBox *pComboBox = dynamic_cast<QComboBox *>(ui.tableWidgetPreHeader->cellWidget(0, i));
		if(!pComboBox)
			continue;
	
		QString strColumn  = pComboBox->currentText();
		sListChosenColumn<<strColumn;

		if(strColumn != "Do not import")
		{
			if(sListAttributes.contains(strColumn))
			{
// 				if (::UsingChinese())
// 					QMessageBox::warning(NULL, GetTr("加载ASCII文件"), GetTr("列不能重复！"));
// 				else
					QMessageBox::warning(NULL, tr("Importing ASCII Files"), tr("Columns could not be duplicated!"));

				return false;
			}

			sListAttributes<<strColumn;
		}
	}

	if(!m_pASCIIFile->CheckSelectedColumns(sListChosenColumn))
		return false;

	//	Try to save column information into settings.
	int iType = m_pASCIIFile->GetFileType();
	QString sType = QString::number(iType);
	QSettings settings("XStudio", "ImportASCIIFile");
	settings.setValue(sType, sListChosenColumn);

	return true;
}