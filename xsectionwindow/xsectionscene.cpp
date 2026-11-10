#include "xsectionscene.h"

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <qevent.h>
#include <qmessagebox.h>

#include "xobject.h"
#include "xglobal.h"
#include "xseismicobject.h"
#include "x2dsectionwindow.h"
#include "xseismicdatavolume.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "x2dseismicline.h"
#include "xseismicdataline.h"
#include "xtimesliceitem.h"
#include "x2dwellitem.h"
#include "x2dwelltopsitem.h"
#include "x2dsectioncurveitem.h"
#include "x2dsurfaceitem.h"
#include "xsectionlinemode.h"
#include "x2dsectionview.h"
#include "xwindowinfosection.h"
#include "xcolormap.h"
#include "xfunctiontemplate.h"
#include "xeventconsole.h"
#include "xviewinfomanager.h"
#include "xcursor.h"
#include "xseismicrandomsection.h"
#include "xsectionbuilder.h"

#include "xlinearitymap.h"
#include "xsectionprojector.h"
#include "xsechorizonitem.h"
#include "xsechorizonpickingitem.h"
#include "xsecfaultitem.h"
#include "xsecfaultpickingitem.h"
#include "xseclfmgeometryitem.h"
#include "x2daxishelper.h"
#include "x2dsectionview.h"
#include "xsecrectzoomitem.h"
#include "xorthosectionitem.h"
#include "xseismicdataline.h"
#include "xcoordtransformer.h"
#include "xrandomlineitem.h"

#define MAXIMUMTRACE 11000

CXSectionScene::CXSectionScene(CXWindow* pWindow, QObject *parent)
    : CXScene(pWindow, parent)
    , m_pBackgroundBuilder(nullptr)
    , m_pForegroundBuilder(nullptr)
{
	m_pSectionWindow = dynamic_cast<CX2DSectionWindow*>(pWindow);
	m_pViewInfo = dynamic_cast<CXWindowInfoSection*>(m_pSectionWindow->GetSecWindowViewInfo());

	m_pProjector = new CXSectionProjector(this);

	m_eEditMode = Edit_NULL;
	m_pActiveItem = NULL;
	m_pRectZoomItem = NULL;
	m_pOrthoSectionItem = NULL;

	_ClearData(m_foreData);
	_ClearData(m_backData);
}

CXSectionScene::~CXSectionScene()
{
	m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();

    if (m_pForegroundBuilder)
    {
        delete m_pForegroundBuilder;
        m_pForegroundBuilder = nullptr;
    }

    if (m_pBackgroundBuilder)
    {
        delete m_pBackgroundBuilder;
        m_pBackgroundBuilder = nullptr;
    }

	m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();

	m_vecBackCount.clear();
	m_vecForeCount.clear();
	
	delete m_pProjector;

    if (m_foreData.m_pData)
    {
        delete m_foreData.m_pData;
        m_foreData.m_pData = nullptr;
    }

    if (m_backData.m_pData)
    {
        delete m_backData.m_pData;
        m_backData.m_pData = nullptr;
    }

    _ClearData(m_foreData);
	_ClearData(m_backData);
}

CXAbstractItem* CXSectionScene::_CreateItemByObj(CXObject* pObject) const
{
	switch (pObject->GetObjectType())
	{
	case EXSeismicSection:
		{
			auto pSeismicSection = dynamic_cast<CXSeismicSection*>(pObject);
			if (pSeismicSection && eTimeSlice == pSeismicSection->GetSectionType())
				return new CXTimeSliceItem(m_pSectionWindow);
			return nullptr;
		}

	case EXRandomSection:
		return new CXRandomLineItem(m_pSectionWindow);
	case EXWell:
		return new CX2DWellItem(m_pSectionWindow);
	case EXWellCurve:
		return new CX2DSectionCurveItem(m_pSectionWindow);
	case EXWellTopFormation:
		return new CX2DWelltopsItem(m_pSectionWindow);
	case  EXFaultSticks:
		return new CXSecFaultItem(m_pSectionWindow);
	case EX3DHorizon:
		return new CXSecHorizonItem(m_pSectionWindow);
	case EX3DSurface:
		return new CX2DSurfaceItem(m_pSectionWindow);
	case EXLowFrequencyModel:
		return new CXSecLFMGeometryItem(m_pSectionWindow);
	default:
		return nullptr;
	}
}

bool CXSectionScene::CreateItem(QUuid objectID, CXViewInfoObject* pViewInfo)
{
    if (m_mapItem.contains(objectID)) 
        return false;

    auto pObject = dynamic_cast<CXObject*>(GetObjectByID(objectID));
	auto pNewItem = _CreateItemByObj(pObject);

	if (pNewItem)
	{
		m_mapItem.insert(objectID, pNewItem);
		addItem(pNewItem);
		pNewItem->ResetData(objectID);
	}

	//m_pSectionWindow->GetAxisWidget()->repaint();
    return true;
}

bool CXSectionScene::DeleteItem(QUuid objectID)
{
	for (auto pItem : items())
	{
		auto pSectionItem = dynamic_cast<CXAbstractItem*>(pItem);
		if (!pSectionItem || !pSectionItem->GetItemObject()) 
			continue;

		if (objectID == pSectionItem->GetItemObject()->GetObjectID())
		{
			m_mapItem.remove(objectID);
			removeItem(pSectionItem);
			delete pSectionItem;
			break;
		}
	}

	//m_pSectionWindow->GetAxisWidget()->repaint();
	return true;
}

CXAbstractItem* CXSectionScene::FindItem(QUuid objID)
{
	for (auto pItem : items())
	{
		auto pAbstractItem = dynamic_cast<CXAbstractItem*>(pItem);
		if (!pAbstractItem) 
			continue;

		if (pAbstractItem->GetItemObject())
			if (pAbstractItem->GetItemObject()->GetObjectID() == objID) 
				return pAbstractItem;
	}
	return nullptr;
}

