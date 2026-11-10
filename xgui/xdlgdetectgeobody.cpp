#include "xdlgdetectgeobody.h"
#include <qmessagebox.h>
#include "xseismicdatavolume.h"
#include "xparametersgeobodydetection.h"
#include "xseismicutmtool.h"
#include "xglobal.h"
#include "xprocessfactory.h"
#include "xbaseconsole.h"
#include "xviewinfoobject.h"

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgDetectGeobody)
EDetectGeobody
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgDetectGeobody)


CXDlgDetectGeobody::CXDlgDetectGeobody(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	m_pPara = dynamic_cast<CXParametersGeobodyDetection*>(pPara);
	m_pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);

	initialize();
}

CXDlgDetectGeobody::~CXDlgDetectGeobody()
{
}

void CXDlgDetectGeobody::initialize()
{
	if (!m_pDV)
		return;

	QString strGeobodyName = m_pDV->GetObjectName() + " Geobody";
	CXObject *pGFolder = ::GetRootObjectFolder(EXGeobodyFolder, false);
	if (pGFolder)
	{
		strGeobodyName = pGFolder->GetUnallocatedName(strGeobodyName);
	}
	ui.lineEditGeobodyName->setText(strGeobodyName);
	ui.lineEditDVName->setText(m_pDV->GetObjectName());

	//	Plane range.
	CXSeismicUTMTool& UTM = m_pDV->GetUTM();
	int iFirstInline, iLastInline, iInlineInc, iFirstXline, iLastXline, iXlineInc;
	UTM.GetLineNumRange(iFirstInline, iLastInline, iInlineInc, iFirstXline, iLastXline, iXlineInc);

    ui.m_lineRangeFrame->AddOneLine("Inline", iFirstInline, iLastInline, iInlineInc);
    ui.m_lineRangeFrame->AddOneLine("Crossline", iFirstXline, iLastXline, iXlineInc);

	//	Z range.
	double dStartTime, dEndTime, dTimeRate;
	double dStartZ, dEndZ;
	m_pDV->GetSamplingRange(dStartTime, dEndTime, dTimeRate);

	dStartZ = dStartTime > ((dStartTime + dEndTime) / 2 - 50 * dTimeRate) ? dStartTime : ((dStartTime + dEndTime) / 2 - 50 * dTimeRate);
	dEndZ = dEndTime < (dStartZ + 100 * dTimeRate) ? dEndTime : (dStartZ + 100 * dTimeRate);

	ui.label_23->setText(QString::number((int)dStartTime));
	ui.label_24->setText(QString::number((int)dStartTime));
	ui.label_22->setText(QString::number((int)dEndTime));
	ui.label_25->setText(QString::number((int)dEndTime));

	ui.lineEditTopTWT->setText(QString::number((int)(dStartZ)));
	ui.lineEditBottomTWT->setText(QString::number((int)(dEndZ)));

	connect(ui.lineEditTopTWT, SIGNAL(editingFinished()), this, SLOT(slotLineEditValueChanged()));
	connect(ui.lineEditBottomTWT, SIGNAL(editingFinished()), this, SLOT(slotLineEditValueChanged()));

	ui.sliderTopTWT->setRange((int)dStartTime, (int)dEndTime);
	ui.sliderTopTWT->setValue((int)(dStartZ));
	ui.sliderTopTWT->setSingleStep((int)dTimeRate);
	ui.sliderBottomTWT->setRange((int)dStartTime, (int)dEndTime);
	ui.sliderBottomTWT->setValue((int)(dEndZ));
	ui.sliderBottomTWT->setSingleStep((int)dTimeRate);

	connect(ui.sliderTopTWT, SIGNAL(valueChanged(int)), this, SLOT(slotSliderValueChanged(int)));
	connect(ui.sliderBottomTWT, SIGNAL(valueChanged(int)), this, SLOT(slotSliderValueChanged(int)));

	//	Threshold.
	double dMin, dMax;
	::GetObjectMinMaxByPercentile(dMin, dMax, 95, 100, m_pDV);
	ui.lineEditLowThreshold->setText(QString::number(dMin));
	ui.lineEditHighThreshold->setText(QString::number(dMax));

	ui.colormapEditor->SetStatic();
	ui.colormapEditor->SetDisplayedObject(m_pDV);
	ui.colormapEditor->SetDisplayedRange(dMin, dMax);
    auto pConsole = reinterpret_cast<CXBaseConsole*>(::GetConsole());
    CXViewInfoObject* pDVViewInfo = pConsole->GetViewInfoForActiveWindow(m_pDV->GetObjectID());
	ui.colormapEditor->SetColormap(pDVViewInfo ? pDVViewInfo->GetColormapName() : "red_white_dkblue");
	ui.colormapEditor->Update();

	connect(ui.pushButtonAddPolygon, SIGNAL(clicked()), this, SLOT(slotPushButtonClicked()));
	connect(ui.pushButtonAddTopHorizon, SIGNAL(clicked()), this, SLOT(slotPushButtonClicked()));
	connect(ui.pushButtonAddBottomHorizon, SIGNAL(clicked()), this, SLOT(slotPushButtonClicked()));
	connect(ui.pushButtonRemovePolygon, SIGNAL(clicked()), this, SLOT(slotPushButtonClicked()));
	connect(ui.pushButtonRemoveTopHorizon, SIGNAL(clicked()), this, SLOT(slotPushButtonClicked()));
	connect(ui.pushButtonRemoveBottomHorizon, SIGNAL(clicked()), this, SLOT(slotPushButtonClicked()));
	connect(ui.radioButtonTopHorizon, SIGNAL(clicked()), this, SLOT(slotRadioButtonClicked()));
	connect(ui.radioButtonTopTWT, SIGNAL(clicked()), this, SLOT(slotRadioButtonClicked()));
	connect(ui.radioButtonBottomHorizon, SIGNAL(clicked()), this, SLOT(slotRadioButtonClicked()));
	connect(ui.radioButtonBottomTWT, SIGNAL(clicked()), this, SLOT(slotRadioButtonClicked()));
	connect(ui.colormapEditor, SIGNAL(DisplayedRangeChanged(double, double)), this, SLOT(slotThresholdRangeChanged(double, double)));
	connect(ui.lineEditLowThreshold, SIGNAL(textChanged(const QString&)), ui.colormapEditor, SLOT(slotDisplayMinChanged(const QString&)));
	connect(ui.lineEditHighThreshold, SIGNAL(textChanged(const QString&)), ui.colormapEditor, SLOT(slotDisplayMaxChanged(const QString&)));
}


