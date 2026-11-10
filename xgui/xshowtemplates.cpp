#include <qmessagebox.h>
#include <qdebug.h>
#include <qdatawidgetmapper.h>
#include "xshowtemplates.h"
#include "xglobal.h"
#include "xdbio.h"
#include "xbuttoncoloredit.h"
#include "xtemplate.h"

CXShowTemplates::CXShowTemplates(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.actionSUS,	SIGNAL(triggered()), this, SLOT(switchUnitSys()));
	connect(ui.actionReset, SIGNAL(triggered()), this, SLOT(reset()));
	connect(ui.actionSave,	SIGNAL(triggered()), this, SLOT(saveToDB()));
	connect(ui.actionExit,	SIGNAL(triggered()), this, SLOT(closeWindow()));
	connect(ui.actionNew,	SIGNAL(triggered()), this, SLOT(newTemplate()));
	connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(slotDeleteTemplate()));

    //  Prepare the database first.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(CXDBIO::GetTemplateFileName());

    if(!db.open())
    {
        qDebug()<<db.lastError();
        return;
    }

	_InitContinuousModel();
	_InitDiscreteModel();

	m_bShowingMetric = false;
	switchUnitSys();

	//	Try to connect the signal of data changing.
	m_bDirty = false;
	connect(m_pContinuousModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(setDirty()));
	connect(m_pDiscreteModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(setDirty()));
}

CXShowTemplates::~CXShowTemplates()
{

}

void CXShowTemplates::_InitContinuousModel()
{
	m_pContinuousModel = new QSqlTableModel(ui.tableView);
	m_pContinuousModel->setTable("Continuous");
	m_pContinuousModel->select();
	m_pContinuousModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pContinuousModel->setHeaderData(2, Qt::Horizontal, "Full Name");
	m_pContinuousModel->setHeaderData(4, Qt::Horizontal, "Unit");
	m_pContinuousModel->setHeaderData(5, Qt::Horizontal, "Unit");
	m_pContinuousModel->setHeaderData(6, Qt::Horizontal, "Data Min");
	m_pContinuousModel->setHeaderData(7, Qt::Horizontal, "Data Max");
	m_pContinuousModel->setHeaderData(8, Qt::Horizontal, "Data Min");
	m_pContinuousModel->setHeaderData(9, Qt::Horizontal, "Data Max");
	m_pContinuousModel->setHeaderData(10, Qt::Horizontal, "Display Min");
	m_pContinuousModel->setHeaderData(11, Qt::Horizontal, "Display Max");
	m_pContinuousModel->setHeaderData(12, Qt::Horizontal, "Display Min");
	m_pContinuousModel->setHeaderData(13, Qt::Horizontal, "Display Max");
	m_pContinuousModel->setHeaderData(14, Qt::Horizontal, "Logrithmic Scale");

	ui.tableView->setModel(m_pContinuousModel);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->hideColumn(0);
	ui.tableView->setColumnWidth(16, 600);

	QDataWidgetMapper * pMapper = new QDataWidgetMapper(this);
	pMapper->setModel(m_pContinuousModel);
	pMapper->addMapping(ui.lineEditName, 1);
	pMapper->addMapping(ui.lineEditFullName, 2);
	pMapper->addMapping(ui.lineEditType, 3);
	pMapper->addMapping(ui.lineEditUnitM, 4);
	pMapper->addMapping(ui.lineEditUnitI, 5);
	pMapper->addMapping(ui.lineEditDataMinM, 6);
	pMapper->addMapping(ui.lineEditDataMaxM, 7);
	pMapper->addMapping(ui.lineEditDataMinI, 8);
	pMapper->addMapping(ui.lineEditDataMaxI, 9);
	pMapper->addMapping(ui.lineEditDspMinM, 10);
	pMapper->addMapping(ui.lineEditDspMaxM, 11);
	pMapper->addMapping(ui.lineEditDspMinI, 12);
	pMapper->addMapping(ui.lineEditDspMaxI, 13);
	pMapper->addMapping(ui.checkBox, 14);
	pMapper->addMapping(ui.comboBoxIcon, 15);
	pMapper->addMapping(ui.lineEditAlias, 16);

	connect(ui.tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		pMapper, SLOT(setCurrentModelIndex(QModelIndex)));
}