QList<CXAbstractItem *> CXSectionScene::FindAllAbsItems(EXObjectType eObjType)
{
	QList<CXAbstractItem *> listItem;
	for (auto pItem : items())
	{
		auto pAbstractItem = dynamic_cast<CXAbstractItem*>(pItem);
		if (!pAbstractItem)
			continue;

		CXObject *pObj = pAbstractItem->GetItemObject();
		if (pObj && pObj->GetObjectType() == eObjType)
			listItem << pAbstractItem;
	}

	return listItem;
}

void CXSectionScene::DeleteAllItems()
{
    for (QGraphicsItem* pItem : this->items())
    {
        auto pObjectItem = dynamic_cast<CXObjectItem*>(pItem);
        if (!pObjectItem)
            continue;

        DeleteItem(pObjectItem->GetObjectID());
    }
}

void CXSectionScene::_UpdateAllItems(EEventType eType)
{
	//	Force update all well items first, since well curve items may depend on well items.
	QList<QGraphicsItem *> listOtherItems;
	for (QGraphicsItem* pWItem : this->items())
	{
		auto pAbstractItem = dynamic_cast<CXAbstractItem*>(pWItem);
		if (!pAbstractItem)
			continue;

		if (pAbstractItem->GetItemObject()->GetObjectType() == EXWell)
			pAbstractItem->UpdateView(eType);
		else
			listOtherItems << pAbstractItem;
	}

	//	Then update others.
	for (QGraphicsItem* pItem : listOtherItems)
    {
        auto pAbstractItem = dynamic_cast<CXAbstractItem*>(pItem);

		pAbstractItem->UpdateView(eType);
    }
}

void CXSectionScene::_UpdateWellItems()
{
	QList<CXAbstractItem*> listWell, listWellDependency;
	for (auto pItem : items())
	{
		auto pKEItem = dynamic_cast<CXAbstractItem*>(pItem);
		if (!pKEItem)
			continue;

		EXObjectType itemObjType = pKEItem->GetItemObject()->GetObjectType();
		if (itemObjType == EXWell)
		{
			listWell << pKEItem;
		}
		else if (itemObjType == EXWellCurve || EXWellTopFormation)
		{
			listWellDependency << pKEItem;
		}
	}

	if (listWell.isEmpty()) // return when no well.
		return;

	for (CXAbstractItem* pItem : listWell)
	{
		pItem->UpdateView(EDataChanged);
	}

	for (CXAbstractItem* pItem : listWellDependency)
	{
		pItem->UpdateView(EDataChanged);
	}
}

void CXSectionScene::UpdateSectionData()
{
	SetForeData(m_foreData.m_pAttObj, m_foreData.m_pGeoObj);
	SetBackData(m_backData.m_pAttObj, m_backData.m_pGeoObj);
}

void CXSectionScene::UpdateView(const CXEventParameter& eventPara)
{
	switch (eventPara.m_eEventType)
	{
    case EAdded:
    {
        m_pSectionWindow->AddNewItemToComboBox(eventPara.m_objID);
        break;
    }
	case EDeleted:
	{
		m_pSectionWindow->RemoveItemFromComboBox(eventPara.m_objID);

		if (m_backData.m_pGeoObj && m_backData.m_pGeoObj->GetObjectID() == eventPara.m_objID)
        {
            SetForeData(nullptr, nullptr);
            SetBackData(nullptr, nullptr);

            DeleteAllItems();
        }
		else if (m_backData.m_pAttObj && m_backData.m_pAttObj->GetObjectID() == eventPara.m_objID)
		{
			// replace the old attribute.
			QUuid currentAttributeID = m_pSectionWindow->GetCurrentAttributeID();
			auto pAttributeObj = dynamic_cast<CXSeismicObject*>(::GetObjectByID(currentAttributeID));
			CXViewInfoObject* pGeoViewInfo = m_pWindow->GetObjectViewInfo(m_backData.m_pGeoObj->GetObjectID());
			pGeoViewInfo->SetAttributeObjID(currentAttributeID);

			SetBackData(pAttributeObj, m_backData.m_pGeoObj);
		}
		else if (m_foreData.m_pAttObj && m_foreData.m_pAttObj->GetObjectID() == eventPara.m_objID)
		{
			SetForeData(nullptr, nullptr);
		}
        else
        {
            auto pItem = FindItem(eventPara.m_objID);
            if (pItem)
            {
				if (pItem == m_pActiveItem)
					m_pActiveItem = NULL;

                m_mapItem.remove(eventPara.m_objID);
                removeItem(pItem);
                delete pItem;
            }
        }

		break;
	}
    case EDataChanged:
    {
		if (m_backData.m_pGeoObj &&
			(m_backData.m_pGeoObj->GetObjectID() == eventPara.m_objID
			|| m_backData.m_pAttObj->GetObjectID() == eventPara.m_objID))
		{
			SetForeData(m_foreData.m_pAttObj, m_foreData.m_pGeoObj);
			if(SetBackData(m_backData.m_pAttObj, m_backData.m_pGeoObj))
				return;

			m_pSectionWindow->GetAxisWidget()->SetDisplaySection(m_backData.m_pGeoObj);

			_UpdateAllItems(EDataChanged);
            m_pSectionWindow->UpdateVCRControlData(eventPara.m_objID);
			m_pSectionWindow->UpdateVolumesName(eventPara.m_objID);
        }
		else if (m_foreData.m_pAttObj && m_foreData.m_pAttObj->GetObjectID() == eventPara.m_objID)
		{
			SetForeData(m_foreData.m_pAttObj, m_foreData.m_pGeoObj);
		}
		else if (m_backData.m_pGeoObj && m_backData.m_pGeoObj->GetParent()->GetObjectID() == eventPara.m_objID) // if survey data changes
		{
			_UpdateWellItems();
		}
		else
        {
            auto pItem = dynamic_cast<CXAbstractItem*>(FindItem(eventPara.m_objID));
			if (pItem)
            {
				pItem->UpdateView(EDataChanged);
            }
        }

        break;
    }
	case EInfoChanged:
	{
		auto pItem = dynamic_cast<CXAbstractItem*>(FindItem(eventPara.m_objID));
		if (pItem)
		{
			pItem->UpdateView(EInfoChanged);
		}

        break;
	}
	case EColormapChanged:
	{
		if (m_backData.m_pGeoObj &&
			(m_backData.m_pGeoObj->GetObjectID() == eventPara.m_objID
			|| m_backData.m_pAttObj->GetObjectID() == eventPara.m_objID))
		{
			_UpdateDisplayRange(m_backData);
			m_pSectionWindow->UpdateColormapWidgetRange(m_backData.m_dMin, m_backData.m_dMax);

			m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();
			_SetTexData(m_backData, m_pBackgroundBuilder);
			m_pSectionWindow->UpdateColormap();
			m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();
		}
		else if (m_foreData.m_pAttObj && m_foreData.m_pAttObj->GetObjectID() == eventPara.m_objID)
		{
			_UpdateDisplayRange(m_foreData);

			m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();
			_SetTexData(m_foreData, m_pForegroundBuilder);
			m_pSectionWindow->UpdateColormap();
			m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();
		}
		else
        {
            auto pSectionItem = dynamic_cast<CXAbstractItem*>(FindItem(eventPara.m_objID));
            if (pSectionItem)
            {
                pSectionItem->UpdateView(EColormapChanged);
            }
        }

		break;
	}
	}

	//	Special for ortho section item.
	if (m_pOrthoSectionItem)
	{
		CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(::GetObjectByID(eventPara.m_objID));
		if (pSection)
		{
			m_pOrthoSectionItem->UpdateView(eventPara.m_eEventType);
		}
	}

	update();
}

