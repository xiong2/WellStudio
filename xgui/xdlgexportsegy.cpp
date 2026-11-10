#include <QFileDialog>
#include <qmessagebox.h>
#include <qdatetime.h>
#include <qtablewidget.h>
#include "xsegylineheader.h"
#include "xdlgexportsegy.h"
#include "xseismicdatavolume.h"
#include "xseismicdataline.h"
#include "x2dseismicline.h"
#include "xseismicsection.h"
#include "xglobal.h"
#include "xebcdicdialog.h"
#include "xdataconvertor.h"
#include "xprogressbar.h"

CXDlgExportSEGY::CXDlgExportSEGY(CXObject *pDV, QWidget *parent)
: QDialog(parent)
{
	m_pDV = dynamic_cast<CXSeismicDataVolume *>(pDV);
	m_p2DSection = dynamic_cast<CXSeismicDataLine *>(pDV);

	ui.setupUi(this);

	initUI();
}

CXDlgExportSEGY::~CXDlgExportSEGY()
{

}

void CXDlgExportSEGY::initUI()
{
	if (!m_pDV && !m_p2DSection)
		return;

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(slotEBCDICDialog()));
	connect(ui.pushButtonHeaderSEGY, SIGNAL(clicked()), this, SLOT(slotEBCDICDialog()));
	connect(ui.comboBoxTraceData, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDataTypeChanged(int)));

	if (m_pDV)
	{
		//	Target file.
		QString sFile = ::GetProjectPath() + m_pDV->GetObjectName() + ".sgy";
		ui.lineEditSEGYFile->setText(sFile);
		connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotSelectFile()));

		//	Range.
		int iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc, iNumO;
		double dSZ, dEZ, dZInc;
		float fSO, fEO, fOInc;
		CXSeismicUTMTool& utm = m_pDV->GetUTM();
		utm.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		m_pDV->GetSamplingRange(dSZ, dEZ, dZInc);
		m_pDV->GetOffsetInfo(fSO, fOInc, iNumO);
		fEO = fSO + (iNumO - 1) * fOInc;

		ui.m_rangeFrame->AddOneLine("Inline", iSInline, iEInline, iInlineInc);
		ui.m_rangeFrame->AddOneLine("Crossline", iSXline, iEXline, iXlineInc);
		ui.m_rangeFrame->AddOneLine("Time", qRound(dSZ), qRound(dEZ), qRound(dZInc));
		ui.m_rangeFrame->AddOneLine("Offset", qRound(fSO), qRound(fEO), qRound(fOInc));

		//	Pre or Post
		if (!m_pDV->IsPrestack())
		{
			ui.m_rangeFrame->SetVisible(6, false);
			ui.m_rangeFrame->SetVisible(7, false);
		}

		ui.spinBox->setRange((int)dZInc, (int)(4 * dZInc));
		ui.spinBox->setValue((int)dZInc);
		ui.spinBox->setSingleStep((int)dZInc);
	}
	else
	{
		//	Target file.
		QString sFile = ::GetProjectPath() + m_p2DSection->GetGeometryObject()->GetObjectName() + ".sgy";
		ui.lineEditSEGYFile->setText(sFile);
		connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotSelectFile()));

		ui.tabWidget->removeTab(0);
	}

}

void CXDlgExportSEGY::slotSelectFile()
{
	QString strFilePath = ui.lineEditSEGYFile->text();

	QString strFilter = "SEGY File (*.sgy)";
	QString strExportFile = QFileDialog::getSaveFileName(NULL, "Export Seismic Data to  SEGY File", strFilePath, strFilter);
	if (strExportFile.isEmpty())
	{
		return;
	}

	//	Make sure the file is writable.
	QFile file(strExportFile);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(NULL, "Export to SEGY file", GetTr("Can not open the file to write!"));
		return;
	}

	ui.lineEditSEGYFile->setText(strExportFile);
}

