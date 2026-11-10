#include <QIntValidator>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <qscrollbar.h>
#include "xdlggatherwin.h"
#include "xprestackgather.h"
#include "xscenegather.h"
#include "xviewgather.h"

XDlgGatherWin::XDlgGatherWin(CXObject *pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pGather = dynamic_cast<CXPreStackGather *>(pObj);

	initUI();
}

XDlgGatherWin::~XDlgGatherWin()
{
	delete m_pScene;
	delete m_pView;
}

void XDlgGatherWin::initUI()
{
	ui.AxesWidget->show();
	m_pScene = new XSceneGather(this);
	m_pView = new XViewGather(m_pScene, this);
	m_pScene->SetView(m_pView);

	ui.AxesWidget->SetView(m_pView);

	int iStart, iEnd, iNum;
	m_pGather->GetShotIDRange(iStart, iEnd, iNum);

	ui.horizontalSlider->setRange(iStart, iEnd);
	ui.horizontalSlider->setValue(iStart);

	ui.lineEdit->setValidator(new QIntValidator(this));
	ui.lineEdit->setText(QString::number(iStart));

	connect(ui.lineEdit, SIGNAL(editingFinished()), this, SLOT(slotUpdateShotID()));
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateShotID()));
	connect(ui.pushButtonShow, SIGNAL(clicked()), this, SLOT(slotShow()));
	connect(ui.pushButtonVA, SIGNAL(clicked()), this, SLOT(slotShowMode()));
	connect(ui.pushButtonW, SIGNAL(clicked()), this, SLOT(slotShowMode()));
	connect(ui.pushButtonVD, SIGNAL(clicked()), this, SLOT(slotShowMode()));
	connect(ui.pushButtonHUp, SIGNAL(clicked()), this, SLOT(slotShowScale()));
	connect(ui.pushButtonHDown, SIGNAL(clicked()), this, SLOT(slotShowScale()));
	connect(ui.pushButtonVUp, SIGNAL(clicked()), this, SLOT(slotShowScale()));
	connect(ui.pushButtonVDown, SIGNAL(clicked()), this, SLOT(slotShowScale()));
	connect(ui.pushButtonIE, SIGNAL(clicked()), this, SLOT(slotShowExcursion()));
	connect(ui.pushButtonDE, SIGNAL(clicked()), this, SLOT(slotShowExcursion()));

	connect(m_pView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(slotHorizontalScroll(int)));
	connect(m_pView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(slotVerticalScroll(int)));

	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(slotShowFB()));
	connect(ui.comboBox, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotFBColor()));
}

void XDlgGatherWin::slotShowMode()
{
	if (!m_bInited)
		return;

	CXViewInfoGather *pViewInfo = m_pScene->GetViewInfo();
	pViewInfo->SetShowVI(ui.pushButtonVD->isChecked());
	pViewInfo->SetShowVA(ui.pushButtonVA->isChecked());
	pViewInfo->SetShowWiggle(ui.pushButtonW->isChecked());

	m_pScene->update();
}

void XDlgGatherWin::slotShowScale()
{
	if (!m_bInited)
		return;

	CXViewInfoGather *pViewInfo = m_pScene->GetViewInfo();
	if (sender() == ui.pushButtonHDown)
	{
		float fHScale = pViewInfo->GetHScale();
		fHScale -= 0.5;
		if (fHScale >= 1.)
			pViewInfo->SetHScale(fHScale);
	}
	else if (sender() == ui.pushButtonHUp)
	{
		float fHScale = pViewInfo->GetHScale();
		fHScale += 0.5;
		if (fHScale <= 6.)
			pViewInfo->SetHScale(fHScale);
	}
	else if (sender() == ui.pushButtonVDown)
	{
		float fVScale = pViewInfo->GetVScale();
		fVScale -= 0.2;
		if (fVScale >= 0.2)
			pViewInfo->SetVScale(fVScale);
	}
	else if ( sender() == ui.pushButtonVUp)
	{
		float fVScale = pViewInfo->GetVScale();
		fVScale += 0.2;
		if (fVScale <= 3.)
			pViewInfo->SetVScale(fVScale);
	}

	int iWid, iHei;
	m_pScene->GetCanvasSize(iWid, iHei);
	QRectF rect(0, 0, iWid, iHei);

	m_pScene->blockSignals(true);
	m_pScene->setSceneRect(rect);
	ui.AxesWidget->repaint();
	m_pScene->blockSignals(false);

	SetScrollbarPos();
	updateROI();

	m_pScene->RedrawFB();
}

