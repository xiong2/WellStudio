#include <qpushbutton.h>
#include "xdlgvolumeintegration.h"
#include "xseismicdatavolume.h"
#include "xseismicdataline.h"
#include "xregulardatawriter.h"
#include "x3dhorizon.h"
#include "xalgorithmutility.h"
#include "xprogressbar.h"
#include "xglobal.h"

XDlgVolumeIntegration::XDlgVolumeIntegration(CXObject *pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pDV = dynamic_cast<CXSeismicDataVolume *>(pObj);
	m_pDLine = dynamic_cast<CXSeismicDataLine *>(pObj);

	init();
}

XDlgVolumeIntegration::~XDlgVolumeIntegration()
{

}

void XDlgVolumeIntegration::init()
{
	ui.lineEditDV->setText("Over Burden Pressure");
	double dZStart, dZStop, dZSampleIntv;
	
	if (m_pDV)
	{
		m_pDV->GetSamplingRange(dZStart, dZStop, dZSampleIntv);
	}
	else
	{
		m_pDLine->GetSamplingRange(dZStart, dZStop, dZSampleIntv);
	}

	int iStep = (int)dZSampleIntv;
	ui.horizontalSlider->setRange((int)dZStart, (int)dZStop);
	ui.horizontalSlider->setValue((int)dZStop);
	ui.horizontalSlider->setSingleStep(iStep);
	ui.horizontalSlider->setPageStep(iStep);
	ui.lineEdit->setText(QString::number((int)dZStop));
	connect(ui.horizontalSlider, &QSlider::valueChanged, this, &XDlgVolumeIntegration::slotSetDepth);

	if (m_pDV)
	{
		int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
		m_pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
		iStep = (int)dZSampleIntv;

		ui.m_pInlineWidget->SetSliderName("Inline");
		ui.m_pInlineWidget->SetRangeAndPrecision(iInlineMin, iInlineMax, iInlineInc, 0);

		ui.m_pXlineWidget->SetSliderName("Crossline");
		ui.m_pXlineWidget->SetRangeAndPrecision(iXlineMin, iXlineMax, iXlineInc, 0);

		ui.comboBox->clear();
		CXObject *pSurvey = m_pDV->GetParent()->GetParent();
		QList<CXObject *> listHor = pSurvey->GetChildren(EX3DHorizon, true);
		if (!listHor.isEmpty())
		{
			QStringList sListHor;
			foreach(CXObject *pHor, listHor)
			{
				sListHor << pHor->GetObjectName();
			}
			ui.comboBox->addItems(sListHor);
			ui.radioButtonHorizon->setDisabled(false);
		}
		else
			ui.radioButtonHorizon->setDisabled(true);

		connect(ui.radioButtonHorizon, &QPushButton::clicked, this, &XDlgVolumeIntegration::slotRadioBox);
		connect(ui.radioButtonDepth, &QPushButton::clicked, this, &XDlgVolumeIntegration::slotRadioBox);
	}
	else
	{
		ui.label_2->setText("Output line");
		ui.m_pInlineWidget->SetSliderName("Inline");
		ui.m_pInlineWidget->setDisabled(true);
		ui.m_pXlineWidget->SetSliderName("Crossline");
		ui.m_pXlineWidget->setDisabled(true);
		ui.radioButtonHorizon->setDisabled(true);
	}
}

void XDlgVolumeIntegration::slotRadioBox()
{
	if (sender() == ui.radioButtonDepth)
	{
		ui.comboBox->setDisabled(true);
		ui.lineEdit->setDisabled(false);
		ui.horizontalSlider->setDisabled(false);
	}
	else
	{
		ui.comboBox->setDisabled(false);
		ui.lineEdit->setDisabled(true);
		ui.horizontalSlider->setDisabled(true);
	}
}
void XDlgVolumeIntegration::slotSetDepth()
{
	ui.lineEdit->setText(QString::number(ui.horizontalSlider->value()));
}

