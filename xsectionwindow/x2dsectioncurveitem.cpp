#include "x2dsectioncurveitem.h"

#include <QMatrix2x2>
#include <QVector2D>

#include "xwellcurve.h"
#include "xglobal.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xviewinfowellcurve.h"
#include "x2dsectionwindow.h"
#include "xbaseconsole.h"
#include "x2dsectionaxis.h"
#include "xlinearitymap.h"
#include "xcolormap.h"
#include "xwindowinfosection.h"

#include "xsectionscene.h"
#include "x2dwellitem.h"
#include "xalgorithmutility.h"
#include "xmathmacro.h"
#include "xbuttoncoloredit.h"
#include "xcoordtransformer.h"

CX2DSectionCurveItem::CX2DSectionCurveItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent) :CXAbstractItem(pWindow)
{
	this->setZValue(1);
}

CX2DSectionCurveItem::~CX2DSectionCurveItem(void)
{
}

void CX2DSectionCurveItem::_UpdateData()
{
	MapToScene();
}

void CX2DSectionCurveItem::MapToScene()
{
	m_vecDrawPoint.clear();
	m_vecBasePoint.clear();
	m_vecColor.clear();

	CXWellCurve *pWellCurve = dynamic_cast<CXWellCurve *>(GetItemObject());
	CXWell *pWell = dynamic_cast<CXWell *>(pWellCurve->GetParent());
	if (pWellCurve == NULL || pWell == NULL)
	{
		return;
	}

	//	Get well item for the path data.
	CXSectionScene *pScene = (CXSectionScene *)scene();
	CX2DWellItem *pWellItem = dynamic_cast<CX2DWellItem *>(pScene->FindItem(pWell->GetObjectID()));
	if (!pWellItem)
		return;

	QVector<QPointF> vecFullPath = pWellItem->GetPathData(true);
	QVector<double> vecFullMD = pWellItem->GetPathMD(true);
	QVector<QPointF> vecPathData = pWellItem->GetPathData(false);
	QVector<double> vecPathMD = pWellItem->GetPathMD(false);

	if (vecPathData.isEmpty() || vecPathData.size() != vecPathMD.size())
		return;

	CXViewInfoWellCurve *pCurveViewInfo = dynamic_cast<CXViewInfoWellCurve*>(m_pViewInfo);
	if (!pCurveViewInfo)
		return;

	unsigned int iNumber = pWellCurve->GetPointNumber();
	double dStep = pWellCurve->GetStep();
	double dStart, dEnd;
	pWellCurve->GetDepthRange(dStart, dEnd);
	vector<double> vecData(iNumber);

	if (!CXAlgorithmUtility::GetFilteredData(pWellCurve, &vecData[0], pCurveViewInfo->GetFilterType(), pCurveViewInfo->GetFilterLowFreq(), pCurveViewInfo->GetFilterLowOverlap(),
		pCurveViewInfo->GetFilterHighFreq(), pCurveViewInfo->GetFilterHighOverlap()))
		return;

	double dDataMin(M_FLT_MAX), dDataMax(M_FLT_NEGATIVEMAX);
	for (int i = 0; i < vecData.size(); ++i)
	{
		if (vecData[i] == ::g_dInvalidData)
			continue;

		dDataMin = qMin(dDataMin, vecData[i]);
		dDataMax = qMax(dDataMax, vecData[i]);
	}

	int fDisplayWidth = pCurveViewInfo->GetFillWidth();
	CXLinearityMap lineMap(dDataMin, dDataMax, 0, fDisplayWidth);

	int i, j = 0, iDataStart = 0, iSOffset = 0;
	double dCurveMD = dStart;
	QLineF segLastLine;

	//	If some curve points above the path, abort them.
	if (dEnd < vecPathMD[0])
		return;

	if (dStart < vecPathMD[0])
	{
		j = (int)((vecPathMD[0] - dStart) / dStep) + 1;
		dCurveMD = dStart + j * dStep;
	}

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	for (i = 0; i < vecPathMD.size() - 1; i++)
	{
		if (dCurveMD > vecPathMD[i + 1])
			continue;

		transformer.World2Scene(vecPathData[i].x(), vecPathData[i].y(), scenex, sceney);
		QPointF FirstPointF(scenex, sceney);

		transformer.World2Scene(vecPathData[i + 1].x(), vecPathData[i + 1].y(), scenex, sceney);
		QPointF LastPointF(scenex, sceney);

		QLineF LineAB(FirstPointF, LastPointF);
		QLineF LineArr = LineAB.normalVector();

		QVector2D vecA(LineArr.x1(), LineArr.y1());
		QVector2D vecB(LineArr.x2(), LineArr.y2());
		QVector2D vecBA = vecB - vecA;
		vecBA.normalize();

		while (j < iNumber && dCurveMD < vecPathMD[i + 1])
		{
			double dValue = vecData[j];
			if (dValue == ::g_dInvalidData)
			{
				//	Abort invalid points at the beginning.
				if (m_vecDrawPoint.isEmpty())
				{
					j++;
					dCurveMD = dStart + j * dStep;
					continue;
				}

				dValue = dDataMin;
			}

			double dWidth = lineMap.GetOutputValue(dValue);
			if (dWidth < 0)
			{
				dWidth = 0;
			}

			QVector2D vecLast = vecBA*dWidth;
			QPointF valuePoint = vecLast.toPointF();
			QVector2D vecAdj = vecBA * (fDisplayWidth / 2);
			QPointF adjPoint = vecAdj.toPointF();

			QPointF curvePoint = _findPostion(iSOffset, dCurveMD, vecFullMD, vecFullPath);

			transformer.World2Scene(curvePoint.x(), curvePoint.y(), scenex, sceney);
			QPointF pos(scenex, sceney);
			QPointF DrawPoint = pos + valuePoint - adjPoint;

			//	Record the start offset of the curve data being drawn.
			if (m_vecBasePoint.isEmpty())
				iDataStart = j;

			m_vecDrawPoint.push_back(DrawPoint);
			m_vecBasePoint.push_back(pos);

			j++;
			dCurveMD = dStart + j * dStep;
		}
	}

	//	Prepare the colors for colorful filling.
	for (i = 0; i < m_vecDrawPoint.size(); i++)
	{
		QColor qColor = _mapColor(vecData[i + iDataStart]);
		m_vecColor << qColor;
	}

	update();
}