void XDlgGatherWin::slotShowExcursion()
{
	CXViewInfoGather *pViewInfo = m_pScene->GetViewInfo();
	float fExcursion = pViewInfo->GetExcusion();
	if (sender() == ui.pushButtonIE)
		pViewInfo->SetExcusion(fExcursion * 1.2);
	else if (sender() == ui.pushButtonDE)
		pViewInfo->SetExcusion(fExcursion * 0.8);
	else
		return;

	m_pScene->RedrawSection();
	m_pScene->update();
}

void XDlgGatherWin::slotShowFB()
{
	if (ui.checkBox->isChecked())
	{
		m_pScene->CreateFBItem(m_pGather);
		m_pScene->update();
	}
	else
	{
		m_pScene->RemoveFBItem();
		m_pScene->update();
	}

	ui.comboBox->setEnabled(ui.checkBox->isChecked());
}

void XDlgGatherWin::slotFBColor()
{
	CXViewInfoGather *pViewInfo = m_pScene->GetViewInfo();
	pViewInfo->SetFBColor(ui.comboBox->GetColor());
	m_pScene->update();
}

void XDlgGatherWin::slotUpdateShotID()
{
	int iStart, iEnd, iNum, iShotID;
	m_pGather->GetShotIDRange(iStart, iEnd, iNum);

	ui.lineEdit->blockSignals(true);
	ui.horizontalSlider->blockSignals(true);

	if (sender() == ui.lineEdit)
		iShotID = ui.lineEdit->text().toInt();		
	else
		iShotID = ui.horizontalSlider->value();

	m_pGather->FindNearbyShot(iShotID);

	ui.lineEdit->setText(QString::number(iShotID));
	ui.horizontalSlider->setValue(iShotID);

	ui.lineEdit->blockSignals(false);
	ui.horizontalSlider->blockSignals(false);
}

void XDlgGatherWin::slotShow()
{
	if (!m_bInited)
	{
		m_pScene->InitOpenGLBuilder();
		m_bInited = true;

		ui.checkBox->setEnabled(true);
	}

	flushSection();
}

void XDlgGatherWin::flushSection()
{
	m_pView->GetGLWidget()->makeCurrent();

	m_pScene->BuildSection(m_pGather, ui.horizontalSlider->value());

	m_pScene->update();

	m_pView->GetGLWidget()->doneCurrent();

	m_pView->verticalScrollBar()->setRange(0, 0);
	m_pView->horizontalScrollBar()->setRange(0, 0);

	int iWid, iHei;
	m_pScene->GetCanvasSize(iWid, iHei);
	QRectF rect(0, 0, iWid, iHei);

	m_pScene->blockSignals(true);
	m_pScene->setSceneRect(rect);
	ui.AxesWidget->repaint();
	m_pScene->blockSignals(false);

	SetScrollbarPos();
	updateROI();

	if (ui.checkBox->isChecked())
	{
		m_pScene->CreateFBItem(m_pGather);
		m_pScene->update();
	}
}

