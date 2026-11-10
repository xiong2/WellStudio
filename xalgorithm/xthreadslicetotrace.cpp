#include <QFile>
#include <QApplication>
#include "xthreadslicetotrace.h"
#include "xsysteminfo.h"
#include "xseismicdatavolume.h"
#include "xconcurrentparameter.h"
#include "xregulardatawriter.h"
#include "xregulardatareader.h"
#include <cassert>
#include "xutility.h"
#include "xglobal.h"

CXThreadSliceToTrace::CXThreadSliceToTrace(CXSeismicDataVolume* pDV)
	: m_pDV(pDV)
{
	if (NULL != m_pDV)
	{
		m_nInlineDim = m_pDV->GetInlineQty();
		m_nCrosslineDim = m_pDV->GetXlineQty();
		m_nTimeDim = m_pDV->GetSamplingQty();
	}
}

CXThreadSliceToTrace::~CXThreadSliceToTrace()
{
	this->wait();

	if (NULL != m_pDV)
		UnlockRead(m_pDV);

	_ReleaseData(false);

	if (IsStopped())
	{
		if (QFile::exists(m_strTraceFileName))
			QFile::remove(m_strTraceFileName);
	}
}

void CXThreadSliceToTrace::RunThread()
{
	// Tell if stopped
	if (IsStopped())
		return;

	// Initialization
	if (!_Initialization())
		return;

	// Set dialog title name and sub-task names
	this->EmitSetWindowName("Converting Slice File to Trace File");
	this->EmitSetTaskName("Waiting for another conversion process to finish...");
	this->EmitResetProgressBar();
	qApp->processEvents();

	// Allow only one slice converter thread running
	forever
	{
		if (CXConcurrentParameter::m_semaphoreSliceLDMConversion.tryAcquire(1, 500))
			break;
		else
		{
			if (IsStopped())
			{
				return;
			}
		}
	}

		// Start converting
	QString strTaskName = QString("Converting... (") + m_pDV->GetObjectName() + ")";
	this->EmitSetTaskName(strTaskName);
	this->EmitStartComputing();
	qApp->processEvents();

	// Allocate memory    
	try
	{
		m_pSliceBuff = new float[m_nCrosslineDim * m_nInlineDim];
	}
	catch (...)
	{
		_ReleaseData();
		EmitMemoryNotEnough();
		return;
	}

	int nFreeMemory = CXSystemInfo::GetFreeMemory();
	if (nFreeMemory < 100)
	{
		_ReleaseData();
		EmitMemoryNotEnough();
		return;
	}

	// Decide how many blocks need to handle, and each block handles how many slices
	qint64 nInlineSize = m_nCrosslineDim * m_nTimeDim;
	int nInline = 1;
	forever
	{
		int nBlockSize = static_cast<int>(nInlineSize * nInline * sizeof(float) / 1000 / 1000);

		if (nBlockSize > nFreeMemory * 90 / 100 || nInline >= m_nInlineDim)
			break;
		else
			nInline++;
	}
	int nBlock;
	if (m_nInlineDim % nInline == 0)
		nBlock = m_nInlineDim / nInline;
	else
		nBlock = m_nInlineDim / nInline + 1;

	// Allocate memory for conversion
	m_nLineNum = nInline;
	m_pSectionData = NXUtility::New2DArray<float>(m_nLineNum, m_nCrosslineDim * m_nTimeDim);
	if (NULL == m_pSectionData)
	{
		_ReleaseData();
		EmitMemoryNotEnough();
		return;
	}

	// Trace file manager for reading data
	CXRegularDataReader<float> dataReader(m_strSliceFileName, m_nTimeDim, m_nInlineDim, m_nCrosslineDim);
	if (!dataReader.Open())
	{
		_ReleaseData();
		QString strErrorMsg = "Cannot open the slice file.";
		EmitGeneralErrorMsg(strErrorMsg);
		return;
	}

	// writer data
	CXRegularDataWriter<float> dataWriter(m_strTraceFileName, m_nInlineDim, m_nCrosslineDim, m_nTimeDim);
	if (!dataWriter.Open())
	{
		_ReleaseData();
		EmitGeneralErrorMsg("Cannot write data to the disk.");
		return;
	}

	// progress info
	m_nTotalStep = m_nTimeDim * nBlock + m_nInlineDim;
	m_iCurrent = 0;

	//Convert
	for (int i = 0; i < nBlock; ++i)
	{
		int iLineIndMin, iLineIndMax;
		iLineIndMin = i * nInline;
		iLineIndMax = iLineIndMin + nInline - 1;
		if (iLineIndMax >= m_nInlineDim)
			iLineIndMax = m_nInlineDim - 1;

		for (int iTimeIndex = 0; iTimeIndex < m_nTimeDim; ++iTimeIndex)
		{
			// progress info
			if (IsStopped())
			{
				_ReleaseData();
				return;
			}
			else
			{
				this->EmitUpdateProgress(m_iCurrent++, m_nTotalStep);
			}

			if (!dataReader.ReadUSection(iTimeIndex, m_pSliceBuff))
			{
				_ReleaseData();
				EmitGeneralErrorMsg("Cannot read data from the disk.");
				return;
			}

			int iSectionIndex;
			for (int iXlineIndex = 0; iXlineIndex < m_nCrosslineDim; ++iXlineIndex)
			{
				for (int iLineIndex = iLineIndMin; iLineIndex <= iLineIndMax; ++iLineIndex)
				{
					iSectionIndex = iLineIndex * m_nCrosslineDim + iXlineIndex;

					m_pSectionData[iLineIndex - iLineIndMin][iXlineIndex * m_nTimeDim + iTimeIndex] = m_pSliceBuff[iSectionIndex];
				}
			}
		}

		//write
		for (int iLineIndex = iLineIndMin; iLineIndex <= iLineIndMax; ++iLineIndex)
		{
			// progress info
			if (IsStopped())
			{
				_ReleaseData();
				return;
			}
			else
			{
				this->EmitUpdateProgress(m_iCurrent++, m_nTotalStep);
			}

			if (!dataWriter.WriteUSection(iLineIndex, m_pSectionData[iLineIndex - iLineIndMin]))
			{
				_ReleaseData();
				EmitGeneralErrorMsg("Cannot write data to the disk.");
				return;
			}
		}
	}

	_ReleaseData();
}

