#pragma warning( push ,0 )
#include "xthreadpythonprocess.h"
#include "xseismicdatavolume.h"
#include <QCoreApplication>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xproject.h"
#include "xutility.h"
#include <QFile>
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>

#pragma warning( pop )


CXThreadPythonProcess::CXThreadPythonProcess(QList<CXObject*> listLockingObj, QList<CXObject*> listDeletingObj,
	QString strStopFileName, QString strProgressFileName, QString strMng)
	:m_listLockingObj(listLockingObj), m_listDeletingObj(listDeletingObj), m_strStopFileName(strStopFileName), m_strProgressFileName(strProgressFileName),
	m_strMng(strMng)
{
	m_bWriteSuccess = false;
	m_bReadSuccess = false;

	for (auto pObj : m_listLockingObj)
		LockRead(pObj);

	_WriteStopFile(0);
}

CXThreadPythonProcess::~CXThreadPythonProcess()
{
	wait();

	for (auto pObj : m_listLockingObj)
		UnlockRead(pObj);

	if (IsStopped())
	{
		for (auto pObj : m_listDeletingObj)
			delete pObj;

		m_listDeletingObj.clear();
	}

	QFile::remove(m_strStopFileName);
	QFile::remove(m_strProgressFileName);
}

void CXThreadPythonProcess::_WriteStopFile(int iStop)
{
	QFile qFile(m_strStopFileName);
	if (!qFile.open(QIODevice::WriteOnly))
	{
		m_bWriteSuccess = false;
	}
	else
	{
		qFile.write((char*)&iStop, sizeof(int));
		m_bWriteSuccess = true;
	}
}

void CXThreadPythonProcess::_ReadProgressFile()
{
	QFile qFile(m_strProgressFileName);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		m_bReadSuccess = false;
	}
	else
	{
		vector<int> buff(3);
		qFile.read((char*)&buff[0], sizeof(int) * 3);
		m_nTotalStep = buff[0];
		m_nCurStep = buff[1];
		m_iError = buff[2];

		m_bReadSuccess = true;
	}
}

void CXThreadPythonProcess::RunThread()
{
	this->EmitSetWindowName(m_strMng);
	this->EmitSetTaskName("Calculating");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	while (!m_bWriteSuccess)
	{
		_WriteStopFile(0);
		msleep(100);
	}

	//this->EmitUpdateProgress(0, m_pOutputDV->GetInlineQty());

	while (true)
	{
		if (IsStopped())
		{
			m_bWriteSuccess = false;

			while (!m_bWriteSuccess)
			{
				_WriteStopFile(1);
				msleep(100);
			}
			return;
		}
		else
		{
			m_bReadSuccess = false;
			while (!m_bReadSuccess)
			{
				if (IsStopped())
					return;

				_ReadProgressFile();
				msleep(200);
			}

			this->EmitUpdateProgress(m_nCurStep, m_nTotalStep);

			if (m_nCurStep == m_nTotalStep || m_iError > 0)
				break;
		}
	}
}


