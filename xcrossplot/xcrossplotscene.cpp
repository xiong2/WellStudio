#include <qdebug.h>
#include <QStatusBar>
#include <qmessagebox.h>
#include <qgraphicssceneevent.h>
#include "xcolormap.h"
#include "xcrossplotscene.h"
#include "xcrossplot.h"
#include "xglobal.h"
#include "xaxis.h"
#include "xhistitemanno.h"
#include "xaxistitleitem.h"
#include "xcpitempoints.h"
#include "x3dhorizon.h"
#include "xwellcurve.h"

CXCrossPlotScene::CXCrossPlotScene(CXWindow *pWindow, QObject *pParent) : CXScene(pWindow, pParent)
{

}

bool CXCrossPlotScene::CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo)
{
	return true;
}

void CXCrossPlotScene::CreateItem(CXObject *pHObj, CXObject *pVObj, QColor penColor, QColor fillColor, int iSize, int iShape, int iResample, double dSZ, double dEZ)
{
	unsigned int iHNum, iVNum;

	bool bNeedFree = false;
	double *pHData = pHObj->GetData(iHNum);
	double *pVData = pVObj->GetData(iVNum);

	if (iHNum != iVNum)
	{
		QMessageBox::warning(NULL, "Cross Plot", "These two objects have different amount data!");
		return;
	}

	if (pHObj->GetObjectType() == EX3DHorizon || pHObj->GetObjectType() == EX3DHorizonAtt)
	{
		bNeedFree = true;
		int iStep = 1;
		if (iResample == 1)
			iStep = 10;
		else if (iResample == 2)
			iStep = 100;
		else if (iResample == 3)
			iStep = 1000;

		CX3DHorizon *pHHor = (CX3DHorizon *)pHObj;
		iHNum = pHHor->GetUTM().GetNI() * pHHor->GetUTM().GetNJ();

		int iDataSize = iHNum / iStep;
		pHData = new double[iDataSize];
		pVData = new double[iDataSize];

		float *pFHData = pHHor->GetData();
		CX3DHorizon *pVHor = (CX3DHorizon *)pVObj;
		float *pFVData = pVHor->GetData();

		for (int i = 0, j = 0; i < iHNum; i += iStep, j++)
		{
			pHData[j] = (double)pFHData[i];
			pVData[j] = (double)pFVData[i];
		}

		iHNum = iDataSize;
	}
	else if (dSZ != ::g_dInvalidData && dEZ != ::g_dInvalidData)
	{
		bNeedFree = true;
		if (dSZ > dEZ)
		{
			double dTmp = dSZ;
			dSZ = dEZ;
			dEZ = dTmp;
		}

		CXWellCurve *pHCurve = (CXWellCurve *)pHObj;
		CXWellCurve *pVCurve = (CXWellCurve *)pVObj;
		double dStep = pHCurve->GetStep();
		iHNum = (dEZ - dSZ) / dStep + 1;
		pHData = new double[iHNum];
		pVData = new double[iHNum];

		pHCurve->GetData(pHData, dSZ, iHNum);
		pVCurve->GetData(pVData, dSZ, iHNum);
	}

	CXCPItemPoints *pItemPoints = new CXCPItemPoints(sceneRect(), m_pAxisX, m_pAxisY, iHNum, pHData, pVData, penColor, fillColor, iSize, iShape, bNeedFree);
	addItem(pItemPoints);
}

