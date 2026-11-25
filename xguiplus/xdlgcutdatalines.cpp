#include <qmessagebox.h>
#include <qvalidator.h>
#include "xdlgcutdatalines.h"
#include "x2dsurvey.h"
#include "xseismicdataline.h"
#include "xprogressbar.h"
#include "xalgorithmutility.h"

XDlgCutDataLines::XDlgCutDataLines(CXObject *pSurvey, QWidget *parent)
	: m_pSurvey((CX2DSurvey *)pSurvey), QDialog(parent)
{
	ui.setupUi(this);

	initGUI();
}

XDlgCutDataLines::~XDlgCutDataLines()
{
}

void XDlgCutDataLines::initGUI()
{
	ui.lineEditNSZ->setValidator(new QDoubleValidator);
	ui.lineEditNEZ->setValidator(new QDoubleValidator);
	ui.lineEditEng->setValidator(new QDoubleValidator);

	double dSZ, dEZ, dStep;
	double dSZMax = -999., dEZMin = 9999., dStepMax = -999.;
	QList<CXObject *> listObj = m_pSurvey->GetChildren(EXSeismicDataLine, true);
	for (CXObject *pObj : listObj)
	{
		CXSeismicDataLine* pLine = dynamic_cast<CXSeismicDataLine *>(pObj);
		if (!pLine)
			continue;

		pLine->GetSamplingRange(dSZ, dEZ, dStep);
		dSZMax = dSZMax > dSZ ? dSZMax : dSZ;
		dEZMin = dEZMin < dEZ ? dEZMin : dEZ;
		dStepMax = dStepMax > dStep ? dStepMax : dStep;
	}

	ui.lineEditSZ->setText(QString::number(dSZMax));
	ui.lineEditNSZ->setText(QString::number(dSZMax));
	ui.lineEditEZ->setText(QString::number(dEZMin));
	ui.lineEditNEZ->setText(QString::number(dEZMin));
	ui.lineEditIntv->setText(QString::number(dStepMax));

	ui.doubleSpinBox->setValue(dStepMax);
	ui.doubleSpinBox->setSingleStep(dStepMax);
	ui.doubleSpinBox->setRange(dStepMax, 4 * dStepMax);
}

void XDlgCutDataLines::accept()
{
	double dSZ = ui.lineEditSZ->text().toDouble();
	double dNSZ = ui.lineEditNSZ->text().toDouble();
	if (dNSZ < dSZ)
	{
		QMessageBox::warning(this, u8"整理二维测线", u8"新的起始时间不能小于最大起始时间！");
		return;
	}

	double dEZ = ui.lineEditEZ->text().toDouble();
	double dNEZ = ui.lineEditNEZ->text().toDouble();
	if (dNEZ > dEZ)
	{
		QMessageBox::warning(this, u8"整理二维测线", u8"新的终止时间不能大于最小终止时间！");
		return;
	}

	float dEng = ui.lineEditEng->text().toFloat();
	if (dEng < 0.0000001 || dEng > 1000000)
	{
		QMessageBox::warning(this, u8"整理二维测线", u8"能量因子超出合理范围！");
		return;
	}

	QDialog::accept();

	int nK = (dNEZ - dNSZ) / ui.doubleSpinBox->value() + 1;
	QList<CXObject *> listObj = m_pSurvey->GetChildren(EXSeismicDataLine, true);
	for (CXObject *pObj : listObj)
	{
		CXSeismicDataLine* pLine = dynamic_cast<CXSeismicDataLine *>(pObj);
		if (!pLine)
			continue;

		pLine->ResetLine(dNSZ, dNEZ, ui.doubleSpinBox->value(), dEng);
		CXAlgorithmUtility::CalculateHistogram(pLine->GetDataFileName(), nK, pLine);
	}
}