
#include "xtableforascii.h"
#include "xsegytraceheader.h"
#include <QContextMenuEvent>
#include <QCursor>
#include <QMenu>
#include <QComboBox>
#include <QHeaderView>
#include <cassert>
#include "xpageloadsegy.h"
#include "xsegyloadparameters.h"
//#include "wizardforloadgsegy.h"

CXTableForLoadSegy::CXTableForLoadSegy(QWidget *parent):QTableWidget(parent)
{
	m_pTraceHeader = NULL;
	m_pStepPage2 = NULL;
	m_plistTraceHeaderItems = NULL;
	CXTableForLoadSegyItemDelegate *pItemDel = new CXTableForLoadSegyItemDelegate(this);
	setItemDelegate(pItemDel);
	m_listDescription.clear();
	m_listDescription<<"Trace number line"<<"Trace number reel"<<"Field record number"<<"Field trace number"
		<<"Energy source point"<<"CDP ensemble"<<"CDP trace number"<<"Trace ID code"<<"Number of vert.traces"<<"Number of hori.traces"
		<<"Data use"<<"Source/Rcvr distance"<<"Rcvr group elevation"<<"Source elevation"<<"Source depth"<<"Datum elev at receiver"
		<<"Datum elev at source"<<"Water depth at source"<<"water depth at group"<<"Scaler for 41-68"<<"Scaler for 73-88"
		<<"Source coordinate x"<<"Source coordinate y"<<"Group coordinate x"<<"Group coordinate y"<<"Coordinate units"<<"Weathering velocity"
		<<"Subweathering velocity"<<"Uphole time at source"<<"Uphole time at group"<<"Source static correction"<<"Group static correction"<<"Total static applied"
		<<"Lag time A"<<"Lag time B"<< "Delay recording time"<<"Mute start"<<"Mute end"<<"Number of samples"<<"Sample interval";
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	this->horizontalHeader()->setStretchLastSection(true);
	this->setEditTriggers(QAbstractItemView::CurrentChanged);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->verticalHeader()->setHidden(true);
	connect(pItemDel,SIGNAL(formatTypeChanged(int)),this,SLOT(slotFormatChanged(int)));
}

CXTableForLoadSegy::~CXTableForLoadSegy(void)
{
}

void CXTableForLoadSegy::SetData(CXSEGYTraceHeader* pTraceHeader)
{
	m_pTraceHeader = pTraceHeader;
	m_plistTraceHeaderItems = &m_pTraceHeader->GetAllItems();
	this->setColumnWidth(0,60);
	this->setColumnWidth(1,120);
	this->setColumnWidth(2,50);
	this->setColumnWidth(3,50);
	if(rowCount() == 0)
	{	
		setRowCount((*m_plistTraceHeaderItems).count());
		_initAscIIView();
	}
	else
	{
UpdateTableValue();
	}
}

void CXTableForLoadSegy::SetParentWidget(QWidget *parentWidget)
{
	m_pStepPage2 = dynamic_cast<CXPageLoadSegyStep2*>(parentWidget);
}

void CXTableForLoadSegy::contextMenuEvent(QContextMenuEvent * event)
{
	if (!m_pStepPage2)
		return;

	int nRow = rowAt(event->pos().y());
	int nRowCount = rowCount() - 1;
	if (nRow != -1)//-1 is invalid row number.
	{
		QMenu menu;
		menu.addAction("Set as Inline", this, SLOT(slotSetAsInline()));
		menu.addAction("Set as Crossline", this, SLOT(slotSetAsCrossLine()));
		if (m_pStepPage2->m_pDataPara->IsPrestack())
		{
			menu.addAction("Set as Offset", this, SLOT(slotSetAsOffset()));
		}
		if (m_pStepPage2 && m_pStepPage2->IsFromScan())
		{
			menu.addAction("Set as Coodinate X", this, SLOT(slotSetAsCoordinateX()));
			menu.addAction("Set as Coodinate Y", this, SLOT(slotSetAsCoordinateY()));
		}
		if (nRow > m_listDescription.count() - 1)
		{

			if ((*m_plistTraceHeaderItems)[nRow]->GetLength() > 2)
			{
				menu.addSeparator();
				menu.addAction("Split to 2 Rows", this, SLOT(slotSplit2Rows()));
			}
			if ((*m_plistTraceHeaderItems)[nRow]->GetLength() == 2)
			{
				menu.addSeparator();

				if (nRow <= nRowCount && (*m_plistTraceHeaderItems)[nRow - 1]->GetLength() == 2 && nRow - 1 >= m_listDescription.count())
				{
					menu.addAction("Merge to Previous Row", this, SLOT(slotMergePrevRow()));
				}
				if (nRow < nRowCount && (*m_plistTraceHeaderItems)[nRow + 1]->GetLength() == 2)
				{
					menu.addAction("Merge to Next Row", this, SLOT(slotMergeNextRow()));
				}
			}

		}
		menu.exec(QCursor::pos());
	}

}

