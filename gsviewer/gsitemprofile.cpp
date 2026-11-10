#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "gsitemprofile.h"
#include "gssection.h"
#include "gssectionscene.h"
#include "x3dhorizon.h"
#include "xseismicutmtool.h"
#include "gssectionviewinfo.h"
#include "xcolormap.h"
#include "gscompressionpulse.h"
#include "xglobal.h"

GSItemProfile::GSItemProfile(GSSection *pSection, CXViewInfoObject *pViewInfo, QGraphicsItem *parent) : GSObjItem(pViewInfo, parent)
{
	m_pSection = pSection;
}

bool GSItemProfile::SceneXToXY(int iX, double& dX, double& dY)
{
	double dHScale, dVScale;
	GSSectionScene *pScene = (GSSectionScene *)scene();
	pScene->GetScale(dHScale, dVScale);
	int iCanWidth = m_pSection->GetSectionLength() * dHScale;

	if (iX < LEFT_MARGIN || iX > LEFT_MARGIN + iCanWidth)
		return false;

	int iDataLen = m_pSection->GetTraces().size();
	int iPos = 1. * iDataLen * (iX - LEFT_MARGIN) / iCanWidth;
	if (iPos > iDataLen - 1)
		iPos = iDataLen - 1;
	m_pSection->GetUTM().IJToXY(m_pSection->GetTraces()[iPos].x(), m_pSection->GetTraces()[iPos].y(), dX, dY);
	return true;
}

