#include <QIntValidator>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <qmessagebox.h>
#include "xdlgpyramid.h"
#include "xseismicdatavolume.h"
#include "xscenepyramid.h"
#include "xthreadpyramid.h"
#include "xthreadslicetotrace.h"
#include "xglobal.h"
#include "xdlgcalculatingprogress.h"
#include "xalgorithmutility.h"
#include "xdlgpyviewer.h"

XDlgPyramid::XDlgPyramid(CXSeismicDataVolume *pDV, QWidget *parent)
	: m_pDV(pDV), QDialog(parent)
{
	ui.setupUi(this);

	initView();
	initUI();
}

XDlgPyramid::~XDlgPyramid()
{
	delete m_pScene;
}

void XDlgPyramid::initUI()
{
	CXSeismicUTMTool utm = m_pDV->GetUTM();
	int iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc;
	utm.GetLineNumRange(iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc);

	ui.lineEditSection->setValidator(new QIntValidator(this));
	ui.lineEditFrom->setValidator(new QIntValidator(this));
	ui.lineEditTo->setValidator(new QIntValidator(this));
	ui.lineEditStep->setValidator(new QIntValidator(this));
	ui.lineEditDegree->setValidator(new QIntValidator(this));
	ui.lineEditOutside->setValidator(new QIntValidator(this));

	//	Processing direction.
	ui.radioButtonT->setEnabled(m_pDV->HasSliceFile());
	connect(ui.radioButtonI, SIGNAL(clicked()), this, SLOT(slotDirection()));
	connect(ui.radioButtonX, SIGNAL(clicked()), this, SLOT(slotDirection()));
	connect(ui.radioButtonT, SIGNAL(clicked()), this, SLOT(slotDirection()));

	//	Preview Section.
	ui.horizontalSliderSection->setRange(iInlineS, iInlineE);
	int iNo = iInlineS + (iInlineE - iInlineS) / (2 * iInlineInc) * iInlineInc;
	ui.horizontalSliderSection->setRange(iInlineS, iInlineE);
	ui.horizontalSliderSection->setSingleStep(iInlineInc);
	ui.horizontalSliderSection->setValue(iNo);
	ui.lineEditSection->setText(QString::number(iNo));

	connect(ui.lineEditSection, SIGNAL(editingFinished()), this, SLOT(slotSection()));
	connect(ui.horizontalSliderSection, SIGNAL(valueChanged(int)), this, SLOT(slotSection()));

	//	Processing degree
	connect(ui.groupBox_4, SIGNAL(clicked(bool)), this, SLOT(slotDegree()));
	connect(ui.lineEditFrom, SIGNAL(editingFinished()), this, SLOT(slotDegree()));
	connect(ui.lineEditTo, SIGNAL(editingFinished()), this, SLOT(slotDegree()));
	connect(ui.lineEditStep, SIGNAL(editingFinished()), this, SLOT(slotDegree()));
	connect(ui.lineEditDegree, SIGNAL(editingFinished()), this, SLOT(slotDegree()));
	connect(ui.horizontalSliderDegree, SIGNAL(valueChanged(int)), this, SLOT(slotDegree()));

	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(slotArea()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(slotDegree()));

	//	The output DV
	resetODVName();
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(slotOutside()));

	//	The output range.
	ui.slideRangeInline->SetSliderName(QString::fromUtf8(u8"主测线"));
	ui.slideRangeInline->SetRangeAndPrecision(iInlineS, iInlineE, iInlineInc);
	ui.slideRangeXline->SetSliderName(QString::fromUtf8(u8"联络测线"));
	ui.slideRangeXline->SetRangeAndPrecision(iXlineS, iXlineE, iXlineInc);

	double dZS, dZE, dZInc;
	m_pDV->GetSamplingRange(dZS, dZE, dZInc);
	ui.slideRangeTimeSlice->SetSliderName(QString::fromUtf8(u8"时间"));
	ui.slideRangeTimeSlice->SetRangeAndPrecision(dZS, dZE, dZInc);
	
	slotDegree();
}