void CXSectionScene::ShowPositionInfo(QMouseEvent *pEvent)
{
	if (!m_backData.m_pAttObj || !m_backData.m_pData)
		return;

	CXCoordTransformer transformer(this);
	double indexx, indexy;
	transformer.View2Index(pEvent->pos().x(), pEvent->pos().y(), indexx, indexy);

	QString str;
	int i, j, k, iLine, iCDP, iNumOffset;
	float fVal, fStartOffset, fOffsetStep;
	double x, y;
	k = (int)(indexy + 0.5);
	j = (int)(indexx + 0.5);

	if (k != qBound(0, k, m_backData.m_nSamplingQty - 1) ||
		j != qBound(0, j, m_backData.m_nTraceQty - 1))
		return;		

	// value
	fVal = m_backData.m_pData[j * m_backData.m_nSamplingQty + k];
	
	// z
	double dStartZ, dStopZ, dStep;
	m_backData.m_pAttObj->GetSamplingRange(dStartZ, dStopZ, dStep);
	double dTime = dStartZ + k*dStep;
		

	CXSeismicUTMTool utm = m_backData.m_pAttObj->GetUTM();
	if (m_backData.m_pAttObj->IsIrregular())
	{
		if (!m_backData.m_pTraceInfo)
		{
			m_pSectionWindow->ShowMessage("Something error!");
			return;
		}

		x = m_backData.m_pTraceInfo[j].m_dX;
		y = m_backData.m_pTraceInfo[j].m_dY;

		str = "Line " + QString::number(m_backData.m_pTraceInfo[j].m_iLine) + "    CDP " + QString::number(m_backData.m_pTraceInfo[j].m_iCDP);
		str += "    Offset " + QString::number(m_backData.m_pTraceInfo[j].m_iOffset);
		if(m_backData.m_pAttObj->IsAzimuth())
			str += "    Azimuth " + QString::number(m_backData.m_pTraceInfo[j].m_iAzimuth);		
	}
	else
	{
		double ratiox, ratioy, scenex, sceney;
		transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), scenex, sceney);
		transformer.Scene2Ratio(scenex, sceney, ratiox, ratioy);

		//	Regular.
		if (m_backData.m_pGeoObj->GetObjectType() == EXSeismicSection)
		{
			CXSeismicSection *pSection = (CXSeismicSection *)m_backData.m_pGeoObj;

			int iSTrace, iETrace, iXStep;
			pSection->GetSectionRange(iSTrace, iETrace);
			if (pSection->GetSectionType() == eInlineSection)
			{
				iXStep = utm.GetCrosslineIncrement();

				iCDP = iSTrace + (iETrace - iSTrace)*ratiox;
				iCDP = ((iCDP - iSTrace) / iXStep)*iXStep + iSTrace;
				iLine = (int)pSection->GetSectionNumber();


				str = "Line " + QString::number(iLine) + "    CDP " + QString::number(iCDP);

				if (m_backData.m_pAttObj->IsPrestack())
				{
					int nXlineQty = (iETrace - iSTrace) / iXStep + 1;

					m_backData.m_pAttObj->GetOffsetInfo(fStartOffset, fOffsetStep, iNumOffset);

					int iOffset = j%iNumOffset;
					float fOffset = fStartOffset + iOffset * fOffsetStep;

					str += "    Offset " + QString::number(fOffset, 'f', 0);
				}
			}
			else if (pSection->GetSectionType() == eCrosslineSection)
			{
				iXStep = utm.GetInlineIncrement();

				iLine = iSTrace + (iETrace - iSTrace)*ratiox;
				iLine = ((iLine - iSTrace) / iXStep)*iXStep + iSTrace;

				iCDP = (int)pSection->GetSectionNumber();

				str = "Line " + QString::number(iLine) + "    CDP " + QString::number(iCDP);

				if (m_backData.m_pAttObj->IsPrestack())
				{
					int nIlineQty = (iETrace - iSTrace) / iXStep + 1;

					m_backData.m_pAttObj->GetOffsetInfo(fStartOffset, fOffsetStep, iNumOffset);
					
					int iOffset = j%iNumOffset;
					float fOffset = fStartOffset + iOffset * fOffsetStep;

					str += "    Offset " + QString::number(fOffset, 'f', 0);
				}
			}

			utm.LineToXY(iLine, iCDP, x, y);

		}
		else if (m_backData.m_pGeoObj->GetObjectType() == EXRandomSection)
		{
			CXSeismicRandomSection *pSection = (CXSeismicRandomSection *)(m_backData.m_pGeoObj);
			int nTraceQty = pSection->GetTraceNum();
			int iIndex = static_cast<int>(ratiox*nTraceQty + 0.5);
			
			pSection->GetTraceInfo(iIndex, iLine, iCDP, x, y);
			str = "Line " + QString::number(iLine) + "    CDP " + QString::number(iCDP);

			if (m_backData.m_pAttObj->IsPrestack())
			{
				m_backData.m_pAttObj->GetOffsetInfo(fStartOffset, fOffsetStep, iNumOffset);

				int iOffset = j%iNumOffset;
				float fOffset = fStartOffset + iOffset * fOffsetStep;

				str += "    Offset " + QString::number(fOffset, 'f', 0);
			}
		}
		else if (m_backData.m_pGeoObj->GetObjectType() == EX2DSeismicLine)
		{
			CX2DSeismicLine *pLine = (CX2DSeismicLine *)m_backData.m_pGeoObj;

			str = "Line " + m_backData.m_pGeoObj->GetObjectName() + " (" + m_backData.m_pAttObj->GetObjectName() + ")";
			

			unsigned int *pCDP = pLine->GetCDPData();
			unsigned int iNumTrace = pLine->GetTraceNumber();
			iCDP = pCDP[j];
			str += "    CDP " + QString::number(iCDP);

			double *pDX, *pDY;
			pLine->GetCoordData(pDX, pDY);
			x = pDX[j];
			y = pDY[j];
		}
	}

	str += "    X " + QString::number(x, 'f', 2) + "    Y " + QString::number(y, 'f', 2);
	str += "    Time " + QString::number(dTime, 'f', 2) + "    Amplitude " + QString::number(fVal, 'f', 2);

	m_pSectionWindow->ShowMessage(str);

	//	Broadcast the position.
	CXProcessEvent processEvent(this);
	CXCursor::Instance().SetPosition(x, y, dTime);
	CXCursor::Instance().AddEvent(EDataChanged);
}

