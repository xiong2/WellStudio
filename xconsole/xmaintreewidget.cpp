#include "xmaintreewidget.h"
#include "xtreewidgetitem.h"
#include "xglobal.h"
#include "xobject.h"
#include <qmenu.h>
#include "xrbm.h"
#include "xconsole.h"
#include "xdef.h"
#include "xeventconsole.h"

#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include "xwellcurve.h"
#include "xwell.h"

CXMainTreeWidget::CXMainTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{	
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setExpandsOnDoubleClick(false);

	connect(this, SIGNAL(itemChanged (QTreeWidgetItem*, int)), this, SLOT(slotItemChanged(QTreeWidgetItem *, int)));
	connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(slotItemActivated(QTreeWidgetItem *,QTreeWidgetItem *)));
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(slotDoubleClicked(QTreeWidgetItem *, int)));
}

CXMainTreeWidget::~CXMainTreeWidget()
{
}

void CXMainTreeWidget::contextMenuEvent (QContextMenuEvent * e)
{
	QList<QTreeWidgetItem*> listItem = this->selectedItems();
	if (listItem.empty())
		return;

	CXTreeWidgetItem* pRLItem = dynamic_cast<CXTreeWidgetItem*>(listItem.front());
	if (!pRLItem)
		return;

	CXObject* pObj = pRLItem->GetKEObject();
	if (!pObj)
		return;

	QMenu menu;

	CXRBM rbm(menu, pObj);

	if (listItem.size() == 1)
		rbm.AddAction();
	else
		rbm.AddDeleteAction();

	menu.exec(QCursor::pos());
}

void CXMainTreeWidget::slotItemChanged(QTreeWidgetItem *pItem, int)
{
	CXTreeWidgetItem* pRLItem = dynamic_cast<CXTreeWidgetItem*>(pItem);
	if (!pRLItem)
		return;

	CXObject* pObj = pRLItem->GetKEObject();
	if (!pObj)
		return;

	bool bVisible = (pRLItem->checkState(0) == Qt::Checked);
	::GetConsole()->SetObjectVisibility(pObj->GetObjectID(), bVisible);

	//Rename
	if (pRLItem->text(0) != pObj->GetObjectName())
	{
		pRLItem->SetName(pRLItem->text(0));
		pObj->SetObjectName(pRLItem->GetName());

		CXProcessEvent processEvent;
		pObj->AddEvent(EDataChanged);
	}
}

void CXMainTreeWidget::slotItemActivated(QTreeWidgetItem *pCurrentItem, QTreeWidgetItem *pPreviousItem)
{
	disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(sloItemChanged(QTreeWidgetItem *, int)));

	if (!pCurrentItem)
		return;

	if (pPreviousItem)
	{
		pPreviousItem->setFont(0, pCurrentItem->font(0));
		pPreviousItem->setBackgroundColor(0, Qt::white);
	}

	QFont bold_font(pCurrentItem->font(0));
	bold_font.setBold(true);
	pCurrentItem->setFont(0, bold_font);
	pCurrentItem->setBackgroundColor(0, QColor(51, 153, 255));

	connect(this, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(sloItemChanged(QTreeWidgetItem *, int)));
}

void CXMainTreeWidget::slotDoubleClicked(QTreeWidgetItem *pItem, int nColumn)
{
	CXTreeWidgetItem* pRLItem = dynamic_cast<CXTreeWidgetItem*>(pItem);
	if (!pRLItem)
		return;	

	QMenu menu;

	CXRBM rbm(menu, pRLItem->GetKEObject());
	rbm.slotProperties();	
}

void CXMainTreeWidget::slotItemEditDone()
{
	
}

void CXMainTreeWidget::mousePressEvent(QMouseEvent *e)
{
	QTreeWidget::mousePressEvent(e);
	m_lstPress.clear();
	//    m_bDragging = true;	
	if (e->button() != Qt::LeftButton) {//·Ç×ó¼üÍË³ö
		return;
	}

	QList<QTreeWidgetItem*> lstItems = this->selectedItems();
	for (int i = 0; i < lstItems.count(); i++)
	{
		CXTreeWidgetItem* PressItem = dynamic_cast<CXTreeWidgetItem*>(lstItems[i]);
		if (!PressItem)
		{
			continue;
		}
		CXObject   *pObj = PressItem->GetKEObject();
		if (dynamic_cast<CXWellCurve*>(pObj)
			|| dynamic_cast<CXWell*>(pObj))
		{
			m_lstPress.append(pObj->GetObjectID());
			m_PressPos = e->pos();
		}

	}

}
#include <QTime>
#include <QDebug>
void CXMainTreeWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (!(e->buttons() & Qt::LeftButton))
		return;
	if ((e->pos() - m_PressPos).manhattanLength()
		< QApplication::startDragDistance())      {
		return;
	}
	if (m_lstPress.count() < 1)
	{
		return;
	}

	QString strMimeData;
	QString strTextData;
	for (int i = 0; i < m_lstPress.count(); i++)
	{
		strMimeData += m_lstPress[i].toString() + ";";
		CXObject* pObject = GetObjectByID(m_lstPress[i]);	
		if (pObject)
		{
			if (strTextData.isEmpty()==false)
			{
				strTextData += "\t";
			}
			strTextData += pObject->GetObjectName();
		}
	}
	
	QDrag *drg = new QDrag(this);
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("text/xstudio", strMimeData.toLatin1());
	mimeData->setText(strTextData);
	drg->setMimeData(mimeData);
	Qt::DropAction dropAction = drg->exec(Qt::CopyAction | Qt::MoveAction);

}

void CXMainTreeWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QTreeWidget::mouseReleaseEvent(e);
	//	m_bDragging = false;
}