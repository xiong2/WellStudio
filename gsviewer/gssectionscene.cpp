#include "stdafx.h"
#include "xglobal.h"
#include "gssectionscene.h"
#include "gssectionwindow.h"
#include "gssection.h"
#include "gsitemprofile.h"

GSSectionScene::GSSectionScene(GSSectionWindow * pWindow, QObject * parent) : QGraphicsScene(parent) 
{
	m_pWindow = pWindow;
	m_dHScale = 0.1;
	m_dVScale = 0.1;
	m_pProfileItem = NULL;
}

GSSectionScene::~GSSectionScene() 
{
	
}

void GSSectionScene::AddObjectItem(CXObject *pObj)
{
	GSSection *pSection = dynamic_cast<GSSection *>(pObj);
	if (!pSection)
		return;

	//	Clear all exist items.
	RemoveObjectItem();

	//	Resize the canvas.
	double dLen = pSection->GetSectionLength(), dHei = pSection->GetSectionHeight();
	double dWidth = LEFT_MARGIN + RIGHT_MARGIN + dLen * m_dHScale;
	double dHeight = TOP_MARGIN + BOTTOM_MARGIN + dHei * m_dVScale;
	QRectF rect(0, 0, dWidth, dHeight);
	setSceneRect(rect);

	m_pProfileItem = new GSItemProfile(pSection, m_pWindow->GetObjectViewInfo(pSection->GetObjectID()));
	addItem(m_pProfileItem);
}

void GSSectionScene::RemoveObjectItem(CXObject *pObj)
{
	if (!pObj || pObj->GetObjectType() == EXGSSection)
	{
		clear();
		m_pProfileItem = NULL;
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

void GSSectionScene::SetScale(double dHScale, double dVScale)
{
	m_dHScale = dHScale;
	m_dVScale = dVScale;

	//	Find the section item and calculate the new size.
	for (QGraphicsItem* pItem : items())
	{
		auto pObjectItem = dynamic_cast<GSItemProfile *>(pItem);
		if (!pObjectItem)
			continue;

		GSSection *pSection = dynamic_cast<GSSection *>(GetObjectByID(pObjectItem->GetObjectID()));

		//	Resize the canvas.
		double dLen = pSection->GetSectionLength(), dHei = pSection->GetSectionHeight();
		double dWidth = LEFT_MARGIN + RIGHT_MARGIN + dLen * m_dHScale;
		double dHeight = TOP_MARGIN + BOTTOM_MARGIN + dHei * m_dVScale;
		QRectF rect(0, 0, dWidth, dHeight);
		setSceneRect(rect);
	}

	UpdateView();
}

void GSSectionScene::UpdateView()
{
	for (QGraphicsItem* pItem : items())
	{
		pItem->update();
	}
}

int GSSectionScene::ZToSceneY(float fZ)
{
	return TOP_MARGIN + fZ * m_dVScale;
}

float GSSectionScene::SceneYToZ(int iY)
{
	if (iY < TOP_MARGIN)
		return 0;

	return (iY - TOP_MARGIN) / m_dVScale;
}

bool GSSectionScene::SceneXToXY(int iX, double& dX, double& dY)
{
	if(!m_pProfileItem)
		return false;

	return m_pProfileItem->SceneXToXY(iX, dX, dY);
}

void GSSectionScene::HandleMouseEvent(QMouseEvent* event, EXGSMouseEventType eMType)
{
	if (!m_pProfileItem)
		return;

	if (eMType == eGSMouseMove)
	{
		double dX, dY;
		QPoint pos = event->pos();
		QPointF fPos = views()[0]->mapToScene(pos);
		float fZ = SceneYToZ(fPos.y());

		if (SceneXToXY(fPos.x(), dX, dY))
		{
			m_pWindow->ShowState("Position: (" + QString::number(dX) + ", " + QString::number(dY, 'f', 0) + ", " + QString::number(fZ) + ")");
			//m_pWindow->BroadcastPosition(dX, dY, fZ);
		}
		else
		{
			m_pWindow->ShowState("");
		}
	}
}
