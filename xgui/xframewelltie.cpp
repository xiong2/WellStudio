#include <qpainter.h>
#include <qscrollarea.h>
#include <QMouseEvent>
#include "xframewelltie.h"
#include "xtemplate.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xwellcurve.h"
#include "xwelltd.h"
#include "xseismicdatavolume.h"
#include "xdlgwelltie.h"
#include "xgraphicsapi.h"

CXFrameWellTie::CXFrameWellTie(CXWell *pWell, CXDlgWellTie *pDlg, QWidget *parent) : m_pWell(pWell), m_pDlg(pDlg), QFrame(parent)
{
	setMouseTracking(true);
}

CXFrameWellTie::~CXFrameWellTie()
{
}

int CXFrameWellTie::GetTrackPos(EXTrack eType)
{
	int iPos = TMARGIN;

	//	A loop from AC (1) to Drift (16)
	for (int i = 1; i <= 16; i *= 2)
	{
		if (eType == i)
			return iPos;

		if (m_sLayout.m_iShowTracks & i)
			iPos += (TWIDTH + TMARGIN);
	}

	if (eType == eSyn)
		return iPos;
	iPos += (50 + TMARGIN);

	if (eType == eNTrace)
		return iPos;
	iPos += (50 + TMARGIN);

	return iPos;
}

int CXFrameWellTie::GetCanvasWidth()
{
	int iWidth = GetTrackPos(eNSec);
	iWidth += (10 * m_sLayout.m_iNumTraces + TMARGIN);
	return iWidth;
}

void CXFrameWellTie::Populate(CXObject *pDV, CXWellCurve *pAC, CXWellCurve *pDen, CXWellCurve *pRC, float *pSyn, double dSTime, double dStep, unsigned int iNum)
{
	m_pDV = (CXSeismicDataVolume *)pDV;

	int iInline, iXline, iSXline, iEXline, i, j;
	double dX, dY, dZS, dZE, dZStep;
	int iNumSample = m_pDV->GetSamplingQty();
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);
	m_iDTSTime = ((int)dZS / 100 + 1) * 100;

	//	Read seismic data.
	CXSeismicUTMTool utm = m_pDV->GetUTM();
	m_pWell->GetWellPosition(dX, dY);
	utm.XYToIJ(dX, dY, i, j);
	utm.XYToLine(dX, dY, iInline, iXline);
	int iNumTrace = (m_sLayout.m_iNumTraces - 1) / 2;
	int iJS = j >= iNumTrace ? j - iNumTrace : 0;
	int iJE = j < utm.GetNJ() - iNumTrace ? j + iNumTrace : utm.GetNJ() - 1;
	iNumTrace = iJE - iJS + 1;
	utm.IJToLine(i, iJS, iInline, iSXline);
	utm.IJToLine(i, iJE, iInline, iEXline);
	float *pSeisData = new float[iNumTrace * iNumSample];
	m_pDV->ReadInline(iInline, iSXline, iEXline, dZS, dZE, pSeisData);

	//	Resize the frame.
	int iHeight = (int)(m_fVScale * (dZE - dZS));
	setFixedHeight(iHeight);
	m_pDlg->SetCanvasSize(iHeight);
	int iWidth = GetCanvasWidth();
	setFixedWidth(iWidth);
	m_pDlg->SetCanvasSize(iWidth, false);

	int iX;
	m_SynPoly.clear();
	m_vecSynPolygon.clear();
	if (pSyn)
	{
		iX = GetTrackPos(eSyn);
		m_SynPoly = calATrace(iX, pSyn, iNum, m_vecSynPolygon, dSTime, dStep);

		qreal y1 = m_fVScale * (dSTime - dZS);
		qreal height = m_fVScale * (iNum - 1) * dStep;

		if (m_iSSynTime == -999)
		{
			m_iSSynTime = (int)dSTime;
			m_iESynTime = m_iSSynTime + (int)(iNum - 1) * dStep;
		}
		SetCorRect();

		m_iDTETime = ((int)(dSTime + (iNum - 1) * dStep) / 100 + 1) * 100;
	}

	m_vecWTPolygon.clear();
	iX = GetTrackPos(eNTrace);
	m_WTPoly = calATrace(iX, pSeisData + (j - iJS) * iNumSample, iNumSample, m_vecWTPolygon);

	m_vecSecPoly.clear();
	m_vecSecPolygon.clear();
	iX = GetTrackPos(eNSec);
	for (i = 0; i < iNumTrace; i++)
	{
		if (i == j - iJS)
			continue;

		m_vecSecPoly << calATrace(iX + i * 10, pSeisData + i * iNumSample, iNumSample, m_vecSecPolygon);
	}

	delete[]pSeisData;

	calCurvePath(pAC, m_acPath, GetTrackPos(eAC));
	calCurvePath(pDen, m_denPath, GetTrackPos(eDen));
	calCurvePath(pRC, m_rcPath, GetTrackPos(eRC));
}