void CXSectionScene::InitOpenGLBuilder()
{
	m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();

	m_pForegroundBuilder = new CXSectionBuilder;
	m_pBackgroundBuilder = new CXSectionBuilder;

	m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();
}

bool CXSectionScene::SetForeData(CXSeismicObject* pAttObj, CXObject *pGeoObj)
{
	if (!_ResetData(pAttObj, pGeoObj, m_foreData))
		return false;

	if (!m_pForegroundBuilder || !m_foreData.m_pAttObj || !m_foreData.m_pData || (!m_pViewInfo->GetVariableIntensity() && !m_pViewInfo->GetWiggle() && !m_pViewInfo->GetWiggleVariableArea()))
        return false;

    m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();

	_SetTexData(m_foreData, m_pForegroundBuilder);
    _SetWiggleData(m_foreData, m_pForegroundBuilder);
    _SetAreaData(m_foreData, m_pForegroundBuilder, m_vecForeCount);

    m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();

	return true;
}

bool CXSectionScene::SetBackData(CXSeismicObject* pObj, CXObject *pGeoObj)
{

	if (!_ResetData(pObj, pGeoObj, m_backData))
		return false;

	if (!m_backData.m_pAttObj || !m_backData.m_pData)
        return false;

	if (!m_pBackgroundBuilder || !m_pViewInfo->GetVariableIntensity() && !m_pViewInfo->GetWiggle() && !m_pViewInfo->GetWiggleVariableArea())
		return false;

    m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();

	_SetTexData(m_backData, m_pBackgroundBuilder);
    _SetWiggleData(m_backData, m_pBackgroundBuilder);
    _SetAreaData(m_backData, m_pBackgroundBuilder, m_vecBackCount);

    m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();

	return true;
}

void CXSectionScene::UpdateItems(EEventType eType)
{
	_UpdateAllItems(eType);
}

void CXSectionScene::UpdateROI(float fLeft, float fRight, float fBottom, float fTop)
{
    m_pSectionWindow->GetView()->GetGLWidget()->makeCurrent();

    //! for debug:
    //QOpenGLContext* pContext = m_pSectionWindow->GetView()->GetGLWidget()->context();

	if (m_pBackgroundBuilder)
    {
		m_pBackgroundBuilder->UpdateROI(fLeft, fRight, fBottom, fTop);
    }

    if (m_pForegroundBuilder)
	{
		m_pForegroundBuilder->UpdateROI(fLeft, fRight, fBottom, fTop);
	}

    m_pSectionWindow->GetView()->GetGLWidget()->doneCurrent();
}