void CXTableForLoadSegy::UpdateTableValue()
{
	CXSEGYTraceHeaderItem * pHeaderData = NULL;
	QTableWidgetItem *pValueItem = NULL;
	for (int nRow = 0; nRow < (*m_plistTraceHeaderItems).count(); ++nRow)
	{
		pHeaderData = (*m_plistTraceHeaderItems)[nRow];

		int i = 0;
		QComboBox *pCBBox = dynamic_cast<QComboBox *>(cellWidget(nRow, 2));
		if (pCBBox)
		{
			i = pCBBox->currentIndex();
		}

		pValueItem = this->item(nRow, 3);

		if (i == 0)
			pValueItem->setText(QString::number((int)(pHeaderData->GetValue())));
		else
			pValueItem->setText(QString::number(pHeaderData->GetValue(), 'f'));
	}
}

void CXTableForLoadSegy::_initAscIIView()
{
	QStringList listHeader;
	listHeader << "Bytes" << "Description" << "Format" << "Value";
	this->setHorizontalHeaderLabels(listHeader);
	CXSEGYTraceHeaderItem * pHeaderData = NULL;
	QTableWidgetItem *pInfomationItem = NULL;
	for (int nRow = 0; nRow < (*m_plistTraceHeaderItems).count(); ++nRow)
	{
		setRowHeight(nRow, 16);
		pHeaderData = (*m_plistTraceHeaderItems)[nRow];
		int nStart = pHeaderData->GetStartByte();
		QString strBytes = QString::number(nStart + 1) + "-" + QString::number(nStart + (int)pHeaderData->GetLength());
		pInfomationItem = new QTableWidgetItem(strBytes);
		pInfomationItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		pInfomationItem->setBackgroundColor(QColor(255, 251, 179));
		setItem(nRow, 0, pInfomationItem);//Bytes
		if (nRow < m_listDescription.count())
			pInfomationItem = new QTableWidgetItem(m_listDescription[nRow]);
		else
			pInfomationItem = new QTableWidgetItem();
		pInfomationItem->setBackgroundColor(QColor(255, 251, 179));
		pInfomationItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		setItem(nRow,1,pInfomationItem);//Description

		pInfomationItem = new QTableWidgetItem();
		pInfomationItem->setBackgroundColor(QColor(255, 251, 179));
		setItem(nRow, 2, pInfomationItem);//Format
		bool bDataIsFloat =  pHeaderData->IsFloat();
		if(bDataIsFloat)
		{
			pInfomationItem->setText("float");
		}
		else
		{
			pInfomationItem->setText("Integer");
		}
		if(pHeaderData->GetLength() >2)
		{
			pInfomationItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
		}
		else
		{	
			pInfomationItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		}

		pInfomationItem = new QTableWidgetItem(QString::number((int)pHeaderData->GetValue()));
		pInfomationItem->setBackgroundColor(QColor(255,251,179));
		pInfomationItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		setItem(nRow,3,pInfomationItem);//Value
	}
}
void CXTableForLoadSegy::slotFormatChanged(int nFormatType)
{
	int nCurrentTraceHeaderItem  = currentRow();
	int nInline,nCrossline,nX,nY;
	if (m_pStepPage2)
		m_pStepPage2->GetCoordinatePara(nInline,nCrossline,nX,nY);
	assert(nCurrentTraceHeaderItem <= (*m_plistTraceHeaderItems).count());
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurrentTraceHeaderItem];

	if(nFormatType == 0)//set format type to int
	{
		pHeaderDataItem->SetToFloat(false);
	}
	else
	{
		pHeaderDataItem->SetToFloat(true);
	}
	item(nCurrentTraceHeaderItem,3)->setText(QString::number(pHeaderDataItem->GetValue()));
	int nStartByte = pHeaderDataItem->GetStartByte()+1;
	if(nInline == nStartByte || nCrossline == nStartByte
		||nX == nStartByte || nY == nStartByte)
	{
		m_pStepPage2->setButtonText(QWizard::NextButton,"Scan");
	}

}


