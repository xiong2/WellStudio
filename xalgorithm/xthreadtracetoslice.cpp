#include <QFile>
#include <QApplication>
#include "xthreadtracetoslice.h"
#include "xsysteminfo.h"
#include "xseismicdatavolume.h"
#include "xconcurrentparameter.h"
#include "xregulardatawriter.h"
#include "xregulardatareader.h"
#include <cassert>
#include "xutility.h"
#include "xglobal.h"

CXThreadTraceToSlice::CXThreadTraceToSlice(CXSeismicDataVolume* pDV)
: m_pDV(pDV)
{
	m_pSectionBuff = NULL;
	m_p2DSliceData  = NULL;
	m_nSliceNum = 0;

	if (NULL != m_pDV)
	{
		m_nInlineDim = m_pDV->GetInlineQty();
		m_nCrosslineDim = m_pDV->GetXlineQty();
		m_nTimeDim = m_pDV->GetSamplingQty();
	}
}

CXThreadTraceToSlice::~CXThreadTraceToSlice()
{
    this->wait(); 
	
	if (NULL != m_pDV)
		UnlockRead(m_pDV);

	_ReleaseData(false);

    if (IsStopped())
    {      
		if (QFile::exists(m_strSliceFileName))
			QFile::remove(m_strSliceFileName);        
    }
}

void CXThreadTraceToSlice::RunThread()
{
    // Tell if stopped
    if (IsStopped())
        return;

    // Initialization
    if (!_Initialization())
        return;

	// Set dialog title name and sub-task names
	this->EmitSetWindowName("Converting Trace File to Slice File");
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
	QString strTaskName = QString("Converting... (")+m_pDV->GetObjectName() + ")";
	this->EmitSetTaskName(strTaskName);
	this->EmitStartComputing();
	qApp->processEvents();

    // Allocate memory    
    try
    {
       m_pSectionBuff = new float [m_nCrosslineDim*m_nTimeDim];
    }
    catch(...)
    {        
		_ReleaseData();
        EmitMemoryNotEnough();        
        return;
    }

	int nFreeMemory = CXSystemInfo::GetFreeMemory();
	if ( nFreeMemory < 100)
	{         
		_ReleaseData();
		EmitMemoryNotEnough();
		return;
	}

     // Decide how many blocks need to handle, and each block handles how many slices
     qint64 nSliceSize = m_nCrosslineDim*m_nInlineDim;
     int nSlice = 1;
     forever
     {   
         int nBlockSize = static_cast<int>(nSliceSize*nSlice*sizeof(float)/1000/1000 );
         
         if ( nBlockSize > nFreeMemory*90/100 || nSlice >= m_nTimeDim)
             break;
         else
             nSlice++;
     }
     int nBlock;
     if (m_nTimeDim % nSlice == 0)
         nBlock = m_nTimeDim/nSlice;
     else
         nBlock = m_nTimeDim/nSlice + 1;

     // Allocate memory for conversion
	 m_nSliceNum = nSlice;
	 m_p2DSliceData = NXUtility::New2DArray<float>(m_nSliceNum, m_nCrosslineDim*m_nInlineDim);
	 if (NULL == m_p2DSliceData)
	 {
		 _ReleaseData();
		 EmitMemoryNotEnough();
		 return;
	 }

	 // Trace file manager for reading data
	 CXRegularDataReader<float> dataReader(m_strTraceFileName, m_nInlineDim, m_nCrosslineDim, m_nTimeDim);
	 if (!dataReader.Open())
	 {
		 _ReleaseData();
		 QString strErrorMsg = "Cannot open the trace file.";
		 EmitGeneralErrorMsg(strErrorMsg);		
		 return;
	 }

	 // writer data
	 CXRegularDataWriter<float> dataWriter(m_strSliceFileName, m_nTimeDim, m_nInlineDim, m_nCrosslineDim);
	 if (!dataWriter.Open())
	 {
		 _ReleaseData();
		 EmitGeneralErrorMsg("Cannot write data to the disk.");		
		 return;
	 }

	 // progress info
	 m_nTotalStep = m_nInlineDim*nBlock + m_nTimeDim;
	 m_iCurrent = 0;

	 //Convert
	 for (int i=0; i<nBlock; ++i)
	 {
		 int iTimeIndMin, iTimeIndMax;
		 iTimeIndMin = i*nSlice;
		 iTimeIndMax = iTimeIndMin + nSlice -1;
		 if (iTimeIndMax >= m_nTimeDim)
			 iTimeIndMax = m_nTimeDim - 1;

		 for (int iInlineIndex=0; iInlineIndex<m_nInlineDim; ++iInlineIndex)
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

			 if (!dataReader.ReadUSection(iInlineIndex, m_pSectionBuff))
			 {
				 _ReleaseData();
				 EmitGeneralErrorMsg("Cannot read data from the disk.");		
				 return;
			 }

			 int iSectionIndex;
			 for (int iXlineIndex=0; iXlineIndex<m_nCrosslineDim; ++iXlineIndex)
			 {
				 for (int iTimeIndex=iTimeIndMin; iTimeIndex<=iTimeIndMax; ++iTimeIndex)
				 {
					 iSectionIndex = iXlineIndex*m_nTimeDim + iTimeIndex;

					 m_p2DSliceData[iTimeIndex-iTimeIndMin][iInlineIndex*m_nCrosslineDim+iXlineIndex] = m_pSectionBuff[iSectionIndex];
				 }
			 }
		 }

		 //write
		 for (int iTimeIndex=iTimeIndMin; iTimeIndex<=iTimeIndMax; ++iTimeIndex)
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

			 if (!dataWriter.WriteUSection(iTimeIndex, m_p2DSliceData[iTimeIndex-iTimeIndMin]))
			 {
				 _ReleaseData();
				 EmitGeneralErrorMsg("Cannot write data to the disk.");		
				 return;
			 }
		 }
	 }

	 _ReleaseData();
}

void CXThreadTraceToSlice::_ReleaseData(bool bWithSemaphore)
{
	if (m_pSectionBuff)		{delete []m_pSectionBuff; m_pSectionBuff = NULL;}
	if (m_p2DSliceData)		{NXUtility::Free2DArray<float>(m_p2DSliceData, m_nSliceNum); m_p2DSliceData = NULL;}

	if (bWithSemaphore)
		CXConcurrentParameter::m_semaphoreSliceLDMConversion.release();
}

bool CXThreadTraceToSlice::_Initialization()
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
	qint64 nRequired = (qint64)m_nInlineDim*m_nCrosslineDim*m_nTimeDim*sizeof(float);

	// Get the available disk space
	qint64 nAvailable = CXSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	qint64 nAdditional = nRequired + 50*1000*1000 - nAvailable;

	if (nAdditional > 0)
	{
		QString strAdditionSpace = CXSystemInfo::GetSpaceSizeString(nAdditional);
		EmitDiskSpaceNotEnough(strAdditionSpace);
		return false;
	}

	return true;
}

	