void XDlgPyramid::initView()
{
	m_pScene = new XScenePyramid(this);
	ui.graphicsView->setScene(m_pScene);
}

void XDlgPyramid::slotArea()
{
	bool bChecked = ui.pushButton_4->isChecked();
	m_pScene->InitializeRect(bChecked);
}

void XDlgPyramid::slotSection()
{
	CXSeismicUTMTool utm = m_pDV->GetUTM();
	int iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc;
	utm.GetLineNumRange(iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc);
	double dZS, dZE, dZInc;
	m_pDV->GetSamplingRange(dZS, dZE, dZInc);

	ui.lineEditSection->blockSignals(true);
	ui.horizontalSliderSection->blockSignals(true);

	int iNo = -1;
	if (sender() == ui.lineEditSection)
	{
		iNo = ui.lineEditSection->text().toInt();
		if (ui.radioButtonI->isChecked())
		{
			iNo = iNo > iInlineS ? iNo : iInlineS;
			iNo = iNo < iInlineE ? iNo : iInlineE;
			iNo -= (iNo - iInlineS) % iInlineInc;
		}
		else if (ui.radioButtonX->isChecked())
		{
			iNo = iNo > iXlineS ? iNo : iXlineS;
			iNo = iNo < iXlineE ? iNo : iXlineE;
			iNo -= (iNo - iXlineS) % iXlineInc;
		}
		else
		{
			iNo = iNo > dZS ? iNo : dZS;
			iNo = iNo < dZE ? iNo : dZE;
			iNo -= (int)(iNo - dZS) %  (int)dZInc;
		}

		ui.lineEditSection->setText(QString::number(iNo));
		ui.horizontalSliderSection->setValue(iNo);
	}
	else if (sender() == ui.horizontalSliderSection)
	{
		iNo = ui.horizontalSliderSection->value();

		ui.lineEditSection->setText(QString::number(iNo));
	}

	ui.lineEditSection->blockSignals(false);
	ui.horizontalSliderSection->blockSignals(false);

	flushSection();
}

void XDlgPyramid::resetODVName()
{
	QString sDir = "_I";
	if (ui.radioButtonX->isChecked())
		sDir = "_X";
	else if (ui.radioButtonT->isChecked())
		sDir = "_T";

	QString sName = m_pDV->GetObjectName() + "_PyFil" + sDir + ui.lineEditDegree->text();
	sName = m_pDV->GetUnallocatedName(sName);
	ui.lineEdit->setText(sName);
}

void XDlgPyramid::slotDirection()
{
	CXSeismicUTMTool utm = m_pDV->GetUTM();
	int iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc;
	utm.GetLineNumRange(iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc);

	ui.lineEditSection->blockSignals(true);
	ui.horizontalSliderSection->blockSignals(true);

	int iNo = -1;
	if (ui.radioButtonI->isChecked())
	{
		iNo = iInlineS + (iInlineE - iInlineS) / (2 * iInlineInc) * iInlineInc;
		ui.horizontalSliderSection->setRange(iInlineS, iInlineE);
		ui.horizontalSliderSection->setSingleStep(iInlineInc);
		ui.horizontalSliderSection->setValue(iNo);
		ui.lineEditSection->setText(QString::number(iNo));
	}
	else if (ui.radioButtonX->isChecked())
	{
		iNo = iXlineS + (iXlineE - iXlineS) / (2 * iXlineInc) * iXlineInc;
		ui.horizontalSliderSection->setRange(iXlineS, iXlineE);
		ui.horizontalSliderSection->setSingleStep(iXlineInc);
		ui.horizontalSliderSection->setValue(iNo);
		ui.lineEditSection->setText(QString::number(iNo));
	}
	else if (ui.radioButtonT->isChecked())
	{
		double dZS, dZE, dZInc;
		m_pDV->GetSamplingRange(dZS, dZE, dZInc);

		iNo = (int)(dZS + int(dZE - dZS) / (int)(2 * dZInc) * dZInc);
		ui.horizontalSliderSection->setRange(dZS, dZE);
		ui.horizontalSliderSection->setSingleStep(dZInc);
		ui.horizontalSliderSection->setValue(iNo);
		ui.lineEditSection->setText(QString::number(iNo));
	}

	ui.lineEditSection->blockSignals(false);
	ui.horizontalSliderSection->blockSignals(false);

	if (iNo != -1)
	{
		//	Direction may changed, clear the read data.
		m_pScene->ClearSection();
	}

	resetODVName();
	slotSection();
}

