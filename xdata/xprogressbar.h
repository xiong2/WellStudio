#ifndef XPROGRESSBAR_H
#define XPROGRESSBAR_H

#include "xdata_global.h"
#include <qprogressdialog.h>

///@brief	The class provides a simple progress dialog
///@author	Yong Shu
///@date	11. 4th, 2015
///@see	
class XDATA_EXPORT CXProgressBar : public QProgressDialog
{
public:
	CXProgressBar(const QString& strWindowName, const QString& strTaskName, qint64 nTotalNum);
	~CXProgressBar();

	void SetValue(qint64 iValue);

	bool IsAborted();

private:
	qint64 m_nStep;
	int m_iCurrent;
};


#endif // KEPROGRESSBAR_H