void CXTableForLoadSegy::slotSetAsInline()
{
	int nCurRow = this->currentRow();
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	m_pStepPage2->m_page2.m_EdtInline->setText(QString::number((int)pHeaderDataItem->GetStartByte()+1));
	m_pStepPage2->m_pDataPara->SetInlinePosition((int)pHeaderDataItem->GetStartByte()+1);

}
void CXTableForLoadSegy::slotSetAsCrossLine()
{
	int nCurRow = this->currentRow();
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	m_pStepPage2->m_page2.m_EdtCrossLine->setText(QString::number((int)pHeaderDataItem->GetStartByte() + 1));
	m_pStepPage2->m_pDataPara->SetCrosslinePosition((int)pHeaderDataItem->GetStartByte() + 1);

}
void CXTableForLoadSegy::slotSetAsOffset()
{
	int nCurRow = this->currentRow();
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	m_pStepPage2->m_page2.lineEditOffset->setText(QString::number((int)pHeaderDataItem->GetStartByte() + 1));
	m_pStepPage2->m_pDataPara->SetOffsetPosition((int)pHeaderDataItem->GetStartByte() + 1);

}
void CXTableForLoadSegy::slotSetAsCoordinateX()
{
	int nCurRow = this->currentRow();
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	m_pStepPage2->m_page2.m_EdtFileX->setText(QString::number((int)pHeaderDataItem->GetStartByte()+1));
	m_pStepPage2->m_pDataPara->SetXPosition((int)pHeaderDataItem->GetStartByte()+1);

}
void CXTableForLoadSegy::slotSetAsCoordinateY()
{
	int nCurRow = this->currentRow();
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	m_pStepPage2->m_page2.m_EdtFileY->setText(QString::number((int)pHeaderDataItem->GetStartByte()+1));
	m_pStepPage2->m_pDataPara->SetYPosition((int)pHeaderDataItem->GetStartByte()+1);
}
void CXTableForLoadSegy::slotSplit2Rows()
{
	int nCurRow = this->currentRow();
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	removeRow(nCurRow);
	insertRow(nCurRow);
	insertRow(nCurRow+1);
	setRowHeight(nCurRow,16);
	setRowHeight(nCurRow+1,16);
	(*m_plistTraceHeaderItems).removeAt(nCurRow);
	CXSEGYTraceHeaderItem *pTemItemnRow = new CXSEGYTraceHeaderItem(m_pTraceHeader,pHeaderDataItem->GetStartByte(),2,false);
	CXSEGYTraceHeaderItem *pTemItemnRow1 = new CXSEGYTraceHeaderItem(m_pTraceHeader,pHeaderDataItem->GetStartByte()+2,2,false);
	(*m_plistTraceHeaderItems).insert(nCurRow,pTemItemnRow);
	(*m_plistTraceHeaderItems).insert(nCurRow+1,pTemItemnRow1);

	QTableWidgetItem *pItem = NULL;
	QString strBytes = QString::number(pTemItemnRow->GetStartByte()+1) + "-"+QString::number(pTemItemnRow->GetStartByte()+pTemItemnRow->GetLength());
	pItem = new QTableWidgetItem(strBytes);
	pItem->setBackgroundColor(QColor(255, 251, 179));
	pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	this->setItem(nCurRow,0,pItem);//Bytes
	pItem = new QTableWidgetItem();
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	this->setItem(nCurRow,1,pItem);//Description
	pItem = new QTableWidgetItem("Integer");
	pItem->setBackgroundColor(QColor(255,251,179));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	this->setItem(nCurRow,2,pItem);//Format Type
	pItem = new QTableWidgetItem(QString::number(pTemItemnRow->GetValue()));
	pItem->setBackgroundColor(QColor(255,251,179));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	this->setItem(nCurRow,3,pItem);//Value

	strBytes = QString::number(pTemItemnRow1->GetStartByte()+1) + "-"+QString::number(pTemItemnRow1->GetStartByte()+pTemItemnRow1->GetLength());
	pItem = new QTableWidgetItem(strBytes);
	pItem->setBackgroundColor(QColor(255, 251, 179));
	pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	this->setItem(nCurRow+1,0,pItem);//Bytes
	pItem = new QTableWidgetItem();
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	this->setItem(nCurRow+1,1,pItem);//Description
	pItem = new QTableWidgetItem("Integer");
	pItem->setBackgroundColor(QColor(255,251,179));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	this->setItem(nCurRow+1,2,pItem);//Format Type
	pItem = new QTableWidgetItem( QString::number(pTemItemnRow1->GetValue()));
	pItem->setBackgroundColor(QColor(255,251,179));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	this->setItem(nCurRow+1,3,pItem);//Value
}
void CXTableForLoadSegy::slotMergeNextRow()
{
	int nCurRow = this->currentRow();
	assert(nCurRow != this->rowCount());

	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow];
	removeRow(nCurRow+1);
	setRowHeight(nCurRow,16);
	CXSEGYTraceHeaderItem *pTemItemnRow = new CXSEGYTraceHeaderItem(m_pTraceHeader,pHeaderDataItem->GetStartByte(),4,true);
	(*m_plistTraceHeaderItems).insert(nCurRow,pTemItemnRow);
	(*m_plistTraceHeaderItems).removeAt(nCurRow+1);
	(*m_plistTraceHeaderItems).removeAt(nCurRow+1);


	QTableWidgetItem *pItem = item(nCurRow,0);
	QString strBytes = QString::number(pTemItemnRow->GetStartByte()+1) + "-"+QString::number(pTemItemnRow->GetStartByte()+pTemItemnRow->GetLength());
	pItem->setBackgroundColor(QColor(255, 251, 179));
	pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	pItem->setText(strBytes);//Bytes

	pItem = item(nCurRow,1);
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	pItem->setText("");//Description

	pItem = item(nCurRow,2);
	pItem->setBackgroundColor(QColor(255, 251, 179));
	pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	pItem->setText("float");//Format Type

	pItem = item(nCurRow,3);
	pItem->setBackgroundColor(QColor(255,251,179));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	pItem->setText(QString::number(pTemItemnRow->GetValue()));//Value
}
void CXTableForLoadSegy::slotMergePrevRow()
{
	int nCurRow = currentRow();
	assert(nCurRow >= m_listDescription.count());
	CXSEGYTraceHeaderItem * pHeaderDataItem = (*m_plistTraceHeaderItems)[nCurRow-1];
	removeRow(nCurRow);
	setRowHeight(nCurRow,16);
	CXSEGYTraceHeaderItem *pTemItemnRow = new CXSEGYTraceHeaderItem(m_pTraceHeader,pHeaderDataItem->GetStartByte(),4,true);
	(*m_plistTraceHeaderItems).insert(nCurRow,pTemItemnRow);
	(*m_plistTraceHeaderItems).removeAt(nCurRow+1);
	(*m_plistTraceHeaderItems).removeAt(nCurRow-1);



	QTableWidgetItem *pItem = item(nCurRow-1,0);
	QString strBytes = QString::number(pTemItemnRow->GetStartByte()+1) + "-"+QString::number(pTemItemnRow->GetStartByte()+pTemItemnRow->GetLength());
	pItem->setBackgroundColor(QColor(196,251,210));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	pItem->setText(strBytes);//Bytes

	pItem = item(nCurRow-1,1);
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	pItem->setText("");//Description

	pItem = item(nCurRow-1,2);
	pItem->setBackgroundColor(QColor(196,251,210));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
	pItem->setText("float");//Format Type

	pItem = item(nCurRow-1,3);
	pItem->setBackgroundColor(QColor(255,251,179));
	pItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	pItem->setText(QString::number(pTemItemnRow->GetValue()));//Value
}
CXTableForLoadSegyItemDelegate::CXTableForLoadSegyItemDelegate(QObject *parent)
	: QItemDelegate(parent)
{
}

QWidget *CXTableForLoadSegyItemDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &/* option */,
	const QModelIndex &/* index */) const
{
	QComboBox *editor = new QComboBox(parent);
	editor->addItem("Integer");
	editor->addItem("Float");
	connect(editor,SIGNAL(currentIndexChanged (int)),this,SLOT(slotEmitFormatTypeChanged(int)));
	return editor;
}

void CXTableForLoadSegyItemDelegate::slotEmitFormatTypeChanged(int nType)
{
	emit formatTypeChanged(nType);
}

void CXTableForLoadSegyItemDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();

	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	comboBox->setCurrentIndex(comboBox->findText(value));
}

void CXTableForLoadSegyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	QString value = comboBox->currentText();

	model->setData(index, value, Qt::EditRole);
}

void CXTableForLoadSegyItemDelegate::updateEditorGeometry(QWidget *editor,
	const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