void CXSectionScene::drawBackground(QPainter* painter, const QRectF& rect)
{
	if (!m_pBackgroundBuilder)
		return;

    painter->beginNativePainting();
	CX2DSectionAxis* pWidget = m_pSectionWindow->GetAxisWidget();

	if (m_backData.m_nTraceQty != 0 && m_backData.m_nSamplingQty != 0 && m_backData.m_pData && m_pBackgroundBuilder)
	{
		m_pBackgroundBuilder->EnableBackgroundSwitch(pWidget->palette().color(pWidget->backgroundRole()));

		m_pBackgroundBuilder->DrawTexture(m_pViewInfo->GetVariableIntensity());
		m_pBackgroundBuilder->DrawWiggle(m_backData.m_nTraceQty, m_backData.m_nSamplingQty, QVector4D(0.f, 0.f, 0.f, 1.f), m_pViewInfo->GetWiggle());
		m_pBackgroundBuilder->DrawArea(m_vecBackCount, QVector4D(0.f, 0.f, 0.f, 1.f), m_pViewInfo->GetWiggleVariableArea());

		m_pBackgroundBuilder->DisableBackgroundSwitch();
	}
	else
	{
		m_pBackgroundBuilder->Update(pWidget->palette().color(pWidget->backgroundRole()));
	}

    painter->endNativePainting();
}

void CXSectionScene::drawForeground(QPainter* painter, const QRectF& rect)
{
	if (!m_pForegroundBuilder)
		return;

	painter->beginNativePainting();

	if (m_foreData.m_nTraceQty != 0 && m_foreData.m_nSamplingQty != 0 && m_foreData.m_pData && m_pForegroundBuilder)
	{
		m_pForegroundBuilder->EnableForegroundSwitch();

		m_pForegroundBuilder->SetAlphaValue(m_pViewInfo->GetForeAlpha());
		m_pForegroundBuilder->DrawTexture(m_pViewInfo->GetForeVariableIntensity());
		m_pForegroundBuilder->DrawWiggle(m_foreData.m_nTraceQty, m_foreData.m_nSamplingQty, QVector4D(0.f, 0.f, 0.f, 1.f), m_pViewInfo->GetForeWiggle());
		m_pForegroundBuilder->DrawArea(m_vecForeCount, QVector4D(0.f, 0.f, 0.f, 1.f), m_pViewInfo->GetForeWiggleVariableArea());

		m_pForegroundBuilder->DisableForegroundSwitch();
	}
    
    painter->endNativePainting();
}

void CXSectionScene::_UpdateDisplayRange(CXSectionData& data) const
{
	if (!data.m_pAttObj)
        return;

	CXViewInfoObject* pViewInfo = m_pSectionWindow->GetObjectViewInfo(data.m_pAttObj->GetObjectID());
    data.m_dMin = pViewInfo->GetDisplayDataMin();
    data.m_dMax = pViewInfo->GetDisplayDataMax();
}

bool CXSectionScene::_ResetData(CXSeismicObject* pObj, CXObject *pGeoObj, CXSectionData& data) const
{
	_ClearData(data); 
	if (!pObj) 
		return false; 

	data.m_pAttObj = pObj;
	data.m_pGeoObj = pGeoObj;
	data.m_nSamplingQty = pObj->GetSamplingQty();

    _UpdateDisplayRange(data);

	return(_readData(data));
}

void CXSectionScene::_ClearData(CXSectionData& data)
{
	data.m_pAttObj = nullptr;
	data.m_pGeoObj = nullptr;

	if (data.m_pData)
		delete []data.m_pData;
	data.m_pData = nullptr;
	
	data.m_nTraceQty = data.m_nSamplingQty = 0;
	data.m_dMin = data.m_dMax = 0;

	if (data.m_pTraceInfo)
		delete[]data.m_pTraceInfo;
	data.m_pTraceInfo = NULL;
}

bool CXSectionScene::_readData(CXSectionData &data)
{
	int iTraceNum = 0;
	if (data.m_pGeoObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSeismicSection = (CXSeismicSection *)data.m_pGeoObj;

		iTraceNum = data.m_pAttObj->GetSectionTraceQty(pSeismicSection);
		if (iTraceNum == 1)
		{
			QMessageBox::warning(0, "Warning", "The section contains only one trace, not accepted.");
			return false;
		}
		else if (iTraceNum > MAXIMUMTRACE || iTraceNum < 0)
		{
			QMessageBox::warning(0, "Warning", "The section contains too many traces!\nPlease reduce the trace range.");
			return false;
		}

		data.m_nTraceQty = iTraceNum;
		data.m_pData = new float[data.m_nTraceQty * data.m_nSamplingQty];

		if (data.m_pAttObj->IsIrregular())
			data.m_pTraceInfo = new SKETraceInfo[data.m_nTraceQty];

		data.m_pAttObj->ReadSection(pSeismicSection, data.m_pData, data.m_pTraceInfo);
	}
	else if (data.m_pGeoObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pRandomSection = (CXSeismicRandomSection *)data.m_pGeoObj;

		auto pVolume = dynamic_cast<CXSeismicDataVolume*>(data.m_pAttObj);
		Q_ASSERT(pVolume);

		data.m_nTraceQty = pRandomSection->GetTraceNum(pVolume);
		data.m_pData = new float[data.m_nTraceQty * data.m_nSamplingQty];

		if (pVolume->IsIrregular())
			data.m_pTraceInfo = new SKETraceInfo[data.m_nTraceQty + 1];

		pVolume->ReadRandomSection(pRandomSection, data.m_pData, data.m_pTraceInfo);
	}
	else if (data.m_pGeoObj->GetObjectType() == EX2DSeismicLine)
	{
		CX2DSeismicLine *p2DLine = (CX2DSeismicLine *)data.m_pGeoObj;
		auto p2DSection = dynamic_cast<CXSeismicDataLine*>(data.m_pAttObj);
		Q_ASSERT(p2DSection);

		data.m_nTraceQty = p2DLine->GetTraceNumber();
		data.m_pData = new float[data.m_nTraceQty * data.m_nSamplingQty];
		float* pOriginData = p2DSection->GetData();
		memcpy(data.m_pData, pOriginData, data.m_nTraceQty * data.m_nSamplingQty * sizeof(float));
	}

	return true;
}

