#include <qfile.h>
#include "xthreadmergedv.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"

XThreadMergeDV::XThreadMergeDV(CXParameterMergeDV *pPara) : m_pPara(pPara)
{

}

void XThreadMergeDV::RunThread()
{
	QString strWindowName = QString::fromUtf8(u8"合并数据体");
	EmitSetWindowName(strWindowName);
	EmitStartComputing();

	EmitSetTaskName(QString::fromUtf8(u8"合并数据体"));
	EmitResetProgressBar();
	cal();
}

void XThreadMergeDV::cal()
{
	int i, j, m, n;
	int iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc, iNumSample;
	double dZS, dZE, dZInc;
	CXSeismicDataVolume *pBDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(m_pPara->GetBaseDV()));
	CXSeismicUTMTool utm = pBDV->GetUTM();
	utm.GetLineNumRange(iInlineS, iInlineE, iInlineInc, iXlineS, iXlineE, iXlineInc);
	pBDV->GetSamplingRange(dZS, dZE, dZInc);
	iNumSample = pBDV->GetSamplingQty();

	CXSeismicDataVolume *pNewDV = new CXSeismicDataVolume(utm, dZS, dZE, dZInc, m_pPara->GetNewDVName());
	QFile qFile(pNewDV->GetTraceFileName());
	if (!qFile.open(QIODevice::WriteOnly))
	{
		EmitGeneralErrorMsg(QString("Unable to write output RC file!"));
		return;
	}
	QVector<float *> vecBuff;
	QVector< CXSeismicDataVolume *> vecDV;
	QVector<float> vecW;

	double dSZS, dSZE;
	std::vector<QUuid> vecUID = m_pPara->GetVecSubDV();
	std::vector<float> vecWei = m_pPara->GetVecWeight();
	for (i = 0; i < vecUID.size(); i++)
	{
		CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(vecUID[i]));
		CXSeismicUTMTool utm2 = pDV->GetUTM();
		int iSXlineS = utm2.GetFirstCrossline();
		int iSXlineE = utm2.GetLastCrossline();
		pDV->GetSamplingRange(dSZS, dSZE, dZInc);

		int iNumT = (qMin(iXlineE, iSXlineE) - qMax(iXlineS, iSXlineS) + 1);
		int iNumZ = ((qMin(dZE, dSZE) - qMax(dZS, dSZS)) / dZInc + 1);

		if (iNumT > 0 && iNumZ > 0)
		{
			vecDV << pDV;
			float *pBuff = new float[iNumT * iNumZ];
			vecBuff << pBuff;
			vecW << vecWei[i];
		}
	}

	int nCurrentPer, nPercent = 0, iCurrentStep = 0;
	float *pBuff = new float[utm.GetNJ() * iNumSample];
	for (i = iInlineS; i <= iInlineE; i += iInlineInc)
	{
		// Progress bar
		nCurrentPer = static_cast<int>((++iCurrentStep) * 100 / utm.GetNI());
		if (nCurrentPer > nPercent)
		{
			nPercent++;
			if (IsStopped())
				break;
			else
			{
				EmitUpdateProgress(nPercent, 100);
			}
		}

		pBDV->ReadInline(i, pBuff);
		for (j = 0; j < vecDV.size(); j++)
		{
			CXSeismicUTMTool utm2 = vecDV[j]->GetUTM();
			int iSInlineS = utm2.GetFirstInline();
			int iSInlineE = utm2.GetLastInline();
			if (i < iSInlineS || i > iSInlineE)
				continue;

			int iSXlineS = utm2.GetFirstCrossline();
			int iSXlineE = utm2.GetLastCrossline();
			vecDV[j]->GetSamplingRange(dSZS, dSZE, dZInc);

			int iUS = qMax(iXlineS, iSXlineS);
			int iUE = qMin(iXlineE, iSXlineE);
			double dVS = qMax(dZS, dSZS);
			double dVE = qMin(dZE, dSZE);
			int iHei = (dVE - dVS) / dZInc + 1;

			vecDV[j]->ReadInline(i, iUS, iUE, dVS, dVE, vecBuff[j]);
			int iSize = iHei * ((iUE - iUS) / iXlineInc + 1);
			for (m = 0; m < iSize; m++)
				vecBuff[j][m] *= vecW[j];

			for (m = iUS, n = 0; m <= iUE; m += iXlineInc, n++)
			{
				int iOffset = iNumSample * (m - iXlineS) / iXlineInc;
				iOffset += (dVS - dZS) / dZInc;
				memcpy(pBuff + iOffset, vecBuff[j] + n * iHei, iHei * sizeof(float));
			}
		}
	
		qFile.write((char *)pBuff, 4 * utm.GetNJ() * iNumSample);
	}

	qFile.close();
	pBDV->GetParent()->AddChild(pNewDV);

	::AddObjectEvent(pNewDV);

	delete[]pBuff;
	foreach(float *pBuff, vecBuff)
		delete[]pBuff;
}