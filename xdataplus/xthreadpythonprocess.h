#pragma once

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include "xseismicutmtool.h"

class CXObject;

/**
* @class CXThreadPythonProcess provided in the file "xthreadpythonprocess.h"
* @brief The Class provides a thread to deal with python process
*
* @author Pr
* @date 3/9/2022
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadPythonProcess : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadPythonProcess(QList<CXObject*> listLockingObj, QList<CXObject*> listDeletingObj, QString strStopFileName, QString strProgressFileName, QString strMng);
	virtual ~CXThreadPythonProcess();

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _WriteStopFile(int iStop);
	void _ReadProgressFile();

private:
	QList<CXObject*> m_listLockingObj;
	QList<CXObject*> m_listDeletingObj;

	QString m_strStopFileName;
	QString m_strProgressFileName;
	QString m_strMng;

	bool m_bWriteSuccess, m_bReadSuccess;

	int m_nTotalStep, m_nCurStep, m_iError;
};

