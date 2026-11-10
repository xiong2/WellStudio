#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "gsitemfrg.h"
#include "gsfrg.h"
#include "gspdgscene.h"
#include "x3dhorizon.h"
#include "xseismicutmtool.h"
#include "gssectionviewinfo.h"
#include "xcolormap.h"
#include "gscompressionpulse.h"
#include "xglobal.h"
#include "xproject.h"
#include "gsdef.h"

#define FRG_GOUGE_LOW  65		/* Value for low percentage addition. */
#define FRG_GOUGE_HIGH 80		/* Value for low percentage addition. */
#define FRG_GOUGE_LOWPCT 0.25	/* Percentage to add for low. */
#define FRG_GOUGE_HIGHPCT 0.50	/* Percentage to add for high. */

GSItemFRG::GSItemFRG(GSFRG *pPDG, CXViewInfoObject *pViewInfo, QGraphicsItem *parent) : GSObjItem(pViewInfo, parent)
{
	m_pFRG = pPDG;
}

bool GSItemFRG::SceneXToXY(int iX, double& dX, double& dY)
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

void GSItemFRG::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	QRectF sceneRect = scene()->sceneRect();
	QRect pdgRect = QRect(LEFT_MARGIN, TOP_MARGIN, sceneRect.width() - RIGHT_MARGIN - LEFT_MARGIN, sceneRect.height() - BOTTOM_MARGIN - TOP_MARGIN);
	setRect(sceneRect);

	GSPDGScene *pScene = (GSPDGScene *)scene();
	double dHScale, dVScale;
	pScene->GetScale(dHScale, dVScale);

	QVector<float>& vecDepth = m_pFRG->GetVecData(0);
	int i, j, k, iPos, iNumPoints = vecDepth.size();

	//	Background.
	painter->save();

	CXColormap* pColormap = CXColormap::GetColormap("stressmap");
	
	painter->setPen(Qt::NoPen);
	int iWidth = pdgRect.width();
	QRect aRect = pdgRect;
	aRect.setWidth(iWidth * 0.13 + 0.5);
	painter->setBrush(QBrush(pColormap->GetColorAt(0)));
	painter->drawRect(aRect);

	aRect.moveLeft(pdgRect.x() + iWidth * 0.13);
	aRect.setWidth(iWidth * 0.16 + 0.5);
	painter->setBrush(QBrush(pColormap->GetColorAt(3)));
	painter->drawRect(aRect);

	aRect.moveLeft(pdgRect.x() + iWidth * 0.29);
	aRect.setWidth(iWidth * 0.21 + 0.5);
	painter->setBrush(QBrush(pColormap->GetColorAt(4)));
	painter->drawRect(aRect);

	aRect.moveLeft(pdgRect.x() + iWidth * 0.50);
	aRect.setWidth(iWidth * 0.3 + 0.5);
	painter->setBrush(QBrush(pColormap->GetColorAt(5)));
	painter->drawRect(aRect);

	aRect.moveLeft(pdgRect.x() + iWidth * 0.8);
	aRect.setWidth(iWidth * 0.20);
	painter->setBrush(QBrush(pColormap->GetColorAt(6)));
	painter->drawRect(aRect);
		
	painter->setBrush(Qt::NoBrush);
	painter->setPen("black");
	painter->drawRect(pdgRect);

	//	Top annotation.
	for (i = 0; i <= 10; i++)
	{		
		iPos = i * pdgRect.width() / 10;
		painter->drawLine(LEFT_MARGIN + iPos, TOP_MARGIN, LEFT_MARGIN + iPos, TOP_MARGIN - 10);
		painter->drawText(LEFT_MARGIN + iPos - 10, TOP_MARGIN - 30, 20, 15, Qt::AlignCenter, QString::number(i * 10));
	}

	//	Left and right annotation.
	for (iPos = 0; iPos <= vecDepth.last(); iPos += 100)
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

	painter->restore();

	//	Strats on the left side.
	painter->save();

	QRect rect(60, TOP_MARGIN, 100, vecDepth[0] * dVScale);
	painter->drawRect(rect);
	painter->drawText(60, TOP_MARGIN, 100, vecDepth[0] * dVScale, Qt::AlignCenter, "Top");
					
	painter->setBrush(QBrush("black"));
	painter->drawEllipse(25, TOP_MARGIN - 15, 30, 30);
	painter->setPen("white");
	painter->drawText(25, TOP_MARGIN - 15, 30, 30, Qt::AlignCenter, "R");

	QList<CXObject*> listSurvey = GetProject()->GetChildren(EX3DSurvey);
	QList<CXObject *> listH = listSurvey[0]->GetChildren(EXGS3DHorizonDepth, true);

	for (i = 0; i < iNumPoints - 1; i++)
	{
		CX3DHorizon *pHor = dynamic_cast<CX3DHorizon *>(listH[i]);

		float fZ1 = vecDepth[i], fZ2 = vecDepth[i+1];
		QRect rect(60, TOP_MARGIN + fZ1 * dVScale, 100, (fZ2 - fZ1) * dVScale);
			
		const QColor color = pHor->GetColor();
		painter->setBrush(QBrush(color));
		painter->setPen("black");
		painter->drawRect(rect);
		painter->drawText(60, TOP_MARGIN + fZ1 * dVScale, 100, (fZ2 - fZ1) * dVScale, Qt::AlignCenter, pHor->GetParent()->GetObjectName());

		//	The horizontal line across the graph.
		painter->drawLine(pdgRect.x(), TOP_MARGIN + fZ1 * dVScale, pdgRect.x() + pdgRect.width(), TOP_MARGIN + fZ1 * dVScale);

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

	//	AV & DE & RP
    painter->setRenderHint(QPainter::Antialiasing);
	QVector<float>& vecAV = m_pFRG->GetVecData(3);
	QVector<float>& vecDE = m_pFRG->GetVecData(2);
	QVector<float>& vecRP = m_pFRG->GetVecData(1);
	float  preAVX = g_dInvalidData, preDEX, preRPX;
	QPainterPath avPath, dePath, rpPath;
	for (i = 0; i < iNumPoints; i++)
	{
		if (vecAV[i] == g_dInvalidData)
		{
			if(preAVX == g_dInvalidData)
				continue;

			avPath.lineTo(LEFT_MARGIN + preAVX * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
			dePath.lineTo(LEFT_MARGIN + preDEX * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
			rpPath.lineTo(LEFT_MARGIN + preRPX * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
		}
		else
		{
			if (preAVX == g_dInvalidData)
			{
				avPath.moveTo(LEFT_MARGIN + vecAV[i] * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
				dePath.moveTo(LEFT_MARGIN + vecDE[i] * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
				rpPath.moveTo(LEFT_MARGIN + vecRP[i] * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
			}
			else
			{
				avPath.lineTo(LEFT_MARGIN + vecAV[i] * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
				dePath.lineTo(LEFT_MARGIN + vecDE[i] * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
				rpPath.lineTo(LEFT_MARGIN + vecRP[i] * iWidth / 100, TOP_MARGIN + vecDepth[i] * dVScale);
			}
			preAVX = vecAV[i];
			preDEX = vecDE[i];
			preRPX = vecRP[i];
		}
	}

	painter->setPen(QPen(QColor("green"), 2));
	painter->drawPath(avPath);
	painter->setPen(QPen(QColor("black"), 2));
	painter->drawPath(dePath);

	QPen pen(QColor("red"), 2);
	painter->setPen(pen);
	painter->drawPath(rpPath);

	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);
	int iLast = 0;
	while (iLast < iNumPoints)
	{
		float pct, gx;
		bool bBeyond = false, bNewLine = false;
		QPointF p(g_dInvalidData, g_dInvalidData);			
		QPainterPath path;

		for (i = iLast; i < iNumPoints; i++)
		{
			QPointF c(vecRP[i], vecDepth[i]);
			if(c.x() == g_dInvalidData)
				c.setX(p.x());

			if (p.x() != g_dInvalidData)
			{
				if (!bBeyond)
				{
					if (p.x() >= FRG_GOUGE_LOW)
					{
						bBeyond = true;
						gx = p.x();
						iLast = i;

						if(p.x() >= FRG_GOUGE_HIGH)
							pct = FRG_GOUGE_HIGHPCT;
						else
							pct = FRG_GOUGE_LOWPCT;

						path.moveTo(LEFT_MARGIN + p.x() * iWidth / 100, TOP_MARGIN + p.y() * dVScale);
					}
				}

				if (bBeyond)
				{
					c.setX(c.x() + qAbs(gx - c.x()) * pct);
					if(c.x() > 100)
						c.setX(100);

					path.lineTo(LEFT_MARGIN + c.x() * iWidth / 100, TOP_MARGIN + c.y() * dVScale);
				}
			}
			if(c.x() != g_dInvalidData)
				p.setX(c.x());
			p.setY(c.y());
		}

		painter->drawPath(path);

		if(!bBeyond)
			break;
	}

	painter->restore();

	//	Title.
	painter->setPen(QPen("balck"));
	QFont font = painter->font();
	font.setPixelSize(20);
	painter->setFont(font);
	painter->drawText(LEFT_MARGIN +  iWidth / 2 - 200, 10, 400, 50, Qt::AlignCenter, "Fault Seal Confidence (%)");
}