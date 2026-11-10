#ifndef XTHREADLFMUPSCALING_H
#define XTHREADLFMUPSCALING_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>

class CXParameterUpscaling;
class CXObject;
class CXLFMUpscalingGeometry;
class CXLFMUpscalingAttribute;


/**
* @class CXThreadLFMUpscaling provided in the file "kethreadlfmupscaling.h"
* @brief The Class provides a thread to calculate upscaling results
*
* @author Yong Shu
* @date 11/25/2015
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadLFMUpscaling : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadLFMUpscaling(CXParameterUpscaling* pPara, CXObject* pObj);
	virtual ~CXThreadLFMUpscaling();

	///@brief Get output
	QList<CXLFMUpscalingAttribute*> GetOutput() { return m_listOutput; }
	

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _CalcOneAlis(int iAliasIndex);

	double _CalcOneSement(int nSampleNum, double* pCurveData, int iTop, int iBot); 
private:
	CXParameterUpscaling* m_pPara;
	CXLFMUpscalingGeometry* m_pLFMUpscalingGeometry;

private:
	QList<CXObject*> m_listAlias;

	int m_iAverageMethod;

	QList<CXLFMUpscalingAttribute*> m_listOutput;



};

#endif // KETHREADLFMUPSCALING_H
