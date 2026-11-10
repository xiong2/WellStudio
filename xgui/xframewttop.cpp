#include <qpainter.h>
#include "xframewttop.h"
#include "xwavelet.h"
#include "xdlgwelltie.h"
#include "xframewelltie.h"

CXFrameWTTop::CXFrameWTTop(CXFrameWellTie *pFrame, QWidget *parent) : QFrame(parent), m_pWTFrame(pFrame)
{
}

CXFrameWTTop::~CXFrameWTTop()
{
}

void CXFrameWTTop::Populate(QString sDVName, QString sACName, QString sDenName, CXWavelet* pWavelet, double dSTime, double dETime)
{
	m_sDVName = sDVName;
	m_sACName = sACName;
	m_sDenName = sDenName;

	m_pWavelet = pWavelet;

	m_iSTime = ((int)dSTime / 100 + 1) * 100;
	m_iETime = ((int)dETime / 100 + 1) * 100;

	setFixedWidth(m_pWTFrame->GetCanvasWidth());
}

void CXFrameWTTop::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setPen("black");
	QFont font = painter.font();
	font.setPixelSize(10);
	painter.setFont(font);

	QRect rect = this->rect();

	//	AC Header.
	if (m_pWTFrame->GetSLayout().m_iShowTracks & eAC)
	{
		int iPos = m_pWTFrame->GetTrackPos(eAC);
		painter.drawText(iPos, rect.bottom() - 45, 100, 20, Qt::AlignCenter, m_sACName + " (m/s)");
		painter.drawText(iPos, rect.bottom() - 25, 70, 20, Qt::AlignLeft, "1000");
		painter.drawText(iPos + 30, rect.bottom() - 25, 70, 20, Qt::AlignRight, "7000");

		painter.setPen("black");
		QRect acRect(iPos, rect.bottom() - 50, 100, 50);
		painter.drawRect(acRect);
		painter.setPen("blue");
		painter.drawLine(QPoint(acRect.left(), rect.bottom() - 5), QPoint(acRect.right(), rect.bottom() - 5));
	}

	//	DEN Header.
	if (m_pWTFrame->GetSLayout().m_iShowTracks & eDen)
	{
		int iPos = m_pWTFrame->GetTrackPos(eDen);
		painter.setPen("black");
		painter.drawText(iPos, rect.bottom() - 45, 100, 20, Qt::AlignCenter, m_sDenName + " (KG/m^3)");
		painter.drawText(iPos, rect.bottom() - 25, 70, 20, Qt::AlignLeft, "2000");
		painter.drawText(iPos + 20, rect.bottom() - 25, 70, 20, Qt::AlignRight, "3000");

		QRect acRect(iPos, rect.bottom() - 50, 100, 50);
		painter.drawRect(acRect);
		painter.setPen("blue");
		painter.drawLine(QPoint(acRect.left(), rect.bottom() - 5), QPoint(acRect.right(), rect.bottom() - 5));
	}

	//	RC Header.
	if (m_pWTFrame->GetSLayout().m_iShowTracks & eRC)
	{
		int iPos = m_pWTFrame->GetTrackPos(eRC);
		painter.setPen("black");
		painter.drawText(iPos, rect.bottom() - 45, 100, 20, Qt::AlignCenter, "RC");

		QRect acRect(iPos, rect.bottom() - 50, 100, 50);
		painter.drawRect(acRect);
		painter.setPen("red");
		painter.drawLine(QPoint(acRect.left(), rect.bottom() - 5), QPoint(acRect.right(), rect.bottom() - 5));
	}

	//	DT Header.
	if (m_pWTFrame->GetSLayout().m_iShowTracks & eTD)
	{
		int iPos = m_pWTFrame->GetTrackPos(eTD);
		painter.setPen("black");
		QRect acRect(iPos, rect.bottom() - 90, 100, 90);
		painter.drawRect(acRect);
		painter.drawText(iPos, rect.bottom() - 85, 100, 20, Qt::AlignCenter, "Corrected Time (ms)");
		painter.drawText(iPos, rect.bottom() - 65, 70, 20, Qt::AlignLeft, QString::number(m_iSTime));
		painter.drawText(iPos + 20, rect.bottom() - 65, 70, 20, Qt::AlignRight, QString::number(m_iETime));
		painter.drawText(iPos, rect.bottom() - 45, 100, 20, Qt::AlignCenter, "Input Time (ms)");
		painter.drawText(iPos, rect.bottom() - 25, 70, 20, Qt::AlignLeft, QString::number(m_iSTime));
		painter.drawText(iPos + 20, rect.bottom() - 25, 70, 20, Qt::AlignRight, QString::number(m_iETime));

		painter.setPen("blue");
		painter.drawLine(QPoint(acRect.left(), rect.bottom() - 5), QPoint(acRect.right(), rect.bottom() - 5));
		painter.setPen("red");
		painter.drawLine(QPoint(acRect.left(), rect.bottom() - 45), QPoint(acRect.right(), rect.bottom() - 45));
	}

	//	Drift Header.
	if (m_pWTFrame->GetSLayout().m_iShowTracks & eDrift)
	{
		int iPos = m_pWTFrame->GetTrackPos(eDrift);
		painter.setPen("black");
		painter.drawText(iPos, rect.bottom() - 45, 100, 20, Qt::AlignCenter, "Drift Curve (ms)");

		QRect acRect(iPos, rect.bottom() - 50, 100, 50);
		painter.drawRect(acRect);
		painter.setPen("blue");
		painter.drawLine(QPoint(acRect.left(), rect.bottom() - 5), QPoint(acRect.right(), rect.bottom() - 5));
	}

	//	Nearby traces.
	int iPos = m_pWTFrame->GetTrackPos(eNSec);
	painter.setPen("black");
	painter.drawText(iPos, rect.bottom() - 45, 10 * m_pWTFrame->GetSLayout().m_iNumTraces, 20, Qt::AlignCenter, m_sDVName);

	if (m_pWavelet)
	{
		showWavelet(m_pWTFrame->GetTrackPos(eSyn));
	}
}

