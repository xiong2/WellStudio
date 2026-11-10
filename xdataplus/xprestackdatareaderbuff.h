#ifndef XPRESTACKDATAREADERBUFF_H
#define XPRESTACKDATAREADERBUFF_H

#include <vector>
#include <qmap.h>
#include <qpair.h>
#include <qvector.h>
#include "xdataplus_global.h"

using std::vector;

class CXSeismicDataVolume;

/**
* @class CXPrestackDataReaderBuff provided in the file "keprestackdatareaderbuff.h"
* @brief The class provides memory buffers for reading 3-D prestack seismic data 
* @author Yong Shu
* @date 10/19/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXPrestackDataReaderBuff
{
public:
	CXPrestackDataReaderBuff();
	~CXPrestackDataReaderBuff();

	void Init(const vector<CXSeismicDataVolume*>& vecDV, int nMaxNZ, int nMaxFold);

	bool Read(int iDV, int iInline, int iXline, float* pGatherData, QVector<float>& vecOffsetAzi);

private:
	bool _ReadOneGather(int iDV, int iInline, int iXline);

private:
	vector<CXSeismicDataVolume*> m_vecDV;

	int m_nMaxNZ, m_nMaxFold;

	int m_nMaxBlockNum;

	vector<QMap<QPair<int, int>, float*> > m_vecmapBuff;
	vector<QMap<QPair<int, int>, float*> > m_vecmapOffAzi;
	vector<QMap<QPair<int, int>, int> > m_vecmapFold;

	vector<QVector<QPair<int, int> > > m_vecVecIndex;
	
	
};

#endif // KEPRESTACKDATAREADERBUFF_H