void XDlgVolumeIntegration::accept()
{
	double dStartZ, dEndZ, dZStep, dZ;

	if (m_pDV)
	{
		m_pDV->GetSamplingRange(dStartZ, dEndZ, dZStep);

		CXSeismicUTMTool horUTM;
		float *pHData = NULL;
		if (ui.radioButtonDepth->isChecked())
		{
			dZ = ui.lineEdit->text().toDouble();
		}
		else
		{
			double dZMin;
			CXObject *pSurvey = m_pDV->GetParent()->GetParent();
			QList<CXObject *> listHor = pSurvey->GetChildren(EX3DHorizon, true);
			CX3DHorizon *pHor = (CX3DHorizon *)listHor.at(ui.comboBox->currentIndex());
			pHor->GetDataRange(dZMin, dZ);

			if (dZ > dEndZ)
				dZ = dEndZ;

			horUTM.Copy(&pHor->GetUTM());
			pHData = pHor->GetData();
		}

		int iFirstLine = ui.m_pInlineWidget->GetMinValue();
		int iLastLine = ui.m_pInlineWidget->GetMaxValue();
		int iFirstCDP = ui.m_pXlineWidget->GetMinValue();
		int iLastCDP = ui.m_pXlineWidget->GetMaxValue();
		int iLineStep = m_pDV->GetUTM().GetInlineIncrement();
		int iCDPStep = m_pDV->GetUTM().GetCrosslineIncrement();
		int iNumLine = (iLastLine - iFirstLine) / iLineStep + 1;
		int iNumCDP = (iLastCDP - iFirstCDP) / iCDPStep + 1;

		CXSeismicUTMTool utm;
		utm.Copy(&m_pDV->GetUTM());
		utm.Resize(iFirstLine, iFirstCDP, iNumLine, iNumCDP);

		QString SName = m_pDV->GetParent()->GetUnallocatedName(ui.lineEditDV->text());
		CXSeismicDataVolume *pOutputDV = new CXSeismicDataVolume(utm, dStartZ, dZ, dZStep, SName);
		int iDataSize = pOutputDV->GetXlineTraceQty() * pOutputDV->GetSamplingQty();
		float *pFloatBuff = new float[iDataSize];
		float *pBigBuff = new float[m_pDV->GetXlineTraceQty() * m_pDV->GetSamplingQty()];

		CXRegularDataWriter<float> *pWriter = new CXRegularDataWriter<float>(pOutputDV->GetTraceFileName(), pOutputDV->GetInlineQty(), pOutputDV->GetXlineTraceQty(), pOutputDV->GetSamplingQty());
		pWriter->Open();

		int iNum = (dZ - dStartZ) / dZStep + 1;
		int i, j, iCount = 0;

		CXProgressBar progress("Seismic Data Volume Integration", "Calculating... ", iNumLine);

		for (i = iFirstLine; i <= iLastLine; i += iLineStep)
		{
			m_pDV->ReadInline(i, pBigBuff);
			memset(pFloatBuff, 0, iDataSize * 4);

			progress.SetValue(iCount);
			iCount++;

			for (j = 0; j < iNumCDP; j++)
			{
				int m, n, iXline = iFirstCDP + j * iCDPStep;
				if (ui.radioButtonHorizon->isChecked())
				{
					horUTM.LineToIJ(i, iXline, m, n);
					float dVal = pHData[horUTM.GetNJ() * m + n];
					iNum = (dVal - dStartZ) / dZStep + 1;
				}

				m_pDV->GetUTM().LineToIJ(i, iXline, m, n);
				integrateOneTrace(pBigBuff + n * m_pDV->GetSamplingQty(), pFloatBuff + j * pOutputDV->GetSamplingQty(), iNum);
			}

			pWriter->Append(iDataSize, pFloatBuff);
		}

		m_pDV->GetParent()->AddChild(pOutputDV);

		CXAlgorithmUtility::CalculateHistogram(pOutputDV->GetTraceFileName(), pOutputDV->GetSamplingQty(), pOutputDV);
		::AddObjectEvent(pOutputDV);

		delete pWriter;
		delete[]pFloatBuff;
		delete[]pBigBuff;
	}
	else
	{
		m_pDLine->GetSamplingRange(dStartZ, dEndZ, dZStep);
		dZ = ui.lineEdit->text().toDouble();

		int iTNum = m_pDLine->GetTraceNumber();
		int iSSNum = (dEndZ - dStartZ) / dZStep + 1;
		int iDSNum = (dZ - dStartZ) / dZStep + 1;

		QString SName = m_pDLine->GetParent()->GetUnallocatedName(ui.lineEditDV->text());
		CXSeismicDataLine *pNewLine = new CXSeismicDataLine(m_pDLine->GetParent(), dStartZ, dZ, dZStep, SName);

		float *pSData = m_pDLine->GetData();
		float *pDData = new float[iTNum * iDSNum];
		for (int i = 0; i < iTNum; i++)
		{
			integrateOneTrace(pSData + i * iSSNum, pDData + i * iDSNum, iDSNum);
		}

		QString strFileName = pNewLine->GetDataFileName();
		QFile qFile(strFileName);
		if (!qFile.open(QIODevice::WriteOnly))
			return;

		qFile.write((char*)pDData, sizeof(float) * iDSNum * iTNum);
		qFile.close();
		delete[]pDData;

		pNewLine->SetModifiedFlag();
		m_pDLine->GetParent()->AddChild(pNewLine);
		
		CXAlgorithmUtility::CalculateHistogram(pNewLine->GetDataFileName(), iDSNum, pNewLine);
		::AddObjectEvent(pNewLine);
	}

	QDialog::accept();
}

void XDlgVolumeIntegration::integrateOneTrace(float *pSData, float *pDData, int iNum)
{
	float fInv;
	if(m_pDV)
		fInv = m_pDV->GetSampleInterval() * 0.0098;
	else
		fInv = m_pDLine->GetSampleInterval() * 0.0098;

	pDData[0] = 0.;
	for (int i = 1; i < iNum; i++)
	{
		pDData[i] = pDData[i - 1] + pSData[i - 1] * fInv;
	}
}