#pragma warning( push ,0 )
#include "xpythonprocess.h"
#include <qcoreapplication.h>
#include <QMessageBox>
#include <qdir.h>
#include <qtimer.h>
#include <qdebug.h>
#include <qdatetime.h>
#include <qfile.h>
#include <qapplication.h>


#include <qjsonobject.h>
#include <qjsondocument.h>
#include "xproject.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
#include <qjsondocument.h>


#ifdef WIN32
#include <windows.h>	
#else
#endif

#pragma warning( pop )


CXPythonProcess::CXPythonProcess(QString strScriptName, QObject *parent) : QObject(parent)
{	
	m_bStarted = false;

	m_strJsonFileName = ::GetProject()->GetProjectDataPath() + QUuid::createUuid().toString() + ".json";
	
	m_strPythonEXEFileName = QCoreApplication::applicationDirPath() + "/python/python.exe";
	m_strScriptFileName = QCoreApplication::applicationDirPath() + "/python/Lib/gss/" + strScriptName + ".py";
	if (!QFile::exists(m_strScriptFileName))
		m_strScriptFileName = QCoreApplication::applicationDirPath() + "/python/Lib/gss/" + strScriptName + ".pyc";
	
	//cnn_fault_prediction
	m_pProcess = nullptr;
}

CXPythonProcess::~CXPythonProcess()
{
	_KillProcess();
}

bool CXPythonProcess::StartProcessWithModel(QJsonObject& jsonObject)
{
	QJsonDocument doc(jsonObject);

	QFile qFile(m_strJsonFileName);
	if (!qFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(nullptr, ::g_strProductName, "Cannot open the parameter file to write.");
		return false;
	}

	qFile.write(doc.toJson());

	_StartProcess();

	return true;
}

void CXPythonProcess::_KillPythonEXE()
{	
#ifdef WIN32
	QString strProcess = QString("taskkill /f /im python.exe");
	QProcess process;
	process.start(strProcess);
	process.waitForFinished();
#endif

}

void CXPythonProcess::_KillProcess()
{
	if (!m_pProcess)
		return;

#ifdef WIN32
	qint64 pid = m_pProcess->processId();

	QString strProcess = QString("taskkill /t /f /pid %1").arg(pid);
	QProcess process;
	process.start(strProcess);
	process.waitForFinished();
#endif

	m_pProcess->kill();
	m_pProcess->waitForFinished(100);
	delete m_pProcess;
	m_pProcess = nullptr;
}


void CXPythonProcess::_StartProcess()
{
	_KillProcess();

	if (!QFile::exists(m_strJsonFileName))
	{
		QMessageBox::warning(nullptr, ::g_strProductName, "Cannot find the parameter file.");
		return;
	}

	if (!QFile::exists(m_strPythonEXEFileName))
	{
		QMessageBox::warning(nullptr, ::g_strProductName, "Cannot find the python interpreter.");
		return;
	}

	if (!QFile::exists(m_strScriptFileName))
	{
		QMessageBox::warning(nullptr, ::g_strProductName, "Cannot find the python scripts.");
		return;
	}

	m_pProcess = new QProcess();

	QObject::connect(m_pProcess, &QProcess::started, this, &CXPythonProcess::slotProcessStarted);
	QObject::connect(m_pProcess, &QProcess::readyReadStandardOutput, this, &CXPythonProcess::slotReadStandardOutput);
	QObject::connect(m_pProcess, &QProcess::readyReadStandardError, this, &CXPythonProcess::slotReadStandardOutput);
	QObject::connect(m_pProcess, &QProcess::errorOccurred, this, &CXPythonProcess::slotReadStandardOutput);

	QString strEXEPathName = "\"" + m_strPythonEXEFileName + "\""; // for bug the cannot run in "Program Files"

	//m_pProcess->setCreateProcessArgumentsModifier(
	//	[](QProcess::CreateProcessArguments *args) {
	//	args->flags |= CREATE_NEW_CONSOLE;
	//	args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
	//	args->startupInfo->dwFlags |= STARTF_USEFILLATTRIBUTE;
	//});

	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	QString strPath1 = QCoreApplication::applicationDirPath() + "\\python\\Library\\bin";
	QString strPath2 = QCoreApplication::applicationDirPath() + "\\python\\Lib\\site-packages";

	env.insert("PATH", env.value("Path") + ";" + strPath1);
	env.insert("PATH", env.value("Path") + ";" + strPath2);
	m_pProcess->setProcessEnvironment(env);


	QStringList listAug;
	listAug << "\"" + m_strScriptFileName + "\"";
	listAug << "\"" + m_strJsonFileName + "\"";

	QString strScriptFileName = "\"" + m_strScriptFileName + "\"";
	QString strJsonFileName = "\"" + m_strJsonFileName + "\"";

	//QString strCommand = m_strPythonEXEFileName + " " + m_strScriptFileName;
	QString strCommand = strEXEPathName + " " + strScriptFileName + " " + strJsonFileName;

	m_pProcess->start(strCommand.toLatin1().data());
	m_pProcess->waitForStarted();
}

void CXPythonProcess::slotProcessError(QProcess::ProcessError error)
{
	QString strMng = QString("Process error code: %1").arg(QString::number(int(error)));
	QMessageBox::warning(nullptr, g_strProductName, strMng);
}

QString CXPythonProcess::_GetCurrentTime()
{
	return QDateTime::currentDateTime().toString("MMMM d yyyy hh:mm:ss");
}

void CXPythonProcess::slotReadStandardOutput()
{
	if (!m_pProcess)
		return;

	QByteArray byteArray = m_pProcess->readAllStandardOutput();
	QString strParagraph = QString(byteArray.data()).simplified();

	qDebug() << strParagraph;

}


void CXPythonProcess::slotProcessStarted()
{
	m_bStarted = true;
	
}
