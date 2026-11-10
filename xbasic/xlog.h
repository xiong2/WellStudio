#ifndef _CXLog_H__
#define _CXLog_H__

#include "xbasic_global.h"

///@brief	This class offer a convenient API to write log.
class XBASIC_EXPORT CXLog
{
public:
	static void AddLog(QString str, bool showMessageBox = false);
	static void LogHandler(QtMsgType type, const QMessageLogContext& context, const QString& log);
	static void Clear();
};

#endif