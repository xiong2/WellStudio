#include <qtextcodec.h>
#include "mainloader.h"
#include "xlog.h"

int main(int argc, char* argv[])
{
	//Log
#ifdef NDEBUG
	CXLog::Clear();
	qInstallMessageHandler(CXLog::LogHandler);
#endif

    QApplication a(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

	NMainLoader::LoadTranslator();

	if (!NMainLoader::Init())
		return 0;

    return a.exec();
}
