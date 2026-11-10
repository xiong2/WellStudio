#include "xprestackdatareaderbuff.h"
#include "xseismicdatavolume.h"
#include "xsysteminfo.h"

CXPrestackDataReaderBuff::CXPrestackDataReaderBuff()
{

}

CXPrestackDataReaderBuff::~CXPrestackDataReaderBuff()
{
	for (int iDV = 0; iDV < m_vecmapBuff.size(); ++iDV)
	{
		QMap<QPair<int, int>, float*>::iterator it;
		for (it = m_vecmapBuff[iDV].begin(); it != m_vecmapBuff[iDV].end(); ++it)
		{
			delete []it.value();
			delete []m_vecmapOffAzi[iDV].value(it.key());
		}

		m_vecmapBuff[iDV].clear();
		m_vecmapOffAzi[iDV].clear();
		m_vecmapFold[iDV].clear();

	}	

	m_vecmapBuff.clear();
	m_vecmapOffAzi.clear();
	m_vecmapFold.clear();
	m_vecVecIndex.clear();

}

void CXPrestackDataReaderBuff::Init(const vector<CXSeismicDataVolume*>& vecDV, int nMaxNZ, int nMaxFold)
{
	m_vecDV = vecDV;
	int nDV = (int) vecDV.size();
	m_vecmapBuff.resize(nDV);
	m_vecmapOffAzi.resize(nDV);
	m_vecVecIndex.resize(nDV);
	m_vecmapFold.resize(nDV);

	m_nMaxNZ = nMaxNZ;
	m_nMaxFold = nMaxFold;

	qint64 nFreeMemory = CXSystemInfo::GetFreeMemory();
	nFreeMemory *= 1000000;

	nFreeMemory = nFreeMemory * 3 / 4;

	qint64 nGatherSize = nMaxNZ*nMaxFold * 4;

	m_nMaxBlockNum = (nFreeMemory / nGatherSize) / nDV;
}

bool CXPrestackDataReaderBuff::Read(int iDV, int iInline, int iXline, float* pGatherData, QVector<float>& vecOffsetAzi)
{
	if (iDV < 0 || iDV >= m_vecDV.size())
		return false;

	QPair<int, int> index = qMakePair(iInline, iXline);

	if (!m_vecmapBuff[iDV].contains(index))
	{
		if (!_ReadOneGather(iDV, iInline, iXline))
			return false;
	}

	memcpy(pGatherData, m_vecmapBuff[iDV].value(index), sizeof(float)*m_nMaxNZ*m_nMaxFold);

	int nFoldX2 = m_vecmapFold[iDV].value(index);
	vecOffsetAzi.resize(nFoldX2);

	memcpy(&vecOffsetAzi[0], m_vecmapOffAzi[iDV].value(index), sizeof(float)*nFoldX2);

	return true;


}

bool CXPrestackDataReaderBuff::_ReadOneGather(int iDV, int iInline, int iXline)
{
	float* pGatherData = NULL;
	float* pOffsetAzi = NULL;

	if (m_vecmapBuff[iDV].size() < m_nMaxBlockNum)
	{
		try
		{
			pGatherData = new float[m_nMaxNZ*m_nMaxFold];
			pOffsetAzi = new float[m_nMaxFold * 2];
		}
		catch (std::bad_alloc)
		{
			return false;
		}

	}
	else
	{
		QPair<int, int> oldIndex = m_vecVecIndex[iDV].front();

		pGatherData = m_vecmapBuff[iDV].value(oldIndex);
		pOffsetAzi = m_vecmapOffAzi[iDV].value(oldIndex);

		m_vecmapBuff[iDV].remove(oldIndex);
		m_vecmapOffAzi[iDV].remove(oldIndex);
		m_vecmapFold[iDV].remove(oldIndex);

		m_vecVecIndex[iDV].pop_front();
	}

	QVector<float> vecOffAzi;

	if (!m_vecDV[iDV]->GetTraceDataAt(iInline, iXline, pGatherData, vecOffAzi))
		return false;

	QPair<int, int> newIndex = qMakePair(iInline, iXline);

	// data
	m_vecmapBuff[iDV].insert(newIndex, pGatherData);

	// fold
	int nFoldX2 = vecOffAzi.size();
	memcpy(pOffsetAzi, &vecOffAzi[0], sizeof(float)*nFoldX2);
	m_vecmapOffAzi[iDV].insert(newIndex, pOffsetAzi);

	m_vecmapFold[iDV].insert(newIndex, nFoldX2);

	// index
	m_vecVecIndex[iDV].push_back(newIndex);

	return true;
}