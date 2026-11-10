#include "xdlglfminterpolation.h"
#include "xparameterlfminterpolation.h"
#include "xlfmgeometry.h"
#include "xlfmupscalingattribute.h"
#include "xlfmupscalinggeometry.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include <QDoubleValidator>
#include <QIntValidator>


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgLFMInterpolation)
ELFMInterpolation
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgLFMInterpolation)

CXDlgLFMInterpolation::CXDlgLFMInterpolation(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	m_pPara = dynamic_cast<CXParameterLFMInterpolation*>(pPara);

	CXLFMUpscalingAttribute* pAttribute = dynamic_cast<CXLFMUpscalingAttribute*>(pParentObj);
	assert(pAttribute);

	m_pLFM = pAttribute->GetUpscalingGeometry()->GetLFMGeometry();
	assert(m_pLFM && m_pPara);

	_Init();

	m_ui.m_pSill->setValidator(new QDoubleValidator(this));
	m_ui.m_pNugget->setValidator(new QDoubleValidator(this));
	m_ui.m_pMajorRange->setValidator(new QDoubleValidator(this));
	m_ui.m_pMinorRange->setValidator(new QDoubleValidator(this));
	m_ui.m_pAzimuth->setValidator(new QDoubleValidator(this));
	m_ui.m_pKMaximumSampleNumber->setValidator(new QIntValidator(this));

	m_ui.m_pSearchRadius->setValidator(new QDoubleValidator(this));
	m_ui.m_pPower->setValidator(new QDoubleValidator(this));
	m_ui.m_pIDPMaximumSampleNumber->setValidator(new QIntValidator(this));

	//	Connections
	connect(m_ui.m_pCombMethod, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMethod(int)));

	connect(m_ui.m_pPower, SIGNAL(editingFinished()), this, SLOT(slotPower()));
	connect(m_ui.m_pIDPMaximumSampleNumber, SIGNAL(editingFinished()), this, SLOT(slotSampleNum()));
	connect(m_ui.m_pSearchRadius, SIGNAL(editingFinished()), this, SLOT(slotRadius()));
		
	connect(m_ui.m_pSill, SIGNAL(editingFinished()), this, SLOT(slotSill()));
	connect(m_ui.m_pNugget, SIGNAL(editingFinished()), this, SLOT(slotNugget()));
	connect(m_ui.m_pMajorRange, SIGNAL(editingFinished()), this, SLOT(slotMajorRange()));
	connect(m_ui.m_pMinorRange, SIGNAL(editingFinished()), this, SLOT(slotMinorRange()));
	connect(m_ui.m_pAzimuth, SIGNAL(editingFinished()), this, SLOT(slotAzimuth()));
	connect(m_ui.m_pKMaximumSampleNumber, SIGNAL(editingFinished()), this, SLOT(slotSampleNum()));
}

CXDlgLFMInterpolation::~CXDlgLFMInterpolation()
{

}

void CXDlgLFMInterpolation::_Init()
{
	int nI = m_pLFM->GetUTM().GetNI();
	int nJ = m_pLFM->GetUTM().GetNJ();
	double x0, y0, x1, y1;
	m_pLFM->GetUTM().IJToXY(0, 0, x0, y0);
	m_pLFM->GetUTM().IJToXY(nI - 1, nJ - 1, x1, y1);
	double dSqure = (x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0);

	double dRadius = sqrt(qMax(dSqure, 0.));
	m_pPara->SetRadius(dRadius);
	m_pPara->SetMaxRange(dRadius);
	m_pPara->SetMinRange(dRadius);

	slotMethod(m_pPara->GetAlgorithmType());
}

void CXDlgLFMInterpolation::slotMethod(int index)
{
	if (index < 0)
		return;

	bool b = CXParameterLFMInterpolation::eInverseDistance == index;
	m_ui.m_pGroupIDP->setVisible(b);
	m_ui.m_pLabelVariogram->setVisible(!b);
	m_ui.m_pCombVariogram->setVisible(!b);
	m_ui.m_pGroupKriging->setVisible(!b);

	if (b)
	{
		m_ui.m_pPower->setText(QString::number(m_pPara->GetPower(), 'f', 3));
		m_ui.m_pIDPMaximumSampleNumber->setText(QString::number(m_pPara->GetMaxSampleNum()));
		m_ui.m_pSearchRadius->setText(QString::number(m_pPara->GetRadius(), 'f', 2));
	}
	else
	{
		m_ui.m_pSill->setText(QString::number(m_pPara->GetSill(), 'f', 2));
		m_ui.m_pNugget->setText(QString::number(m_pPara->GetNugget(), '4', 4));
		m_ui.m_pMajorRange->setText(QString::number(m_pPara->GetMaxRange(), 'f', 2));
		m_ui.m_pMinorRange->setText(QString::number(m_pPara->GetMinRange(), 'f', 2));
		m_ui.m_pAzimuth->setText(QString::number(m_pPara->GetAzimuth(), 'f', 2));
		m_ui.m_pKMaximumSampleNumber->setText(QString::number(m_pPara->GetMaxSampleNum()));
	}

	m_pPara->SetAlgorithmType(index);
}