void CXFrameWellTie::RefreshLayout()
{
	int i, x, iDelta;
	if (m_sLayout.m_iShowTracks & eDen)
	{
		x = GetTrackPos(eDen);
		QRectF rect = m_denPath.boundingRect();
		iDelta = qRound(x - rect.x());
		iDelta /= 130;
		iDelta *= 130;
		m_denPath.translate(iDelta, 0);
	}

	if (m_sLayout.m_iShowTracks & eRC)
	{
		x = GetTrackPos(eRC);
		QRectF rect = m_rcPath.boundingRect();
		iDelta = qRound(x - rect.x());
		iDelta /= 130;
		iDelta *= 130;
		m_rcPath.translate(iDelta, 0);
	}

	if (m_sLayout.m_iShowTracks & eTD)
	{
		x = GetTrackPos(eTD);
		iDelta = qRound(x - m_dtI.x1());
		iDelta /= 130;
		iDelta *= 130;
		m_dtI.translate(iDelta, 0);
	}

	x = GetTrackPos(eNTrace);
	qreal rx = m_WTPoly.first().x();
	iDelta = qRound(x - rx);
	iDelta /= 130;
	iDelta *= 130;
	m_WTPoly.translate(iDelta, 0);
	for (i = 0; i < m_vecWTPolygon.size(); i++)
		m_vecWTPolygon[i].translate(iDelta, 0);

	for (i = 0; i < m_vecSecPoly.size(); i++)
		m_vecSecPoly[i].translate(iDelta, 0);
	for (i = 0; i < m_vecSecPolygon.size(); i++)
		m_vecSecPolygon[i].translate(iDelta, 0);

	if (!m_SynPoly.isEmpty())
	{
		m_SynPoly.translate(iDelta, 0);
		for(int i = 0; i < m_vecSynPolygon.size(); i++)
			m_vecSynPolygon[i].translate(iDelta, 0);
	}

	if (!m_recCorr.isEmpty())
		m_recCorr.translate(iDelta, 0);

	for (i = 0; i < m_vecSynLines.size(); i++)
		m_vecSynLines[i].translate(iDelta, 0);
	for (i = 0; i < m_vecWTLines.size(); i++)
		m_vecWTLines[i].translate(iDelta, 0);

	int iWidth = GetCanvasWidth();
	setFixedWidth(iWidth);
	m_pDlg->SetCanvasSize(iWidth, false);

	update();
}

void CXFrameWellTie::SetCorRect(int iSTime, int iETime)
{
	if (iSTime != -999)
	{
		m_iSSynTime = iSTime;
		m_iESynTime = iETime;
	}

	double dZS, dZE, dZStep;
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);
	int iX = GetTrackPos(eSyn);
	int height = (m_iESynTime - m_iSSynTime) * m_fVScale;
	m_recCorr = QRectF(iX - 5, m_fVScale * (m_iSSynTime - dZS), 135, height);

	update();
}

void CXFrameWellTie::calCurvePath(double *pData, int iNum, double dSTime, double dStep, QPainterPath& path, qreal x)
{
	double dZS, dZE, dZStep, dMax = qAbs(pData[0]);
	int i;
	for (i = 1; i < iNum; i++)
		dMax = dMax > qAbs(pData[i]) ? dMax : qAbs(pData[i]);

	m_pDV->GetSamplingRange(dZS, dZE, dZStep);

	path.clear();
	for (i = 0; i < iNum; i++)
	{
		path.moveTo(x, m_fVScale * (dSTime + i * dStep - dZS));
		path.lineTo(x + 50 * pData[i] / dMax, m_fVScale * (dSTime + i * dStep - dZS));
	}
}

