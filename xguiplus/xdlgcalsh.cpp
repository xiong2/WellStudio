#include <qmessagebox.h>
#include "xdlgcalsh.h"
#include "x3dhorizon.h"
#include "xseismicdatavolume.h"
#include "xregulardatawriter.h"
#include "xalgorithmutility.h"
#include "xglobal.h"
#include "xprogressbar.h"

XDlgCalSH::XDlgCalSH(CXObject *pFolder, QWidget *parent) : QDialog(parent), m_pParent(pFolder)
{
	ui.setupUi(this);

	initUI();
}

XDlgCalSH::~XDlgCalSH()
{

}

void XDlgCalSH::initUI()
{
	QStringList sListDV;
	EXObjectType eObjType;
	if (m_pParent->GetObjectType() == EXSeismicDVFolder)
		eObjType = EXSeismicDataVolume;
	else
	{
		eObjType = EX3DHorizon;
		ui.label_10->setText("Output ¦ÒH horizon");
		ui.label_11->setText("Output ¦Òh horizon");
		ui.lineEditSHDV->setText("SH Hor");
		ui.lineEditShDV->setText("Sh Hor");
	}

	QList<CXObject *> listDV = m_pParent->GetChildren(eObjType, true);
	foreach(CXObject *pDV, listDV)
		sListDV << pDV->GetObjectName();

	ui.comboBoxBiot->clear();
	ui.comboBoxNiu->clear();
	ui.comboBoxE->clear();
	ui.comboBoxPp->clear();
	ui.comboBoxSv->clear();

	ui.comboBoxBiot->addItems(sListDV);
	ui.comboBoxNiu->addItems(sListDV);
	ui.comboBoxE->addItems(sListDV);
	ui.comboBoxPp->addItems(sListDV);
	ui.comboBoxSv->addItems(sListDV);
}