void CXThreadSliceToTrace::_ReleaseData(bool bWithSemaphore)
{
	if (m_pSliceBuff) { delete[]m_pSliceBuff; m_pSliceBuff = NULL; }
	if (m_pSectionData) { NXUtility::Free2DArray<float>(m_pSectionData, m_nLineNum); m_pSectionData = NULL; }

	if (bWithSemaphore)
		CXConcurrentParameter::m_semaphoreSliceLDMConversion.release();
}

bool CXThreadSliceToTrace::_Initialization()
{
	if (NULL == m_pDV)
	{
		QString strErrorMsg = "The data volume does not exist!";
		EmitGeneralErrorMsg(strErrorMsg);
		return false;
	}

	// Get the data volume info
	m_strTraceFileName = m_pDV->GetTraceFileName();
	m_strSliceFileName = m_pDV->GetSliceFileName();

	LockRead(m_pDV);

	// Get the required disk space
	qint64 nRequired = (qint64)m_nInlineDim*m_nCrosslineDim*m_nTimeDim * sizeof(float);

	// Get the available disk space
	qint64 nAvailable = CXSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	qint64 nAdditional = nRequired + 50 * 1000 * 1000 - nAvailable;

	if (nAdditional > 0)
	{
		QString strAdditionSpace = CXSystemInfo::GetSpaceSizeString(nAdditional);
		EmitDiskSpaceNotEnough(strAdditionSpace);
		return false;
	}

	return true;
}