void CXFrameWellTie::calCurvePath(CXWellCurve *pCurve, QPainterPath& path, qreal x)
{
	CXWellTD *pTD = m_pDlg->GetWellTD();
	path.clear();

	if (!pCurve)
		return;

	double dMDS, dMDE, dZS, dZE, dZStep, dX, dY, dTVD, dTWT;
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);
	pCurve->GetDepthRange(dMDS, dMDE);
	dZStep = pCurve->GetStep();
	int i, iNum = pCurve->GetPointNumber();
	double *pData = pCurve->GetData();
	CXWellPath *pWellPath = m_pWell->GetWellPath();

	CXTemplate *pTemplate = CXTemplate::GetTemplate(pCurve->GetTemplateID());
	if (pTemplate->GetType() == "SONIC")
	{
		for (i = 0; i < iNum; i++)
		{
			//	To find the fist valid sample.
			if (pData[i] > 1.)
				break;
		}

		dTVD = pWellPath->Md2Tvd(dMDS + i * dZStep);
		dTWT = pTD->GetAValue(dTVD);

		dX = x + (1000000. / pData[i] - 1000.) / 60;
		dY = (dTWT - dZS) * m_fVScale;
		double dSY = dY > 100 ? dY - 100 : 0;

		path.moveTo(dX, dY);
		i++;

		for (; i < iNum; i++)
		{
			if (pData[i] <= 1.)
				continue;

			dTVD = pWellPath->Md2Tvd(dMDS + i * dZStep);
			dTWT = pTD->GetAValue(dTVD);

			dX = x + (1000000. / pData[i] - 1000.) / 60;
			dY = (dTWT - dZS) * m_fVScale;

			path.lineTo(dX, dY);
		}
	}
	else if (pTemplate->GetType() == "RHO")
	{
		double dDisMin, dDisMax;
		pTemplate->GetDisplayRange(dDisMin, dDisMax);
		double dHScale = 100 / (dDisMax - dDisMin);

		for (i = 0; i < iNum; i++)
		{
			//	To find the fist valid sample.
			if (pData[i] > 1.)
				break;
		}

		dTVD = pWellPath->Md2Tvd(dMDS + i * dZStep);
		dTWT = pTD->GetAValue(dTVD);

		dX = x + (pData[i] - dDisMin) * dHScale;
		dY = (dTWT - dZS) * m_fVScale;
		double dSY = dY > 100 ? dY - 100 : 0;

		path.moveTo(dX, dY);
		i++;

		for (; i < iNum; i++)
		{
			if (pData[i] <= 1.)
				continue;

			dTVD = pWellPath->Md2Tvd(dMDS + i * dZStep);
			dTWT = pTD->GetAValue(dTVD);

			dX = x + (pData[i] - dDisMin) * dHScale;
			dX = dX < x ? x : dX;
			dX = dX > x + 100 ? x + 100 : dX;
			dY = (dTWT - dZS) * m_fVScale;

			path.lineTo(dX, dY);
		}
	}
	else if (pTemplate->GetType() == "RC")
	{
		double dDisMin, dDisMax;
		pCurve->GetDataRange(dDisMin, dDisMax);
		dDisMax = qMax(qAbs(dDisMin), dDisMax);
		double dHScale = 50 / dDisMax;
		x += 50;

		for (i = 0; i < iNum; i++)
		{
			if (pData[i] == g_dInvalidData)
				continue;

			dTVD = pWellPath->Md2Tvd(dMDS + i * dZStep);
			dTWT = pTD->GetAValue(dTVD);

			dX = x + pData[i] * dHScale;
			dY = (dTWT - dZS) * m_fVScale;

			path.moveTo(x, dY);
			path.lineTo(dX, dY);
		}

		QPointF p1 = QPointF(GetTrackPos(eTD), (m_iDTSTime - dZS) * m_fVScale);
		dX = 100 * (dTWT - m_iDTSTime) / (m_iDTETime - m_iDTSTime) + p1.x();
		QPointF p2 = QPointF(dX, dY);
		m_dtI = QLineF(p1, p2);

		m_dtC.clear();
		m_dtC << p1 << p2;
	}
}

