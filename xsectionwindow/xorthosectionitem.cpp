#include <qevent.h>
#include "xorthosectionitem.h"
#include "xsectionscene.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xglobal.h"
#include "xeventconsole.h"
#include "xcoordtransformer.h"
#include "xseismicutmtool.h"

CXOrthoSectionItem::CXOrthoSectionItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent) :CXAbstractItem(pWindow)
{
	setZValue(2);
}


CXOrthoSectionItem::~CXOrthoSectionItem(void)
{
}

QRectF CXOrthoSectionItem::boundingRect() const
{
	CXSectionScene *pScene = (CXSectionScene *)scene();
	if (!pScene)
		return QRectF();
	else
		return pScene->sceneRect();
}

void CXOrthoSectionItem::_UpdateData()
{		
	m_iDraggingIndex = -1;

	m_vecSectionID.clear();
	m_vecSectionRatio.clear();

	CXSectionScene *pScene = (CXSectionScene *)scene();
	CXObject *pGeoObj = pScene->GetBackgroundSection();
	CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(pGeoObj);
	if (!pSection)
		return;

	QList<CXObject *> listObj = pSection->GetParent()->GetChildren(EXSeismicSection);
	EXSectionType eOrthoSectionType;
	EXSectionType eSectionType = pSection->GetSectionType();
	if (eSectionType == eCrosslineSection)
	{
		eOrthoSectionType = eInlineSection;
	}
	else if (eSectionType == eInlineSection)
	{
		eOrthoSectionType = eCrosslineSection;
	}
	else
	{
		return;
	}

	int iSTrace, iETrace, iSTrace2, iETrace2;
	pSection->GetSectionRange(iSTrace, iETrace);

	for (CXObject *pObj : listObj)
	{
		CXSeismicSection *pOrthoSection = (CXSeismicSection *)pObj;
		if (pOrthoSection->GetSectionType() != eOrthoSectionType)
			continue;

		pOrthoSection->GetSectionRange(iSTrace2, iETrace2);
		if (iSTrace2 != -1 &&
			iETrace2 != -1 &&
			(pSection->GetSectionNumber() < iSTrace2 || 
			pSection->GetSectionNumber() > iETrace2))
			continue;

		int iTrace = (int)pOrthoSection->GetSectionNumber();
		if (iTrace < iSTrace || iTrace > iETrace)
			continue;

		m_vecSectionID << pObj->GetObjectID();

		double dRatio = (iTrace - iSTrace)*1.0 / (iETrace - iSTrace);
		m_vecSectionRatio << dRatio;
	}
}


void CXOrthoSectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_vecSectionRatio.isEmpty())
		return;

	CXSectionScene *pScene = (CXSectionScene *)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);

	painter->setPen(QColor("red"));

	for (double dRatio : m_vecSectionRatio)
	{
		double scenex1, sceney1, scenex2, sceney2;
		transformer.Ratio2Scene(dRatio, 0, scenex1, sceney1);
		transformer.Ratio2Scene(dRatio, 1, scenex2, sceney2);

		painter->drawLine(scenex1, sceney1, scenex2, sceney2);
	}
}

void CXOrthoSectionItem::HandleMouseEvent(QMouseEvent *pEvent, EXMouseEventType eType)
{
	if (eType == eSecButtonPress && pEvent->button() == Qt::LeftButton)
		_leftButtonPressed(pEvent);
	else if (eType == eSecMouseMove)
		_mouseMoving(pEvent);
	else if (eType == eSecButtonRelease)
		_buttonRelease();
}

void CXOrthoSectionItem::_leftButtonPressed(QMouseEvent *pEvent)
{
	CXSectionScene *pScene = (CXSectionScene *)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);

	double scenex, sceney, eventscenex, eventsceney;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), eventscenex, eventsceney);

	for (int i=0; i<m_vecSectionRatio.size(); ++i)
	{
		transformer.Ratio2Scene(m_vecSectionRatio[i], 0, scenex, sceney);		

		if (qAbs(scenex - eventscenex) < 3)
		{
			m_iDraggingIndex = i;
			return;
		}
	}
}

void CXOrthoSectionItem::_mouseMoving(QMouseEvent *pEvent)
{
	CXSectionScene *pScene = (CXSectionScene *)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);

	double scenex, sceney, eventscenex, eventsceney;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), eventscenex, eventsceney);
	
	if (m_iDraggingIndex < 0)
	{
		for (int i = 0; i<m_vecSectionRatio.size(); ++i)
		{			
			transformer.Ratio2Scene(m_vecSectionRatio[i], 0, scenex, sceney);		

			if (qAbs(scenex - eventscenex) < 3)
			{
				setCursor(Qt::SizeHorCursor);
				return;
			}
		}
		
		setCursor(Qt::ArrowCursor);
	}
	else
	{
		CXSeismicSection *pOrthoSection = dynamic_cast<CXSeismicSection *>(::GetObjectByID(m_vecSectionID[m_iDraggingIndex]));
		if (!pOrthoSection)
			return;

		CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(this->GetItemObject());
		if (!pSection)
			return;	
		

		int iSTrace, iETrace;
		pSection->GetSectionRange(iSTrace, iETrace);

		double ratiox, ratioy;		
		transformer.Scene2Ratio(eventscenex, eventsceney, ratiox, ratioy);
		
		int iTrace = ratiox*(iETrace - iSTrace) + iSTrace;
		int iStep = static_cast<int>(pSection->GetLineStep());
		iTrace = ((iTrace - iSTrace) / iStep)*iStep + iSTrace;

		// update ratio
		ratiox = (iTrace - iSTrace)*1. / (iETrace - iSTrace);			

		m_vecSectionRatio[m_iDraggingIndex] = ratiox;

		pOrthoSection->SetSectionNumber(iTrace);
		CXProcessEvent processEvent;
		pOrthoSection->AddEvent(EDataChanged);

		update();
	}
}

void CXOrthoSectionItem::_buttonRelease()
{
	m_iDraggingIndex = -1;
}