void XDlgPyramid::slotDegree()
{
	if (sender() == ui.groupBox_4)
	{
		flushSection();
		return;
	}
	else if (sender() == ui.pushButton_3)
	{
		int iAng = ui.lineEdit_3->text().toInt();
		ui.horizontalSliderDegree->setValue(iAng);
		ui.checkBox->setChecked(true);
		return;
	}

	ui.lineEditFrom->blockSignals(true);
	ui.lineEditTo->blockSignals(true);
	ui.lineEditStep->blockSignals(true);
	ui.lineEditDegree->blockSignals(true);
	ui.horizontalSliderDegree->blockSignals(true);

	int iS = ui.lineEditFrom->text().toInt();
	int iE = ui.lineEditTo->text().toInt();
	int iStep = ui.lineEditStep->text().toInt();

	if (iE < iS)
	{
		iE = iS;
		ui.lineEditTo->setText(QString::number(iE));
	}

	if (iStep < 1)
	{
		iStep = 1;
		ui.lineEditStep->setText("1");
	}

	ui.horizontalSliderDegree->setRange(iS, iE);
	ui.horizontalSliderDegree->setSingleStep(iStep);

	int iDeg = -1;
	if (sender() == ui.lineEditDegree)
	{
		iDeg = ui.lineEditDegree->text().toInt();
		iDeg = iDeg > iS ? iDeg : iS;
		iDeg = iDeg < iE ? iDeg : iE;
		iDeg -= (iDeg - iS) % iStep;

		ui.lineEditDegree->setText(QString::number(iDeg));
		ui.horizontalSliderDegree->setValue(iDeg);
	}
	else if (sender() == ui.horizontalSliderDegree)
	{
		iDeg = ui.horizontalSliderDegree->value();
		iDeg -= (iDeg - iS) % iStep;

		ui.lineEditDegree->setText(QString::number(iDeg));
		ui.horizontalSliderDegree->setValue(iDeg);
	}

	ui.lineEditFrom->blockSignals(false);
	ui.lineEditTo->blockSignals(false);
	ui.lineEditStep->blockSignals(false);
	ui.lineEditDegree->blockSignals(false);
	ui.horizontalSliderDegree->blockSignals(false);

	if (iDeg != -1)
	{
		ui.lineEdit_2->setText(QString::number(iDeg));
		resetODVName();

		flushSection(true);
	}
}

void XDlgPyramid::flushSection(bool bOnlyAngle)
{
	XViewPyramid *pView = dynamic_cast<XViewPyramid *>(ui.graphicsView);
	pView->GetGLWidget()->makeCurrent();

	int iDir = 0;
	if (ui.radioButtonX->isChecked())
		iDir = 1;
	else if (ui.radioButtonT->isChecked())
		iDir = 2;

	bool bF = ui.groupBox_4->isChecked();
	if(bOnlyAngle)
		m_pScene->BuildSection(ui.horizontalSliderDegree->value(), bF);
	else
		m_pScene->BuildSection(m_pDV, iDir, ui.horizontalSliderSection->value(), ui.horizontalSliderDegree->value(), bF);
	m_pScene->update();

	pView->GetGLWidget()->doneCurrent();
}

