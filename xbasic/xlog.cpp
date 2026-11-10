#include "xlog.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QTextStream>
#include <QMessageBox>

void CXLog::AddLog(QString str, bool showMessageBox)
{
    static QFile qFile("./XLog.txt");

    if ( qFile.exists() ) {
        if ( !qFile.open(QIODevice::Append | QIODevice::Text) ) return;
    } else {
        if ( !qFile.open(QIODevice::WriteOnly | QIODevice::Text) ) return;
    }

    str = "[" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "] " + str + "\n";

    qFile.write(str.toUtf8().constData());

    qFile.close();

	if (showMessageBox)
		QMessageBox::warning(NULL, "Warning", str);
}

void CXLog::LogHandler(QtMsgType type, const QMessageLogContext & context, const QString & log)
{
	static QFile file("./XTempLog.txt");
	
	if (!file.open(QIODevice::Append | QIODevice::Text))
		return;

	QTextStream in(&file);
	in << "[" << QDateTime::currentDateTime().toString(Qt::ISODate) << "]";

	QByteArray localLog = log.toLocal8Bit();
	switch (type)
	{
	case QtDebugMsg:
		in << "[Debug]";
		break;
	case QtInfoMsg:
		in << "[Info]";
		break;
	case QtWarningMsg:
		in << "[Warning]";
		break;
	case QtCriticalMsg:
		in << "[Critical]";
		break;
	case QtFatalMsg:
		in << "[Fatal]";
		break;
	}

	in << "[" << context.file << "][" << context.line << "]" << log << "\n";

	file.close();
}

void CXLog::Clear()
{
	QFile file("./XTempLog.txt");
	file.remove();
}
