#include <QPainter>
#include "xaxeswidget.h"
#include "xdlggatherwin.h"
#include "xscenegather.h"

constexpr auto GMARGIN = 60;

XAxesWidget::XAxesWidget(QWidget* parent)
{
	m_pWindow = dynamic_cast<XDlgGatherWin *>(parent);
}

void XAxesWidget::SetView(QWidget *pViewWidget)
{
	m_pLayout = new QGridLayout(this);
	m_pLayout->setContentsMargins(GMARGIN, GMARGIN, 0, 0);
	m_pLayout->addWidget(pViewWidget, 0, 0, 1, 1);
}

void XAxesWidget::paintEvent(QPaintEvent* event)
{
	if (!m_pScene)
	{
		m_pScene = m_pWindow->GetScene();
		if (!m_pScene)
			return;
	}

	if(m_pScene->GetCurrentShotID() == -1)
		return;

	int iTraceNum, iSampleNum;
	float fStartZ, fZInc;
	m_pScene->GetSectionSize(iTraceNum, iSampleNum);
	m_pScene->GetZInfo(fStartZ, fZInc);

	QRectF rectScene = m_pScene->sceneRect();

	QPainter painter(this);

	//	Draw horizontal ticks
	painter.save();
	painter.setClipRect(GMARGIN, 0, this->rect().width(), GMARGIN);

	painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignTop, "Shot " + QString::number(m_pScene->GetCurrentShotID()));

	float fIntv = rectScene.width() / iTraceNum;
	int i, iStep = 100 * fIntv > 100 ? 100 : 200;
	for (i = 0; i <= iTraceNum - 1; i += iStep / 10)
	{
		int iX = (int)(rectScene.left() + (i + 0.5) * fIntv + 0.5) + GMARGIN;

		if (i > 0 && i % iStep == 0)
		{
			painter.drawLine(iX, GMARGIN, iX, GMARGIN - 12);
			painter.drawText(iX - 50, GMARGIN - 30, 100, 30, Qt::AlignHCenter | Qt::AlignTop, QString::number(i));
		}
		else
			painter.drawLine(iX, GMARGIN, iX, GMARGIN - 5);
	}
	painter.restore();

	//	Draw vertical ticks.
	painter.setClipRect(0, GMARGIN, GMARGIN, this->rect().height() - GMARGIN);

	int iY;

	int iZ = (int)fStartZ;
	if (iZ % 100 != 0)
		iZ = 100 * ((iZ + 100) / 100);

	float fEndZ = fStartZ + (iSampleNum - 1) * fZInc;
	for (; iZ <= fEndZ; iZ += 100)
	{
		iY = GMARGIN + rectScene.top() + (iZ - fStartZ) / (fEndZ - fStartZ) * rectScene.height();
		if (iZ % 500 == 0)
		{
			painter.drawText(GMARGIN - 50, iY - 10, 38, 20, Qt::AlignRight | Qt::AlignVCenter, QString::number(iZ));
			painter.drawLine(GMARGIN, iY, GMARGIN - 10, iY);
		}
		else
		{
			painter.drawLine(GMARGIN, iY, GMARGIN - 5, iY);
		}
	}

	iY = this->rect().height() / 2;
	if (iY > rectScene.height() / 2 + GMARGIN)
		iY = rectScene.height() / 2 + GMARGIN;

	painter.translate(10, iY);
	painter.rotate(-90);
	painter.drawText(0, 5, "Time");
}