void CXDlgDetectGeobody::slotThresholdRangeChanged(double dMin, double dMax)
{
	ui.lineEditLowThreshold->setText(QString::number(dMin));
	ui.lineEditHighThreshold->setText(QString::number(dMax));
}

void CXDlgDetectGeobody::slotLineEditValueChanged()
{
	QLineEdit *pLineEdit = dynamic_cast<QLineEdit *>(sender());
	if (!pLineEdit)
		return;

	pLineEdit->blockSignals(true);

	if (pLineEdit == ui.lineEditTopTWT)
	{
		int iTopTWT = pLineEdit->text().toInt();

		//	Correct the value.
		if (iTopTWT < ui.sliderTopTWT->minimum())
			iTopTWT = ui.sliderTopTWT->minimum();
		if (iTopTWT > ui.sliderTopTWT->maximum())
			iTopTWT = ui.sliderTopTWT->maximum();
		pLineEdit->setText(QString::number(iTopTWT));

		//	Set the value of slider.
		ui.sliderTopTWT->setValue(iTopTWT);
	}
	else if (pLineEdit == ui.lineEditBottomTWT)
	{
		int iBottomTWT = pLineEdit->text().toInt();

		//	Correct the value.
		if (iBottomTWT < ui.sliderBottomTWT->minimum())
			iBottomTWT = ui.sliderBottomTWT->minimum();
		if (iBottomTWT > ui.sliderBottomTWT->maximum())
			iBottomTWT = ui.sliderBottomTWT->maximum();
		pLineEdit->setText(QString::number(iBottomTWT));

		//	Set the value of slider.
		ui.sliderBottomTWT->setValue(iBottomTWT);
	}

	pLineEdit->blockSignals(false);
}

void CXDlgDetectGeobody::slotSliderValueChanged(int iValue)
{
	QSlider *pSlider = dynamic_cast<QSlider *>(sender());
	if (!pSlider)
		return;

	if (pSlider == ui.sliderTopTWT)
	{
		ui.lineEditTopTWT->setText(QString::number(iValue));

		if (iValue > ui.sliderBottomTWT->value())
			ui.sliderBottomTWT->setValue(iValue);
	}
	else if (pSlider == ui.sliderBottomTWT)
	{
		ui.lineEditBottomTWT->setText(QString::number(iValue));

		if (iValue < ui.sliderTopTWT->value())
			ui.sliderTopTWT->setValue(iValue);
	}
}

