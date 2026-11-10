#include <qmessagebox.h>
#include "xdlgcalbiot.h"
#include "x3dhorizon.h"
#include "xseismicdatavolume.h"
#include "xregulardatawriter.h"
#include "xalgorithmutility.h"
#include "xglobal.h"
#include "xprogressbar.h"

XDlgCalBiot::XDlgCalBiot(CXObject *pObj, QWidget *parent) : QDialog(parent), m_pParent(pObj)
{
	ui.setupUi(this);

	initUI();
}

XDlgCalBiot::~XDlgCalBiot()
{

}

void XDlgCalBiot::initUI()
{
	QStringList sListDV;
	EXObjectType eObjType;
	if (m_pParent->GetObjectType() == EXSeismicDVFolder)
		eObjType = EXSeismicDataVolume;
	else
	{
		eObjType = EX3DHorizon;
		ui.label_2->setText("Ouput horizon(¦Á):");
		ui.lineEditDV->setText("Boit Horizon");
	}

	QList<CXObject *> listDV = m_pParent->GetChildren(eObjType, true);
	foreach(CXObject *pDV, listDV)
		sListDV << pDV->GetObjectName();

	ui.comboBox->clear();
	ui.comboBox_2->clear();
	ui.comboBox_3->clear();

	ui.comboBox->addItems(sListDV);
	ui.comboBox_2->addItems(sListDV);
	ui.comboBox_3->addItems(sListDV);
}

void XDlgCalBiot::accept()
{
	float fP = ui.lineEditP->text().toFloat();
	float fVp = ui.lineEditVp->text().toFloat();
	float fVs = ui.lineEditVs->text().toFloat();
	float *pData, *pPData, *pVpData, *pVsData;

	if (m_pParent->GetObjectType() == EXSeismicDVFolder)
	{
		QList<CXObject *> listAllDV = m_pParent->GetChildren(EXSeismicDataVolume);
		CXSeismicDataVolume *pPDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBox->currentIndex()));
		CXSeismicDataVolume *pVpDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBox_2->currentIndex()));
		CXSeismicDataVolume *pVsDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBox_3->currentIndex()));

		//	Make sure all 3 volumes the same size.
		QList<CXObject *> listSameSizeDV;
		pPDV->GetAllDVWithSameSize(listSameSizeDV);

		if (!listSameSizeDV.contains(listAllDV.at(ui.comboBox_2->currentIndex()))
			|| !listSameSizeDV.contains(listAllDV.at(ui.comboBox_3->currentIndex())))
		{
			QMessageBox::warning(NULL, "Biot Coefficent", "The input 3 volumes must have the same size!");
			return;
		}

		double dStartZ, dEndZ, dZStep;
		pPDV->GetSamplingRange(dStartZ, dEndZ, dZStep);
		int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
		pPDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
		int iDataSize = pPDV->GetXlineTraceQty() * pPDV->GetSamplingQty();
		pData = new float[iDataSize];
		pPData = new float[iDataSize];
		pVpData = new float[iDataSize];
		pVsData = new float[iDataSize];

		QString SName = m_pParent->GetUnallocatedName(ui.lineEditDV->text());
		CXSeismicDataVolume *pOutputDV = new CXSeismicDataVolume(pPDV->GetUTM(), dStartZ, dEndZ, dZStep, SName);
		CXRegularDataWriter<float> *pWriter = new CXRegularDataWriter<float>(pOutputDV->GetTraceFileName(), pOutputDV->GetInlineQty(), pOutputDV->GetXlineTraceQty(), pOutputDV->GetSamplingQty());
		pWriter->Open();

		CXProgressBar progress("Caculating Biot Volume", "Calculating... ", pPDV->GetUTM().GetNI());

		int i, j, iCount = 0;
		for (i = iInlineMin; i <= iInlineMax; i += iInlineInc)
		{
			progress.SetValue(iCount);
			iCount++;

			pPDV->ReadInline(i, pPData);
			pVpDV->ReadInline(i, pVpData);
			pVsDV->ReadInline(i, pVsData);

			for (j = 0; j < iDataSize; j++)
			{
				pData[j] = 1 - pPData[j] / fP * (3 * pVpData[j] * pVpData[j] - 4 * pVsData[j] * pVsData[j]) / (3 * fVp * fVp - 4 * fVs * fVs);
			}

			pWriter->Append(iDataSize, pData);
		}

		CXAlgorithmUtility::CalculateHistogram(pOutputDV->GetTraceFileName(), pOutputDV->GetSamplingQty(), pOutputDV);

		delete pWriter;
		delete[]pPData;
		delete[]pVpData;
		delete[]pVsData;
		delete[]pData;

		m_pParent->AddChild(pOutputDV);
		::AddObjectEvent(pOutputDV);
	}
	else
	{
		QList<CXObject *> listAllHor = m_pParent->GetChildren(EX3DHorizon);
		CX3DHorizon *pPHor = (CX3DHorizon *)(listAllHor.at(ui.comboBox->currentIndex()));
		CX3DHorizon *pVpHOr = (CX3DHorizon *)(listAllHor.at(ui.comboBox_2->currentIndex()));
		CX3DHorizon *pVsHor = (CX3DHorizon *)(listAllHor.at(ui.comboBox_3->currentIndex()));

		CXSeismicUTMTool utm = pPHor->GetUTM();
		int iDataSize = utm.GetNI() * utm.GetNJ();
		pData = new float[iDataSize];
		pPData = pPHor->GetData();
		pVpData = pVpHOr->GetData();
		pVsData = pVsHor->GetData();

		for (int i = 0; i < iDataSize; i++)
		{
			pData[i] = 1 - pPData[i] / fP * (3 * pVpData[i] * pVpData[i] - 4 * pVsData[i] * pVsData[i]) / (3 * fVp * fVp - 4 * fVs * fVs);
		}

		CX3DHorizon *pNewHor = new CX3DHorizon(pPHor->GetSurveyID(), utm, m_pParent->GetUnallocatedName(ui.lineEditDV->text()));
		pNewHor->SetData(pData);
		m_pParent->AddChild(pNewHor);

		::AddObjectEvent(pNewHor);
	}

	QDialog::accept();
}