#ifndef _CXWavelet_H__
#define	_CXWavelet_H__

#include "xdata_global.h"
#include "xobject.h"

extern int XDATA_EXPORT fft(double *fr, double *fi, int n, int flag);
extern double XDATA_EXPORT dsinc(double x);

class XDATA_EXPORT CXWavelet: public CXObject
{
public:
	CXWavelet(QString sName = "");
	~CXWavelet();

	///	Re-set the data by given points.
	void ResetData(double fStart, double fStep, unsigned int iNumPoints, double*pData);

	///	Get data range.
	void GetDepthRange(double& fStart, double& fEnd);

	virtual QString GetTypeString() { return "Seismic Wavelet"; }

	virtual QStringList GetDescription();

	double GetStep()
	{
		return m_dStep;
	}

	double GetStartTime()
	{
		return m_dStart;
	}

	double* GetData();

	///	Copy the data to the given pointer (space already allocated), INVALID value be used if beyond the data range.
	bool GetData(double *pData, double dStartDepth, unsigned int iNumPoints);

	/// Copy the data to the given vector by range MD.
	void GetData(double dStartDepth, double dEndDepth, vector<double> &vec);

	///	Get point number.
	unsigned int GetPointNumber()
	{
		return m_nSamplingNum;
	}

	///	Get unit (from the template actually.
	QString GetUnit();

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);

protected:	
	double				m_dStep;			//	The step of each point along the well (in MD).
	double				m_dStart;			//	The start of measured points (in MD)	
};

#endif