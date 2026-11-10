#include <qmessagebox.h>
#include "gsdlgselecthorizon.h"
#include "gsgeologicstage.h"

GSDlgSelectHorizon::GSDlgSelectHorizon(CXObject *pObj, GSGeologicStage *pGStage, QWidget *parent)
	: QDialog(parent), m_pSurvey(pObj), m_pStage(pGStage)
{
	ui.setupUi(this);

	QList<CXObject *> listHor = m_pSurvey->GetChildren(EXGSFolderHorizon, true);
	QStringList strList;
	foreach(CXObject *pHF, listHor)
	{
		strList << pHF->GetObjectName();
	}
	ui.listWidget->addItems(strList);

	ui.listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

GSDlgSelectHorizon::~GSDlgSelectHorizon()
{

}

void GSDlgSelectHorizon::accept()
{
	QList<QListWidgetItem *> listItem = ui.listWidget->selectedItems();
	if (listItem.isEmpty())
	{
		QMessageBox::warning(NULL, "Select horizons", "No horizon selected!");
		return;
	}
	QList<CXObject *> listStage = m_pSurvey->GetChildren(EXGSGeologicStage, true);
	QList<CXObject *> listHor = m_pSurvey->GetChildren(EXGSFolderHorizon);
	foreach(QListWidgetItem *pItem, listItem)
	{
		QString sName = pItem->text();
		CXObject *pHor = NULL;

		foreach(CXObject *pObj, listHor)
		{
			if (sName == pObj->GetObjectName())
			{
				pHor = pObj;
				break;
			}
		}

		QUuid objID = pHor->GetObjectID();

		foreach(CXObject *pObj, listStage)
		{
			GSGeologicStage *pStage = (GSGeologicStage *)pObj;
			QList<QUuid>& listHID = pStage->GetAllHID();

			if (listHID.contains(objID))
			{
				listHID.removeOne(objID);
			}

			if(pStage == m_pStage)
				listHID << objID;
		}
	}

	QDialog::accept();
}