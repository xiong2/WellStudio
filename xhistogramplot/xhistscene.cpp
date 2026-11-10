#include <qmessagebox.h>
#include "xhistscene.h"
#include "xeventconsole.h"
#include "xhistogramplot.h"
#include "xglobal.h"
#include "xhistitem.h"
#include "xhistitemanno.h"
#include "xhistitemname.h"
#include "xaxis.h"

#define SCENEMARGIN 20

CXHistScene::CXHistScene(CXWindow* pWindow, QObject *parent) : CXScene(pWindow, parent)
{
	m_pWindow = (CXHistogramPlot *)pWindow;
}

CXHistScene::~CXHistScene()
{

}

bool CXHistScene::CreateItem(QUuid objectID, CXViewInfoObject* pViewInfo)
{
	if (m_mapItem.contains(objectID))
		return false;

	auto pObject = dynamic_cast<CXObject*>(GetObjectByID(objectID));

	if (m_eObjType == EXEnd)
	{
		if (pObject->GetObjectType() == EXWellCurve)
			m_eObjType = pObject->GetTemplateID();
		else
			m_eObjType = pObject->GetObjectType();
	}
	else if ((pObject->GetObjectType() == EXWellCurve && pObject->GetTemplateID() != m_eObjType)
		|| (pObject->GetObjectType() != EXWellCurve && pObject->GetObjectType() != m_eObjType))
	{
		QMessageBox::warning(NULL, "Histogram Window", "Only the objects with same type or template could be displayed together!");
		return false;
	}

	CXHistogram histogram = pObject->GetHistogram();
	m_dDMin = qMin(m_dDMin, histogram.m_dDataMin);
	m_dDMax = qMax(m_dDMax, histogram.m_dDataMax);
	if (m_dDMin == m_dDMax)
		return false;

	if (!m_pAxisX)
	{
		m_pAxisX = new CXAxis(m_dDMin, m_dDMax);
		m_pAxisX->SetAxisType(CXAxis::XAxis);
	}
	else
	{
		m_pAxisX->SetBegin(m_dDMin);
		m_pAxisX->SetEnd(m_dDMax);
	}

	if (!m_pAxisY)
	{
		m_pAxisY = new CXAxis(0., 100.);
	}

	QRectF rect = sceneRect();
	rect.adjust(SCENEMARGIN, SCENEMARGIN, -SCENEMARGIN, -SCENEMARGIN);

	if (!m_pAnnoItem)
	{
		m_pAnnoItem = new CXHistItemAnno(rect, m_pAxisX, m_pAxisY, 100);
		addItem(m_pAnnoItem);
	}

	if (!m_pNameItem)
	{
		m_pNameItem = new CXHistItemName(rect);
		addItem(m_pNameItem);
	}
	
	QString sName = pObject->GetObjectName();
	if (pObject->GetObjectType() == EXWellCurve)
	{
		sName = pObject->GetParent()->GetObjectName() + "-" + sName;
	}
	m_pNameItem->AddItem(objectID, sName, pObject->GetColor());

	CXHistItem *pItem = new CXHistItem(histogram, rect, m_pAxisX, m_pAxisY);
	pItem->SetColor(pObject->GetColor());
	pItem->setZValue(m_iZValue++);
	addItem(pItem);
	m_mapItem.insert(objectID, pItem);

	m_dYMax = qMax(m_dYMax, pItem->Get2ndMaxValue());
	m_pAxisY->SetEnd(m_dYMax * 1.2);

	return true;
}

bool CXHistScene::DeleteItem(QUuid objectID)
{
	if (m_mapItem.contains(objectID))
	{
		CXHistItem *pItem = m_mapItem.value(objectID);
		m_mapItem.remove(objectID);
		removeItem(pItem);
		delete pItem;

		if (m_mapItem.isEmpty())
		{
			initialize();
		}

		return true;
	}

	return false;
}

void CXHistScene::initialize()
{
	if (!m_mapItem.isEmpty())
		return;

	if (m_pAnnoItem)
	{
		removeItem(m_pAnnoItem);
		delete m_pAnnoItem;
		m_pAnnoItem = NULL;
	}

	if (m_pNameItem)
	{
		removeItem(m_pNameItem);
		delete m_pNameItem;
		m_pNameItem = NULL;
	}

	m_eObjType = EXEnd;
	m_iZValue = 1;
	m_dDMin = 99999999.;
	m_dDMax = -99999999.;
	m_dYMax = -99999999.;
}