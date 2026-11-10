#include <qevent.h>
#include "xsechorizonpickingitem.h"
#include "x3dhorizon.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xglobal.h"
#include "xviewinfo3dhorizon.h"
#include "xsectionscene.h"
#include "xeventconsole.h"
#include "x2daxishelper.h"
#include "xcoordtransformer.h"

CXSecHorizonPickingItem::CXSecHorizonPickingItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent) : CXAbstractItem(pWindow)
{
	setZValue(2);
	m_eMode		= eSecHorizonManual;
}


CXSecHorizonPickingItem::~CXSecHorizonPickingItem(void)
{
}

void CXSecHorizonPickingItem::_UpdateData()
{
	m_pScene = (CXSectionScene *)scene();
	m_vecZ.clear();
	m_vecPoints.clear();
	m_rubberyLine = QLineF();

	m_pHorizon = dynamic_cast<CX3DHorizon*>(GetItemObject());
	if (m_pHorizon == NULL)
	{
		return;
	}

	CXSeismicUTMTool& hUTM = m_pHorizon->GetUTM();
	float *pHorizonData = m_pHorizon->GetData();
	int i, j, nJ = hUTM.GetNJ();

	CXObject* pCurSection = m_pSectionWindow->GetCurrentGeometryObj();
	CXSeismicSection* pSeismicSection = dynamic_cast<CXSeismicSection*>(pCurSection);
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pCurSection);

	if (pSeismicSection != NULL)
	{
		int i, iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc;
		CXSeismicUTMTool sUTM = pSeismicSection->GetUTM();
		sUTM.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		int iSectionNumber = (int)pSeismicSection->GetSectionNumber();
		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			m_iSTrace = iSXline;
			m_iTraceInc = iXlineInc;

			for (int m = iSXline; m <= iEXline; m += iXlineInc)
			{
				hUTM.LineToIJ(iSectionNumber, m, i, j);
				m_vecZ.push_back(pHorizonData[i * nJ + j]);
			}
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			m_iSTrace = iSInline;
			m_iTraceInc = iInlineInc;

			for (int m = iSInline; m <= iEInline; m += iInlineInc)
			{
				hUTM.LineToIJ(m, iSectionNumber, i, j);
				m_vecZ.push_back(pHorizonData[i * nJ + j]);
			}
		}
	}
	else if (NULL != pRandomSection)
	{
		m_iSTrace = 0;
		m_iTraceInc = 1;

		std::vector<int> vecInlineNum, vecXlineNum;
		pRandomSection->GetLineNumbers(vecInlineNum, vecXlineNum);
		int iSize = vecInlineNum.size();
		for (int m = 0; m < iSize; ++m)
		{
			hUTM.LineToIJ(vecInlineNum[m], vecXlineNum[m], i, j);
			m_vecZ.push_back(pHorizonData[i * nJ + j]);
		}
	}

	MapToScene();
}

void CXSecHorizonPickingItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;	

	m_Path = QPainterPath();
	m_vecIntPoints.clear();
	bool bHasNew(false);
	int nSize = m_vecZ.size();

	for (int i = 0; i < nSize; ++i)
	{
		if (m_vecZ[i] == g_dInvalidData)
		{
			bHasNew = true;
			continue;
		}

		float fTrace = m_iSTrace + i * m_iTraceInc;

		transformer.World2Scene(fTrace, qAbs(m_vecZ[i]), scenex, sceney);

		QPointF fPos(scenex, sceney);

		if (m_Path.elementCount() == 0 || bHasNew)
		{
			m_Path.moveTo(fPos);
			bHasNew = false;

			if (i < nSize - 1 && m_vecZ[i + 1] == g_dInvalidData)
				m_vecIntPoints << fPos;
		}
		else
		{
			m_Path.lineTo(fPos);
		}
	}

	update();
}

void CXSecHorizonPickingItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	CX3DHorizon *p3DHorizon = dynamic_cast<CX3DHorizon*>(GetItemObject());
	CXViewInfo3DHorizon *pHorizonViewInfo = dynamic_cast<CXViewInfo3DHorizon*>(m_pViewInfo);

	QPen pen;
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	int iWidth = pHorizonViewInfo->GetSectionLineWidth();
	pen.setWidthF(iWidth);
	pen.setColor(Qt::yellow);
	painter->setPen(pen);

	painter->drawPath(m_Path);

	if (m_eMode == eSecHorizonErase)
	{
		if (m_rubberyLine.x2() > m_rubberyLine.x1())
		{	
			CXCoordTransformer transformer(m_pScene);

			double scenex, sceney;
			transformer.View2Scene(0, 0, scenex, sceney);

			QPointF oriPoint(scenex, sceney);

			painter->save();
			painter->setPen(QColor("red"));
			painter->drawLine(m_rubberyLine.x1(), oriPoint.y(), m_rubberyLine.x1(), oriPoint.y() + m_pScene->sceneRect().height());
			painter->drawLine(m_rubberyLine.x2(), oriPoint.y(), m_rubberyLine.x2(), oriPoint.y() + m_pScene->sceneRect().height());
			painter->setOpacity(0.4);
			painter->fillRect(m_rubberyLine.x1(), oriPoint.y(), m_rubberyLine.x2() - m_rubberyLine.x1(), m_pScene->sceneRect().height(), Qt::red);

			painter->restore();
		}
	}
	else
		painter->drawLine(m_rubberyLine);

	pen.setWidthF(4 * iWidth);
	painter->setPen(pen);
	painter->drawPoints(m_vecIntPoints.data(), m_vecIntPoints.size());
}

void CXSecHorizonPickingItem::HandleMouseEvent(QMouseEvent *pEvent, EXMouseEventType eType)
{
	if (eType == eSecButtonPress && pEvent->button() == Qt::LeftButton)
		_leftButtonPressed(pEvent);
	else if (eType == eSecButtonPress && pEvent->button() == Qt::MidButton)
		_middleButtonPressed();
	else if (eType == eSecDoubleClick && pEvent->button() == Qt::LeftButton)
		_leftButtonDoubleClicked(pEvent);
	else if (eType == eSecMouseMove)
		_mouseMoving(pEvent);
	else if (eType == eSecButtonRelease)
		_buttonRelease();
}

void CXSecHorizonPickingItem::_leftButtonPressed(QMouseEvent *pEvent)
{
	CXCoordTransformer transformer(m_pScene);

	double scenex, sceney;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), scenex, sceney);

	QPointF scenePos(scenex, sceney);

	if (m_eMode == eSecHorizonErase)
	{
		m_rubberyLine = QLineF(scenePos, scenePos + QPointF(.1, 0));
	}
	else
	{
		//	Picking mode.
		if (m_eMode == eSecHorizonManual || m_eMode == eSecHorizonSemiAuto)
		{
			if (m_vecPoints.size() > 0 && m_vecPoints.last().x() > scenePos.x())
			{
				//	Only support pick from left to right!
				return;
			}

			m_rubberyLine = QLineF(scenePos, scenePos);

			if (m_vecPoints.size() > 0)
			{
				double worldx, worldy;

				transformer.Scene2World(m_vecPoints[m_vecPoints.size() - 1].x(), m_vecPoints[m_vecPoints.size() - 1].y(), worldx, worldy);
				int iT1 = (int)worldx;
				double dZ1 = worldy;

				transformer.Scene2World(scenex, sceney, worldx, worldy);
				int iT2 = (int)worldx;
				double dZ2 = worldy;

				iT1 = (iT1 - m_iSTrace) / m_iTraceInc;
				iT2 = (iT2 - m_iSTrace) / m_iTraceInc;
				if (iT2 == iT1)
					return;

				double dDeltaZ = (dZ2 - dZ1) / (iT2 - iT1);
				for (int i = iT1; i <= iT2; i++)
					m_vecZ[i] = dZ1 + (i - iT1) * dDeltaZ;

				MapToScene();

				_saveBackHorizonData();
			}

			m_vecPoints << scenePos;
		}
	}
}

void CXSecHorizonPickingItem::_middleButtonPressed()
{
	if ((m_eMode != eSecHorizonManual && m_eMode != eSecHorizonSemiAuto) || m_vecPoints.isEmpty())
		return;

	if (m_vecPoints.size() == 1)
	{
		m_vecPoints.clear();
		m_rubberyLine = QLineF();

		MapToScene();
	}
	else
	{
		CXCoordTransformer transformer(m_pScene);

		double worldx, worldy;

		transformer.Scene2World(m_vecPoints.last().x(), m_vecPoints.last().y(), worldx, worldy);
		int iT1 = (int)worldx;

		QPointF lastPoint = m_vecPoints.takeLast();
		transformer.Scene2World(lastPoint.x(), lastPoint.y(), worldx, worldy);
		int iT2 = (int)worldx;

		iT1 = (iT1 - m_iSTrace) / m_iTraceInc;
		iT2 = (iT2 - m_iSTrace) / m_iTraceInc;
		for (int i = iT1; i <= iT2; i++)
			m_vecZ[i] = g_dInvalidData;

		m_rubberyLine.setP1(m_vecPoints.last());

		MapToScene();

		_saveBackHorizonData();
	}
}

