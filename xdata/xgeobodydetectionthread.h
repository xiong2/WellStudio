#ifndef _CXGEOBODYDETECTIONTHREAD_H__
#define _CXGEOBODYDETECTIONTHREAD_H__ 

#include <qbitarray.h>
#include <vector>
#include "xdata_global.h"
#include "xbasethread.h"

class CXParametersGeobodyDetection;
class CXSeismicUTMTool;
class CXBrickReader;
class CXGeobody;

/**
*@brief		This class is a thread that detect geobody on seismic data volume.
*@author	Xiong Xiong
*@date		Nov, 2015
*/
class XDATA_EXPORT CXGeobodyDetectionThread : public CXBaseThread
{
public:
	///@brief Constructor
	CXGeobodyDetectionThread(CXParametersGeobodyDetection* pDetectionParameters);

	///@brief Destructor
	virtual ~CXGeobodyDetectionThread();

	///@brief Get output results
	std::vector<CXGeobody*> GetOutput() { return m_vecOutput; }

protected:
	///@brief Reimplementation of run()
	virtual void RunThread();

private:
	CXParametersGeobodyDetection*	m_pDetectionParameters;		//	Pointer to the load parameters instance.
	CXBrickReader*					m_pBFReader;				//	Brick file reader.
	CXSeismicUTMTool*				m_pUTM;						//	UTM of the bounding box of the output geobody.
	std::vector<bool>				m_vecFlags;					//	Used to store the flags of whether a sample be tracked.

	unsigned char	m_cLowTh;		//	Threshold in 8 bits.
	unsigned char	m_cHighTh;
	float			m_fSZ;
	float			m_fEZ;
	double			m_dZInc;
	int				m_nZ;

	//	Judge one cell specified by index whether a valid geobody cell.
	bool isOneCell(qint64 iIDX);

	void wipeOutInsideCells(QVector<qint64>& vecOutputCells, QVector<qint64>& vecInputCells);

	std::vector<CXGeobody*> m_vecOutput;
};

#endif