void CXFrameWTTop::showWavelet(qreal x)
{
	int i;
	double dDMin, dDMax, dDelta, px, py;
	m_pWavelet->GetDataRange(dDMin, dDMax);
	dDelta = dDMax - dDMin;
	double *pData = m_pWavelet->GetData();
	unsigned int iNum = m_pWavelet->GetPointNumber();

	QPainter painter(this);

	QRectF boundR(x, rect().bottom() - 80, 120, 80);
	painter.setPen(QPen(Qt::gray, 1));
	QFont font = painter.font();
	font.setPixelSize(10);
	painter.setFont(font);
	painter.drawRect(boundR);
	for (i = 1; i < 4; i++)
	{
		painter.drawLine(boundR.x() + i * boundR.width() / 4, boundR.y(), boundR.x() + i * boundR.width() / 4, boundR.bottom());
	}
	painter.drawText(boundR.right() + 10, boundR.y() - 5, 100, 20, Qt::AlignLeft, "1");
	py = boundR.bottom() - boundR.height() * (0 - dDMin) / dDelta;
	painter.drawLine(boundR.x(), py, boundR.right(), py);
	painter.drawText(boundR.right() + 10, py - 5, 100, 20, Qt::AlignLeft, "0");
	py = boundR.bottom() - boundR.height() * (0.5 * dDMax - dDMin)/ dDelta;
	painter.drawLine(boundR.x(), py, boundR.right(), py);
	painter.drawText(boundR.right() + 10, py - 5, 100, 20, Qt::AlignLeft, "0.5");
	py = boundR.bottom() - boundR.height() * (-0.5 * dDMax - dDMin) / dDelta;
	if (py < boundR.bottom())
	{
		painter.drawLine(boundR.x(), py, boundR.right(), py);
		painter.drawText(boundR.right() + 10, py - 5, 100, 20, Qt::AlignLeft, "-0.5");
	}

	py = boundR.bottom() - boundR.height() * (pData[0] - dDMin) / dDelta;
	painter.setPen(QPen(Qt::blue, 2));
	painter.setRenderHint(QPainter::Antialiasing, true);
	QPainterPath path(QPointF(x, py));
	for (i = 1; i < iNum; i++)
	{
		px = x + boundR.width() * i / (iNum - 1);
		py = boundR.bottom() - boundR.height() * (pData[i] - dDMin) / dDelta;
		path.lineTo(QPointF(px, py));
	}
	painter.drawPath(path);
}