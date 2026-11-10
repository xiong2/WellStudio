#include "xdlgavocssiadvanced.h"
#include "xparameter3terminversion.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include <QDoubleValidator>


CXDlgAVOCSSIAdvanced::CXDlgAVOCSSIAdvanced(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Advanced Settings for AVO Sparse Spike Inversion");

	m_pPara = dynamic_cast<CXParameter3TermInversion*>(pPara);
	assert(m_pPara);

	m_ui.m_pLineEdtPAlpha->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtSAlpha->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtDAlpha->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtPSigma->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtSSigma->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtDSigma->setValidator(new QDoubleValidator(this));		

	_Init();
	_InitAngle();
}

CXDlgAVOCSSIAdvanced::~CXDlgAVOCSSIAdvanced()
{
}

void CXDlgAVOCSSIAdvanced::_Init()
{
	std::vector<float> vecAlpha = m_pPara->GetvecAlpha();
	std::vector<float> vecSigma = m_pPara->GetvecSigma();

	if (vecAlpha.empty())
	{
		m_ui.m_pLineEdtPAlpha->setText(QString::number(m_pPara->GetAlpha(), 'f', 2));
		m_ui.m_pLineEdtSAlpha->setText(QString::number(m_pPara->GetAlpha(), 'f', 2));
		m_ui.m_pLineEdtDAlpha->setText(QString::number(m_pPara->GetAlpha(), 'f', 2));
	}
	else
	{
		m_ui.m_pLineEdtPAlpha->setText(QString::number(vecAlpha[0], 'f', 2));
		m_ui.m_pLineEdtSAlpha->setText(QString::number(vecAlpha[1], 'f', 2));
		m_ui.m_pLineEdtDAlpha->setText(QString::number(vecAlpha[2], 'f', 2));
	}

	if (vecSigma.empty())
	{		
		m_ui.m_pLineEdtPSigma->setText(QString::number(m_pPara->GetSigma(), 'f', 2));
		m_ui.m_pLineEdtSSigma->setText(QString::number(m_pPara->GetSigma(), 'f', 2));
		m_ui.m_pLineEdtDSigma->setText(QString::number(m_pPara->GetSigma(), 'f', 2));
	}
	else
	{
		m_ui.m_pLineEdtPSigma->setText(QString::number(vecSigma[0], 'f', 2));
		m_ui.m_pLineEdtSSigma->setText(QString::number(vecSigma[1], 'f', 2));
		m_ui.m_pLineEdtDSigma->setText(QString::number(vecSigma[2], 'f', 2));

	}
}

void CXDlgAVOCSSIAdvanced::_InitAngle()
{
	std::vector<float> vecAngle = m_pPara->GetVecAngleValue();
	std::vector<float> vecWaveletScale = m_pPara->GetvecWaveletScale();
	std::vector<float> vecLambda = m_pPara->GetvecLambda();

	m_ui.m_pTable->setRowCount(vecAngle.size());
	for (int i = 0; i < vecAngle.size(); ++i)
	{
		// angle
		QTableWidgetItem* pAngleItem = new QTableWidgetItem;
		pAngleItem->setText(QString::number(vecAngle[i], 'f', 1));
		pAngleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 0, pAngleItem);

		// Lambda
		float fLambda = m_pPara->GetLambda();
		if (!vecLambda.empty())
			fLambda = vecLambda[i];

		QTableWidgetItem* pLambdaItem = new QTableWidgetItem;
		pLambdaItem->setText(QString::number(fLambda, 'f', 2));
		pLambdaItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		m_ui.m_pTable->setItem(i, 1, pLambdaItem);

		// wavelet scale
		float fScale = 1.f;
		if (!vecWaveletScale.empty())
			fScale = vecWaveletScale[i];

		QTableWidgetItem* pScaleItem = new QTableWidgetItem;
		pScaleItem->setText(QString::number(fScale, 'f', 2));
		pScaleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		m_ui.m_pTable->setItem(i, 2, pScaleItem);
	}


}

void CXDlgAVOCSSIAdvanced::accept()
{
	std::vector<float> vecAlpha, vecSigma;

	vecAlpha.push_back(m_ui.m_pLineEdtPAlpha->text().toFloat());
	vecAlpha.push_back(m_ui.m_pLineEdtSAlpha->text().toFloat());
	vecAlpha.push_back(m_ui.m_pLineEdtDAlpha->text().toFloat());

	vecSigma.push_back(m_ui.m_pLineEdtPSigma->text().toFloat());
	vecSigma.push_back(m_ui.m_pLineEdtSSigma->text().toFloat());
	vecSigma.push_back(m_ui.m_pLineEdtDSigma->text().toFloat());

	m_pPara->SetvecAlpha(vecAlpha);
	m_pPara->SetvecSigma(vecSigma);

	// angle
	std::vector<float> vecLambda, vecScale;
	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		vecLambda.push_back(m_ui.m_pTable->item(i, 1)->text().toFloat());
		vecScale.push_back(m_ui.m_pTable->item(i, 2)->text().toFloat());
	}

	m_pPara->SetvecLambda(vecLambda);
	m_pPara->SetvecWaveletScale(vecScale);

	QDialog::accept();
}


