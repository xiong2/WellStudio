#include <QFile>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qnetworkinterface.h>
#include "xlicensemanager.h"
#include "xlog.h"

bool CXLicenseManager::CheckLicense()
{
	QFile qFile("./license.dat");
	if(!qFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(NULL, "Check License", "Can not find the license file!");
		CXLog::AddLog("Can not find the license file.");
		return false;
	}

	QTextStream stream(&qFile);
	QString strLicense = "";
	while(!stream.atEnd())
	{
		QString str = stream.readLine();

		if(str.startsWith("The license key is: "))
		{
			strLicense = str.remove("The license key is: ");
			break;
		}
	}

	if(strLicense == "")
	{
		QMessageBox::warning(NULL, "Check License", "Can not read license key from the license file!");
		CXLog::AddLog("Can not read license key from the license file!");
		return false;
	}

	QList<QNetworkInterface> listNI = QNetworkInterface::allInterfaces();
	if(listNI.size() == 0)
	{
		QMessageBox::warning(NULL, "Check License", "Can not read the network card information!");
		CXLog::AddLog("Can not read the network card information!");
		return false;
	}

	for(int i = 0; i < listNI.size(); i++)
	{
		QString strPA = listNI[i].hardwareAddress();
		QString strKey = CXLicenseManager::getKeyFromHAddress(strPA);

		if(strLicense == strKey)
		{
			CXLog::AddLog("License check successfully for network card " + strPA);
			return true;
		}
	}

	QMessageBox::warning(NULL, "Check License", "Can not find the valid license key!");
	CXLog::AddLog("Can not find the valid license key!");
	return false;
}

QString CXLicenseManager::getKeyFromHAddress(QString str)
{
	str.remove(QChar('-'));
	str.remove(QChar(':'));

	bool bFlag = true;
	QString strRes;
	for(int i = 0; i < str.length(); i++)
	{
		bFlag = !bFlag;

		int iUni = str[i].unicode();
		if(iUni % 2 == 0)
			iUni /= 2;

		if(i % 3 == 0)
			iUni += 9;

		if(i % 5 == 0)
			iUni += 7;

		if(bFlag)
			strRes = strRes + QString::number(iUni) + strRes.left(2);
		else 
			strRes = strRes.right(1) + QString::number(iUni) + strRes;
	}

	return strRes;
}