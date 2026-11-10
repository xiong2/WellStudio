#include "xpageselectformation.h"

#include <cassert>
#include <QMessageBox>
#include <QListWidgetItem>

#include "xparameterwellhorzionintersect.h"
#include "xglobal.h"
#include "xobject.h"

CXPageSelectFormation::CXPageSelectFormation(CXParameterWellHorzionIntersect* pPara, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);
	m_pPara = pPara;

	QList<CXObject*> listSurfaceObj = ::GetRootObjectFolder(EXSurfaceFolder)->GetChildren(EX3DSurface, true);

	foreach(CXObject* obj, listSurfaceObj)
	{
		double dMin, dMax;
		obj->GetDataRange(dMin, dMax);
		m_mapSurfaceObj.insert(dMax, obj);
	}
}

void CXPageSelectFormation::initializePage()
{
	foreach(CXObject* obj, m_mapSurfaceObj)
	{
		QListWidgetItem *item = new QListWidgetItem(obj->GetObjectName(), m_ui.m_lwgtFormation);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setCheckState(Qt::Unchecked);
	}

	connect(m_ui.m_pbSelectAll, SIGNAL(clicked()), this, SLOT(_SelectAllItem()));
	connect(m_ui.m_pbUnSelectAll, SIGNAL(clicked()), this, SLOT(_UnSelectAllItem()));
}

bool CXPageSelectFormation::validatePage()
{
	// get selected formation
	QStringList listSelectedName;
	std::vector<QUuid> vecSelectedUid;

	QMapIterator<double, CXObject*> iter(m_mapSurfaceObj);
	for (int i=0; i<m_ui.m_lwgtFormation->count(); ++i)
	{
		iter.next();
		if (m_ui.m_lwgtFormation->item(i)->checkState())
		{
			listSelectedName << iter.value()->GetObjectName();
			vecSelectedUid.push_back(iter.value()->GetObjectID());
		}
	}

	if (listSelectedName.size() < 2)
	{
		QMessageBox::warning(NULL, tr("Select Formation"), tr("Please select at least two of formations!"));
		return false;
	}

	// save result
	m_pPara->SetHorizonNameList(listSelectedName);
	m_pPara->SetvecHorizonID(vecSelectedUid);

	return true;
}

void CXPageSelectFormation::_SelectAllItem()
{
	for (int i=0; i<m_ui.m_lwgtFormation->count(); ++i)
	{
		m_ui.m_lwgtFormation->item(i)->setCheckState(Qt::Checked);
	}
}

void CXPageSelectFormation::_UnSelectAllItem()
{
	for (int i=0; i<m_ui.m_lwgtFormation->count(); ++i)
	{
		m_ui.m_lwgtFormation->item(i)->setCheckState(Qt::Unchecked);
	}
}