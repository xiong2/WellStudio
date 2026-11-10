#ifndef XGEOQUESTCARDIMAGE7FILE_H__
#define XGEOQUESTCARDIMAGE7FILE_H__

#include "xdataplus_global.h"
#include "xasciifile.h"

class XDATAPLUS_EXPORT CXGeoQuestCardImage7File : public CXASCIIFile
{
public:
	CXGeoQuestCardImage7File(QString sFile, bool bHorizon = true);
	virtual bool Import();

protected:
	bool	m_bHorizon;

	bool importHorizon();
	bool importFault();
};
	
#endif