void CXSectionScene::_SetWiggleData(const CXSectionData& data, CXSectionBuilder* pBuilder) const
{
	auto pXYData = new float[data.m_nTraceQty * data.m_nSamplingQty * 2];

	_CalcWiggleData(pXYData, data);

    pBuilder->SetWiggleData(pXYData, data.m_nTraceQty * data.m_nSamplingQty * 2);

	delete[] pXYData;
}

void CXSectionScene::_SetAreaData(const CXSectionData& data, CXSectionBuilder* pBuilder, std::vector<int>& vecCount)
{
	auto pAreaData = new float[data.m_nTraceQty * data.m_nSamplingQty * 2 * 2];

	vecCount.assign({ 0 });
	_CalcAreaData(pAreaData, data, vecCount);

	pBuilder->SetAreaData(pAreaData, vecCount.back() * 2);

	delete[] pAreaData;
}

void CXSectionScene::_CalcWiggleData(float* pData, const CXSectionData& data) const
{
	// Wiggle min and max
	float fWiggleMin, fWiggleMax;
	if (data.m_dMin * data.m_dMax < 0)
	{
		fWiggleMax = qMax(qAbs(data.m_dMin), data.m_dMax);
		fWiggleMin = -fWiggleMax;
	}
	else
	{
		fWiggleMax = data.m_dMax;
		fWiggleMin = 0.f;
	}

	// parameters
	float fXUnit = 2.0 / data.m_nTraceQty;
	float fYUnit = 2.0 / (data.m_nSamplingQty - 1);
	auto fClipping = m_pViewInfo->GetCliping() * fXUnit;
	auto fExcursion = m_pViewInfo->GetExcursion() * fXUnit;

	float x, y, length, value;
	auto index = -1;

	for (auto i = 0; i < data.m_nTraceQty; ++i)
	{
		for (auto k = 0; k < data.m_nSamplingQty; ++k)
		{
			value = data.m_pData[i * data.m_nSamplingQty + k];

			// In seismic part, we see invalid value as zero.
			if (qFuzzyCompare(value, (float)::g_dInvalidData))
			{
				value = 0.f;
			}

			// X
			length = qMin(qAbs(value) / fWiggleMax * fExcursion, fClipping);
			if (fWiggleMin == 0.f)
			{
				x = -1.f + i * fXUnit + length;
			}
			else
			{
				x = -1.f + (i + 0.5f) * fXUnit + Sign(value) * length;
			}

			// Y
			y = 1.f - k * fYUnit;

			// set x and y
			pData[++index] = x;
			pData[++index] = y;
		}
	}
}

void CXSectionScene::_CalcAreaData(float* pData, const CXSectionData& data, std::vector<int>& vecCount) const
{
	auto pXYData = new float[data.m_nTraceQty * data.m_nSamplingQty * 2];

	_CalcWiggleData(pXYData, data);

	// parameters
	auto fXUnit = 2.0f / data.m_nTraceQty;
	auto fTraceStart = data.m_dMin * data.m_dMax < 0 ? fXUnit / 2.f : 0.f;

	float fXMiddle, fXPre, fX, fXNext, fYPre, fY, y;
	auto index = 0;
	for (auto i = 0; i < data.m_nTraceQty; ++i)
	{
		fXMiddle = -1.f + i * fXUnit + fTraceStart;

		for (auto k = 0; k < data.m_nSamplingQty; ++k)
		{
			fX = pXYData[2 * (i * data.m_nSamplingQty + k)];
			fY = pXYData[2 * (i * data.m_nSamplingQty + k) + 1];

			// each K deals with its own and above data
			if (k == 0)
			{
				fXNext = pXYData[2 * (i * data.m_nSamplingQty + k + 1)];

				if (fX < fXMiddle)
				{
					if (fXNext <= fXMiddle) continue;
				}
				else if (fX == fXMiddle)
				{
					if (fXNext <= fXMiddle) continue;
					
					pData[index++] = fX;
					pData[index++] = fY;
				}
				else // fX > fXMiddle
				{
					pData[index++] = fXMiddle;
					pData[index++] = fY;

					pData[index++] = fX;
					pData[index++] = fY;
				}
			}
			else if (k == data.m_nSamplingQty - 1)
			{
				fXPre = pXYData[2 * (i * data.m_nSamplingQty + k - 1)];
				fYPre = pXYData[2 * (i * data.m_nSamplingQty + k - 1) + 1];

				if (fX < fXMiddle)
				{
					if (fXPre <= fXMiddle) continue;
					else
					{
						y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

						pData[index++] = fXMiddle;
						pData[index++] = y;

                        vecCount.push_back(index / 2);
					}
				}
				else if (fX == fXMiddle)
				{
					if (fXPre > fXMiddle)
					{
						pData[index++] = fX;
						pData[index++] = fY;

						vecCount.push_back(index / 2);
					}
				}
				else // fX > fXMiddle
				{
					if (fXPre < fXMiddle)
					{
						y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

						pData[index++] = fXMiddle;
						pData[index++] = y;
					}

					pData[index++] = fXMiddle;
					pData[index++] = fY;

					pData[index++] = fX;
					pData[index++] = fY;

					vecCount.push_back(index / 2);
				}
			}
			else // 0<k<data.m_nSamplingQty
			{
				fXPre = pXYData[2 * (i * data.m_nSamplingQty + k - 1)];
				fYPre = pXYData[2 * (i * data.m_nSamplingQty + k - 1) + 1];

				fXNext = pXYData[2 * (i * data.m_nSamplingQty + k + 1)];
				//fYNext = pXYData[2*(i*data.m_nSamplingQty + k+1)+1];

				if (fX == fXMiddle)
				{
					if (fXPre > fXMiddle)
					{
						pData[index++] = fX;
						pData[index++] = fY;

						vecCount.push_back(index / 2);
					}

					if (fXNext > fXMiddle)
					{
						pData[index++] = fX;
						pData[index++] = fY;
					}
				}
				else if (fX < fXMiddle)
				{
					if (fXPre <= fXMiddle) continue;
					else
					{
						y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

						pData[index++] = fXMiddle;
						pData[index++] = y;

						vecCount.push_back(index / 2);
					}
				}
				else // fX > fXMiddle
				{
					if (fXPre < fXMiddle)
					{
						y = (fY * (fXPre - fXMiddle) + fYPre * (fXMiddle - fX)) / (fXPre - fX);

						pData[index++] = fXMiddle;
						pData[index++] = y;
					}

					pData[index++] = fXMiddle;
					pData[index++] = fY;

					pData[index++] = fX;
					pData[index++] = fY;
				}
			}
		}
	}

	delete[] pXYData;
}