void GSItemProfile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	setRect(scene()->sceneRect());

	double dHScale, dVScale, dLen = m_pSection->GetSectionLength(), dHei = m_pSection->GetSectionHeight();
	GSSectionScene *pScene = (GSSectionScene *)scene();
	pScene->GetScale(dHScale, dVScale);

	int i, j, k;
	double dOffset = 0;
	QPolygonF turnPoints = m_pSection->GetTurnPoints();

	//	Boarder.
	painter->drawRect(LEFT_MARGIN, TOP_MARGIN, dLen * dHScale, dHei * dVScale);

	//	Draw horizons.
	QPen pen(QColor("black"));
	pen.setWidth(2);
	painter->setPen(pen);

	int iDataLen = m_pSection->GetTraces().size();
	QList<QUuid> listHID = m_pSection->GetHorizonsID();
	float *pData = m_pSection->GetData();
	float fDX = dLen * dHScale / (iDataLen - 1);

	GSSectionViewInfo *pViewInfo = (GSSectionViewInfo *)m_pViewInfo;

	QPainterPath path;
	QPolygon poly1, poly2;

	if (pViewInfo->GetFillByStress() == true)
	{
		painter->save();
		painter->setPen(Qt::NoPen);

		CXColormap* pColormap = CXColormap::GetColormap("stressmap");
		char *pStress = m_pSection->GetStressData();
		for (i = 0; i < listHID.size() - 1; i++)
		{
			int iStart = 0, iLastID = pStress[i * iDataLen];
			poly1.clear();
			poly1 << QPoint(LEFT_MARGIN, pScene->ZToSceneY(pData[i * iDataLen]));

			for (j = 1; j < iDataLen; j++)
			{
				poly1 << QPoint(LEFT_MARGIN + j * fDX, pScene->ZToSceneY(pData[i * iDataLen + j]));

				if (pStress[i * iDataLen + j] != iLastID)
				{
					for (k = j; k >= iStart; k--)
					{
						poly1 << QPoint(LEFT_MARGIN + k * fDX, pScene->ZToSceneY(pData[(i + 1) * iDataLen + k]));
					}


					QColor color = QColor("white");
					if (iLastID != -1)
						color = pColormap->GetColorAt(iLastID);
					painter->setBrush(QBrush(color));
					painter->drawPolygon(poly1);

					iLastID = pStress[i * iDataLen + j];
					iStart = j;
					poly1.clear();
					poly1 << QPoint(LEFT_MARGIN + j * fDX, pScene->ZToSceneY(pData[i * iDataLen + j]));
				}
			}

			for (k = j - 1; k >= iStart; k--)
			{
				poly1 << QPoint(LEFT_MARGIN + k * fDX, pScene->ZToSceneY(pData[(i + 1) * iDataLen + k]));
			}


			QColor color = QColor("white");
			if (iLastID != -1)
				color = pColormap->GetColorAt(iLastID);
			painter->setBrush(QBrush(color));
			painter->drawPolygon(poly1);
		}

		painter->restore();
	}

	poly1.clear();
	poly1 << QPoint(LEFT_MARGIN, TOP_MARGIN) << QPoint(LEFT_MARGIN + dLen * dHScale, TOP_MARGIN);
	bool bL2R = false;
	for (i = 0; i < listHID.size(); i++)
	{
		if (pViewInfo->GetFillByStress() == false)
		{
			QColor color = GetObjectByID(listHID[i])->GetColor();
			painter->setBrush(QBrush(color));
		}

		if (bL2R)
		{
			for (j = 0; j < iDataLen; j++)
			{
				poly1 << QPoint(LEFT_MARGIN + j * fDX, pScene->ZToSceneY(pData[i * iDataLen + j]));
			}

			poly2 += poly1;

			painter->drawPolygon(poly2);
			poly2.clear();
			bL2R = false;
		}
		else
		{
			for (j = iDataLen - 1; j >= 0; j--)
			{
				poly2 << QPoint(LEFT_MARGIN + j * fDX, pScene->ZToSceneY(pData[i * iDataLen + j]));
			}

			poly1 += poly2;

			painter->drawPolygon(poly1);
			poly1.clear();
			bL2R = true;
		}
	}


	//	Horizon name.
	QStringList sListHName, sListPName;
	int iOdd = 1;
	if (pViewInfo->GetLeftHName() == true || pViewInfo->GetLeftPName() == true
		|| pViewInfo->GetRightHName() == true || pViewInfo->GetRightPName() == true)
	{
		for (i = 0; i < listHID.size(); i++)
		{
			CX3DHorizon *pHor = dynamic_cast<CX3DHorizon *>(GetObjectByID(listHID[i]));
			if (pHor)
			{
				sListHName << pHor->GetParent()->GetObjectName();

				sListPName << GSCompressionPulse::GetOnePulse(pHor->GetPulse(), false);
			}
			else
			{
				sListHName << "Nan";
				sListPName << "Nan";
			}

			if (pViewInfo->GetLeftHName() == true)
			{
				painter->drawText(LEFT_MARGIN + 10, pScene->ZToSceneY(pData[i * iDataLen]), 150, 15, Qt::AlignLeft, sListHName[i]);
			}

			if (pViewInfo->GetRightHName() == true)
			{
				painter->drawText(LEFT_MARGIN + dLen * dHScale - 160, pScene->ZToSceneY(pData[(i + 1) * iDataLen - 1]), 150, 15, Qt::AlignRight, sListHName[i]);
			}

			if (pViewInfo->GetLeftPName() == true || pViewInfo->GetRightPName() == true)
			{
				iOdd = 1 - iOdd;
				painter->save();
				painter->setBrush(QBrush("black"));

				if (pViewInfo->GetLeftPName() == true)
				{
					painter->drawEllipse(LEFT_MARGIN + (iOdd + 1) * 30, pScene->ZToSceneY(pData[i * iDataLen]), 30, 30);
					painter->setPen("white");
					painter->drawText(LEFT_MARGIN + (iOdd + 1) * 30, pScene->ZToSceneY(pData[i * iDataLen]), 30, 30, Qt::AlignCenter, sListPName[i]);
				}

				if (pViewInfo->GetRightPName() == true)
				{
					painter->drawEllipse(LEFT_MARGIN + dLen * dHScale - 60 - iOdd * 30, pScene->ZToSceneY(pData[(i + 1) * iDataLen - 1]), 30, 30);
					painter->setPen("white");
					painter->drawText(LEFT_MARGIN + dLen * dHScale - 60 - iOdd * 30, pScene->ZToSceneY(pData[(i + 1) * iDataLen - 1]), 30, 30, Qt::AlignCenter, sListPName[i]);
				}

				painter->restore();
			}
		}
	}

	//	Left/right side annotation.
	for (int iPos = 0; iPos <= dHei; iPos += 100)
	{
		painter->drawLine(LEFT_MARGIN, TOP_MARGIN + iPos * dVScale, LEFT_MARGIN - 5, TOP_MARGIN + iPos * dVScale);
		painter->drawLine(LEFT_MARGIN + dLen * dHScale, TOP_MARGIN + iPos * dVScale, LEFT_MARGIN + dLen * dHScale + 5, TOP_MARGIN + iPos * dVScale);

		if (iPos % 500 == 0)
		{
			painter->drawLine(LEFT_MARGIN, TOP_MARGIN + iPos * dVScale, LEFT_MARGIN - 10, TOP_MARGIN + iPos * dVScale);
			painter->drawText(LEFT_MARGIN - 40, TOP_MARGIN + iPos * dVScale - 5, 25, 15, Qt::AlignRight, QString::number(iPos));

			painter->drawLine(LEFT_MARGIN + dLen * dHScale, TOP_MARGIN + iPos * dVScale, LEFT_MARGIN + dLen * dHScale + 10, TOP_MARGIN + iPos * dVScale);
			painter->drawText(LEFT_MARGIN + dLen * dHScale + 15, TOP_MARGIN + iPos * dVScale - 5, 25, 15, Qt::AlignLeft, QString::number(iPos));
		}
	}

	//	Top annotation and turn points' line.
	dOffset = 0;
	pen.setWidth(1);
	painter->setPen(pen);
	for (i = 0; i < turnPoints.size(); i++)
	{
		int iX = LEFT_MARGIN + dOffset * dHScale - 100;
		painter->drawText(iX, TOP_MARGIN - 20, 200, 20, Qt::AlignCenter, "(" + QString::number(turnPoints[i].x()) + ", " + QString::number(turnPoints[i].y(), 'f', 0) + ")");

		painter->drawLine(LEFT_MARGIN + dOffset * dHScale, TOP_MARGIN - 5, LEFT_MARGIN + dOffset * dHScale, TOP_MARGIN + dHei * dVScale);

		dOffset += m_pSection->GetSectionLength(i);
	}

	//	Title.
	QFont font = painter->font();
	font.setPixelSize(30);
	painter->setFont(font);
	QString sName = m_pSection->GetObjectName() + " (Depth)";
	painter->drawText(LEFT_MARGIN + dLen * dHScale / 2 - 200, 10, 400, 50, Qt::AlignCenter, sName);
}