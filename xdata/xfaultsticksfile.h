#ifndef _CXFaultStickSFILE_H__
#define _CXFaultStickSFILE_H__

#include "xdata_global.h"
#include "xasciifile.h"

class CXFaultStick;

///@brief	Used to represent an ASCII fault sticks file being imported.
///@author	Xiong Xiong
///@date	Apr, 2014
///@see		
class XDATA_EXPORT CXFaultSticksFile: public CXASCIIFile
{
public:
	CXFaultSticksFile(QString sFile, EImportFileType eFileType): CXASCIIFile(eFileType, sFile)
	{
	}

	virtual bool Import();

	virtual bool CheckSelectedColumns(QStringList&) override;

	void SetSurveyID(QUuid surveyID)
	{
		m_surveyID = surveyID;
	}

protected:
	bool importFaultSticks();
	bool importFaultPolygons();

	void checkStickType(CXFaultStick *);
	
	QUuid	m_surveyID;
};

#endif