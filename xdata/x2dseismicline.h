#ifndef _CX2DSEISMICLINE_H__
#define _CX2DSEISMICLINE_H__

#include "xdata_global.h"
#include "xobject.h"

///@brief	The class used to represent a 2D seismic line.
///@author	Xiong Xiong
///@date	Sep, 2015
///@see		

class CXSeismicDataLine;

class XDATA_EXPORT CX2DSeismicLine : public CXObject
{
public:
	CX2DSeismicLine(QString strName = "");
	~CX2DSeismicLine();

	void PopulateData(unsigned int numTraces, unsigned int* pCDP, double *pX, double *pY);

	virtual QString GetTypeString() { return "2D Seismic Line"; }

	virtual QStringList GetDescription();

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	unsigned int GetTraceNumber() { return m_numTraces; }

	///@brief Overwrite the super class' implementation to avoid dead-loop nest.	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	///@brief Getter
	unsigned int* GetCDPData() { return m_pCDP; }
	void GetCoordData(double* &pX, double* &pY) { pX = m_pX; pY = m_pY; }

	std::pair<double, double> GetOffset() { return std::make_pair(m_dOffsetX, m_dOffsetY); }
	void SetOffset(const double& offsetX, const double& offsetY) { m_dOffsetX = offsetX; m_dOffsetY = offsetY; }

	///	Get the indices of inflexion.
	QList<int>& GetInflexionIndices() { return m_listInflexionInd; }

	CXSeismicDataLine* GetDefaultSection(bool bIncludePrestack);

protected:
	virtual void _SetSelfDimension();

	void calculateInflexions();

	void freeMemory();

	unsigned int	m_numTraces;
	unsigned int*	m_pCDP;
    double*			m_pX;
    double*			m_pY;
	
	double			m_dOffsetX = 0.0;
	double			m_dOffsetY = 0.0;

	QList<int>		m_listInflexionInd;
};

#endif