QPolygonF CXFrameWellTie::calATrace(qreal x, float *pData, int iNumSample, QVector<QPolygon>& vecPolygon, double dSTime, double dStep)
{
	int i;
	double dDMin, dDMax, dZS, dZE, dZStep;
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);

	if (dSTime == -999.25)
	{
		dSTime = dZS;
		dStep = dZStep;
		m_pDV->GetDataRange(dDMin, dDMax);
		dDMax = qMax(qAbs(dDMin), qAbs(dDMax));
	}
	else
	{
		dDMax = qAbs(pData[0]);
		for (i = 1; i < iNumSample; i++)
		{
			if (dDMax < qAbs(pData[i]))
				dDMax = qAbs(pData[i]);
		}
	}

	//	Wiggle.
	QPolygonF path;
	path << QPointF(x, m_fVScale * (dSTime - dZS));
	for (i = 1; i < iNumSample; i++)
	{
		path << QPointF(x + TRACEW * pData[i] / dDMax, m_fVScale * (dSTime + i * dStep - dZS));
	}

	//	Area.
	QPolygon polygon;
	if (pData[0] > 0.)
		polygon << QPoint(x, m_fVScale * (dSTime - dZS)) << QPoint(x + TRACEW * pData[0] / dDMax, m_fVScale * (dSTime - dZS));

	for (i = 1; i < iNumSample; i++)
	{
		if (pData[i] <= 0)
		{
			if (polygon.isEmpty())
				continue;

			polygon << QPoint(x, m_fVScale * (dSTime + dStep * i - dZS - 1));
			vecPolygon << polygon;
			polygon.clear();
		}
		else
		{
			if (polygon.isEmpty())
			{
				polygon << QPoint(x, m_fVScale * (dSTime + dStep * i - dZS - 1));
			}
			polygon << QPoint(x + TRACEW * pData[i] / dDMax, m_fVScale * (dSTime + dStep * i - dZS));
		}
	}

	if (!polygon.isEmpty())
	{
		polygon << QPoint(x, m_fVScale * (dSTime + dStep * i - dZS));
		vecPolygon << polygon;
	}

	return path;
}

void CXFrameWellTie::paintEvent(QPaintEvent *)
{
	if (!m_pDV)
		return;

	drawAnno();

	drawCurves();

	drawTraces();

	drawStretchLines();
}

void CXFrameWellTie::drawTraces()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	//	Synthetic traces.
	for (int i = 0; i < 50; i += 10)
	{
		painter.setPen("blue");
		QPolygonF path = m_SynPoly.translated(i, 0);
		painter.drawPolyline(path);
		painter.setBrush(QBrush(QColor("blue")));
		foreach(QPolygon polygon, m_vecSynPolygon)
		{
			QPolygon p = polygon.translated(i, 0);
			painter.drawPolygon(p);
		}
		painter.setBrush(QBrush());

		painter.setPen("red");
		path = m_WTPoly.translated(i, 0);
		painter.drawPolyline(path);
		painter.setBrush(QBrush(QColor("red")));
		foreach(QPolygon polygon, m_vecWTPolygon)
		{
			QPolygon p = polygon.translated(i, 0);
			painter.drawPolygon(p);
		}
		painter.setBrush(QBrush());
	}

	//	Nearby traces.
	QPolygonF path = m_WTPoly.translated(120, 0);
	painter.drawPolyline(path);
	painter.setBrush(QBrush(QColor("red")));
	foreach(QPolygon polygon, m_vecWTPolygon)
	{
		QPolygon p = polygon.translated(120, 0);
		painter.drawPolygon(p);
	}
	painter.setBrush(QBrush());

	//	Nearby section.
	painter.setPen("black");
	foreach(QPolygonF path, m_vecSecPoly)
	{
		painter.drawPolyline(path);
	}
	painter.setBrush(QBrush(QColor("black")));
	foreach(QPolygon polygon, m_vecSecPolygon)
	{
		painter.drawPolygon(polygon);
	}

	//	Correlation rectangle.
	if (!m_recCorr.isEmpty())
	{
		painter.setPen("green");
		painter.setBrush(QBrush(QColor(0, 255, 0, 30)));
		painter.drawRect(m_recCorr);
	}
}

