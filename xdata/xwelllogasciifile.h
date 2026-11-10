#ifndef _CXWELLLOGASCIIFILE_H__
#define _CXWELLLOGASCIIFILE_H__

#include "xdata_global.h"
#include "xasciifile.h"

///@brief	Used to represent an ASCII well log file being imported.
///@author	Xiong Xiong
///@date	Sep, 2015
///@see		
class XDATA_EXPORT CXWellLogASCIIFile : public CXASCIIFile
{
public:
	CXWellLogASCIIFile(QString sFile) : CXASCIIFile(eWellASCIILog, sFile)
	{
		m_iDepthID = 999;
	}

	void SetDepthID(unsigned int iIDX) { m_iDepthID = iIDX; }
	QStringList& GetTemplateList() { return m_sListTemplate; }

	virtual bool Import();

protected:
	unsigned int	m_iDepthID;			//	Which curve is the depth curve.
	QStringList		m_sListTemplate;	//	List of templates of each curve.
};

#endif