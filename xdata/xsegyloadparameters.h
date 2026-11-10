#ifndef _CXSEGYLoadParameters_H__
#define _CXSEGYLoadParameters_H__

#include <QStringList>
#include <QUuid>
#include <qhash.h>
#include <qvector.h>

#include "xdata_global.h"
#include "xdef.h"

#define VOLUMEHEADERLENGTH 3200

class QFile;
class CXObject;
class CXSEGYLineHeader;
class CXSEGYTraceHeader;
class CXSeismicUTMTool;
class CXSeismicDataVolume;
class CXPreStackGather;
//class CRLNode;

struct SKETraceOffsets
{
	float			m_fX;
	float			m_fY;
	QVector<short>	m_vecIOffsetAzim;		//	Offset, or pair of offset & azimuth.
};

/**
*@brief		This class contains all parameters relevant to one SEGY (maybe multiple files) loading.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXSEGYLoadParameters
{
public:
	CXSEGYLoadParameters(QStringList listStrSEGYFiles);
	~CXSEGYLoadParameters();

	///@brief	Get the 3200 bytes ASCII volume header.
	char* GetVolumeHeader()
	{
		return m_pVolumeHeader;
	}

	///@brief	Get data type.
	int GetDataType()
	{
		return m_iDataType;
	}

	///@brief	Set data type.
	void SetDataType(int iDataType);

	///@brief	Data need flip?
	bool DataNeedFlip()
	{
		return m_bDataFlip;
	}

	///@brief	Set wthether data need flip.
	void SetDataFlip(bool bFlip)
	{
		m_bDataFlip = bFlip;
	}

	///@brief	Need Overwrite the sample number?
	bool IsSampleNumberOverwrited()
	{
		return m_bOverwriteSampleNumber;
	}

	///@brief	Set whether Overwrite the sample number.
	void SetOverwriteSampleNumber(bool bOverwrite)
	{
		m_bOverwriteSampleNumber = bOverwrite;
	}

	///@brief	Get number of samples per trace.
	unsigned short GetSampleNumber()
	{
		return m_iSampleNumber;
	}

	///@brief	Set the number of samples per trace.  Note only while "can Overwrite" then this function works.
	void SetSampleNumber(unsigned short iSampleNumber);

	///@brief	Need Overwrite the sample interval?
	bool IsSampleIntervalOverwrited()
	{
		return m_bOverwriteSampleInterval;
	}

	///@brief	Set whether Overwrite the sample number.
	void SetOverwriteSampleInterval(bool bOverwrite)
	{
		m_bOverwriteSampleInterval = bOverwrite;
	}

	///@brief	Get sample interval.
	float GetSampleInterval()
	{
		return m_fSampleInterval;
	}

	///@brief	Set sample interval.  Note only while "can Overwrite" then this function works.
	void SetSampleInterval(float fSampleInterval)
	{
		if (m_bOverwriteSampleInterval)
			m_fSampleInterval = fSampleInterval;
	}

	///@brief	Get the tace number of the 1st segy file.
	qint64 GetTraceNumber()
	{
		return m_iTraceNumber;
	}

	///@brief	Get unit.
	unsigned short GetUnit()
	{
		return m_iUnit;
	}

	///@brief	Set unit.
	void SetUnit(unsigned short iUnit)
	{
		m_iUnit = iUnit;
	}

	///@brief	Need Overwrite the scale?
	bool IsScaleOverwrited()
	{
		return m_bOverwriteScale;
	}

	///@brief	Set whether Overwrite the scale.
	void SetOverwriteScale(bool bOverwrite)
	{
		m_bOverwriteScale = bOverwrite;
	}

	///@brief	Get XY coordinates' scale.
	double GetScale()
	{
		return m_dXYScale;
	}

	///@brief	Set XY coordinates' scale.  Note only while "can Overwrite" then this function works.
	void SetScale(double dScale)
	{
		if (m_bOverwriteScale)
			m_dXYScale = dScale;
	}

	///@brief	Get inline start byte.
	unsigned short GetInlinePosition()
	{
		return m_iInlinePos;
	}

	///@brief	Set inline start bypte.
	void SetInlinePosition(unsigned short iPosition);

	///@brief	Get crossline start byte.
	unsigned short GetCrosslinePosition()
	{
		return m_iCrosslinePos;
	}

	///@brief	Set crossline start bypte.
	void SetCrosslinePosition(unsigned short iPosition);

	///@brief	Get crossline start byte.
	unsigned short GetOffsetPosition()
	{
		return m_iOffsetPos;
	}

	///@brief	Set crossline start bypte.
	void SetOffsetPosition(unsigned short iPosition);

	///@brief	Get crossline start byte.
	unsigned short GetAzimuthPosition()
	{
		return m_iAzimuthPos;
	}

	///@brief	Set crossline start bypte.
	void SetAzimuthPosition(unsigned short iPosition);

	///@brief	Get X start byte.
	unsigned short GetXPosition()
	{
		return m_iXPos;
	}

	///@brief	Set X start bypte.
	void SetXPosition(unsigned short iPosition);

	///@brief	Get Y start byte.
	unsigned short GetYPosition()
	{
		return m_iYPos;
	}

	///@brief	Set inline start bypte.
	void SetYPosition(unsigned short iPosition);

	///@brief	Get X start byte.
	unsigned short GetDXPosition()
	{
		return m_iDXPos;
	}

	///@brief	Set X start bypte.
	void SetDXPosition(unsigned short iPosition);

	///@brief	Get Y start byte.
	unsigned short GetDYPosition()
	{
		return m_iDYPos;
	}

	///@brief	Set inline start bypte.
	void SetDYPosition(unsigned short iPosition);

	///@brief	Get X start byte.
	unsigned short GetSEPosition()
	{
		return m_iSEPos;
	}

	///@brief	Set X start bypte.
	void SetSEPosition(unsigned short iPosition);

	///@brief	Get Y start byte.
	unsigned short GetDEPosition()
	{
		return m_iDEPos;
	}

	///@brief	Set inline start bypte.
	void SetDEPosition(unsigned short iPosition);

	///@brief	Get Y start byte.
	unsigned short GetFBPosition()
	{
		return m_iFBPos;
	}

	///@brief	Set inline start bypte.
	void SetFBPosition(unsigned short iPosition);

	///	Get the specified (index start from 1 rather than 0) trace header of the 1st segy file, do not delete the return pointer!
	CXSEGYTraceHeader*	GetOneTraceHeader(qint64 iTraceIndex);

	///	Get the specified (index start from 1 rather than 0) trace of the 1st segy file, pData should allocated by caller.
	bool GetOneTraceData(qint64 iTraceIndex, float* pData);

	///	Get the line header instance.
	CXSEGYLineHeader* GetLineHeader()
	{
		return m_pLineHeader;
	}

	///	Get all the SEGY files.
	QStringList& GetAllSEGYFiles()
	{
		return m_listStrSEGYFile;
	}

	///	Used by scan prestack gather, return value is the start position of current trace in the SEGY file.
	qint64 ReadAGatherTrace(QFile& qFile, unsigned int& iShotID, double& dX1, double& dY1, double& dSE, double& dX2, double& dY2, double& dDE, double& dFB);

	///	Read a trace, the file pointer moved to the begining of next trace.
	///	If the last pointer is NULL, only read the trace header.
	bool ReadATrace(QFile& qFile, int& iInline, int& iCrossline, float& fOffset, int& iAzimuth, double& dX, double& dY, char *pDataBuff = NULL);

	///	Read one line's trance header.  Only used by scanning trace header.
	bool ReadLineTrace(QFile& qFile, int& nTrace, int& iCrosslineInc, int& inline1, int& xline1,
		double &x1, double& y1, int& inline2, int& xline2, double& x2, double& y2);

	///	Scan offset information, return false means offset information not coincide for each CDP.
	bool ScanOffsetInfo(QFile& qFile);

	///	Get the UTM.
	CXSeismicUTMTool* GetUTMTool()
	{
		return m_pUTMTool;
	}
	///	Get the ORG UTM.
	CXSeismicUTMTool* GetOrgUTMTool()
	{
		return m_pOriUTMTool;
	}

	//	Reset the UTM
	void ResetUTMTool();

	///	Get the parent object, maybe NULL.
	CXObject *GetParentObject()
	{
		return m_pParentObject;
	}

	///	Get destinate survey name.
	QString GetDestSurveyName()
	{
		return m_strSurveyName;
	}

	///	Set destinate survey name.
	void SetDestSurveyName(QString strSurveyName)
	{
		m_strSurveyName = strSurveyName;
	}

	///	Get start time.
	float GetStartTime()
	{
		return m_fStartTime;
	}

	///	Set import start time.
	void SetImportStartTime(float fTime)
	{
		m_fStartImportTime = fTime;
	}

	///	Get import start time.
	float GetImportStartTime()
	{
		return m_fStartImportTime;
	}

	///	Set import end time.
	void SetImportEndTime(float fTime)
	{
		m_fEndImportTime = fTime;
	}

	///	Get import end time.
	float GetImportEndTime()
	{
		return m_fEndImportTime;
	}

	///	Set import smaple interval.
	void SetImportSampleInterval(float fInterval)
	{
		m_fImportSampleInterval = fInterval;
	}

	///	Get import sample interval.
	float GetImportSampleInterval()
	{
		return m_fImportSampleInterval;
	}

	///	Get import sample number.
	unsigned int GetImportSampleNumber();

	///	Get volume name.
	QString GetDVName()
	{
		return m_strDVName;
	}

	///	Set voume name.
	void SetDVName(QString strName)
	{
		m_strDVName = strName;
	}

	///	Get DV template.
	QUuid GetTemplate()
	{
		return m_seismicTemplate;
	}

	///	Set DV template.
	void SetTemplate(QUuid id)
	{
		m_seismicTemplate = id;
	}

	///	Set Datum.
	void SetDatum(float fDatum)
	{
		m_fImportDatum = fDatum;
	}

	///	Set the time shift to.
	void SetTimeShiftTo(float fTime)
	{
		m_fTimeShiftTo = fTime;
	}

	///	Set whether need slice file.
	void SetCreateSliceFile(bool bCreate)
	{
		m_bCreateSliceFile = bCreate;
	}

	///	Get whether need slice file.
	bool GetCreateSliceFile()
	{
		return m_bCreateSliceFile;
	}

	///	Set whether need brick file.
	void SetCreateBrickFile(bool bCreate)
	{
		m_bCreateBrickFile = bCreate;
	}

	///	Set whether need brick file.
	bool GetCreateBrickFile()
	{
		return m_bCreateBrickFile;
	}

	///	How much space required (unit is GB).
	QString GetRequiredSpaceString();
	qint64 GetRequiredSpaceValue();///>@ byte

	///	Get uint of Z
	QString GetZUnit()
	{
		return m_sZUnit;
	}

	///	Set unit of Z
	void SetUnitZ(QString sZUnit)
	{
		m_sZUnit = sZUnit;
	}

	///	Get the imported data volume.
	CXSeismicDataVolume* GetDataVolume();

	///	Get trace length in bytes (not include trace header)
	qint64 GetTraceLength()
	{
		return m_iTraceLength;
	}

	///	Convert one trace data from original SEGY format to float*
	void ConvertTraceData(char *pOriData, float *pDstData);

	///	Correct the DV time range after importing.
	void CorrectTimeRange();

	///	Automatically parse parameters from SEGY file.
	void AutoParseParameters();

	void SetDomainType(EDomainType eType)
	{
		m_eDomainType = eType;
	}

	EDomainType GetDomainType()
	{
		return m_eDomainType;
	}

	///	Refresh several parameters while flip line header.
	void RefreshParameters();
	void SetValidStartLine(int nStartLine)
	{
		m_iValidStartLine = nStartLine;
	}
	int GetValidStartLine()
	{
		return m_iValidStartLine;
	}
	void SetValidEndLine(int nEndLine)
	{
		m_iValidEndLine = nEndLine;
	}
	int GetValidEndLine()
	{
		return m_iValidEndLine;
	}

	void SetAzimuth(bool bAzimuth)
	{
		m_bAzimuth = bAzimuth;
	}

	bool IsAzimuth()
	{
		return m_bAzimuth;
	}

	void SetPrestack(bool bPrestack)
	{
		m_bPrestack = bPrestack;
	}

	bool IsPrestack()
	{
		return m_bPrestack;
	}

	unsigned int GetMaxFold()
	{
		return m_iMaxFold;
	}

	void SetMaxFold(unsigned int iMaxFold)
	{
		m_iMaxFold = iMaxFold;
	}

	unsigned int GetOffsetNumber()
	{
		return m_iNumOffset;
	}

	void SetOffsetNumber(unsigned int iNumOffset)
	{
		m_iNumOffset = iNumOffset;
	}

	void GetOffsetInfo(float& fStartOffset, float& fOffsetInc)
	{
		fStartOffset = m_fStartOffset;
		fOffsetInc = m_fOffsetInc;
	}

	float GetStartOffset()
	{
		return m_fStartOffset;
	}

	void SetStartOffset(float fStartOffset)
	{
		m_fStartOffset = fStartOffset;
	}

	float GetEndOffset()
	{
		return m_fEndOffset;
	}

	void SetEndOffset(float fEndOffset)
	{
		m_fEndOffset = fEndOffset;
	}

	int GetMinAzim()
	{
		return m_iMinAzi;
	}

	void SetMinAzim(int iAzim)
	{
		m_iMinAzi = iAzim;
	}

	int GetMaxAzim()
	{
		return m_iMaxAzi;
	}

	void SetMaxAzim(int iAzim)
	{
		m_iMaxAzi = iAzim;
	}

	bool IsIrregular()
	{
		return m_iMaxFold > 1 && m_fOffsetInc == 0.;
	}

	QHash<QPair<unsigned short, unsigned short>, SKETraceOffsets *>& GetTraceInfo()
	{
		return m_hashTraceInfo;
	}

	void FreeTraceInfo();

	void SetAzimuthInfo(bool bEast, bool bCounterclockwise)
	{
		m_bEast = bEast;
		m_bCounterclockwise = bCounterclockwise;
	}

	void GetAzimuthInfo(bool& bEast, bool& bCounterclockwise)
	{
		bEast = m_bEast;
		bCounterclockwise = m_bCounterclockwise;
	}

	bool IsDataLine()
	{
		return m_bDataLine;
	}

	void SetDataLine(bool bDataLine)
	{
		m_bDataLine = bDataLine;
	}

	bool IsPrestackGather()
	{
		return m_bPrestackGather;
	}

	void SetPrestackGather(bool bPrestackGather)
	{
		m_bPrestackGather = bPrestackGather;
	}

	CXPreStackGather* GetPrestackGather();

private:
	bool			m_bPrestack;					//	Prestack seismic?
	bool			m_bAzimuth;						//	Azimuth seismic?

	bool			m_bDataLine;					//	Only one line and want to imported as data line.

	int				m_iValidStartLine;				//	The valid min line number.
	int				m_iValidEndLine;				//	The valid max line number.
	QStringList		m_listStrSEGYFile;				//	List of multiple SEGY files.
	int				m_iDataType;					//	0: 32-bit IEEE float;	1: 32-bit IBM float;
													//	2: 32-bit integer;		3: 16-bit integer;		4: character	
	bool			m_bDataFlip;					//	Data need flip?  (IBM float always need flip!)

	unsigned short	m_iSampleNumber;				//	Number of samples per trace, original saved in line header.
	bool			m_bOverwriteSampleNumber;		//	Whether Overwrite the sample number mannually.

	float			m_fSampleInterval;				//	Sample Interval, original one saved in line header.
	bool			m_bOverwriteSampleInterval;		//	Whether Overwrite the sample interval.

	qint64			m_iTraceLength;					//	Trace length in byte, not include trace header.
	qint64			m_iTraceNumber;					//	Trace number of the 1st segy file.

	unsigned short	m_iUnit;						//	1 Meters;	2 Feet;
	bool			m_bOverwriteScale;				//	Whether overwrite the scale; 
	double			m_dXYScale;						//	Scale to the XY coordinate.

	unsigned short	m_iInlinePos;					//	Start byte of inline.
	unsigned short	m_iCrosslinePos;				//	Start byte of crossline.
	unsigned short	m_iXPos;						//	Start byte of X.
	unsigned short	m_iYPos;						//	Start byte of Y.
	unsigned short  m_iOffsetPos;					//	Start byte of offset.
	unsigned short  m_iAzimuthPos;					//	Start byte of azimuth.

	unsigned short	m_iInlineInd;					//	Item index of inline.
	unsigned short	m_iCrosslineInd;				//	Item index of crossline.
	unsigned short	m_iXInd;						//	Item index of X.
	unsigned short	m_iYInd;						//	Item index of Y.
	unsigned short  m_iOffsetInd;					//	Item index of offset.
	unsigned short  m_iAzimuthInd;					//	Item index of azimuth.

	unsigned short	m_iDXPos;						//	Start byte of X.
	unsigned short	m_iDYPos;						//	Start byte of Y.
	unsigned short	m_iDXInd;						//	Item index of X.
	unsigned short	m_iDYInd;						//	Item index of Y.

	unsigned short	m_iSEPos;						//	Start byte of Source Elev.
	unsigned short	m_iDEPos;						//	Start byte of Detector Elev.
	unsigned short	m_iFBPos;						//	Start byte of First break.
	unsigned short	m_iSEInd;						//	Item index of Source Elev.
	unsigned short	m_iDEInd;						//	Item index of Detector Elev.
	unsigned short	m_iFBInd;						//	Item index of First break.

	
	//	Below parameters used for prestack only.
	unsigned int	m_iMaxFold;

	float			m_fStartOffset;
	float			m_fEndOffset;
	float			m_fOffsetInc;
	unsigned int	m_iNumOffset;

	int				m_iMinAzi;
	int				m_iMaxAzi;

	//	Only used for prestack gather.
	bool	m_bPrestackGather;

	//	Only used for irregular offsets prestack.
	bool	m_bIrregularPrestack;
	bool	m_bEast;				//	Azimuth start from.
	bool	m_bCounterclockwise;	//	Azimuth oritentation.
	QHash<QPair<unsigned short, unsigned short>, SKETraceOffsets *>	m_hashTraceInfo;

	CXObject*		m_pParentObject;				//	The parent of the just loading volume.
	CXSeismicUTMTool	*m_pUTMTool;				//	UTM of imported 3D seismic volume.
	CXSeismicUTMTool	*m_pOriUTMTool;				//	UTM of the selected survey UTM.

	QString			m_strSurveyName;				//	Destinate survey name.

	float			m_fStartTime;					//	Start time of original segy.
	float			m_fStartImportTime;				//	Start time of import range.
	float			m_fEndImportTime;				//	End time of import range.
	float			m_fImportSampleInterval;		//	Import sample interval.

	float			m_fImportDatum;					//	Original datum of import volume.
	
	float			m_fTimeShiftTo;					//	Time shift to.

	EDomainType		m_eDomainType;

	QString			m_sZUnit;		

	QString			m_strDVName;					//	Name of the imported volume.
	QUuid			m_seismicTemplate;				//	Seismic template.

	bool			m_bCreateSliceFile;				//	Whether create slice file.
	bool			m_bCreateBrickFile;				//	Whether create brick file.

	char			m_pVolumeHeader[VOLUMEHEADERLENGTH];		//	3200 bytes ASCII volume header.

	CXSEGYLineHeader	*m_pLineHeader;				//	Pointer to a line header instance.
	CXSEGYTraceHeader	*m_pTraceHeader;			//	Pointer to a trace header instance.

	CXSeismicDataVolume	*m_pDV;					//	The imported DV.

	CXPreStackGather	*m_pGather;

	bool skipTraces(QFile&, qint64 pos);			//	Skip multiple traces, only used by scanning trace header.

	//	Read 4 traces to guess which byte is inline/crossline/X/Y.
	void guessTraceHeaderPosition();		
};

#endif