void CXFrameWellTie::drawCurves()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	//	Draw curve.
	painter.setPen("blue");
	if(m_sLayout.m_iShowTracks & eAC)
		painter.drawPath(m_acPath);
	if (m_sLayout.m_iShowTracks & eDen)
		painter.drawPath(m_denPath);
	painter.setPen("red");
	if (m_sLayout.m_iShowTracks & eRC)
		painter.drawPath(m_rcPath);

	if (m_sLayout.m_iShowTracks & eTD)
	{
		painter.setPen("blue");
		painter.drawLine(m_dtI);
		painter.setPen("red");
		painter.drawPolyline(m_dtC);

		painter.setPen(QPen(Qt::red, 5));
		for (int i = 1; i < m_dtC.size() - 1; i++)
		{
			painter.drawPoint(m_dtC[i]);
		}
	}

	if ((m_sLayout.m_iShowTracks & eDrift) && !m_driLine.isEmpty())
	{
		painter.setPen("blue");
		std::vector<QPointF> vecIP = m_driLine.toStdVector();
		std::vector<QPointF> vecOP;
		CXGraphicsAPI::GetSplinePoints(vecOP, vecIP, false, 20, 80);
		QVector<QPointF> olines = QVector<QPointF>::fromStdVector(vecOP);
		painter.drawPolyline(olines);

		painter.setPen(QPen(Qt::blue, 5));
		for (int i = 1; i < m_driLine.size() - 1; i++)
		{
			painter.drawPoint(m_driLine[i]);
		}
	}
}

void CXFrameWellTie::drawStretchLines()
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::yellow, 3));
	painter.drawLines(m_vecSynLines);
	painter.drawLines(m_vecWTLines);
	for (int i = 0; i < m_vecWTLines.size(); i++)
	{
		painter.drawLine(m_vecSynLines[i].p2(), m_vecWTLines[i].p1());
	}

	if (m_iSta % 2 == 0)
	{
		QRectF rectS = m_SynPoly.boundingRect();
		rectS.setWidth(50);
		if (rectS.contains(m_pos))
			painter.drawLine(rectS.left(), m_pos.y(), rectS.right(), m_pos.y());
	}
	else
	{
		QRectF rectW = m_WTPoly.boundingRect();
		rectW.setWidth(50);
		if (rectW.contains(m_pos))
		{
			painter.drawLine(rectW.left(), m_pos.y(), rectW.right() + 5, m_pos.y());
			painter.drawLine(QPointF(rectW.left(), m_pos.y()), m_vecSynLines.last().p2());
		}
		else
			painter.drawLine(m_pos, m_vecSynLines.last().p2());
	}
}

void CXFrameWellTie::drawAnno()
{
	double dZS, dZE, dZStep;
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);

	QPainter painter(this);
	QRect rect = this->rect();
	painter.setPen("light grey");
	int i, j, iCurNum = 0;
	if (m_sLayout.m_iShowTracks & eAC)
		iCurNum++;
	if (m_sLayout.m_iShowTracks & eDen)
		iCurNum++;
	if (m_sLayout.m_iShowTracks & eRC)
		iCurNum++;
	if (m_sLayout.m_iShowTracks & eTD)
		iCurNum++;
	if (m_sLayout.m_iShowTracks & eDrift)
		iCurNum++;

	for (j = 0; j < iCurNum; j++)
	{
		for (i = 0; i <= 10; i++)
		{
			painter.drawLine(QPoint(TMARGIN + j * 130 + 10 * i, 0), QPoint(TMARGIN + j * 130 + 10 * i, rect.bottom()));
		}

		double dX, dY;
		m_pDV->GetSamplingRange(dZS, dZE, dZStep);
		int iS = ((int)(dZS / 100)) * 100;
		for (int iZ = iS; iZ < dZE; iZ += 100)
		{
			if (iZ <= dZS)
				continue;

			int y = (iZ - dZS) * m_fVScale;
			painter.drawLine(QPoint(TMARGIN + j * 130, y), QPoint(TMARGIN + j * 130 + 100, y));
		}
	}
}

