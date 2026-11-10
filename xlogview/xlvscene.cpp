#include <qmessagebox.h>
#include <qgraphicssceneevent.h>
#include "xlvscene.h"
#include "xlvwindowinfo.h"
#include "xlvitemwell.h"
#include "xlvitemcurve.h"
#include "xlvitemwelltops.h"
#include "xglobal.h"
#include "xwellcurve.h"
#include "xtemplate.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xlogview.h"

CXLVScene::CXLVScene(CXWindow *pWindow, QObject *pParent) : CXScene(pWindow, pParent)
{
	m_pWindowViewInfo = new CXLVWindowInfo;
}

CXLVScene::~CXLVScene()
{
	delete m_pWindowViewInfo;

	foreach(CXLVItemWell *pItem, m_vecWellItem)
	{
		removeItem(pItem);
		delete pItem;
	}

	if (m_pTopsItem)
	{
		removeItem(m_pTopsItem);
		delete m_pTopsItem;
	}
}

bool CXLVScene::CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo)
{
	CXObject *pObj = ::GetObjectByID(objectID);
	if (pObj->GetObjectType() == EXWell)
	{
		foreach(CXLVItemWell *pWItem, m_vecWellItem)
		{
			if (pWItem->GetObjectID() == objectID)
				return true;
		}

		qreal dSZ, dEZ;
		CXWell *pWell = (CXWell *)pObj;
		pWell->GetDepthRange(dSZ, dEZ);
		CXLVWindowInfo *pWInfo = (CXLVWindowInfo *)m_pWindowViewInfo;
		pWInfo->m_dSDepth = qMin(pWInfo->m_dSDepth, dSZ);
		pWInfo->m_dEDepth = qMax(pWInfo->m_dEDepth, dEZ);

		CXLVItemWell *pItem = new CXLVItemWell(this, objectID, pViewInfo);
		m_vecWellItem << pItem;

		setSceneRect(QRectF(0, 0, GetRightEdge() + pWInfo->m_iHIntv, GetBottomEdge() + MARGIN));

		addItem(pItem);
		update();
		return true;
	}
	else if (pObj->GetObjectType() == EXWellCurve)
	{
		//	Need do nothing with depth track.
		if (pObj->GetTemplateID() == CXTemplate::GetTemplate("MD")->GetID())
			return true;

		CXObject *pParent = pObj->GetParent();
		CXLVItemWell *pWItem = findWellItem(pParent->GetObjectID());
		if (!pWItem)
		{
			qDebug() << "Seems somewhere wrong!";
			return false;
		}

		QList<QGraphicsItem *> listGItem = pWItem->childItems();
		foreach(QGraphicsItem *pGItem, listGItem)
		{
			CXLVItemCurve *pCItem = dynamic_cast<CXLVItemCurve *>(pGItem);
			if (pCItem)
			{
				if (pCItem->GetObjectID() == objectID)
					return true;
			}
		}

		CXLVItemCurve *pItem = new CXLVItemCurve(this, objectID, pViewInfo, pWItem);
		addItem(pItem);
		update();
		return true;
	}
	else if (pObj->GetObjectType() == EXWellTops)
	{
		if (m_vecWellItem.isEmpty())
		{
			QMessageBox::warning(NULL, "Log View", "Well tops only can be shown after wells being shown!");
			return false;
		}

		//	So far only one tops item.
		if (m_pTopsItem)
		{
			removeItem(m_pTopsItem);
			delete m_pTopsItem;
		}

		m_pTopsItem = new CXLVItemWellTops(this, objectID, pViewInfo);
		addItem(m_pTopsItem);
		update();
		return true;
	}

	return false;
}