void CXDlgExportSEGY::slotEBCDICDialog()
{
	if (ui.radioButton->isChecked())
	{
		generateEBCDIC();
	}
	else
	{
		QFile fileSEGY;

		fileSEGY.setFileName(ui.lineEditHeaderSEGY->text());
		if (!fileSEGY.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(0, "SEG-Y Trace Header Dump ", "Failed to open the SEG-Y file:" + ui.lineEditHeaderSEGY->text(), 0, 0, 1);
			return;
		}
		fileSEGY.read((char*)m_charReelEBCDIC, 3200);
		EBCDIC_ASCII(m_charReelEBCDIC, 3200);
		fileSEGY.close();
	}

	CXEBCDICDialog *pEBCDICDialog = new CXEBCDICDialog(this);
	pEBCDICDialog->setWindowTitle("SEG-Y File EBCDIC Information");
	pEBCDICDialog->SetEBCDIC(m_charReelEBCDIC);
	pEBCDICDialog->setModal(false);
	pEBCDICDialog->table->setEditTriggers(QAbstractItemView::DoubleClicked);
	pEBCDICDialog->show();
	if (pEBCDICDialog->exec() == QDialog::Accepted)
	{
		memcpy(m_charReelEBCDIC, pEBCDICDialog->m_pReelEBCDIC, 3200);
	}
}

void CXDlgExportSEGY::generateEBCDIC()
{
	QStringList strList;
	int i, j, soffset, eoffset;

	if (m_pDV)
	{
		int sline	= ui.m_rangeFrame->GetValueAt(0);
		int eline	= ui.m_rangeFrame->GetValueAt(1);
		int scdp	= ui.m_rangeFrame->GetValueAt(2);
		int ecdp	= ui.m_rangeFrame->GetValueAt(3);
		int stime	= ui.m_rangeFrame->GetValueAt(4);
		int etime	= ui.m_rangeFrame->GetValueAt(5);

		bool bPrestack = m_pDV->IsPrestack();
		QString sPre = "Poststack";
		if (bPrestack)
		{
			soffset = ui.m_rangeFrame->GetValueAt(6);
			eoffset = ui.m_rangeFrame->GetValueAt(7);
			sPre = "Prestack";
		}

		double xmin, xmax, ymin, ymax;
		double x1, y1, x2, y2, x3, y3, x4, y4;
		CXSeismicUTMTool& utm = m_pDV->GetUTM();
		utm.LineToXY(sline, scdp, x1, y1);
		utm.LineToXY(sline, ecdp, x2, y2);
		utm.LineToXY(eline, scdp, x3, y3);
		utm.LineToXY(eline, ecdp, x4, y4);

		xmin = qMin(x1, x2);
		xmin = qMin(xmin, x3);
		xmin = qMin(xmin, x4);

		ymin = qMin(y1, y2);
		ymin = qMin(ymin, y3);
		ymin = qMin(ymin, y4);

		xmax = qMax(x1, x2);
		xmax = qMax(xmax, x3);
		xmax = qMax(xmax, x4);

		ymax = qMax(y1, y2);
		ymax = qMax(ymax, y3);
		ymax = qMax(ymax, y4);

		strList << "C 1 3-D " + sPre + " SEGY output from XStudio " + QDateTime::currentDateTime().toString(Qt::ISODate)
			<< "C 2 Data Volume Name: " + m_pDV->GetObjectName()
			<< "C 3 Inline from " + QString::number(sline) + " to " + QString::number(eline)
			<< "C 4 Crossline from " + QString::number(scdp) + " to " + QString::number(ecdp)
			<< "C 5 X minimum: " + QString::number(xmin) + " maximum: " + QString::number(xmax)
			<< "C 6 Y minimum: " + QString::number(ymin) + " maximum: " + QString::number(ymax)
			<< "C 7 Time from " + QString::number(stime) + " to " + QString::number(etime)
			<< "C 8 Inline number: bytes 9-12"
			<< "C 9 Crossline number: bytes 21-24";

		i = 10;
		if (bPrestack)
		{
			strList << "C " + QString::number(i++) + " Offset number: bytes 25-28";
		}
	}
	else
	{
		strList << "C 1 2-D SEGY output from XStudio " + QDateTime::currentDateTime().toString(Qt::ISODate)
			<< "C 2 Line Name: " + m_p2DSection->GetGeometryObject()->GetObjectName();
		i = 3;
	}

	strList << "C " + QString::number(i++) + " X coordinate: bytes 73-76";
	strList << "C " + QString::number(i++) + " Y coordinate: bytes 77-80";
	strList << "C " + QString::number(i++) + " Sample interval: bytes 117-118";
	strList << "C " + QString::number(i++) + " Number of samples per trace: bytes 115-116";

	QString str = "C " + QString::number(i++) + " Trace data format: " + ui.comboBoxTraceData->currentText();
	if (ui.checkBoxFlipLH->isChecked())
		str += " need flip";
	else
		str += " need not flip";
	strList << str;

	for (j = i; j < 40; j++)
		strList << "C " + QString::number(j);

	strList << "C 40 END EBCDIC";

	memset(m_charReelEBCDIC, 0, 3200);

	for (i = 0; i < 40; i++)
	{
		char *pBuff = m_charReelEBCDIC + i * 80;
		str = strList.at(i);
		QChar *pData = str.data();
		int j = 0;
		while (!pData->isNull())
		{
			pBuff[j] = pData->toLatin1();
			j++;
			pData++;
		}
	}
}