void CXShowTemplates::_InitDiscreteModel()
{
	m_pDiscreteModel = new QSqlTableModel(ui.m_pTableViewDiscrete);
	m_pDiscreteModel->setTable("Discrete");
	m_pDiscreteModel->select();
	m_pDiscreteModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pDiscreteModel->setHeaderData(2, Qt::Horizontal, "Full Name");
	m_pDiscreteModel->setHeaderData(4, Qt::Horizontal, "Unit");
	m_pDiscreteModel->setHeaderData(5, Qt::Horizontal, "Unit");

	ui.m_pTableViewDiscrete->setModel(m_pDiscreteModel);
	ui.m_pTableViewDiscrete->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_pTableViewDiscrete->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_pTableViewDiscrete->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.m_pTableViewDiscrete->hideColumn(0);
	ui.m_pTableViewDiscrete->hideColumn(8);
	ui.m_pTableViewDiscrete->hideColumn(9);
	ui.m_pTableViewDiscrete->setColumnWidth(7, 600);

	QDataWidgetMapper * pMapper = new QDataWidgetMapper(this);
	pMapper->setModel(m_pDiscreteModel);
	pMapper->addMapping(ui.m_pEdtDiscreteName, 1);
	pMapper->addMapping(ui.m_pEdtDiscreteFullName, 2);
	pMapper->addMapping(ui.m_pEdtDiscreteType, 3);
	pMapper->addMapping(ui.m_pEdtDiscreteMetricUnit, 4);
	pMapper->addMapping(ui.m_pEdtDiscreteImperialUnit, 5);
	pMapper->addMapping(ui.m_pEdtDiscreteIcon, 6);
	pMapper->addMapping(ui.m_pEdtDiscreteAlias, 7);

	connect(ui.m_pTableViewDiscrete->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
		pMapper, SLOT(setCurrentModelIndex(QModelIndex)));

	connect(ui.m_pTableViewDiscrete, &QTableView::pressed, this, &CXShowTemplates::slotSetCurrentDiscreteModelIndex);

	connect(ui.m_pBtnPropertyNew, &QPushButton::pressed, this, &CXShowTemplates::slotNewDiscreteProperty);
	connect(ui.m_pBtnPropertyDelete, &QPushButton::pressed, this, &CXShowTemplates::slotDelDiscreteProperty);
	connect(ui.m_pTableProperties, &QTableWidget::itemChanged, this, &CXShowTemplates::slotDiscretePropertyChanged);
}

void CXShowTemplates::_NewContinuousTemplate()
{
	int iLastRow = m_pContinuousModel->rowCount();
	if (!m_pContinuousModel->insertRow(iLastRow))
		return;

	//	Initial the new tempalte.
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 1), "New template");
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 2), "");
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 3), "GENERAL");
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 4), "");
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 5), "");
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 6), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 7), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 8), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 9), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 10), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 11), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 12), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 13), -999.25);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 14), false);
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 15), "");
	m_pContinuousModel->setData(m_pContinuousModel->index(iLastRow, 16), "");

	//	Set it as the active one.
	ui.tableView->setCurrentIndex(m_pContinuousModel->index(iLastRow, 0));

	//	Let the table view scoll to the bottom.
	ui.tableView->scrollToBottom();
}

void CXShowTemplates::_NewDiscreteTemplate()
{
	int iLastRow = m_pDiscreteModel->rowCount();
	if (!m_pDiscreteModel->insertRow(iLastRow))
		return;

	//	Initial the new tempalte.
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 1), "New template");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 2), "");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 3), "GENERAL");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 4), "");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 5), "");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 6), "");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 7), "");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 8), "");
	m_pDiscreteModel->setData(m_pDiscreteModel->index(iLastRow, 9), "");

	//	Set it as the active one.
	ui.m_pTableViewDiscrete->setCurrentIndex(m_pDiscreteModel->index(iLastRow, 0));

	//	Let the table view scoll to the bottom.
	ui.m_pTableViewDiscrete->scrollToBottom();
}

void CXShowTemplates::switchUnitSys()
{
	m_bShowingMetric = !m_bShowingMetric;

	ui.tableView->setColumnHidden(4, !m_bShowingMetric);		//	Metric Unit
	ui.tableView->setColumnHidden(5, m_bShowingMetric);			//	Imperical Unit
	ui.tableView->setColumnHidden(6, !m_bShowingMetric);		//	Metric Data Min
	ui.tableView->setColumnHidden(7, !m_bShowingMetric);		//	Metric Data Max
	ui.tableView->setColumnHidden(8, m_bShowingMetric);			//	Imperial Data Min
	ui.tableView->setColumnHidden(9, m_bShowingMetric);			//	Imperial Data Max
	ui.tableView->setColumnHidden(10, !m_bShowingMetric);		//	Metric Display Min
	ui.tableView->setColumnHidden(11, !m_bShowingMetric);		//	Metric Display Max
	ui.tableView->setColumnHidden(12, m_bShowingMetric);		//	Imperial Display Min
	ui.tableView->setColumnHidden(13, m_bShowingMetric);		//	Imperial Display Max

	ui.m_pTableViewDiscrete->setColumnHidden(4, !m_bShowingMetric);
	ui.m_pTableViewDiscrete->setColumnHidden(5, m_bShowingMetric);
}