void CXSectionScene::_SetTexData(const CXSectionData& data, CXSectionBuilder* pBuilder) const
{
	if (!data.m_pAttObj || !data.m_pData) return;

	// get QImage data
	auto pViewInfo = m_pSectionWindow->GetObjectViewInfo(data.m_pAttObj->GetObjectID());
	auto pColormap = CXColormap::GetColormap(pViewInfo->GetColormapName());

    QVector4D colormap[256];
	for (auto i = 0; i < 256; ++i)
	{
		QColor color = (i == 255) ? pColormap->GetInvalidColor() : pColormap->GetColorAt(i);
        colormap[i].setX(color.redF());
        colormap[i].setY(color.greenF());
        colormap[i].setZ(color.blueF());
        colormap[i].setW(color.alphaF());
	}

	// image data
	auto pImageData = new unsigned int[data.m_nTraceQty * data.m_nSamplingQty];
	
	for (auto i = 0; i < data.m_nTraceQty; ++i)
	{
		for (auto k = 0; k < data.m_nSamplingQty; ++k)
		{
			double dCurrValue = static_cast<double>(data.m_pData[i * data.m_nSamplingQty + k]);

			int index;
			if (qAbs(data.m_dMax - data.m_dMin) < M_FEPS)
			{
				index = 0;
			}
			else if (qFuzzyCompare(dCurrValue, ::g_dInvalidData) || (pViewInfo->GetBZeroIsInvalid() && dCurrValue == 0.0))
			{
				pImageData[(data.m_nSamplingQty - 1 - k)*data.m_nTraceQty + i] = pColormap->GetInvalidColor().rgba();
				continue;
			}
			else
			{
				index = static_cast<int>((dCurrValue - data.m_dMin) / (data.m_dMax - data.m_dMin) * 254);
				index = qBound(0, index, 254);
			}

			pImageData[(data.m_nSamplingQty - 1 - k)*data.m_nTraceQty + i] = QColor(index, index, index).rgba();
		}
	}

	QImage image(reinterpret_cast<uchar*>(pImageData), data.m_nTraceQty, data.m_nSamplingQty, QImage::Format_RGB32);
    //image.save("test.png");

    pBuilder->SetTextureData(image, colormap);

	delete[] pImageData;
}

void CXSectionScene::_CreateItemOfOtherSection(CXObject* pSection)
{
	auto pLineModeItem = new CXSectionLineMode(m_pSectionWindow);
	pLineModeItem->ResetData(pSection->GetObjectID());
	addItem(pLineModeItem);
	connect(this, SIGNAL(sceneRectChanged(const QRectF)), pLineModeItem, SLOT(slotSceneChanged()));
}

void CXSectionScene::_RemoveItemOfOtherSection(CXObject* pSection)
{
	for (auto pItem : items())
	{
		auto pSectionItem = dynamic_cast<CXAbstractItem*>(pItem);
		if (pSectionItem && pSectionItem->GetItemObject() == pSection)
			removeItem(pItem);
	}
	update();
}

EDomainType CXSectionScene::GetDomainType()
{
	if (m_backData.m_pAttObj)
		return m_backData.m_pAttObj->GetDomainType();
	else
		return eTimeDomain;
}

CXObject* CXSectionScene::GetBackgroundSection(bool bGeometry)
{
	if (bGeometry)
		return m_backData.m_pGeoObj;
	else
		return m_backData.m_pAttObj;
}

void CXSectionScene::GetSectionSize(float& fTraceNumber, float& fMS)
{
	fTraceNumber = 0.;
	fMS = 0.;

	if (m_backData.m_pAttObj)
	{
		fTraceNumber = (float)m_backData.m_nTraceQty;
		fMS = m_backData.m_nSamplingQty * m_backData.m_pAttObj->GetSampleInterval();
	}
}

void CXSectionScene::SetActiveItem(QUuid objID)
{
	//	Check current one.
	if (m_pActiveItem)
	{
		if (m_pActiveItem->GetObjectID() == objID)
			return;

		DeactiveItem();
	}

	//	If the object show as general item, delete it first.
	DeleteItem(objID);

	SetEditMode(Edit_NULL);

	CXObject *pObj = ::GetObjectByID(objID);
	if (!pObj)
		return;

	if (pObj->GetObjectType() == EXFaultSticks)
	{
		m_pActiveItem = new CXSecFaultPickingItem(m_pSectionWindow);
		m_mapItem.insert(objID, m_pActiveItem);
		addItem(m_pActiveItem);
		m_pActiveItem->ResetData(objID);

		SetEditMode(Edit_Fault);
	}
	else if (pObj->GetObjectType() == EX3DHorizon)
	{
		m_pActiveItem = new CXSecHorizonPickingItem(m_pSectionWindow);
		m_mapItem.insert(objID, m_pActiveItem);
		addItem(m_pActiveItem);
		m_pActiveItem->ResetData(objID);

		SetEditMode(Edit_Horizon);
	}
	else if (pObj->GetObjectType() == EXSeismicSection)
	{
		m_pActiveItem = new CXOrthoSectionItem(m_pSectionWindow);
		m_mapItem.insert(objID, m_pActiveItem);
		addItem(m_pActiveItem);
		m_pActiveItem->ResetData(objID);

		SetEditMode(Edit_OrthoSection);
	}
}

