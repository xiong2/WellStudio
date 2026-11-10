#ifndef _CXTRACECONTAINER_H__
#define _CXTRACECONTAINER_H__

#include <qvector.h>
#include <qfile.h>
#include "xdata_global.h"

struct SKETraceInfo;
struct SKEOneTrace
{
	SKETraceInfo*	m_pTraceInfo;
	float*			m_pData;
};

/**
* @class CXTraceContainer in the file "ketracecontainer.h"
* @brief Offers an internal-used instance that help doing the partial stack of 5D seismic data.
* @author Xiong
* @date Sep 2016
* @see
*/
class XDATA_EXPORT CXTraceContainer
{
public:
	CXTraceContainer(int iTimeStep, int nZ, std::vector<int> vecOffset, std::vector<int> vecAzi, bool bOffsetFirst, QString sDataFile, QString sTIFile);
	~CXTraceContainer();

	bool AddOneTrace(SKEOneTrace);

	void StackOneCDP();

private:
	int		m_iTimeStep;
	int		m_nZ;
	bool	m_bOffsetFirst;

	std::vector<int>	m_vecOffset;
	std::vector<int>	m_vecAzi;

	QVector<SKEOneTrace>*	m_pVector;
	QFile	m_qFileData;
	QFile	m_qFileTI;

	SKETraceInfo*	m_pTIBuffer;
	float*			m_pDataBuffer;
};

#endif