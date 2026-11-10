#pragma once

#include <qobject.h>
#include <qprocess.h>
#include <qstringlist.h>
#include <qjsonobject.h>
#include "xdataplus_global.h"

class QProcess;
class CXSeismicDataVolume;

class XDATAPLUS_EXPORT CXPythonProcess :public QObject
{
	Q_OBJECT
public:
	CXPythonProcess(QString strScriptFileName, QObject *parent = nullptr);
	~CXPythonProcess();

	bool StartProcessWithModel(QJsonObject& jsonObject);

private slots:
	void slotReadStandardOutput();
	void slotProcessStarted();
	void slotProcessError(QProcess::ProcessError error);

private:
	void _KillPythonEXE();
	void _StartProcess();
	QString _GetCurrentTime();
	void _KillProcess();
	

private:
	QProcess* m_pProcess;

	QString m_strJsonFileName;

	QString m_strPythonEXEFileName;

	QString m_strScriptFileName;

	bool m_bStarted;
};
