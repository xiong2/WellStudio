#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "gsitempdg.h"
#include "gspdg.h"
#include "gspdgscene.h"
#include "x3dhorizon.h"
#include "xutmtool.h"
#include "gssectionviewinfo.h"
#include "xcolormap.h"
#include "gscompressionpulse.h"
#include "gsdef.h"
#include "xglobal.h"

GSItemPDG::GSItemPDG(GSPDG *pPDG, CXViewInfoObject *pViewInfo, QGraphicsItem *parent) : GSObjItem(pViewInfo, parent)
{
	m_pPDG = pPDG;
}

bool GSItemPDG::SceneXToXY(int iX, double& dX, double& dY)
{
	//double dHScale, dVScale;
	//GSSectionScene *pScene = (GSSectionScene *)scene();
	//pScene->GetScale(dHScale, dVScale);
	//int iCanWidth = m_pSection->GetSectionLength() * dHScale;

	//if (iX < LEFT_MARGIN || iX > LEFT_MARGIN + iCanWidth)
	//	return false;

	//int iDataLen = m_pSection->GetTraces().size();
	//int iPos = 1. * iDataLen * (iX - LEFT_MARGIN) / iCanWidth;
	//if (iPos > iDataLen - 1)
	//	iPos = iDataLen - 1;
	//m_pSection->GetUTM().IJToXY(m_pSection->GetTraces()[iPos].x(), m_pSection->GetTraces()[iPos].y(), dX, dY);
	return true;
}

