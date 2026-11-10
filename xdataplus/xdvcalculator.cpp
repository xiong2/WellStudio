#include <qmessagebox.h>
#include "xdvcalculator.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
#include "xregulardatawriter.h"
#include "x3dsurvey.h"
#include "xalgorithmutility.h"
#include "xprogressbar.h"

CXDVCalculator::CXDVCalculator(QUuid objID) : CXObjCalculator(objID)
{
	m_pOutputDV = NULL;
	m_pWriter = NULL;
	m_pFloatBuff = NULL;
}

CXObject* CXDVCalculator::Calculate(QString str, double& fVal)
{
	int i, j;
	double res;
	m_strNewObjName = "New Object";
	fVal = g_dInvalidData;

	//	Pre-process.
	if (!_preProcess(str))
	{
		QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
		return NULL;
	}

	QString strOri = str;

	int iNumLine = 1;
	if (!m_listDV.isEmpty())
	{
		iNumLine = m_listDV[0]->GetInlineQty();
	}

	CXProgressBar progress("Seismic Data Volume Calculation", "Calculating... ", iNumLine);

	for (j = 0; j < iNumLine; j++)
	{
		str = strOri;

		progress.SetValue(j);
		_updateData(j);

		for (i = 0; i < 20; i++)
		{
			if (m_pBoolArray[i] != NULL) delete m_pBoolArray[i];
			m_pBoolArray[i] = NULL;
		}

		//	Process all the "if" expression.
		while (str.contains("If("))
		{
			//	Extract the "if(...){...}else if(...){...}else{...}" expression.
			int len = str.length();
			int tcount = 1;
			int pos1 = str.indexOf("If(");
			int pos2 = str.indexOf("else");
			for (i = pos2 + 5; i < len; i++)
			{
				if (str[i] == '{') tcount++;
				if (str[i] == '}') tcount--;
				if (tcount == 0) break;
			}

			if (i >= len)
			{
				QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
				return NULL;
			}

			//	The tmpstr is the expression.
			QString tmpstr = str.mid(pos1, i - pos1 + 1);

			double *pObject = NULL;
			short tres = _ifCal(tmpstr, pObject);
			if (tres == -1)
			{
				QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
				return NULL;
			}
			else
			{
				str.replace(pos1, i - pos1 + 1, tmpstr);
			}
		}


		int loopTime = 0;
		while (_calInnerMostExp(str))
		{
			//	To avoid dead loop
			if (loopTime > 100)
			{
				QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
				return NULL;
			}
			loopTime++;
		}

		double *pObject = NULL;
		short s = _simpleCal(str, res, pObject);

		for (i = 0; i < 20; i++)
		{
			if (m_pBoolArray[i] != NULL) delete m_pBoolArray[i];
			m_pBoolArray[i] = NULL;
		}

		if (s == 0)
		{
			//	The result is a figure.
			if (fabs(res) < 0.0000000001)
			res = 0;

			fVal = res;
		}
		else if (s == 1)
		{
			//	The result is an object.
			for (i = 0; i < m_iDataSize; i++)
				m_pFloatBuff[i] = (float)pObject[i];

			m_pWriter->Append(m_iDataSize, m_pFloatBuff);
		}
		else if (s == -1)
		{
			QMessageBox::critical(NULL, "Calculator Error", "Invalid Expression!");
			break;
		}
	}

	for (i = 65; i < m_count - 1; i++)
	{
		double *pData = m_vecPData.at(i - 65);
		delete[]pData;
	}

	if (m_pWriter)
		delete m_pWriter;
	m_pWriter = NULL;

	delete[]m_pFloatBuff;

	//	Add DV to the survey.
	CX3DSurvey *pSurvey = (CX3DSurvey *)::GetObjectByID(m_listDV[0]->GetSurveyID());
	CXObject *pDVFolder = pSurvey->GetFolder(EXSeismicDVFolder);
	QString sDVName = pDVFolder->GetUnallocatedName(m_pOutputDV->GetObjectName());
	m_pOutputDV->SetObjectName(sDVName);
	pDVFolder->AddChild(m_pOutputDV);

	CXAlgorithmUtility::CalculateHistogram(m_pOutputDV->GetTraceFileName(), m_pOutputDV->GetSamplingQty(), m_pOutputDV);

	return m_pOutputDV;
}