void CXSectionScene::DeactiveItem()
{
	if (!m_pActiveItem)
		return;

	if (dynamic_cast<CXSecFaultPickingItem *>(m_pActiveItem) ||
		dynamic_cast<CXSecHorizonPickingItem *>(m_pActiveItem))
	{
		QUuid objID = m_pActiveItem->GetObjectID();

		//	Remove it as active item.
		DeleteItem(objID);
		m_pActiveItem = NULL;

		//	Then add it as general item, if the section still there.
		if (m_backData.m_pGeoObj && ::GetObjectByID(objID) != NULL)
			CreateItem(objID, NULL);
	}
	else if (dynamic_cast<CXOrthoSectionItem *>(m_pActiveItem))
	{
		QUuid objID = m_pActiveItem->GetObjectID();

		//	Remove it as active item.
		DeleteItem(objID);
		m_pActiveItem = NULL;
	}
}

void CXSectionScene::HandleMouseEvent(QMouseEvent *pEvent, EXMouseEventType eType)
{
	if (m_pRectZoomItem)
	{
		m_pRectZoomItem->HandleMouseEvent(pEvent, eType);
		return;
	}

	if (m_eEditMode == Edit_NULL || !m_pActiveItem)
		return;

	m_pActiveItem->HandleMouseEvent(pEvent, eType);
}

void CXSectionScene::ShowOrthoSections(bool bOn)
{
	if (bOn)
	{
		SetActiveItem(m_backData.m_pGeoObj->GetObjectID());
	}
}

void CXSectionScene::SwitchRectZoom(bool bOn)
{
	if (bOn)
	{
		if (m_pRectZoomItem)
			delete m_pRectZoomItem;

		m_pRectZoomItem = new CXSecRectZoomItem(m_pSectionWindow);
		addItem(m_pRectZoomItem);
	}
	else
	{
		if (m_pRectZoomItem)
		{
			removeItem(m_pRectZoomItem);
			delete m_pRectZoomItem;
			m_pRectZoomItem = NULL;
		}
	}
}

void CXSectionScene::FaultStickAssign(QUuid sourceFaultID, QUuid destFaultID)
{
	CXSecFaultPickingItem *pFPItem = dynamic_cast<CXSecFaultPickingItem *>(m_pActiveItem);
	if (!pFPItem)
		return;

	pFPItem->FaultStickAssign(sourceFaultID, destFaultID);

	CXAbstractItem *pDFItem = FindItem(destFaultID);
	if (pDFItem)
		pDFItem->ResetData(destFaultID);
}

void CXSectionScene::GetXYByTraceNumber(double& dX, double& dY, double dTrace)
{
	dX = dY = -999.;

	if (!m_backData.m_pGeoObj)
		return;

	if (m_backData.m_pGeoObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSection = (CXSeismicSection *)m_backData.m_pGeoObj;
		CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(m_backData.m_pAttObj);
		if (!pDV)
			return;
		CXSeismicUTMTool& utm = pDV->GetUTM();

		if (pSection->GetSectionType() == eInlineSection)
		{
			utm.LineToXY(pSection->GetSectionNumber(), dTrace, dX, dY);
		}
		else if (pSection->GetSectionType() == eCrosslineSection)
		{
			utm.LineToXY(dTrace, pSection->GetSectionNumber(), dX, dY);
		}
	}
	else if (m_backData.m_pGeoObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pRSection = (CXSeismicRandomSection *)m_backData.m_pGeoObj->GetObjectType();
		vector<double> vecX, vecY;
		pRSection->GetXYofTuringPoint(vecX, vecY);
		for (auto i = 0; i < vecX.size() - 1; ++i)
		{
			double dTuringBeg = pRSection->GetTPTraceIndex(i);
			double dTuringEnd = pRSection->GetTPTraceIndex(i + 1);

			if (dTuringBeg <= dTrace && dTrace <= dTuringEnd)
			{
				CXLinearityMap xLineMap(dTuringBeg, dTuringEnd, vecX[i], vecX[i + 1]);
				CXLinearityMap yLineMap(dTuringBeg, dTuringEnd, vecY[i], vecY[i + 1]);
				dX = xLineMap.GetOutputValue(dTrace);
				dY = yLineMap.GetOutputValue(dTrace);
				break;
			}
		}
	}
	else if (m_backData.m_pGeoObj->GetObjectType() == EXRandomSection)
	{
		CX2DSeismicLine *p2DLine = (CX2DSeismicLine *)m_backData.m_pGeoObj;

		double *pX, *pY;
		p2DLine->GetCoordData(pX, pY);
		auto pCDP = p2DLine->GetCDPData();
		for (auto i = 0; i != p2DLine->GetTraceNumber() - 1; ++i)
		{
			if (pCDP[i] <= dTrace && dTrace <= pCDP[i + 1])
			{
				CXLinearityMap xLineMap(pCDP[i], pCDP[i + 1], pX[i], pX[i + 1]);
				CXLinearityMap yLineMap(pCDP[i], pCDP[i + 1], pY[i], pY[i + 1]);
				dX = xLineMap.GetOutputValue(dTrace);
				dY = yLineMap.GetOutputValue(dTrace);
				break;
			}
		}
	}
}

void CXSectionScene::GetSectionDimension(int & nJ, int & nK)
{
	nJ = m_backData.m_nTraceQty;
	nK = m_backData.m_nSamplingQty;
}