bool CXLVScene::DeleteItem(QUuid objectID)
{
	CXObject *pObj = ::GetObjectByID(objectID);
	if (pObj->GetObjectType() == EXWell)
	{
		for (int i = 0; i < m_vecWellItem.size(); i++)
		{
			if (m_vecWellItem[i]->GetObjectID() == objectID)
			{
				CXLVItemWell *pItem = m_vecWellItem[i];
				m_vecWellItem.removeAt(i);
				removeItem(pItem);
				delete pItem;

				update();

				return true;
			}
		}

		return false;
	}
	else if (pObj->GetObjectType() == EXWellCurve)
	{
		CXObject *pParent = pObj->GetParent();
		CXLVItemWell *pWItem = NULL;
		foreach(CXLVItemWell *pItem, m_vecWellItem)
		{
			if (pItem->GetObjectID() == pParent->GetObjectID())
			{
				pWItem = pItem;
				break;
			}
		}
		if (!pWItem)
			return false;

		CXLVItemCurve *pCItem = NULL;
		QList<QGraphicsItem *> listItem = pWItem->childItems();
		foreach(QGraphicsItem *pItem, listItem)
		{
			pCItem = dynamic_cast<CXLVItemCurve *>(pItem);
			if (!pCItem)
				continue;

			if (pCItem->GetObjectID() == objectID)
				break;
			pCItem = NULL;
		}
		if (!pCItem)
			return false;

		QRectF rect = pCItem->rect();
		listItem.removeOne(pCItem);
		removeItem(pCItem);
		delete pCItem;

		update();
		return true;
	}
	else if (pObj->GetObjectType() == EXWellTops)
	{
		if (!m_pTopsItem)
			return false;

		if (pObj->GetObjectID() == m_pTopsItem->GetObjectID())
		{
			removeItem(m_pTopsItem);
			delete m_pTopsItem;
			m_pTopsItem = NULL;
			return true;
		}
	}

	return false;
}

void CXLVScene::mouseMoveEvent(QGraphicsSceneMouseEvent *pEvent)
{
	if (m_vecWellItem.isEmpty())
		return;

	QString sMessage;
	CXLogView *pWindow = (CXLogView *)m_pWindow;
	QPointF pos = pEvent->scenePos();

	foreach(CXLVItemWell *pWItem, m_vecWellItem)
	{
		if (pWItem->contains(pos))
		{
			CXWell *pWell = (CXWell *)::GetObjectByID(pWItem->GetObjectID());
			sMessage = "Well: " + pWell->GetObjectName();

			QList<QGraphicsItem *> listCItem = pWItem->childItems();
			foreach(QGraphicsItem *pGItem, listCItem)
			{
				CXLVItemCurve *pCItem = dynamic_cast<CXLVItemCurve *>(pGItem);
				if (pCItem)
				{
					if (pCItem->contains(pos))
					{
						CXWellCurve *pCurve = (CXWellCurve *)::GetObjectByID(pCItem->GetObjectID());
						sMessage = sMessage + ", Curve: " + pCurve->GetObjectName();

						qreal dDepth, dValue;
						if (pCItem->GetValue(pos.y(), dDepth, dValue))
						{
							sMessage = sMessage + ", Depth: " + QString::number(dDepth);
							sMessage = sMessage + ", Value: " + QString::number(dValue);
						}

						break;
					}
				}
			}

			pWindow->ShowStatus(sMessage);
			return;
		}
	}
}

void CXLVScene::update()
{
	qreal dLastRight = 0.;
	foreach(CXLVItemWell *pWItem, m_vecWellItem)
	{
		pWItem->Configure(dLastRight);

		dLastRight = pWItem->rect().right();
	}

	QGraphicsScene::update();
}

qreal CXLVScene::GetRightEdge()
{
	if (m_vecWellItem.isEmpty())
		return 0;
	else
	{
		return m_vecWellItem.last()->rect().right();
	}
}

qreal CXLVScene::GetBottomEdge()
{
	qreal dBottom = 0.;

	foreach(CXLVItemWell *pItem, m_vecWellItem)
	{
		dBottom = qMax(dBottom, pItem->rect().bottom());
	}

	return dBottom;
}

CXLVItemWell* CXLVScene::findWellItem(QUuid wellID)
{
	foreach(CXLVItemWell *pItem, m_vecWellItem)
	{
		if (pItem->GetObjectID() == wellID)
			return pItem;
	}

	return NULL;
}