QString CXDVCalculator::_findOutObjects(QString str)
{
	m_pBValid = NULL;

	CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(m_objID));
	if (!pDV)
		return str;

	QList<CXObject *> listDV;
	pDV->GetAllDVWithSameSize(listDV);

	//	Initialize.
	int i, j;
	m_count = 65;
	m_vecPData.clear();
	m_listDV.clear();

	//	We should search log name from long to short, so sort the log name first.
	//std::sort(vecChildren.begin(), vecChildren.end(), _ObjectCompareByLengthDescend);
	std::sort(listDV.begin(), listDV.end(), [](CXObject* p1, CXObject* p2) {
		return p1->GetObjectName().length() > p2->GetObjectName().length();
	});

	for (i = 0; i < listDV.size(); i++)
	{
		QString strLogName = listDV[i]->GetObjectName();
		if (str.indexOf(strLogName) != -1)
		{
			//	Deal with the object's name has only one character.
			if (strLogName.size() == 1)
			{
				int ind = str.indexOf(strLogName);
				if (ind > 0 && ind < str.size() - 1)
				{
					if (str.at(ind - 1) == '$' && str.at(ind + 1) == '$')
						continue;
				}
			}

			m_listDV.append((CXSeismicDataVolume *)listDV[i]);

			QString strTmpName = "$";
			strTmpName += QChar(m_count);
			strTmpName += "$";
			str.replace(strLogName, strTmpName);
			m_count++;
		}
	}

	if (!m_listDV.isEmpty() || m_bObj)
	{
		double dStartZ, dEndZ, dZStep;
		float fSOffset, fOffsetStep;
		int iNumOffset;

		pDV->GetSamplingRange(dStartZ, dEndZ, dZStep);
		pDV->GetOffsetInfo(fSOffset, fOffsetStep, iNumOffset);
		m_pOutputDV = new CXSeismicDataVolume(pDV->GetUTM(), dStartZ, dEndZ, dZStep, m_strNewObjName, iNumOffset, fSOffset, fOffsetStep);
		m_iDataSize = pDV->GetXlineTraceQty() * pDV->GetSamplingQty();
		m_pFloatBuff = new float[m_iDataSize];

		m_pWriter = new CXRegularDataWriter<float>(m_pOutputDV->GetTraceFileName(), pDV->GetInlineQty(), pDV->GetXlineTraceQty(), pDV->GetSamplingQty());
		m_pWriter->Open();
	}
	
	for (i = 0; i < m_listDV.size(); i++)
	{
		double *pData = new double[m_iDataSize];
		m_vecPData.push_back(pData);
	}

	return str;
}

void CXDVCalculator::_updateData(unsigned int iLineIDX)
{
	if (m_listDV.isEmpty())
		return;

	int i, j, iLine;
	CXSeismicUTMTool utm = m_listDV[0]->GetUTM();
	utm.IJToLine(iLineIDX, 0, iLine, j);

	m_count = 65 + m_listDV.size();
	for (i = 0; i < m_listDV.size(); i++)
	{
		double *pBuff = m_vecPData[i];
		m_listDV[i]->ReadInline(iLine, m_pFloatBuff);

		for (j = 0; j < m_iDataSize; j++)
			pBuff[j] = (double)m_pFloatBuff[j];
	}

	for (; i < m_vecPData.size(); i++)
	{
		double *pBuff = m_vecPData[i];
		delete pBuff;
	}

	m_vecPData.resize(m_listDV.size());
}