void CXDlgLFMInterpolation::slotPower()
{
	bool b;
	double dPower = m_ui.m_pPower->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, ::g_strProductName, "Please enter a number.");
		m_ui.m_pPower->undo();
		m_ui.m_pPower->setFocus();
		return;
	}
	if (dPower <= 0.0 || dPower > 2.0)
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number between 0 and 2.");
		m_ui.m_pPower->undo();
		m_ui.m_pPower->setFocus();
		return;
	}

	m_pPara->SetPower(dPower);
}

void CXDlgLFMInterpolation::slotSampleNum()
{
	QObject* pObj = QObject::sender();
	QLineEdit* pLineEdt = dynamic_cast<QLineEdit*>(pObj);
	if (!pLineEdt)
		return;

	bool b;
	int nNum = pLineEdt->text().toInt(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		pLineEdt->undo();
		pLineEdt->setFocus();
		return;
	}
	if (nNum <= 0 || nNum > 30)
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number between 0 and 30.");
		pLineEdt->undo();
		pLineEdt->setFocus();
		return;
	}

	m_pPara->SetMaxSampleNum(nNum);
}

void CXDlgLFMInterpolation::slotRadius()
{
	bool b;
	double dValue = m_ui.m_pSearchRadius->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		m_ui.m_pSearchRadius->undo();
		m_ui.m_pSearchRadius->setFocus();
		return;
	}
	if (dValue <= 0.0)
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number greater than zero.");
		m_ui.m_pSearchRadius->undo();
		m_ui.m_pSearchRadius->setFocus();
		return;
	}

	m_pPara->SetRadius(dValue);
}


void CXDlgLFMInterpolation::slotSill()
{
	bool b;
	double dValue = m_ui.m_pSill->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		m_ui.m_pSill->undo();
		m_ui.m_pSill->setFocus();
		return;
	}
	if (dValue <= 0.0)
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number greater than zero.");
		m_ui.m_pSill->undo();
		m_ui.m_pSill->setFocus();
		return;
	}

	m_pPara->SetSill(dValue);
}

void CXDlgLFMInterpolation::slotNugget()
{
	bool b;
	double dValue = m_ui.m_pNugget->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		m_ui.m_pNugget->undo();
		m_ui.m_pNugget->setFocus();
		return;
	}
	if (dValue < 0.0)
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number greater than zero.");
		m_ui.m_pNugget->undo();
		m_ui.m_pNugget->setFocus();
		return;
	}

	m_pPara->SetNugget(dValue);
}

void CXDlgLFMInterpolation::slotMajorRange()
{
	bool b;
	double dValue = m_ui.m_pMajorRange->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		m_ui.m_pMajorRange->undo();
		m_ui.m_pMajorRange->setFocus();
		return;
	}
	if (dValue < m_pPara->GetMinRange())
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number not less than than the range along the minor direction.");
		m_ui.m_pMajorRange->undo();
		m_ui.m_pMajorRange->setFocus();
		return;
	}

	m_pPara->SetMaxRange(dValue);
}

void CXDlgLFMInterpolation::slotMinorRange()
{
	bool b;
	double dValue = m_ui.m_pMinorRange->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		m_ui.m_pMinorRange->undo();
		m_ui.m_pMinorRange->setFocus();
		return;
	}
	if (dValue > m_pPara->GetMaxRange())
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number not greater than than the range along the major direction.");
		m_ui.m_pMinorRange->undo();
		m_ui.m_pMinorRange->setFocus();
		return;
	}

	m_pPara->SetMinRange(dValue);
}

void CXDlgLFMInterpolation::slotAzimuth()
{
	bool b;
	double dValue = m_ui.m_pAzimuth->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, g_strProductName, "Please enter a number.");
		m_ui.m_pAzimuth->undo();
		m_ui.m_pAzimuth->setFocus();
		return;
	}
	if (dValue < 0. || dValue > 360.)
	{
		QMessageBox::warning(0, g_strProductName, "Please select a number between 0 and 360.");
		m_ui.m_pAzimuth->undo();
		m_ui.m_pAzimuth->setFocus();
		return;
	}

	m_pPara->SetAzimuth(dValue);
}


void CXDlgLFMInterpolation::accept()
{
	m_pPara->SetVariogramType(m_ui.m_pCombVariogram->currentIndex());

	QDialog::accept();
}