void CXSecHorizonPickingItem::_leftButtonDoubleClicked(QMouseEvent *pEvent)
{
	m_vecPoints.clear();
	m_rubberyLine = QLineF();
}

void CXSecHorizonPickingItem::_mouseMoving(QMouseEvent *pEvent)
{
	CXCoordTransformer transformer(m_pScene);

	double scenex, sceney;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), scenex, sceney);

	if (m_eMode == eSecHorizonErase && !m_rubberyLine.isNull())
	{
		m_rubberyLine.setP2(QPointF(scenex, sceney));
		update();
	}
	else if (m_eMode == eSecHorizonManual || m_eMode == eSecHorizonSemiAuto)
	{
		if (m_vecPoints.size() > 0)
		{
			m_rubberyLine.setP2(QPointF(scenex, sceney));
			update();
		}
	}
}

void CXSecHorizonPickingItem::_buttonRelease()
{
	if (m_eMode == eSecHorizonErase && !m_rubberyLine.isNull())
	{
		if (m_rubberyLine.x1() <= m_rubberyLine.x2())
		{
			CXCoordTransformer transformer(m_pScene);

			double worldx, worldy;

			transformer.Scene2World(m_rubberyLine.x1(), m_rubberyLine.y1(), worldx, worldy);
			int iT1 = (int)worldx;
			
			transformer.Scene2World(m_rubberyLine.x2(), m_rubberyLine.y2(), worldx, worldy);
			int iT2 = (int)worldx;
			
			iT1 = (iT1 - m_iSTrace) / m_iTraceInc;
			iT2 = (iT2 - m_iSTrace) / m_iTraceInc;

			for (int i = iT1; i <= iT2; i++)
				m_vecZ[i] = g_dInvalidData;

			_saveBackHorizonData();
		}

		m_rubberyLine = QLineF();
		MapToScene();
	}
}

void CXSecHorizonPickingItem::_saveBackHorizonData()
{
	CXSeismicUTMTool& hUTM = m_pHorizon->GetUTM();
	float *pHorizonData = m_pHorizon->GetData();
	int i, j, nJ = hUTM.GetNJ();

	CXObject* pCurSection = m_pSectionWindow->GetCurrentGeometryObj();
	CXSeismicSection* pSeismicSection = dynamic_cast<CXSeismicSection*>(pCurSection);
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pCurSection);

	if (pSeismicSection != NULL)
	{
		int i, iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc;
		CXSeismicUTMTool sUTM = pSeismicSection->GetUTM();
		sUTM.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		int iSectionNumber = (int)pSeismicSection->GetSectionNumber();
		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			for (int m = iSXline; m <= iEXline; m += iXlineInc)
			{
				hUTM.LineToIJ(iSectionNumber, m, i, j);
				pHorizonData[i * nJ + j] = m_vecZ[(m - iSXline) / iXlineInc];
			}
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			for (int m = iSInline; m <= iEInline; m += iInlineInc)
			{
				hUTM.LineToIJ(m, iSectionNumber, i, j);
				pHorizonData[i * nJ + j] = m_vecZ[(m - iSInline) / iInlineInc];
			}
		}
	}
	else if (NULL != pRandomSection)
	{
		std::vector<int> vecInlineNum, vecXlineNum;
		pRandomSection->GetLineNumbers(vecInlineNum, vecXlineNum);
		int iSize = vecInlineNum.size();
		for (int m = 0; m < iSize; ++m)
		{
			hUTM.LineToIJ(vecInlineNum[m], vecXlineNum[m], i, j);
			pHorizonData[i * nJ + j] = m_vecZ[m];
		}
	}

	m_pHorizon->SetNeedCalcDimension();
	m_pHorizon->SetModifiedFlag();

	CXProcessEvent pEvent(m_pScene);
	m_pHorizon->AddEvent(EDataChanged);
}