void CXDlgExportSEGY::slotSelectCopyFile()
{
	QString sInitDir = ::GetProjectPath();

	QString sInitName = sInitDir + "/exported.segy";

	QString strCopyedFile = QFileDialog::getOpenFileName(NULL, "Select one file to copy", sInitDir, "SEG-Y files (*.sgy;*.segy)");
	if (strCopyedFile.isEmpty())
	{
		return;
	}
	ui.lineEditHeaderSEGY->setText(strCopyedFile);
}

void CXDlgExportSEGY::accept()
{
	//	The target file.
	QFile qFile(ui.lineEditSEGYFile->text());
	if (!qFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(0, "Warning", "The target SEGY file " + qFile.fileName() + " can not be opened to write!");
		return;
	}

	// Now generate the 3200 volume header.
	if (ui.radioButton->isChecked())
	{
		generateEBCDIC();
	}
	else
	{
		QFile fileSEGY;

		fileSEGY.setFileName(ui.lineEditHeaderSEGY->text());
		if (!fileSEGY.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(0, "SEG-Y Trace Header Dump ", "Failed to open the 3-D SEG-Y file:" + ui.lineEditHeaderSEGY->text(), 0, 0, 1);
			return;
		}
		fileSEGY.read((char*)m_charReelEBCDIC, 3200);
		EBCDIC_ASCII(m_charReelEBCDIC, 3200);
		fileSEGY.close();
	}

	//	Convert it to EBCDIC and write into file.
	ASCII_EBCDIC((char*)m_charReelEBCDIC, 3200);
	qFile.write((char*)m_charReelEBCDIC, 3200);

	//	Now prepare the line header.
	CXSEGYLineHeader lineHeader(true);

	bool bZeroInvalid = ui.checkBoxNanValue->isChecked();

	if (m_pDV)
	{
		//	Write sample interval.
		int iSampleInt = ui.spinBox->value() * 1000;
		lineHeader.WriteSampleInterval(iSampleInt);

		//	Write sample number.
		int iSZ = ui.m_rangeFrame->GetValueAt(4);
		int iEZ = ui.m_rangeFrame->GetValueAt(5);
		int iZInc = ui.spinBox->value();
		int iNumSample = (iEZ - iSZ) / iZInc + 1;
		lineHeader.WriteSampleNumber(iNumSample);

		//	Data Type.
		//	1: 4-byte IBM float;	2: 4-byte integer;	3: 2-byte integer;	4: obsolete;	5: 4-byte IEEE float;	8: 1-byte integer.
		int iDataType = ui.comboBoxTraceData->currentIndex();
		if (iDataType == 0)
			iDataType = 5;
		else if (iDataType == 1)
			iDataType = 1;
		else if (iDataType == 2)
			iDataType = 2;
		else if (iDataType == 3)
			iDataType = 3;
		else if (iDataType == 4)
			iDataType = 8;
		lineHeader.WriteDataType(iDataType);

		//	Write the unit as meter so far.
		lineHeader.WriteUnit(1);

		//	Flip the line header?
		if (ui.checkBoxFlipLH->isChecked())
			lineHeader.FlipBuff();

		//	Write the line header.
		qFile.write(lineHeader.GetLineHeaderBuff(), 400);

		//	Range.
		int iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc, iNumO;
		double dSZ, dEZ, dZInc, dX, dY;
		float fSO, fEO, fOInc;
		CXSeismicUTMTool& utm = m_pDV->GetUTM();
		utm.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		m_pDV->GetSamplingRange(dSZ, dEZ, dZInc);
		m_pDV->GetOffsetInfo(fSO, fOInc, iNumO);
		fEO = fSO + (iNumO - 1) * fOInc;

		//	Prepare the data buff.
		int i, j, k, m, n, iCDP;
		iSXline = ui.m_rangeFrame->GetValueAt(2);
		iEXline = ui.m_rangeFrame->GetValueAt(3);
		int iSouTraceLen = (iEZ - iSZ) / dZInc + 1;
		int iSouCDPNum = (iEXline - iSXline) / iXlineInc + 1;
		int iMaxTraceNum = iSouCDPNum * iNumO;
		int iBuffSize = iSouTraceLen * iMaxTraceNum;
		int iZStep = iSouTraceLen / iNumSample;
		float *pBuff = new float[iBuffSize];
		float *pData = new float[iNumSample];
		float *pTmpData = new float[iNumSample];
		int *pIntData = new int[iNumSample];
		short *pShData = new short[iNumSample];
		char *pChData = new char[iNumSample];
		char *pTH = new char[240];

		double dDataMin, dDataMax, dDataSpan;
		m_pDV->GetDataRange(dDataMin, dDataMax);
		dDataSpan = dDataMax - dDataMin;
		double dShortThre = 32767. / (dDataMax - dDataMin);
		double dcharThre = 255. / (dDataMax - dDataMin);

		SKETraceInfo* pTraceInfo = NULL;
		if (m_pDV->IsIrregular())
			pTraceInfo = new SKETraceInfo[iMaxTraceNum];

		// progress bar
		int iNumLine = (ui.m_rangeFrame->GetValueAt(1) - ui.m_rangeFrame->GetValueAt(0)) / iInlineInc + 1;
		CXProgressBar progress("Export to SEGY file", m_pDV->GetObjectName(), iNumLine);

		//	Loop for each line.
		for (i = ui.m_rangeFrame->GetValueAt(0), n = 0; i <= ui.m_rangeFrame->GetValueAt(1); n++, i += iInlineInc)
		{
			//   Cancel 
			if (progress.IsAborted())
			{
				//	Delete the file!
				qFile.close();
				QFile::remove(qFile.fileName());

				break;
			}

			//progress
			progress.SetValue(n);

			m_pDV->ReadInline(i, iSXline, iEXline, (double)iSZ, (double)iEZ, pBuff, pTraceInfo);

			if (m_pDV->IsIrregular())
			{
				CXSeismicSection section(eInlineSection, i);
				section.SetSectionRange(iSXline, iEXline);
				int iRealTraceNum = m_pDV->GetSectionTraceQty(&section);
				int iLastCDP = -1;
				for (j = 0; j < iRealTraceNum; j++)
				{
					if (iLastCDP != pTraceInfo[j].m_iCDP)
					{
						k = 0;
						iLastCDP = pTraceInfo[j].m_iCDP;
					}
					k++;

					//	Process trace header.
					memset(pTH, 0, 240);
					short *pShort = (short *)(pTH + 104);
					pShort[0] = iSZ;						//	105, Start Z.
					pShort[2] = iSZ;						//	109, Start Z.
					pShort[5] = iNumSample;					//	115, number of samples per trace.
					pShort[6] = iZInc * 1000;				//	117, sample interval.
					int *pInt = (int *)(pTH + 8);
					pInt[0] = i;							//	9, line number.
					pInt[3] = iLastCDP;						//	21, CDP number.
					pInt[4] = k;							//	25, offset index.
					pInt[7] = pTraceInfo[j].m_iOffset;		//	37, offset.
					pInt[16] = (int)pTraceInfo[j].m_dX;		//	73, X.
					pInt[17] = (int)pTraceInfo[j].m_dY;		//	77, Y.
					if (ui.comboBoxCoord->currentIndex() == 1)
					{
						float *pFloat = (float *)(pTH + 72);
						pFloat[0] = pTraceInfo[j].m_dX;		//	73, X.
						pFloat[1] = pTraceInfo[j].m_dY;		//	77, Y.
					}

					if (m_pDV->IsAzimuth())
					{
						pInt[56] = pTraceInfo[j].m_iAzimuth;
					}

					if (ui.checkBoxFlipLH->isChecked())
						flipTH(pTH);

					//	Write the trace header.
					qFile.write(pTH, 240);

					//	Now the trace data.
					if (iZStep == 1)
					{
						memcpy(pData, pBuff + j * iSouTraceLen, iSouTraceLen * 4);
					}
					else
					{
						for (m = 0; m < iNumSample; m++)
							pData[m] = pBuff[j * iSouTraceLen + m * iZStep];
					}

					if (bZeroInvalid)
					{
						for (m = 0; m < iNumSample; m++)
						{
							if (pData[m] == ::g_dInvalidData)
								pData[m] = 0.;
						}
					}

					if (iDataType == 5)
					{
						//	IEEE float
						if (ui.checkBoxFlipTD->isChecked())
							flip((unsigned char *)pData, iNumSample);

						qFile.write((char *)pData, iNumSample * 4);
					}
					else if (iDataType == 1)
					{
						//	IBM float
						IEEEToIBM((int *)pData, (int *)pTmpData, iNumSample);

						//	IBM data always need flip.
						flip((unsigned char *)pTmpData, iNumSample);

						qFile.write((char *)pTmpData, iNumSample * 4);
					}
					else if (iDataType == 2)
					{
						//	int
						for (m = 0; m < iNumSample; m++)
							pIntData[m] = (int)pData[m];

						if (ui.checkBoxFlipTD->isChecked())
							flip((unsigned char *)pIntData, iNumSample);

						qFile.write((char *)pIntData, iNumSample * 4);
					}
					else if (iDataType == 3)
					{
						//	short
						for (m = 0; m < iNumSample; m++)
							pShData[m] = (short)((pData[m] - dDataMin) * dShortThre);

						if (ui.checkBoxFlipTD->isChecked())
							flip_shortInt((unsigned char *)pShData, iNumSample);

						qFile.write((char *)pShData, iNumSample * 2);
					}
					else if (iDataType == 8)
					{
						//	char
						for (m = 0; m < iNumSample; m++)
							pChData[m] = (char)((pData[m] - dDataMin) * dcharThre);

						qFile.write((char *)pChData, iNumSample);
					}

				}
			}
			else
			{
				//	Loop for each CDP.
				for (j = 0; j < iSouCDPNum; j++)
				{
					iCDP = iSXline + j * iXlineInc;
					utm.LineToXY(i, iCDP, dX, dY);

					//	Loop for each offset.
					for (k = 0; k < iNumO; k++)
					{
						//	Process trace header.
						memset(pTH, 0, 240);
						short *pShort = (short *)(pTH + 104);
						pShort[0] = iSZ;					//	105, Start Z.
						pShort[2] = iSZ;					//	109, Start Z.
						pShort[5] = iNumSample;				//	115, number of samples per trace.
						pShort[6] = iZInc * 1000;			//	117, sample interval.
						int *pInt = (int *)(pTH + 8);
						pInt[0] = i;						//	9, line number.
						pInt[3] = iCDP;						//	21, CDP number.
						pInt[4] = k + 1;					//	25, offset index.
						pInt[7] = (int)(fSO + fOInc * k);	//	37, offset.
						pInt[16] = (int)dX;					//	73, X.
						pInt[17] = (int)dY;					//	77, Y.
						if (ui.comboBoxCoord->currentIndex() == 1)
						{
							float *pFloat = (float *)(pTH + 72);
							pFloat[0] = dX;					//	73, X.
							pFloat[1] = dY;					//	77, Y.
						}

						if (ui.checkBoxFlipLH->isChecked())
							flipTH(pTH);

						//	Write the trace header.
						qFile.write(pTH, 240);

						//	Now the trace data.
						if (iZStep == 1)
						{
							memcpy(pData, pBuff + (j * iNumO + k) * iSouTraceLen, iSouTraceLen * 4);
						}
						else
						{
							for (m = 0; m < iNumSample; m++)
								pData[m] = pBuff[(j * iNumO + k) * iSouTraceLen + m * iZStep];
						}

						if (bZeroInvalid)
						{
							for (m = 0; m < iNumSample; m++)
							{
								if (pData[m] == ::g_dInvalidData)
									pData[m] = 0.;
							}
						}

						if (iDataType == 5)
						{
							//	IEEE float
							if (ui.checkBoxFlipTD->isChecked())
								flip((unsigned char *)pData, iNumSample);

							qFile.write((char *)pData, iNumSample * 4);
						}
						else if (iDataType == 1)
						{
							//	IBM float
							IEEEToIBM((int *)pData, (int *)pTmpData, iNumSample);

							//	IBM data always need flip.
							flip((unsigned char *)pTmpData, iNumSample);

							qFile.write((char *)pTmpData, iNumSample * 4);
						}
						else if (iDataType == 2)
						{
							//	int
							for (m = 0; m < iNumSample; m++)
								pIntData[m] = (int)pData[m];

							if (ui.checkBoxFlipTD->isChecked())
								flip((unsigned char *)pIntData, iNumSample);

							qFile.write((char *)pIntData, iNumSample * 4);
						}
						else if (iDataType == 3)
						{
							//	short
							for (m = 0; m < iNumSample; m++)
								pShData[m] = (short)((pData[m] - dDataMin) * dShortThre);

							if (ui.checkBoxFlipTD->isChecked())
								flip_shortInt((unsigned char *)pShData, iNumSample);

							qFile.write((char *)pShData, iNumSample * 2);
						}
						else if (iDataType == 8)
						{
							//	char
							for (m = 0; m < iNumSample; m++)
								pChData[m] = (char)((pData[m] - dDataMin) * dcharThre);

							qFile.write((char *)pChData, iNumSample);
						}

					}
				}
			}
		}

		delete[]pBuff;
		delete[]pData;
		delete[]pTmpData;
		delete[]pIntData;
		delete[]pShData;
		delete[]pChData;
		delete[]pTH;

		if (pTraceInfo)
			delete[]pTraceInfo;
	}
	else
	{
		CX2DSeismicLine *p2DLine = dynamic_cast<CX2DSeismicLine *>(m_p2DSection->GetGeometryObject());

		//	Write sample interval.
		int iSampleInt = m_p2DSection->GetSampleInterval() * 1000;
		lineHeader.WriteSampleInterval(iSampleInt);

		//	Write sample number.
		double dSZ, dEZ, dZInc;
		m_p2DSection->GetSamplingRange(dSZ, dEZ, dZInc);
		int iSZ = (int)dSZ;
		int iEZ = (int)dEZ;
		int iZInc = (int)dZInc;
		int iNumSample = (iEZ - iSZ) / iZInc + 1;
		lineHeader.WriteSampleNumber(iNumSample);

		//	Data Type.
		//	1: 4-byte IBM float;	2: 4-byte integer;	3: 2-byte integer;	4: obsolete;	5: 4-byte IEEE float;	8: 1-byte integer.
		int iDataType = ui.comboBoxTraceData->currentIndex();
		if (iDataType == 0)
			iDataType = 5;
		else if (iDataType == 1)
			iDataType = 1;
		else if (iDataType == 2)
			iDataType = 2;
		else if (iDataType == 3)
			iDataType = 3;
		else if (iDataType == 4)
			iDataType = 8;
		lineHeader.WriteDataType(iDataType);

		//	Write the unit as meter so far.
		lineHeader.WriteUnit(1);

		//	Flip the line header?
		if (ui.checkBoxFlipLH->isChecked())
			lineHeader.FlipBuff();

		//	Write the line header.
		qFile.write(lineHeader.GetLineHeaderBuff(), 400);

		//	Prepare the data buff.
		int i, j, k, m, n, iCDP;

		float *pData = new float[iNumSample];
		float *pTmpData = new float[iNumSample];
		int *pIntData = new int[iNumSample];
		short *pShData = new short[iNumSample];
		char *pChData = new char[iNumSample];
		char *pTH = new char[240];

		double dDataMin, dDataMax, dDataSpan;
		m_p2DSection->GetDataRange(dDataMin, dDataMax);
		dDataSpan = dDataMax - dDataMin;
		double dShortThre = 32767. / (dDataMax - dDataMin);
		double dcharThre = 255. / (dDataMax - dDataMin);

		int iNumTrace = p2DLine->GetTraceNumber();
		unsigned int *pCDP = p2DLine->GetCDPData();
		double *pX, *pY;
		p2DLine->GetCoordData(pX, pY);
		float *pBuff = m_p2DSection->GetData();

		for (i = 0; i < iNumTrace; i++)
		{
			//	Process trace header.
			memset(pTH, 0, 240);
			short *pShort = (short *)(pTH + 104);
			pShort[0] = iSZ;						//	105, Start Z.
			pShort[2] = iSZ;						//	109, Start Z.
			pShort[5] = iNumSample;					//	115, number of samples per trace.
			pShort[6] = iZInc * 1000;				//	117, sample interval.
			int *pInt = (int *)(pTH + 8);
			pInt[0] = i;							//	9, line number.
			pInt[3] = pCDP[i];						//	21, CDP number.
			pInt[16] = (int)pX[i];					//	73, X.
			pInt[17] = (int)pY[i];					//	77, Y.
			if (ui.comboBoxCoord->currentIndex() == 1)
			{
				float *pFloat = (float *)(pTH + 72);
				pFloat[0] = pX[i];		//	73, X.
				pFloat[1] = pY[i];		//	77, Y.
			}

			if (ui.checkBoxFlipLH->isChecked())
				flipTH(pTH);

			//	Write the trace header.
			qFile.write(pTH, 240);

			//	Now the trace data.
			memcpy(pData, pBuff + i * iNumSample, iNumSample * 4);

			if (bZeroInvalid)
			{
				for (m = 0; m < iNumSample; m++)
				{
					if (pData[m] == ::g_dInvalidData)
						pData[m] = 0.;
				}
			}

			if (iDataType == 5)
			{
				//	IEEE float
				if (ui.checkBoxFlipTD->isChecked())
					flip((unsigned char *)pData, iNumSample);

				qFile.write((char *)pData, iNumSample * 4);
			}
			else if (iDataType == 1)
			{
				//	IBM float
				IEEEToIBM((int *)pData, (int *)pTmpData, iNumSample);

				//	IBM data always need flip.
				flip((unsigned char *)pTmpData, iNumSample);

				qFile.write((char *)pTmpData, iNumSample * 4);
			}
			else if (iDataType == 2)
			{
				//	int
				for (m = 0; m < iNumSample; m++)
				pIntData[m] = (int)pData[m];

				if (ui.checkBoxFlipTD->isChecked())
					flip((unsigned char *)pIntData, iNumSample);

				qFile.write((char *)pIntData, iNumSample * 4);
			}
			else if (iDataType == 3)
			{
				//	short
				for (m = 0; m < iNumSample; m++)
					pShData[m] = (short)((pData[m] - dDataMin) * dShortThre);

				if (ui.checkBoxFlipTD->isChecked())
					flip_shortInt((unsigned char *)pShData, iNumSample);

				qFile.write((char *)pShData, iNumSample * 2);
			}
			else if (iDataType == 8)
			{
				//	char
				for (m = 0; m < iNumSample; m++)
					pChData[m] = (char)((pData[m] - dDataMin) * dcharThre);

				qFile.write((char *)pChData, iNumSample);
			}
		}

		delete[]pData;
		delete[]pTmpData;
		delete[]pIntData;
		delete[]pShData;
		delete[]pChData;
		delete[]pTH;
	}

	QDialog::accept();
}