void CXFrameWellTie::mouseMoveEvent(QMouseEvent *event)
{
	double dZS, dZE, dZStep;
	m_pDV->GetSamplingRange(dZS, dZE, dZStep);
	m_pos = event->pos();
	int y = m_pos.y();

	QString sMes = "  TWT is " + QString::number(y + dZS);

	CXWellTD *pTD = m_pDlg->GetWellTD();
	CXWellPath *pWellPath = m_pWell->GetWellPath();
	double dTVD = pTD->GetAValue(y + dZS, false);
	double dMD = pWellPath->Tvd2Md(dTVD);
	sMes = sMes + "ms, SSTVD is " + QString::number(dTVD) + "m, and MD is " + QString::number(dMD) + "m";
	m_pDlg->ShowMessage(sMes);

	update();
}

void CXFrameWellTie::mousePressEvent(QMouseEvent *event)
{
	if (m_SynPoly.isEmpty())
		return;

	if (event->button() == Qt::MiddleButton && m_iSta > 0)
	{
		if (m_iSta % 2 == 0)
			m_vecWTLines.removeLast();
		else
			m_vecSynLines.removeLast();

		m_iSta--;

		if (m_iSta == 0)
			m_pDlg->UpdateButtons(0);

		update();
		return;
	}

	QRectF rectS = m_SynPoly.boundingRect();
	QRectF rectW = m_WTPoly.boundingRect();
	rectS.setWidth(50);
	rectW.setWidth(50);
	if (!rectS.contains(event->pos()) && !rectW.contains(event->pos()))
		return;

	if (m_iSta % 2 == 0 && rectS.contains(event->pos()))
	{
		int y = snap(event->y());
		int iX = GetTrackPos(eSyn) - 5;
		QLineF line(iX, y, iX + 50, y);
		m_vecSynLines << line;

		m_iSta++;
		m_pDlg->UpdateButtons(4);
	}
	else if (m_iSta % 2 == 1 && rectW.contains(event->pos()))
	{
		int y = snap(event->y(), false);
		int iX = GetTrackPos(eNTrace) - 5;
		QLineF line(iX, y, iX + 50, y);
		m_vecWTLines << line;

		m_iSta++;
		m_pDlg->UpdateButtons(5);
		updateDTLines();
	}

	update();
}

int CXFrameWellTie::snap(int y, bool bSyn)
{
	int i, iVal, iSnap = m_sLayout.m_iSnap;
	if (iSnap == 3)
		return y;	//	No snap.

	int i1, i2;
	qreal dV1, dV2;
	findKP(y, bSyn, i1, dV1, i2, dV2);

	if (iSnap == 0)
	{
		//	Nearby Peak or trough
		if (bSyn)
		{
			if (qAbs(i1 - y) < qAbs(i2 - y))
			{
				m_bPeak = dV1 > dV2;
				return i1;
			}
			else
			{
				m_bPeak = dV1 < dV2;
				return i2;
			}
		}
		else
		{
			if (m_bPeak)
				return dV1 > dV2 ? i1 : i2;
			else
				return dV1 > dV2 ? i2 : i1;
		}
	}
	else if (iSnap == 1)
	{
		//	Nearby Peak
		return dV1 > dV2 ? i1 : i2;
	}
	else
	{
		//	Nearby Trough
		return dV1 > dV2 ? i2 : i1;
	}
}

void CXFrameWellTie::findKP(int y, bool bSyn, int& i1, qreal& dV1, int& i2, qreal& dV2)
{
	QPolygonF poly = m_WTPoly;
	if (bSyn)
		poly = m_SynPoly;

	qreal dVal;
	int i, iC, iNum = poly.size();
	for (i = 0; i < iNum; i++)
		if (poly[i].y() > y)
		{
			dVal = poly[i].x();
			iC = i;
			break;
		}

	if (iC > 0)
	{
		bool bP = dVal < poly[i - 1].x();
		while (i > 0)
		{
			if (bP != poly[i].x() < poly[i - 1].x())
				break;
			i--;
		}

		i1 = poly[i].y();
		dV1 = poly[i].x();
	}

	if (iC < iNum - 1)
	{
		i = iC;
		bool bP = dVal < poly[i + 1].x();
		while (i < iNum - 1)
		{
			if (bP != poly[i].x() < poly[i + 1].x())
				break;
			i++;
		}

		i2 = poly[i].y();
		dV2 = poly[i].x();
	}

	if ((dVal - dV1) * (dVal - dV2) > 0)
	{
		//	Means input point itself is a peak or trough.
		if (y - i1 > i2 - y)
		{
			i1 = y;
			dV1 = dVal;
		}
		else
		{
			i2 = y;
			dV2 = dVal;
		}
	}
}