void CXCrossPlotScene::CreateItem(CXObject *pHObj, CXObject *pVObj, CXObject *pCObj, QColor penColor, int iSize, int iShape, int iResample, double dSZ, double dEZ)
{
	unsigned int iHNum, iVNum, iCNum;

	bool bNeedFree = false;
	double *pHData = pHObj->GetData(iHNum);
	double *pVData = pVObj->GetData(iVNum);
	double *pCData = pCObj->GetData(iCNum);

	if (iHNum != iVNum || iHNum != iCNum)
	{
		QMessageBox::warning(NULL, "Cross Plot", "These three objects have different amount data!");
		return;
	}

	CXCrossPlot *pCP = (CXCrossPlot *)m_pWindow;
	pCP->UpdateColormap(m_iColormapIDX, pCObj->GetObjectName(), m_pAxisC->GetBegin(), m_pAxisC->GetEnd());

	if (pHObj->GetObjectType() == EX3DHorizon || pHObj->GetObjectType() == EX3DHorizonAtt)
	{
		bNeedFree = true;
		int iStep = 1;
		if (iResample == 1)
			iStep = 10;
		else if (iResample == 2)
			iStep = 100;
		else if (iResample == 3)
			iStep = 1000;

		CX3DHorizon *pHHor = (CX3DHorizon *)pHObj;
		iHNum = pHHor->GetUTM().GetNI() * pHHor->GetUTM().GetNJ();

		int iDataSize = iHNum / iStep;
		pHData = new double[iDataSize];
		pVData = new double[iDataSize];
		pCData = new double[iDataSize];

		float *pFHData = pHHor->GetData();
		CX3DHorizon *pVHor = (CX3DHorizon *)pVObj;
		float *pFVData = pVHor->GetData();
		CX3DHorizon *pCHor = (CX3DHorizon *)pCObj;
		float *pFCData = pCHor->GetData();

		for (int i = 0, j = 0; i < iHNum; i += iStep, j++)
		{
			pHData[j] = (double)pFHData[i];
			pVData[j] = (double)pFVData[i];
			pCData[j] = (double)pFCData[i];
		}

		iHNum = iDataSize;
	}
	else if (dSZ != ::g_dInvalidData && dEZ != ::g_dInvalidData)
	{
		bNeedFree = true;
		if (dSZ > dEZ)
		{
			double dTmp = dSZ;
			dSZ = dEZ;
			dEZ = dTmp;
		}

		CXWellCurve *pHCurve = (CXWellCurve *)pHObj;
		CXWellCurve *pVCurve = (CXWellCurve *)pVObj;
		CXWellCurve *pCCurve = (CXWellCurve *)pCObj;
		double dStep = pHCurve->GetStep();
		iHNum = (dEZ - dSZ) / dStep + 1;
		pHData = new double[iHNum];
		pVData = new double[iHNum];
		pCData = new double[iHNum];

		pHCurve->GetData(pHData, dSZ, iHNum);
		pVCurve->GetData(pVData, dSZ, iHNum);
		pCCurve->GetData(pCData, dSZ, iHNum);
	}

	CXCPItemPoints *pItemPoints = new CXCPItemPoints(sceneRect(), m_pAxisX, m_pAxisY, m_pAxisC, iHNum, pHData, pVData, pCData, penColor, m_iColormapIDX, iSize, iShape, bNeedFree);
	addItem(pItemPoints);
}

void CXCrossPlotScene::mouseMoveEvent(QGraphicsSceneMouseEvent *pEvent)
{
	if (!m_pAxisX)
		return;

	CXCrossPlot *pCP = (CXCrossPlot *)m_pWindow;
	QPointF newPos = pEvent->scenePos();
	QRectF rect = sceneRect();
	rect.adjust(2 * SCENEMARGIN + 30, SCENEMARGIN + 10, -SCENEMARGIN - 10, -2 * SCENEMARGIN - 20);
	if (!rect.contains(newPos))
	{
		pCP->ShowStatus("");
		return;
	}

	double dX = (newPos.x() - rect.left()) / rect.width();
	dX = m_pAxisX->GetBegin() + dX * m_pAxisX->GetValueRange();
	double dY = (newPos.y() - rect.top()) / rect.height();
	dY = m_pAxisY->GetEnd() - dY * m_pAxisY->GetValueRange();

	pCP->ShowStatus(m_pHTitleItem->GetName() + ": " + QString::number(dX) + ",  " + m_pVTitleItem->GetName() + ": " + QString::number(dY));
}

void CXCrossPlotScene::SetRange(QString sHTitle, QString sVTitle, double dXMin, double dXMax, double dYMin, double dYMax, double dCMin, double dCMax)
{
	clear();

	if (!m_pAxisX)
	{
		m_pAxisX = new CXAxis(dXMin, dXMax);
		m_pAxisX->SetAxisType(CXAxis::XAxis);
	}
	else
	{
		m_pAxisX->SetBegin(dXMin);
		m_pAxisX->SetEnd(dXMax);
	}

	if (!m_pAxisY)
	{
		m_pAxisY = new CXAxis(dYMin, dYMax);
	}
	else
	{
		m_pAxisY->SetBegin(dYMin);
		m_pAxisY->SetEnd(dYMax);
	}

	if (!m_pAxisC)
	{
		m_pAxisC = new CXAxis(dCMin, dCMax);
	}
	else
	{
		m_pAxisC->SetBegin(dCMin);
		m_pAxisC->SetEnd(dCMax);
	}

	QRectF rect = sceneRect();
	rect.adjust(2 * SCENEMARGIN, SCENEMARGIN, -SCENEMARGIN, -2 * SCENEMARGIN);
	m_pAnnoItem = new CXHistItemAnno(rect, m_pAxisX, m_pAxisY);
	addItem(m_pAnnoItem);

	m_pHTitleItem = new CXAxisTitleItem(sHTitle);
	m_pHTitleItem->Populate(true, false);
	addItem(m_pHTitleItem);

	m_pVTitleItem = new CXAxisTitleItem(sVTitle);
	m_pVTitleItem->Populate(false, true);
	addItem(m_pVTitleItem);
}