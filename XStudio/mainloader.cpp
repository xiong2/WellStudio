#include "mainloader.h"

#include <vector>

#include <QLibrary>
#include <QFile>
#include <QDesktopWidget>
#include <QTranslator>
#include <QMetaType>
#include <QFileInfo>

#include "xbaseparameter.h"
#include "xtemplate.h"
#include "xlog.h"
#include "xdbio.h"
#include "xconsole.h"
#include "xglobal.h"
#include "mainwindow.h"
#include "simple_license.h"
#include <fstream>
#include <QMessageBox>

bool NMainLoader::Init()
{
#ifdef NDEBUG
	//Below added by Xiong for license control.
	std::pair<bool, std::string> result;
	std::ifstream licFile("XStudio.lic", std::ios::binary);
	if (!licFile.is_open())
	{
		QMessageBox::warning(NULL, "Check License", "Can not find valid license file (XStudio.lic) !");
		std::exit(1);
	}
	else
	{
		licFile.seekg(258);
		PT::LicenseCrypto licenseCtypto(licFile, 1);
		result = licenseCtypto.Check();
	}

	if (!result.first)
	{
		QMessageBox::warning(NULL, "Check License Error", result.second.data());
		std::exit(1);
	}
#endif

	//! Load necessary libraries
	QLibrary libDataPlus("xdataplus");
	if (!libDataPlus.load())
	{
		CXLog::AddLog("Cannot find the dataplus library!", true);
		return false;
	}

	QLibrary libGUIPlus("xguiplus");
	if (!libGUIPlus.load())
	{
		CXLog::AddLog("Cannot find the GUIPlus library!", true);
		return false;
	}

	//! Init QVariantData
	qRegisterMetaTypeStreamOperators< std::vector<int> >("std::vector<int> ");
	qRegisterMetaTypeStreamOperators< std::vector<unsigned int> >("std::vector<unsigned int> ");
	qRegisterMetaTypeStreamOperators< std::vector<float> >("std::vector<float> ");
	qRegisterMetaTypeStreamOperators< std::vector<bool> >("std::vector<bool> ");
	qRegisterMetaTypeStreamOperators< std::vector<double> >("std::vector<double> ");
	qRegisterMetaTypeStreamOperators< std::vector<QUuid> >("std::vector<QUuid> ");
	qRegisterMetaTypeStreamOperators< std::vector<qint64> >("std::vector<qint64> ");
	qRegisterMetaTypeStreamOperators< QUuid >("QUuid ");

	//! Init Template
	if (!CXTemplate::InitializeTemplates())
	{
		CXLog::AddLog("Cannot find the template file to initialize the application!", true);
		return false;
	}

	//! Init DB Template
	if (!QFile::exists(CXDBIO::GetDefaultDBFileName()))
	{
		CXLog::AddLog("Cannot find the template database of the application!", true);
		return false;
	}

	//! Create console
	CXConsole* pConsole = new CXConsole();
	::SetConsole(pConsole);

	//! Create main window.
	CMainWindow* pMainWindow = new CMainWindow;
	pConsole->SetMainWindowWidget(pMainWindow);

	if (pMainWindow->IsMDI())
		pMainWindow->showMaximized();
	else
	{
		int mainHeight = QApplication::desktop()->height() * 0.93;
		pMainWindow->showNormal();
		pMainWindow->move(0, 0);
		pMainWindow->resize(400, mainHeight);
	}

	return true;
}

void NMainLoader::LoadTranslator()
{
	QTranslator translator;
	QString locale = QLocale::system().name();
	
#ifdef QT_NO_DEBUG
	translator.load("xgui_" + locale + ".qm");
	translator.load("xdata_" + locale + ".qm");
#else
	translator.load("../xgui/kegui_" + locale + ".qm");
	translator.load("../xdata/kedata_" + locale + ".qm");
#endif // QT_NO_DEBUG

	qApp->installTranslator(&translator);
}
