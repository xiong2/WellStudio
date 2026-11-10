#include "xdlglfmintersection.h"
#include "xparameterlfmintersecton.h"
#include "xlfmgeometry.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgLFMIntersection)
EIntersectLFMAndWell
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgLFMIntersection)

CXDlgLFMIntersection::CXDlgLFMIntersection(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	m_pPara = dynamic_cast<CXParameterLFMIntersecton*>(pPara);
	m_pLFM = dynamic_cast<CXLFMGeometry*>(pParentObj);
	assert(m_pPara && m_pLFM);

	// two buttons
	QPixmap pixAdd, pixRemove;
	pixAdd.load(::GetIconPath() + "SelectAll.png");
	pixRemove.load(::GetIconPath() + "DisSelectAll.png");
	m_ui.m_pBtbAddAll->setIcon(QIcon(pixAdd));
	m_ui.m_pBtnRemoveAll->setIcon(QIcon(pixRemove));

	_Init();

	//	Connections
	connect(m_ui.m_pBtbAddAll, SIGNAL(clicked()), this, SLOT(slotAddAll()));
	connect(m_ui.m_pBtnRemoveAll, SIGNAL(clicked()), this, SLOT(slotRemoveAll()));
}

CXDlgLFMIntersection::~CXDlgLFMIntersection()
{
}

void CXDlgLFMIntersection::_Init()
{
	CXObject* pFolderObj = ::GetRootObjectFolder(EXWellFolder, false);
	if (!pFolderObj)
		return;

	QList<CXObject*>listObj = pFolderObj->GetChildren(EXWell, true);
	QList<CXWell*> listWell;
	for (int i = 0; i < listObj.size(); ++i)
	{
		CXWell* pWell = dynamic_cast<CXWell*>(listObj[i]);
		if (pWell  && pWell->GetWellTD())
		{
			QListWidgetItem* pItem = new QListWidgetItem(pWell->GetObjectName());
			pItem->setCheckState(Qt::Checked);
			pItem->setData(Qt::UserRole, pWell->GetObjectID());

			m_ui.m_pListWidget->addItem(pItem);
		}
	}
}

void CXDlgLFMIntersection::slotAddAll()
{
	for (int i = 0; i < m_ui.m_pListWidget->count(); ++i)
	{
		m_ui.m_pListWidget->item(i)->setCheckState(Qt::Checked);
	}
}

void CXDlgLFMIntersection::slotRemoveAll()
{
	for (int i = 0; i < m_ui.m_pListWidget->count(); ++i)
	{
		m_ui.m_pListWidget->item(i)->setCheckState(Qt::Unchecked);
	}
}

void CXDlgLFMIntersection::accept()
{
	std::vector<QUuid> vecWellID;
	for (int i = 0; i < m_ui.m_pListWidget->count(); ++i)
	{
		if (m_ui.m_pListWidget->item(i)->checkState() == Qt::Checked)
		{
			vecWellID.push_back(QUuid(m_ui.m_pListWidget->item(i)->data(Qt::UserRole).toString()));
		}
	}

	if (vecWellID.empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "At least one well has to be selected.");
		return;
	}
	else
	{
		m_pPara->SetVecWellID(vecWellID);
	}

	QDialog::accept();
}