void CXDlgDetectGeobody::slotPushButtonClicked()
{
	CXObject *pCurObj = ::GetCurrentObject();

	if (sender() == ui.pushButtonAddPolygon)
	{
		if (pCurObj->GetObjectType() != EX2DPolygon)
		{
			QMessageBox::warning(NULL, "Geobody Detection", "Please highlight a polygon first!");
			return;
		}

		ui.lineEditPolygon->setText(pCurObj->GetObjectName());
		m_pPara->SetBoundaryPolygonID(pCurObj->GetObjectID());		
	}
	else if (sender() == ui.pushButtonAddTopHorizon)
	{
		if (pCurObj->GetObjectType() != EX3DHorizon)
		{
			QMessageBox::warning(NULL, "Geobody Detection", "Please highlight a horizon first!");
			return;
		}

		ui.lineEditTopHorizon->setText(pCurObj->GetObjectName());
		m_pPara->SetTopSurfaceID(pCurObj->GetObjectID());
	}
	else if (sender() == ui.pushButtonAddBottomHorizon)
	{
		if (pCurObj->GetObjectType() != EX3DHorizon)
		{
			QMessageBox::warning(NULL, "Geobody Detection", "Please highlight a horizon first!");
			return;
		}

		ui.lineEditBottomHorizon->setText(pCurObj->GetObjectName());
		m_pPara->SetBottomSurfaceID(pCurObj->GetObjectID());
	}
	else if (sender() == ui.pushButtonRemovePolygon)
	{
		ui.lineEditPolygon->clear();
		m_pPara->SetBoundaryPolygonID(QUuid::createUuid());
	}
	else if (sender() == ui.pushButtonRemoveTopHorizon)
	{
		ui.lineEditTopHorizon->clear();
		m_pPara->SetTopSurfaceID(QUuid::createUuid());
	}
	else if (sender() == ui.pushButtonRemoveBottomHorizon)
	{
		ui.lineEditBottomHorizon->clear();
		m_pPara->SetBottomSurfaceID(QUuid::createUuid());
	}
}

void CXDlgDetectGeobody::slotRadioButtonClicked()
{
	if (sender() == ui.radioButtonTopTWT || sender() == ui.radioButtonTopHorizon)
	{
		bool bTWT = ui.radioButtonTopTWT->isChecked();

		ui.lineEditTopTWT->setDisabled(!bTWT);
		ui.sliderTopTWT->setDisabled(!bTWT);
		ui.pushButtonAddTopHorizon->setDisabled(bTWT);
		ui.lineEditTopHorizon->setDisabled(bTWT);
		ui.pushButtonRemoveTopHorizon->setDisabled(bTWT);
	}
	else if (sender() == ui.radioButtonBottomTWT || sender() == ui.radioButtonBottomHorizon)
	{
		bool bTWT = ui.radioButtonBottomTWT->isChecked();

		ui.lineEditBottomTWT->setDisabled(!bTWT);
		ui.sliderBottomTWT->setDisabled(!bTWT);
		ui.pushButtonAddBottomHorizon->setDisabled(bTWT);
		ui.lineEditBottomHorizon->setDisabled(bTWT);
		ui.pushButtonRemoveBottomHorizon->setDisabled(bTWT);
	}
}

void CXDlgDetectGeobody::accept()
{
	if (!m_pDV)
		return;

	//	Populate the parameters.

	m_pPara->SetGeobodyName(ui.lineEditGeobodyName->text());
	m_pPara->SetDVID(m_pDV->GetObjectID());

	m_pPara->SetStartInline(ui.m_lineRangeFrame->GetValueAt(0));
	m_pPara->SetEndInline(ui.m_lineRangeFrame->GetValueAt(1));
	m_pPara->SetStartXline(ui.m_lineRangeFrame->GetValueAt(2));
	m_pPara->SetEndXline(ui.m_lineRangeFrame->GetValueAt(3));

	m_pPara->SetStartZ(ui.sliderTopTWT->value());
	m_pPara->SetEndZ(ui.sliderBottomTWT->value());

	m_pPara->SetLowThreshold(ui.lineEditLowThreshold->text().toFloat());
	m_pPara->SetHighThreshold(ui.lineEditHighThreshold->text().toFloat());

	int iSize = ui.lineEditMinimumSize->text().toInt();
	if (iSize <= 0)
	{
		QMessageBox::warning(0, ::g_strProductName, "Minimum geobody size is invalid!");
		return;
	}
	m_pPara->SetMiniSize(iSize);

	m_pPara->SetFaceConnectivity(ui.radioButtonFaceConnect->isChecked());

	m_pPara->SetMerge(ui.checkBoxSeperate->isChecked());

	QDialog::accept();
}