void XDlgPyramid::accept()
{
	if (!ui.groupBox_4->isChecked())
	{
		QMessageBox::warning(this, QString::fromUtf8(u8"金字塔滤波"), QString::fromUtf8(u8"未选择滤波处理！"));
		return;
	}

	QString sOName = ui.lineEdit->text();
	if (sOName.isEmpty())
	{
		QMessageBox::warning(this, QString::fromUtf8(u8"金字塔滤波"), QString::fromUtf8(u8"未提供输出数据体名称！"));
		return;
	}

	QPolygonF polygon = m_pScene->GetPolygon();
	if (ui.checkBox->isChecked() && polygon.isEmpty())
	{
		QMessageBox::warning(this, QString::fromUtf8(u8"金字塔滤波"), 
			QString::fromUtf8(u8"未选择合理的目标区域！"));
		return;
	}

	XParameterPyramid *pPara = new XParameterPyramid;
	pPara->SetDVID(m_pDV->GetObjectID());
	pPara->SetInputInlineS((int)(ui.slideRangeInline->GetMinValue()));
	pPara->SetInputInlineE((int)(ui.slideRangeInline->GetMaxValue()));
	pPara->SetInputXlineS((int)(ui.slideRangeXline->GetMinValue()));
	pPara->SetInputXlineE((int)(ui.slideRangeXline->GetMaxValue()));
	pPara->SetInputTimeS(ui.slideRangeTimeSlice->GetMinValue());
	pPara->SetInputTimeE(ui.slideRangeTimeSlice->GetMaxValue());

	int iDir = 0;
	if (ui.radioButtonX->isChecked())
		iDir = 1;
	else if (ui.radioButtonT->isChecked())
		iDir = 2;

	pPara->SetFDirection(iDir);
	pPara->SetFDegree(ui.horizontalSliderDegree->value());

	pPara->SetUsingPolygon(ui.checkBox->isChecked());
	if (ui.checkBox->isChecked())
	{
		std::vector<double> vecPoints;
		foreach(QPointF point, polygon)
		{
			vecPoints.push_back(point.x());
			vecPoints.push_back(point.y());
		}

		pPara->SetVecPoints(vecPoints);
		pPara->SetODegree(ui.lineEditOutside->text().toInt());
	}

	sOName = m_pDV->GetUnallocatedName(sOName);
	pPara->SetODVName(sOName);

	XThreadPyramid *pThread = new XThreadPyramid(pPara);
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread);

	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		CXSeismicDataVolume *pDV = pThread->GetOutputDV();

		if (pDV)
		{
			if (iDir == 2)
			{
				//	DV generated along slice, need the trace file!
				CXThreadSliceToTrace *pThread = new CXThreadSliceToTrace(pDV);
				CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread);

				pProgress->show();
				pThread->start();

				if (pProgress->exec() == QDialog::Accepted)
				{
					CXAlgorithmUtility::CalculateHistogram(pDV->GetTraceFileName(), pDV->GetSamplingQty(), pDV);
					delete pThread;
				}
			}
			else
			{
				CXAlgorithmUtility::CalculateHistogram(pDV->GetTraceFileName(), pDV->GetSamplingQty(), pDV);
			}
		}

		delete pThread;
	}

	QDialog::accept();
}

void XDlgPyramid::CalVar(float* pData, int iWWidth, int iWHeight, int iIWidth, int iIHeight)
{
	XDlgPyViewer dlg(this);
	dlg.ResizeFrame(iWWidth, iWHeight, iIWidth, iIHeight, pData);
	dlg.exec();
}

void XDlgPyramid::SetSugAng(QString sAng)
{
	ui.lineEdit_3->setText(sAng);
	//m_pScene->InitializeRect(false);
}

void XDlgPyramid::slotOutside()
{
	ui.lineEditOutside->setEnabled(ui.checkBox->isChecked());
	if (ui.checkBox->isChecked())
	{
		int iAng = ui.lineEditDegree->text().toInt();
		iAng += 90;
		if (iAng > 360)
			iAng -= 360;

		ui.lineEditOutside->setText(QString::number(iAng));
	}
}