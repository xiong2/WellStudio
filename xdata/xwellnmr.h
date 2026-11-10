#ifndef CXWELLNMR_H
#define CXWELLNMR_H

#include "xdata_global.h"
#include "xobject.h"
#include <QFile>

/**
* @class CXWellNMR in the file "kewellnmr.h"
* @brief The class provides data structure for a NMR Data
* 
* @author Tian Lin
* @date 7/27/2016
* @see 
*/
class  XDATA_EXPORT CXWellNMR : public CXObject
{
public:
	///@brief Constructor and destructor
    CXWellNMR ();
	CXWellNMR(double dSamplingStart, double dSamplingRate, int iSamplingNum, 
		double dHorizontalStart, double dHorizontalRate, int iHorizontalNum, const QString& strName = "");
    virtual ~CXWellNMR (); 

	virtual QString GetTypeString();

	virtual int GetTraceNumber(){ return m_nTraceNum; };
	virtual int GetSamplingQty(){ return m_Num_2D; };
	virtual double GetDepthStart(){ return m_dSamplingStart; }
	virtual double GetDepthStop(){ return m_dSamplingRate*(m_nTraceNum-1)+m_dSamplingStart; }
	virtual double GetDepthRate(){ return m_dSamplingRate; }
	virtual double GetHorizonStart(){ return m_dHorizontalStart; }
	virtual double GetHorizonStop() { return m_dHorizontalRate*(m_Num_2D-1)+ m_dHorizontalStart; }
	virtual double GetHorizonRate() { return m_dHorizontalRate; }

	void CloseFile();
	float* GetDataCache();//仅获取缓存
	virtual float* ReadTraceData(int iIndex,float* pCopyData = NULL);	//ReadTraceData和WriteTraceData模式切换需要先CloseFile
	virtual bool WriteTraceData(int iIndex);//ReadTraceData和WriteTraceData模式切换需要先CloseFile



	///	For regular volume, it's inline * xline * offset number; for irregular volume...
	qint64 GetTotalTraceQty();


	///@brief Get file names
	QString GetTraceFileName();

	///@brief Only used by irregular offsets pre-stack volume.
	QString GetTraceInfoFileName();


	///@brief Reimplement to save/load the data
    virtual bool SerializeData(CXArchive &ar);

	///@brief Get the max value
	float GetMaxValue();

	virtual QStringList GetDescription(); 

protected:
	virtual void _SetSelfDimension();
	float* m_pTraceData;
	double m_dSamplingStart, m_dSamplingRate;
	double m_dHorizontalStart, m_dHorizontalRate;
	int m_nTraceNum;

	int m_Num_2D;

	QFile m_fileTrace;
};

#endif // RLSEISMICDATAVOLUME_H