void CXFrameWellTie::Interact(int iSta)
{
	if (iSta == 0 || iSta == 2 || iSta == 3 || iSta == 6 || iSta == 7)
	{
		//	Reset or clear all or stretched or undo or redo.
		m_vecSynLines.clear();
		m_vecWTLines.clear();
		m_iSta = 0;

		m_pDlg->UpdateButtons(iSta);
	}
	else if (iSta == 1)
	{
		//	Clear last pick.
		if (m_iSta == 0)
			return;

		if (m_iSta % 2 == 0)
			m_vecWTLines.removeLast();
		else
			m_vecSynLines.removeLast();

		m_iSta--;

		if (m_iSta % 2 == 0)
			m_pDlg->UpdateButtons(5);
		else
			m_pDlg->UpdateButtons(4);
	}

	updateDTLines();
	update();
}

void CXFrameWellTie::updateDTLines()
{
	if (m_iSta % 2 != 0)
		return;

	int iNum = m_iSta / 2;
	if (iNum == 0)
	{
		m_dtC.clear();
		m_dtC << m_dtI.p1() << m_dtI.p2();
		m_driLine.clear();
	}
	else if (iNum == 1)
	{
		qreal dY = m_fVScale * (m_vecWTLines[0].y1() - m_vecSynLines[0].y1());
		dY = 100 * dY / (m_iDTETime - m_iDTSTime);
		m_dtC.translate(dY, 0);
		m_driLine.clear();
	}
	else
	{
		m_dtC.clear();
		qreal dDelta = m_fVScale * (m_vecWTLines[0].y1() - m_vecSynLines[0].y1());
		dDelta = 100 * dDelta / (m_iDTETime - m_iDTSTime);
		m_dtC << QPointF(m_dtI.x1() + dDelta, m_dtI.y1());

		QVector<qreal> vecDelta;
		qreal dMax = -99999., dMin = 99999.;
		for (int i = 0; i < iNum; i++)
		{
			qreal dY = m_vecSynLines[i].y1();
			qreal dX = m_dtI.x1() + m_dtI.dx() * (dY - m_dtI.y1()) / m_dtI.dy();
			dDelta = m_fVScale * (m_vecWTLines[i].y1() - m_vecSynLines[i].y1());
			vecDelta << dDelta;
			dMax = dMax > dDelta ? dMax : dDelta;
			dMin = dMin < dDelta ? dMin : dDelta;
			dDelta = 100 * dDelta / (m_iDTETime - m_iDTSTime);
			m_dtC << QPointF(dX + dDelta, dY);
		}
		m_dtC << QPointF(m_dtI.x2() + dDelta, m_dtI.y2());

		dDelta = dMax - dMin;
		m_driLine.clear();
		int x0 = GetTrackPos(eDrift);
		qreal dX = x0 + (vecDelta[0] - dMin) * 100 / dDelta;
		qreal dY = m_dtI.y1();
		m_driLine << QPointF(dX, dY);
		for (int i = 0; i < iNum; i++)
		{
			dX = x0 + (vecDelta[i] - dMin) * 100 / dDelta;
			dY = m_dtC[i + 1].y();
			m_driLine << QPointF(dX, dY);
		}
		m_driLine << QPointF(dX, m_dtI.y2());
	}
}

QPolygonF CXFrameWellTie::GetStretchPairs()
{
	QPolygonF polyStr;
	if (m_iSta > 0 && m_iSta % 2 == 0)
	{
		for (int i = 0; i < m_vecSynLines.size(); i++)
			polyStr << QPointF(m_vecSynLines[i].y1(), m_vecWTLines[i].y1());
	}

	return polyStr;
}