QPointF CX2DSectionCurveItem::_findPostion(int& iSOffset, double dMD, QVector<double>& vecMD, QVector<QPointF>& vecPath)
{
	int iSize = vecMD.size() - 1;
	for (; iSOffset < iSize; iSOffset++)
	{
		if (dMD >= vecMD[iSOffset] && dMD < vecMD[iSOffset + 1])
		{
			float fPercentage = (dMD - vecMD[iSOffset]) / (vecMD[iSOffset + 1] - vecMD[iSOffset]);
			return QPointF(vecPath[iSOffset].x() + fPercentage * (vecPath[iSOffset + 1].x() - vecPath[iSOffset].x()),
				vecPath[iSOffset].y() + fPercentage * (vecPath[iSOffset + 1].y() - vecPath[iSOffset].y()));
		}
	}

	return QPointF();
}

QColor CX2DSectionCurveItem::_mapColor(double dValue)
{
	CXViewInfoWellCurve *pCurveViewInfo = dynamic_cast<CXViewInfoWellCurve*>(m_pViewInfo);

	if (pCurveViewInfo->GetFillColorMode() == 0) // use single color manually
	{
		return pCurveViewInfo->GetFillColor();
	}
	else if (pCurveViewInfo->GetFillColorMode() == 1) // use object color
	{
		return pCurveViewInfo->GetColor();
	}
	else if (pCurveViewInfo->GetFillColorMode() == 2) // use colormap.
	{
		CXColormap *pColormap = CXColormap::GetColormap(pCurveViewInfo->GetColormapName());
		Q_ASSERT(pColormap);

		double dMin = pCurveViewInfo->GetDisplayDataMin();
		double dMax = pCurveViewInfo->GetDisplayDataMax();

		return pColormap->GetColorAt(qRound((dValue - dMin) / (dMax - dMin) * 255));
	}
	else
	{
		return QColor::Invalid;
	}
}

void CX2DSectionCurveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_vecDrawPoint.isEmpty())
		return;

	CXViewInfoWellCurve *pCurveViewInfo = dynamic_cast<CXViewInfoWellCurve*>(m_pViewInfo);

	int iSize = m_vecBasePoint.size();

	if (pCurveViewInfo->GetDisplayModeSection() == CXViewInfoWellCurve::ECurve)
	{
		if (pCurveViewInfo->GetFillVisible())
		{
			int iColorMode = pCurveViewInfo->GetFillColorMode();

			if (CXButtonColorEdit::SelectColor == iColorMode 
				|| CXButtonColorEdit::ObjColor == iColorMode)
			{
				QVector<QPointF> vecRBasePoint;
				for (int i = 0; i < iSize; ++i)
				{
					vecRBasePoint.push_back(m_vecBasePoint[iSize - i - 1]);
				}
				vecRBasePoint += m_vecDrawPoint;

				painter->setBrush(iColorMode ? pCurveViewInfo->GetColor() : pCurveViewInfo->GetFillColor());
				painter->drawPolygon(vecRBasePoint);
			}
			else // Colormap
			{
				for (int i = 0; i < iSize; i++)
				{
					painter->setPen(m_vecColor[i]);
					painter->drawLine(m_vecBasePoint[i], m_vecDrawPoint[i]);
				}
			}
		}

		if (pCurveViewInfo->GetLineVisible())
		{
			QPen pen;
			pen.setColor(pCurveViewInfo->GetLineColorMode() ? pCurveViewInfo->GetColor() : pCurveViewInfo->GetLineColor());
			pen.setWidth(pCurveViewInfo->GetLineWidth());
			painter->setPen(pen);
			painter->drawPolyline(m_vecDrawPoint.data(), m_vecDrawPoint.size());
		}
	}
	else if (pCurveViewInfo->GetDisplayModeSection() == CXViewInfoWellCurve::EVI)
	{
		int nWidth = pCurveViewInfo->GetVIWidth();

		for (int i = 0; i < iSize; ++i)
		{
			painter->setPen(m_vecColor[i]);
			QPointF pointStart(m_vecBasePoint[i].x() - nWidth, m_vecBasePoint[i].y());
			QPointF pointEnd(m_vecBasePoint[i].x() + nWidth, m_vecBasePoint[i].y());

			painter->drawLine(pointStart, pointEnd);
		}
	}
	else
	{
		Q_ASSERT(false);
	}
}

QRectF	CX2DSectionCurveItem::boundingRect() const
{
	QPolygonF polygon(m_vecDrawPoint);
	return polygon.boundingRect();
}