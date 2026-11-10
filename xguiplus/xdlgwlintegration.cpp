#include <cmath>
#include "xdlgwlintegration.h"
#include "xglobal.h"
#include "xwellcurve.h"
#include "xwell.h"
#include "xwellpath.h"

XDlgWLIntegration::XDlgWLIntegration(CXObject * pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QString sCurveName = "OBPressure";
	sCurveName = pObj->GetParent()->GetUnallocatedName(sCurveName);
	ui.lineEditCurve->setText(sCurveName);

	m_pDenCurve = dynamic_cast<CXWellCurve *>(pObj);
}

XDlgWLIntegration::~XDlgWLIntegration()
{

}

void XDlgWLIntegration::accept()
{
	CXWell *pWell = (CXWell *)(m_pDenCurve->GetParent());
	CXWellPath *pWellPath = pWell->GetWellPath();

	double dStart, dEnd, dStep;
	m_pDenCurve->GetDepthRange(dStart, dEnd);
	dStep = m_pDenCurve->GetStep();
	int iDataNum = (dEnd - dStart) / dStep + 1;
	double *pData = m_pDenCurve->GetData();
	double *pBuff = new double[iDataNum];

	double p0 = ui.lineEditP0->text().toDouble();
	double dA = ui.lineEditA->text().toDouble();
	double dB = ui.lineEditB->text().toDouble();

	double dDeltaZ, dZ = pWellPath->Md2Tvd(dStart);
	pBuff[0] = p0 + dA * powl(dZ, dB);

	dZ = dStart;
	for (int i = 1; i < iDataNum; i++)
	{
		dDeltaZ = pWellPath->Md2Tvd(dZ + dStep) - dZ;

		if (pData[i - 1] != g_dInvalidData)
		{
			pBuff[i] = pBuff[i - 1] + dDeltaZ * 0.0098 * pData[i - 1];
		}
		else
		{
			pBuff[i] = pBuff[i - 1] + dDeltaZ * 0.0098 * 2.3;
		}

		dZ += dStep;
	}

	QString sName = pWell->GetUnallocatedName(ui.lineEditCurve->text());
	
	CXWellCurve *pCurve = new CXWellCurve(sName);
	pCurve->ResetData(dStart, dStep, iDataNum, pBuff);
	pWell->AddChild(pCurve);

	::AddObjectEvent(pCurve);

	QDialog::accept();
}