#include "stdafx.h"
#include "xglobal.h"
#include "gspdgscene.h"
#include "gspdgwindow.h"
#include "gspdg.h"
#include "gsfrg.h"
#include "gsitempdg.h"
#include "gsitemfrg.h"

GSPDGScene::GSPDGScene(GSPDGWindow * pWindow, QObject * parent) : QGraphicsScene(parent) 
{
	m_pWindow = pWindow;
	m_dHScale = 3.;
	m_dVScale = 0.15;
	m_pPDGItem = NULL;
}

GSPDGScene::~GSPDGScene() 
{
	
}

void GSPDGScene::AddObjectItem(CXObject *pObj)
{
	//	Clear all exist items.
	RemoveObjectItem();

	EXObjectType eType = pObj->GetObjectType();
	if (eType == EXGSPDG)
	{
		GSPDG *pPDG = dynamic_cast<GSPDG *>(pObj);

		////	Resize the canvas.
		QVector<float>& vecPoints = pPDG->GetStressPoints();
		double dLen = vecPoints[vecPoints.size() - 3], dHei = vecPoints[vecPoints.size() - 5];
		if(vecPoints[vecPoints.size() - 2] > 1)
			dLen *= vecPoints[vecPoints.size() - 2];
		double dWidth = LEFT_MARGIN + RIGHT_MARGIN + dLen * m_dHScale;
		double dHeight = TOP_MARGIN + BOTTOM_MARGIN + dHei * m_dVScale;
		QRectF rect(0, 0, dWidth, dHeight);
		setSceneRect(rect);

		m_pPDGItem = new GSItemPDG(pPDG, m_pWindow->GetObjectViewInfo(pPDG->GetObjectID()));
	}
	else if (eType == EXGSFRG)
	{
		GSFRG *pPDG = dynamic_cast<GSFRG *>(pObj);

		////	Resize the canvas.
		QVector<float>& vecDepth = pPDG->GetVecData(0);
		double dLen = 160, dHei = vecDepth.last();
		double dWidth = LEFT_MARGIN + RIGHT_MARGIN + dLen * m_dHScale;
		double dHeight = TOP_MARGIN + BOTTOM_MARGIN + dHei * m_dVScale;
		QRectF rect(0, 0, dWidth, dHeight);
		setSceneRect(rect);

		m_pPDGItem = new GSItemFRG(pPDG, m_pWindow->GetObjectViewInfo(pPDG->GetObjectID()));
	}

	addItem(m_pPDGItem);
}

void GSPDGScene::RemoveObjectItem(CXObject *pObj)
{
	if (!pObj || pObj->GetObjectType() == EXGSPDG || pObj->GetObjectType() == EXGSFRG)
	{
		clear();
		m_pPDGItem = NULL;
	}
	else
	{
		for (QGraphicsItem* pItem : items())
		{
			auto pObjectItem = dynamic_cast<GSObjItem *>(pItem);
			if (!pObjectItem)
				continue;
			if (pObj->GetObjectID() == pObjectItem->GetObjectID())
			{
				removeItem(pObjectItem);
				delete pObjectItem;
				break;
			}
		}
	}
}

void GSPDGScene::SetScale(double dHScale, double dVScale)
{
	//m_dHScale = dHScale;
	//m_dVScale = dVScale;

	////	Find the section item and calculate the new size.
	//for (QGraphicsItem* pItem : items())
	//{
	//	auto pObjectItem = dynamic_cast<GSItemProfile *>(pItem);
	//	if (!pObjectItem)
	//		continue;

	//	GSSection *pSection = dynamic_cast<GSSection *>(xGlobal.GetObjectByID(pObjectItem->GetObjectID()));

	//	//	Resize the canvas.
	//	double dLen = pSection->GetSectionLength(), dHei = pSection->GetSectionHeight();
	//	double dWidth = LEFT_MARGIN + RIGHT_MARGIN + dLen * m_dHScale;
	//	double dHeight = TOP_MARGIN + BOTTOM_MARGIN + dHei * m_dVScale;
	//	QRectF rect(0, 0, dWidth, dHeight);
	//	setSceneRect(rect);
	//}

	//UpdateView();
}

void GSPDGScene::UpdateView()
{
	for (QGraphicsItem* pItem : items())
	{
		pItem->update();
	}
}

int GSPDGScene::ZToSceneY(float fZ)
{
	return TOP_MARGIN + fZ * m_dVScale;
}

float GSPDGScene::SceneYToZ(int iY)
{
	if (iY < TOP_MARGIN)
		return 0;

	return (iY - TOP_MARGIN) / m_dVScale;
}

bool GSPDGScene::SceneXToXY(int iX, double& dX, double& dY)
{
	//if(!m_pProfileItem)
	//	return false;

	//return m_pProfileItem->SceneXToXY(iX, dX, dY);
	return false;
}

void GSPDGScene::HandleMouseEvent(QMouseEvent* event, EXGSMouseEventType eMType)
{
	//if (!m_pProfileItem)
	//	return;

	//if (eMType == eSecMouseMove)
	//{
	//	double dX, dY;
	//	QPoint pos = event->pos();
	//	QPointF fPos = views()[0]->mapToScene(pos);
	//	float fZ = SceneYToZ(fPos.y());

	//	if (SceneXToXY(fPos.x(), dX, dY))
	//	{
	//		m_pWindow->ShowState("Position: (" + QString::number(dX) + ", " + QString::number(dY, 'f', 0) + ", " + QString::number(fZ) + ")");
	//		m_pWindow->BroadcastPosition(dX, dY, fZ);
	//	}
	//	else
	//	{
	//		m_pWindow->ShowState("");
	//	}
	//}
}