void GSItemPDG::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	QRectF sceneRect = scene()->sceneRect();
	QRect pdgRect = QRect(LEFT_MARGIN, TOP_MARGIN, sceneRect.width() - RIGHT_MARGIN - LEFT_MARGIN, sceneRect.height() - BOTTOM_MARGIN - TOP_MARGIN);
	setRect(sceneRect);

	GSPDGScene *pScene = (GSPDGScene *)scene();
	double dHScale, dVScale;
	pScene->GetScale(dHScale, dVScale);

	QVector<float>& vecPoints = m_pPDG->GetStressPoints();
	int i, j, k, iPos, iNumPoints = vecPoints.size() / 6;

	//	Strats on the left side.
	painter->save();

	QRect rect(60, TOP_MARGIN, 100, vecPoints[1] * dVScale);
	painter->drawRect(rect);
	painter->drawText(60, TOP_MARGIN, 100, vecPoints[1] * dVScale, Qt::AlignCenter, "Top");
					
	painter->setBrush(QBrush("black"));
	painter->drawEllipse(25, TOP_MARGIN - 15, 30, 30);
	painter->setPen("white");
	painter->drawText(25, TOP_MARGIN - 15, 30, 30, Qt::AlignCenter, "R");

	QList<QUuid> listHID = m_pPDG->GetHorizonsID();
	for (i = 0; i < iNumPoints - 1; i++)
	{
		CX3DHorizon *pHor = dynamic_cast<CX3DHorizon *>(GetObjectByID(listHID[i]));

		float fZ1 = vecPoints[6 * i + 1], fZ2 = vecPoints[6 * i + 7];
		QRect rect(60, TOP_MARGIN + fZ1 * dVScale, 100, (fZ2 - fZ1) * dVScale);
			
		const QColor color = pHor->GetColor();
		painter->setBrush(QBrush(color));
		painter->setPen("black");
		painter->drawRect(rect);
		painter->drawText(60, TOP_MARGIN + fZ1 * dVScale, 100, (fZ2 - fZ1) * dVScale, Qt::AlignCenter, pHor->GetParent()->GetObjectName());

		painter->setBrush(QBrush("black"));
		QString sPulse = GSCompressionPulse::GetOnePulse(pHor->GetPulse(), false);
		int iXPos = 25;
		if (i % 2 == 0)
			iXPos = 165;

		painter->drawEllipse(iXPos, TOP_MARGIN + fZ1 * dVScale - 15, 30, 30);
		painter->setPen("white");
		painter->drawText(iXPos, TOP_MARGIN + fZ1 * dVScale - 15, 30, 30, Qt::AlignCenter, sPulse);
	}

	painter->restore();

	//	Fill the background.
	painter->save();
	painter->setPen(Qt::NoPen);
	CXColormap* pColormap = CXColormap::GetColormap("stressmap");
	for (i = 0; i < iNumPoints - 1; i++)
	{
		QPolygon polygon;
		float fMag = vecPoints[6 * i + 4];
		float fZ1 = vecPoints[6 * i + 1], fZ2 = vecPoints[6 * i + 7];
		float fSV1 = vecPoints[6 * i + 3], fSV2 = vecPoints[6 * i + 9];
		if(fMag > 1)
		{
			fSV1 *= fMag;
			fSV2 *= fMag;
		}

		polygon << QPoint(LEFT_MARGIN, TOP_MARGIN + fZ1 * dVScale);
		polygon << QPoint(LEFT_MARGIN + fSV1 * dHScale, TOP_MARGIN + fZ1 * dVScale);
		polygon << QPoint(LEFT_MARGIN + fSV2 * dHScale, TOP_MARGIN + fZ2 * dVScale);
		polygon << QPoint(LEFT_MARGIN, TOP_MARGIN + fZ2 * dVScale);

		for (k = 6; k >= 0; k--)
		{
			if (fMag > gStressMagRange[k].m_fSHMagLower)
				break;
		}
		QColor color = pColormap->GetColorAt((unsigned char)k);

		painter->setBrush(QBrush(color));
		painter->drawPolygon(polygon);

	}
	painter->restore();

	//	PDG boarder and annotation.
	painter->drawRect(pdgRect);

	//	Left and right.
	for (iPos = 0; iPos <= vecPoints[vecPoints.size() - 5]; iPos += 100)
	{
		painter->drawLine(LEFT_MARGIN, TOP_MARGIN + iPos * dVScale, LEFT_MARGIN - 5, TOP_MARGIN + iPos * dVScale);
		painter->drawLine(LEFT_MARGIN + pdgRect.width(), TOP_MARGIN + iPos * dVScale, LEFT_MARGIN + pdgRect.width() + 5, TOP_MARGIN + iPos * dVScale);

		if (iPos % 500 == 0)
		{
			painter->drawLine(LEFT_MARGIN, TOP_MARGIN + iPos * dVScale, LEFT_MARGIN - 10, TOP_MARGIN + iPos * dVScale);
			painter->drawText(LEFT_MARGIN - 40, TOP_MARGIN + iPos * dVScale - 5, 25, 15, Qt::AlignRight, QString::number(iPos));

			painter->drawLine(LEFT_MARGIN + pdgRect.width(), TOP_MARGIN + iPos * dVScale, LEFT_MARGIN + pdgRect.width() + 10, TOP_MARGIN + iPos * dVScale);
			painter->drawText(LEFT_MARGIN + pdgRect.width() + 15, TOP_MARGIN + iPos * dVScale - 5, 25, 15, Qt::AlignLeft, QString::number(iPos));
		}
	}

	//	Top/bottom.
	int iVPos = pdgRect.height() + TOP_MARGIN;
	for (i = 0;; i += 10)
	{
		iPos = i * dHScale;
		if(iPos > pdgRect.width())
			break;

		painter->drawLine(LEFT_MARGIN + iPos, TOP_MARGIN, LEFT_MARGIN + iPos, TOP_MARGIN - 5);
		painter->drawLine(LEFT_MARGIN + iPos, iVPos, LEFT_MARGIN + iPos, iVPos + 5);

		if (i % 50 == 0)
		{
			painter->drawLine(LEFT_MARGIN + iPos, TOP_MARGIN, LEFT_MARGIN + iPos, TOP_MARGIN - 10);
			painter->drawText(LEFT_MARGIN + iPos - 10, TOP_MARGIN - 30, 20, 15, Qt::AlignCenter, QString::number(i));

			painter->drawLine(LEFT_MARGIN + iPos, iVPos, LEFT_MARGIN + iPos, iVPos + 10);
			painter->drawText(LEFT_MARGIN + iPos - 10, iVPos + 15, 20, 15, Qt::AlignCenter, QString::number(i));
		}
	}

	//	Four lines: Sv, SH, Sh and Pp.
	QPainterPath SvPath, SHPath, ShPath, PpPath;
	SvPath.moveTo(LEFT_MARGIN, TOP_MARGIN);
	PpPath.moveTo(LEFT_MARGIN, TOP_MARGIN);
	ShPath.moveTo(LEFT_MARGIN, TOP_MARGIN);
	SvPath.lineTo(LEFT_MARGIN + vecPoints[3] * dHScale, TOP_MARGIN + vecPoints[1] * dVScale);
	PpPath.lineTo(LEFT_MARGIN + vecPoints[2] * dHScale, TOP_MARGIN + vecPoints[1] * dVScale);
	ShPath.lineTo(LEFT_MARGIN + vecPoints[3] * vecPoints[5] * dHScale, TOP_MARGIN + vecPoints[1] * dVScale);
	SHPath.moveTo(LEFT_MARGIN + vecPoints[3] * vecPoints[4] * dHScale, TOP_MARGIN + vecPoints[1] * dVScale);
	for (i = 1; i < iNumPoints; i++)
	{
		ShPath.lineTo(LEFT_MARGIN + vecPoints[6 * i + 3] * vecPoints[6 * i - 1] * dHScale, TOP_MARGIN + vecPoints[6 * i + 1] * dVScale);
		ShPath.lineTo(LEFT_MARGIN + vecPoints[6 * i + 3] * vecPoints[6 * i + 5] * dHScale, TOP_MARGIN + vecPoints[6 * i + 1] * dVScale);
		SHPath.lineTo(LEFT_MARGIN + vecPoints[6 * i + 3] * vecPoints[6 * i - 2] * dHScale, TOP_MARGIN + vecPoints[6 * i + 1] * dVScale);
		SHPath.lineTo(LEFT_MARGIN + vecPoints[6 * i + 3] * vecPoints[6 * i + 4] * dHScale, TOP_MARGIN + vecPoints[6 * i + 1] * dVScale);
		SvPath.lineTo(LEFT_MARGIN + vecPoints[6 * i + 3] * dHScale, TOP_MARGIN + vecPoints[6 * i + 1] * dVScale);
		PpPath.lineTo(LEFT_MARGIN + vecPoints[6 * i + 2] * dHScale, TOP_MARGIN + vecPoints[6 * i + 1] * dVScale);
	}

	painter->drawPath(SHPath);
	painter->drawText(LEFT_MARGIN + vecPoints[vecPoints.size() - 2] * vecPoints[vecPoints.size() - 3] * dHScale - 20, 
					  TOP_MARGIN + pdgRect.height() + 5, 40, 15, Qt::AlignCenter, "SH/Sv");

	painter->setPen(QPen("blue"));
	painter->drawPath(PpPath);
	painter->drawText(LEFT_MARGIN + vecPoints[vecPoints.size() - 4] * dHScale - 20, 
					  TOP_MARGIN + pdgRect.height() + 5, 40, 15, Qt::AlignCenter, "Pp");

	painter->setPen(QPen("red"));
	painter->drawPath(ShPath);
	painter->drawText(LEFT_MARGIN + vecPoints[vecPoints.size() - 1] * vecPoints[vecPoints.size() - 3] * dHScale - 20, 
					  TOP_MARGIN + pdgRect.height() + 5, 40, 15, Qt::AlignCenter, "Sh/Sv");

	painter->setPen(QPen("green"));
	painter->drawPath(SvPath);
	painter->drawText(LEFT_MARGIN + vecPoints[vecPoints.size() - 3] * dHScale - 20, 
					  TOP_MARGIN + pdgRect.height() + 5, 40, 15, Qt::AlignCenter, "Sv");

	//	Title.
	painter->setPen(QPen("balck"));
	QFont font = painter->font();
	font.setPixelSize(30);
	painter->setFont(font);
	painter->drawText(60, 10, 100, 50, Qt::AlignCenter, m_pPDG->GetObjectName());

	font.setPixelSize(15);
	painter->setFont(font);
	painter->drawText(LEFT_MARGIN, 10, pdgRect.width(), 50, Qt::AlignCenter, "Pressure (MPa)");

	QPolygonF polygon = m_pPDG->GetTrajectoryPoints();
	QString sPos = "(" + QString::number(polygon[0].x(), 'f', 0) + ", " + QString::number(polygon[0].y(), 'f', 0) + ")";
	painter->drawText(60, TOP_MARGIN + pdgRect.height() + 15, 200, 50, Qt::AlignLeft, sPos);
}