void CXDlgExportSEGY::flipTH(char *pTH)
{
	flip((unsigned char *)(pTH + 8), 1);				//	line
	flip((unsigned char *)(pTH + 20), 1);				//	cdp
	flip((unsigned char *)(pTH + 24), 1);				//	offset
	flip((unsigned char *)(pTH + 36), 1);				//	offset
	flip((unsigned char *)(pTH + 72), 1);				//	X
	flip((unsigned char *)(pTH + 76), 1);				//	Y
	flip_shortInt((unsigned char *)(pTH + 104), 1);		//	start z
	flip_shortInt((unsigned char *)(pTH + 108), 1);		//	start z
	flip_shortInt((unsigned char *)(pTH + 114), 1);		//	sample number
	flip_shortInt((unsigned char *)(pTH + 116), 1);		//	sample interval
	flip((unsigned char *)(pTH + 232), 1);				//	azimuth
}

void CXDlgExportSEGY::slotDataTypeChanged(int iValue)
{
	if (iValue == 1)
	{
		//	IBM float must flip
		ui.checkBoxFlipTD->setChecked(true);
		ui.checkBoxFlipTD->setDisabled(true);
	}
	else if (iValue == 4)
	{
		//	8 bits char need not flip
		ui.checkBoxFlipTD->setChecked(false);
		ui.checkBoxFlipTD->setDisabled(true);
	}
	else
		ui.checkBoxFlipTD->setDisabled(false);
}