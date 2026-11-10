#include "xlicense.h"
#include <QtWidgets/QApplication>
#include "xlog.h"

int main(int argc, char *argv[])
{
	//Log
#ifdef NDEBUG
	CXLog::Clear();
	qInstallMessageHandler(CXLog::LogHandler);
#endif

	QApplication a(argc, argv);
	CXLicense w;
	w.show();
	return a.exec();
}
