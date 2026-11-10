#include <QFile>
#include "xload2dsegythread.h"
#include "xsegyloadparameters.h"
#include "x2dseismicline.h"
#include "xseismicdataline.h"
#include <QCoreApplication>

CXLoad2DSEGYThread::CXLoad2DSEGYThread(CXSEGYLoadParameters* pLoadParameters)
{
	m_pLoadParameters = pLoadParameters;
	m_p2DSeismicLine = NULL;
}

CXLoad2DSEGYThread::~CXLoad2DSEGYThread()
{
	this->wait();

	if (IsStopped())
	{
		if (m_p2DSeismicLine)
		{
			delete m_p2DSeismicLine;
			m_p2DSeismicLine = NULL;
		}
	}
}


void CXLoad2DSEGYThread::RunThread()
{
	// Set the names for progress dialog
	QString strWindowName = "Loading 2D SEG-Y File";
	QString strTaskName = "Converting SEG-Y File to Trace File";
	EmitSetWindowName(strWindowName);
	EmitSetTaskName(strTaskName);
	EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	//	Open the segy file and skip the volume header.
	QFile qFile(m_pLoadParameters->GetAllSEGYFiles().at(0));
	if (!qFile.open(QIODevice::ReadOnly))
	{
		EmitGeneralErrorMsg(QString("Unable to read the SEGY file!"));
		return;
	}
	qFile.seek(3600);

	//	Inline is not used for 2D seismic, set it to CDP to avoid checking failed.
	m_pLoadParameters->SetInlinePosition(m_pLoadParameters->GetCrosslinePosition());

	//	Prepare the buffer memory.
	unsigned int numTrace = m_pLoadParameters->GetTraceNumber();
	unsigned int numSample = m_pLoadParameters->GetSampleNumber();

	//progress bar
	this->EmitUpdateProgress(10, 10 + numTrace + 50);

	int i, iInline, iCrossline, iAzim;
	float fOffset;	//	Only used for prestack.
	float *pData		= new float[numTrace * numSample];
	char *pDataBuff		= new char[m_pLoadParameters->GetTraceLength()];
    double *pX = new double[numTrace];
    double *pY = new double[numTrace];
	unsigned int *pCDP	= new unsigned int[numTrace];
    double dX, dY;

	//	A loop to read each trace.
	

	for (i = 0; i < numTrace; i++)
	{
		if (IsStopped())
			break;
		else
			this->EmitUpdateProgress(10 + i, 10 + numTrace + 50);
			

		if (!m_pLoadParameters->ReadATrace(qFile, iInline, iCrossline, fOffset, iAzim, dX, dY, pDataBuff))
		{
			this->EmitGeneralErrorMsg("Cannot read data from the disk.");;
			break;
		}

        pX[i] = dX;
        pY[i] = dY;
		pCDP[i] = iCrossline;
		m_pLoadParameters->ConvertTraceData(pDataBuff, pData + i * numSample);
	}

	if (IsStopped())
	{
		delete[]pDataBuff;
		delete[]pData;
		return;
	}


	//	Now create the imported line.
	m_p2DSeismicLine = new CX2DSeismicLine(m_pLoadParameters->GetDVName());
	m_p2DSeismicLine->PopulateData(numTrace, pCDP, pX, pY);

	//	Then the seismic section
	double dEnd = m_pLoadParameters->GetStartTime() + m_pLoadParameters->GetSampleInterval() * (numSample - 1);
	CXSeismicDataLine *pSection = new CXSeismicDataLine(m_p2DSeismicLine, m_pLoadParameters->GetStartTime(), dEnd, m_pLoadParameters->GetSampleInterval());
	m_p2DSeismicLine->AddChild(pSection);

	QFile qFileSection(pSection->GetDataFileName());
	if (!qFileSection.open(QIODevice::WriteOnly))
	{
		EmitGeneralErrorMsg("Cannot write data to the disk.");
	}
	else
	{
		qFileSection.write((char*)pData, sizeof(float)*numTrace*numSample);
		qFileSection.close();
	}

	this->EmitUpdateProgress(10 + numTrace + 40, 10 + numTrace + 50);

	delete[]pDataBuff;
	delete[]pData;
}