void CXShowTemplates::slotSetCurrentDiscreteModelIndex(const QModelIndex& index)
{
	int row = index.row();
	int col = index.column();

	QSqlRecord record = m_pDiscreteModel->record(row);
	QStringList listProperties = record.value("Properties").toString().split(',');
	QStringList listColors = record.value("Colors").toString().split(',');

	Q_ASSERT(listProperties.size() == listColors.size());

	ui.m_pTableProperties->blockSignals(true);
	ui.m_pTableProperties->clearContents();
	ui.m_pTableProperties->setRowCount(listProperties.size());
	for (int i = 0; i != listProperties.size(); ++i)
	{
		auto pItemProperty = new QTableWidgetItem(listProperties.at(i));
		auto pItemColor = new CXButtonColorEdit(nullptr, QColor(listColors.at(i).toUInt()));

		ui.m_pTableProperties->setItem(i, 0, pItemProperty);
		ui.m_pTableProperties->setCellWidget(i, 1, pItemColor);

		connect(pItemColor, &CXButtonColorEdit::ColorSelected, this, &CXShowTemplates::slotDiscretePropertyChanged);
	}
	ui.m_pTableProperties->blockSignals(false);
}

void CXShowTemplates::slotNewDiscreteProperty()
{
	ui.m_pTableProperties->blockSignals(true);
	ui.m_pTableProperties->insertRow(ui.m_pTableProperties->rowCount());

	auto pItemProperty = new QTableWidgetItem("new property");
	auto pItemColor = new CXButtonColorEdit(ui.m_pTableProperties, ::GetRandomColor());

	ui.m_pTableProperties->setItem(ui.m_pTableProperties->rowCount() - 1, 0, pItemProperty);
	ui.m_pTableProperties->setCellWidget(ui.m_pTableProperties->rowCount() - 1, 1, pItemColor);

	connect(pItemColor, &CXButtonColorEdit::ColorSelected, this, &CXShowTemplates::slotDiscretePropertyChanged);
	ui.m_pTableProperties->blockSignals(false);

	ui.m_pTableProperties->setCurrentCell(ui.m_pTableProperties->rowCount() - 1, 0);
	ui.m_pTableProperties->editItem(pItemProperty);

	slotDiscretePropertyChanged();
}

void CXShowTemplates::slotDelDiscreteProperty()
{
	ui.m_pTableProperties->removeRow(ui.m_pTableProperties->currentRow());
	slotDiscretePropertyChanged();
}

void CXShowTemplates::slotDiscretePropertyChanged()
{
	QString strProperties, strColors;
	for (int i = 0; i != ui.m_pTableProperties->rowCount(); ++i)
	{
		strProperties += ui.m_pTableProperties->item(i, 0)->text();
		auto pItemColor = dynamic_cast<CXButtonColorEdit*>(ui.m_pTableProperties->cellWidget(i, 1));
		strColors += QString::number(pItemColor->GetColor().rgba());
	
		if (i != ui.m_pTableProperties->rowCount() - 1)
		{
			strProperties += ",";
			strColors += ",";
		}
	}

	QSqlRecord record = m_pDiscreteModel->record(ui.m_pTableViewDiscrete->currentIndex().row());
	record.setValue("Properties", strProperties);
	record.setValue("Colors", strColors);

	m_pDiscreteModel->setRecord(ui.m_pTableViewDiscrete->currentIndex().row(), record);
	setDirty();
}

void CXShowTemplates::slotDeleteTemplate()
{
	int iTabIndex = ui.tabWidget->currentIndex();

	if (0 == iTabIndex)
	{
		m_pContinuousModel->removeRow(ui.tableView->currentIndex().row());
	}
	else
	{
		m_pDiscreteModel->removeRow(ui.tableView->currentIndex().row());
	}

	setDirty();
}

void CXShowTemplates::closeWindow()
{
	if(m_bDirty)
	{
		int ret = QMessageBox::question(this, GetTr("Show Templates"), GetTr("要保存修改吗？"),
			QMessageBox::Yes | QMessageBox::No);

		if(ret == QMessageBox::Yes)
		{
			m_pContinuousModel->submitAll();
		}
	}

	close();
}

void CXShowTemplates::saveToDB()
{
	m_bDirty = false;
	m_pContinuousModel->submitAll();
	m_pDiscreteModel->submitAll();

	//	Disable the save/reset menu.
	ui.actionSave->setDisabled(true);
	ui.actionReset->setDisabled(true);

	CXTemplate::InitializeTemplates();
}

void CXShowTemplates::setDirty()
{
	m_bDirty = true;

	//	Enable the save/reset menu.
	ui.actionSave->setEnabled(true);
	ui.actionReset->setEnabled(true);
}

void CXShowTemplates::reset()
{
	int ret = QMessageBox::question(this, GetTr("Show Templates"), GetTr("要保存修改吗？"),
		QMessageBox::Yes | QMessageBox::No);

	if(ret == QMessageBox::Yes)
	{
		m_pContinuousModel->revertAll();
		m_pDiscreteModel->revertAll();
		m_bDirty = false;

		//	Disable the save/reset menu.
		ui.actionSave->setDisabled(true);
		ui.actionReset->setDisabled(true);
	}
}

void CXShowTemplates::newTemplate()
{
	int iTabIndex = ui.tabWidget->currentIndex();

	if (0 == iTabIndex)
	{
		_NewContinuousTemplate();
	}
	else
	{
		_NewDiscreteTemplate();
	}
}