void XDlgCalSH::accept()
{
	float fSH = ui.lineEditSH->text().toFloat();
	float fSh = ui.lineEditSh->text().toFloat();

	int iDataSize;
	float *pSHData, *pShData, *pBData, *pNData, *pEData, *pPpData, *pSvData; 
	if (m_pParent->GetObjectType() == EXSeismicDVFolder)
	{
		QList<CXObject *> listAllDV = m_pParent->GetChildren(EXSeismicDataVolume);
		CXSeismicDataVolume *pBDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBoxBiot->currentIndex()));
		CXSeismicDataVolume *pNDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBoxNiu->currentIndex()));
		CXSeismicDataVolume *pEDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBoxE->currentIndex()));
		CXSeismicDataVolume *pPpDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBoxPp->currentIndex()));
		CXSeismicDataVolume *pSvDV = (CXSeismicDataVolume *)(listAllDV.at(ui.comboBoxSv->currentIndex()));

		//	Make sure all 3 volumes the same size.
		QList<CXObject *> listSameSizeDV;
		pBDV->GetAllDVWithSameSize(listSameSizeDV);

		if (!listSameSizeDV.contains(listAllDV.at(ui.comboBoxNiu->currentIndex()))
			|| !listSameSizeDV.contains(listAllDV.at(ui.comboBoxE->currentIndex()))
			|| !listSameSizeDV.contains(listAllDV.at(ui.comboBoxPp->currentIndex()))
			|| !listSameSizeDV.contains(listAllDV.at(ui.comboBoxSv->currentIndex())))
		{
			QMessageBox::warning(NULL, "Horizontal Stresses", "The input 5 volumes must have the same size!");
			return;
		}

		double dStartZ, dEndZ, dZStep;
		pBDV->GetSamplingRange(dStartZ, dEndZ, dZStep);
		int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
		pBDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
		iDataSize = pBDV->GetXlineTraceQty() * pBDV->GetSamplingQty();
		pSHData = new float[iDataSize];
		pShData = new float[iDataSize];
		pBData = new float[iDataSize];
		pNData = new float[iDataSize];
		pEData = new float[iDataSize];
		pPpData = new float[iDataSize];
		pSvData = new float[iDataSize];

		QString SName = m_pParent->GetUnallocatedName(ui.lineEditSHDV->text());
		CXSeismicDataVolume *pSHDV = new CXSeismicDataVolume(pBDV->GetUTM(), dStartZ, dEndZ, dZStep, SName);
		CXRegularDataWriter<float> *pWriterSH = new CXRegularDataWriter<float>(pSHDV->GetTraceFileName(), pSHDV->GetInlineQty(), pSHDV->GetXlineTraceQty(), pSHDV->GetSamplingQty());
		pWriterSH->Open();
		SName = m_pParent->GetUnallocatedName(ui.lineEditShDV->text());
		CXSeismicDataVolume *pShDV = new CXSeismicDataVolume(pBDV->GetUTM(), dStartZ, dEndZ, dZStep, SName);
		CXRegularDataWriter<float> *pWriterSh = new CXRegularDataWriter<float>(pShDV->GetTraceFileName(), pShDV->GetInlineQty(), pShDV->GetXlineTraceQty(), pShDV->GetSamplingQty());
		pWriterSh->Open();

		CXProgressBar progress("Caculating Biot Volume", "Calculating... ", pBDV->GetUTM().GetNI());

		int i, j, iCount = 0;
		for (i = iInlineMin; i <= iInlineMax; i += iInlineInc)
		{
			progress.SetValue(iCount);
			iCount++;

			pBDV->ReadInline(i, pBData);
			pNDV->ReadInline(i, pNData);
			pEDV->ReadInline(i, pEData);
			pPpDV->ReadInline(i, pPpData);
			pSvDV->ReadInline(i, pSvData);

			for (j = 0; j < iDataSize; j++)
			{
				if (pNData[j] == g_dInvalidData || pSvData[j] == g_dInvalidData
					|| pPpData[j] == g_dInvalidData || pBData[j] == g_dInvalidData || pEData[j] == g_dInvalidData)
				{
					pShData[j] = g_dInvalidData;
					pSHData[j] = g_dInvalidData;
				}
				else
				{
					pShData[j] = pNData[j] * (pSvData[j] - pBData[j] * pPpData[j]) / (1 - pNData[j])
						+ pEData[j] * fSh / (1 - pNData[j] * pNData[j])
						+ pNData[j] * pEData[j] * fSH / (1 - pNData[j] * pNData[j])
						+ pBData[j] * pPpData[j];

					pSHData[j] = pNData[j] * (pSvData[j] - pBData[j] * pPpData[j]) / (1 - pNData[j])
						+ pEData[j] * fSH / (1 - pNData[j] * pNData[j])
						+ pNData[j] * pEData[j] * fSh / (1 - pNData[j] * pNData[j])
						+ pBData[j] * pPpData[j];
				}
			}

			pWriterSh->Append(iDataSize, pShData);
			pWriterSH->Append(iDataSize, pSHData);
		}

		m_pParent->AddChild(pShDV);
		m_pParent->AddChild(pSHDV);

		CXAlgorithmUtility::CalculateHistogram(pShDV->GetTraceFileName(), pShDV->GetSamplingQty(), pShDV);
		CXAlgorithmUtility::CalculateHistogram(pSHDV->GetTraceFileName(), pSHDV->GetSamplingQty(), pSHDV);

		::AddObjectEvent(pShDV);
		::AddObjectEvent(pSHDV);

		delete pWriterSh;
		delete pWriterSH;
		delete[]pSHData;
		delete[]pShData;
		delete[]pBData;
		delete[]pEData;
		delete[]pNData;
		delete[]pPpData;
		delete[]pSvData;
	}
	else
	{
		QList<CXObject *> listAllHor = m_pParent->GetChildren(EX3DHorizon);
		CX3DHorizon *pBDV = (CX3DHorizon *)(listAllHor.at(ui.comboBoxBiot->currentIndex()));
		CX3DHorizon *pNDV = (CX3DHorizon *)(listAllHor.at(ui.comboBoxNiu->currentIndex()));
		CX3DHorizon *pEDV = (CX3DHorizon *)(listAllHor.at(ui.comboBoxE->currentIndex()));
		CX3DHorizon *pPpDV = (CX3DHorizon *)(listAllHor.at(ui.comboBoxPp->currentIndex()));
		CX3DHorizon *pSvDV = (CX3DHorizon *)(listAllHor.at(ui.comboBoxSv->currentIndex()));

		CXSeismicUTMTool utm = pBDV->GetUTM();
		iDataSize = utm.GetNI() * utm.GetNJ();
		pSHData = new float[iDataSize];
		pShData = new float[iDataSize];
		pBData = pBDV->GetData();
		pNData = pNDV->GetData();
		pEData = pEDV->GetData();
		pPpData = pPpDV->GetData();
		pSvData = pSvDV->GetData();

		for (int i = 0; i < iDataSize; i++)
		{
			if (pNData[i] == g_dInvalidData || pSvData[i] == g_dInvalidData
				|| pPpData[i] == g_dInvalidData || pBData[i] == g_dInvalidData || pEData[i] == g_dInvalidData)
			{
				pShData[i] = g_dInvalidData;
				pSHData[i] = g_dInvalidData;
			}
			else
			{

				pShData[i] = pNData[i] * (pSvData[i] - pBData[i] * pPpData[i]) / (1 - pNData[i])
					+ pEData[i] * fSh / (1 - pNData[i] * pNData[i])
					+ pNData[i] * pEData[i] * fSH / (1 - pNData[i] * pNData[i])
					+ pBData[i] * pPpData[i];

				pSHData[i] = pNData[i] * (pSvData[i] - pBData[i] * pPpData[i]) / (1 - pNData[i])
					+ pEData[i] * fSH / (1 - pNData[i] * pNData[i])
					+ pNData[i] * pEData[i] * fSh / (1 - pNData[i] * pNData[i])
					+ pBData[i] * pPpData[i];
			}
		}

		CX3DHorizon *pSHHor = new CX3DHorizon(pBDV->GetSurveyID(), utm, m_pParent->GetUnallocatedName(ui.lineEditSHDV->text()));
		pSHHor->SetData(pSHData);
		m_pParent->AddChild(pSHHor);

		CX3DHorizon *pShHor = new CX3DHorizon(pBDV->GetSurveyID(), utm, m_pParent->GetUnallocatedName(ui.lineEditShDV->text()));
		pShHor->SetData(pShData);
		m_pParent->AddChild(pShHor);

		::AddObjectEvent(pSHHor);
		::AddObjectEvent(pShHor);
	}

	QDialog::accept();
}