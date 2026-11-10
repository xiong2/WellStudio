#ifndef XTHREADCALCHISTOGRAM_H
#define XTHREADCALCHISTOGRAM_H


#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QFile>
#include "xhistogram.h"


/**
* @class CXThreadCalcHistogram provided in the file "kethreadcalchistogram.h"
* @brief The Class provides a thread to calculate histogram from the data file
*
* @author Yong Shu
* @date 11/19/2015
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadCalcHistogram : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadCalcHistogram(const QString& strFileName, int nK);
	virtual ~CXThreadCalcHistogram();

	CXHistogram& GetHistogram() { return m_histogram; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	QFile m_qFile;

	qint64 m_nK, m_nTraceNum;

	CXHistogram m_histogram;

};

#endif // KETHREADCALCHISTOGRAM_H