void XDlgGatherWin::SetScrollbarPos(bool bChangeScale)
{
	QRect rectWidget = m_pView->rect();
	int nWidth = rectWidget.width() - m_pView->verticalScrollBar()->width();
	int nHeight = rectWidget.height() - m_pView->horizontalScrollBar()->height();

	int nHorPos = m_pView->horizontalScrollBar()->value();
	int nVerPos = m_pView->verticalScrollBar()->value();
	double dHorCenterRatio(0), dVerCenterRatio(0);
	if (bChangeScale)
	{
		double dHorMin = m_pView->horizontalScrollBar()->minimum();
		double dHorMax = m_pView->horizontalScrollBar()->maximum();
		if (dHorMin != dHorMax)
		{
			dHorCenterRatio = (nHorPos + 0.5*nWidth) / (nWidth + dHorMax - dHorMin);
		}

		double dVerMin = m_pView->verticalScrollBar()->minimum();
		double dVerMax = m_pView->verticalScrollBar()->maximum();
		if (dVerMin != dVerMax)
		{
			dVerCenterRatio = (nVerPos + 0.5*nHeight) / (nHeight + dVerMax - dVerMin);
		}
	}

	QRectF sceneRect = m_pScene->sceneRect();
	int nMaxValue = qMax(0, sceneRect.toRect().width() - nWidth);
	m_pView->horizontalScrollBar()->setRange(0, nMaxValue);
	m_pView->horizontalScrollBar()->setPageStep(sceneRect.toRect().width() - nMaxValue);

	if (bChangeScale)
	{
		nHorPos = static_cast<int>(dHorCenterRatio * sceneRect.toRect().width() - 0.5*nWidth);
		nHorPos = qBound(0, nHorPos, nMaxValue);
	}
	else
	{
		nHorPos = qMin(nHorPos, nMaxValue);
	}
	m_pView->horizontalScrollBar()->setValue(nHorPos);


	nMaxValue = qMax(0, sceneRect.toRect().height() - nHeight);
	m_pView->verticalScrollBar()->setRange(0, nMaxValue);
	m_pView->verticalScrollBar()->setPageStep(sceneRect.toRect().height() - nMaxValue);

	if (bChangeScale)
	{
		nVerPos = static_cast<int>(dVerCenterRatio * sceneRect.toRect().height() - 0.5*nHeight);
		nVerPos = qBound(0, nVerPos, nMaxValue);
	}
	else
	{
		nVerPos = qMin(nVerPos, nMaxValue);
	}
	m_pView->verticalScrollBar()->setValue(nVerPos);
}

void XDlgGatherWin::updateROI()
{
	QRect rectWidget = m_pView->rect();
	int nWidth = rectWidget.width() - m_pView->verticalScrollBar()->width();
	int nHeight = rectWidget.height() - m_pView->horizontalScrollBar()->height();

	// scrollbar
	int nHorPos = m_pView->horizontalScrollBar()->value();
	int nVerPos = m_pView->verticalScrollBar()->value();

	QRectF rectScene = m_pScene->sceneRect();
	QRect rectView;
	rectView.setX(nHorPos + rectScene.toRect().x());
	rectView.setY(nVerPos + rectScene.toRect().y());
	rectView.setWidth(qMin(rectScene.toRect().width() - nHorPos, nWidth));
	rectView.setHeight(qMin(rectScene.toRect().height() - nVerPos, nHeight));

	float fLeft = 2.*(rectView.left() - rectScene.left()) / rectScene.width() - 1.;
	float fRight = 2.*(rectView.right() - rectScene.left()) / rectScene.width() - 1.;

	float fBottom = 1. - 2.*(rectView.bottom() - rectScene.top()) / rectScene.height();
	float fTop = 1. - 2.*(rectView.top() - rectScene.top()) / rectScene.height();

	m_pScene->UpdateROI(fLeft, fRight, fBottom, fTop);
	m_pView->viewport()->setFixedSize(rectView.width(), rectView.height());
	m_pView->viewport()->update();
}

void XDlgGatherWin::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);
	if (!m_bInited)
		return;

	SetScrollbarPos();
	updateROI();
	m_pScene->update();
}

void XDlgGatherWin::slotHorizontalScroll(int nValue)
{
	if (!m_bInited)
		return;

	if (nValue < 0)
		return;

	m_pScene->blockSignals(true);
	QRectF rectScene = m_pScene->sceneRect(); 
	rectScene.moveLeft(-nValue);
	m_pScene->setSceneRect(rectScene);
	ui.AxesWidget->repaint();
	m_pScene->blockSignals(false);

	// view port
	updateROI();
	m_pScene->update();
}

void XDlgGatherWin::slotVerticalScroll(int nValue)
{
	if (!m_bInited)
		return;

	if (nValue < 0)
		return;

	QRectF rectScene = m_pScene->sceneRect();
	rectScene.moveTop(-nValue);
	m_pScene->blockSignals(true);
	m_pScene->setSceneRect(rectScene);
	ui.AxesWidget->repaint();
	m_pScene->blockSignals(false);

	// view port
	updateROI();
	m_pScene->update();
}