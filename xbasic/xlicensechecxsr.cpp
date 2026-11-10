#include "xlicensechecker.h"

#include <QFile>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>
#include <QNetworkInterface>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

#include "xsimplecrypt.h"

const QString CXLicenseChecker::LICENSE_VERSION0 = "EncryptXStudio0";
const QString CXLicenseChecker::LICENSE_VERSION1 = "EncryptXStudio1";
const QString CXLicenseChecker::LICENSE_FILE_NAME = "license.lic";
const QString CXLicenseChecker::LICENSE_PRIVILEGE = "On the Origin of Species by Means of Natural Selection, or the Preservation of Favoured Races in the Struggle for Life";

bool CXLicenseChecker::Check(const QString &app)
{
	m_strError.clear();

	m_licInfo = DecryptoToInfo(LICENSE_FILE_NAME, m_strError);
	if (!m_strError.isEmpty())
		return false;

	if (!_CheckTime(m_licInfo, m_strError))
		return false;

	if (LICENSE_PRIVILEGE == m_licInfo.privilege)
		return true;

	if (!GetLocalMACAddress().contains(m_licInfo.mac.toUpper()))
	{
		m_strError = "MAC address does not match.";
		return false;
	}

	if (GetLocalHostname() != m_licInfo.pcname)
	{
		m_strError = "Computer name does not match.";
		return false;
	}

	if (!m_licInfo.apps.contains(app))
	{
		m_strError = app + " authentication is required.";
		return false;
	}

	return true;
}

QList<bool> CXLicenseChecker::Check(QStringList apps)
{
	QList<bool> listRet{ false, false, false ,false };

	m_strError.clear();

	m_licInfo = DecryptoToInfo(LICENSE_FILE_NAME, m_strError);
	if (!m_strError.isEmpty())
		return listRet;

	if (!GetLocalMACAddress().contains(m_licInfo.mac.toUpper()))
	{
		m_strError = "MAC address does not match.";
		return listRet;
	}

	if (GetLocalHostname() != m_licInfo.pcname)
	{
		m_strError = "Computer name does not match.";
		return listRet;
	}

	if (!_CheckTime(m_licInfo, m_strError))
		return listRet;

	for (int i = 0; i != apps.size(); ++i)
	{
		listRet[i] = m_licInfo.apps.contains(apps[i]);
	}

	return listRet;
}

QString CXLicenseChecker::GetSystemInfo()
{
	const QStringList& listMac = GetLocalMACAddress();
	if (listMac.isEmpty())
		return QString("error: Windows cannot find any network cards.");

	return QString("Username: %1\nPC Name: %2\nMAC Address: %3").arg(GetLocalUsername()).arg(GetLocalHostname()).arg(listMac.first());
}

CXLicenseChecker::LicenseInfo CXLicenseChecker::DecryptoToInfo(const QString& filename, QString& strError)
{
	LicenseInfo licInfo;

	QFile licFile(filename);
	if (!licFile.open(QFile::ReadOnly))
	{
		strError = "License file cannot find.";
		return licInfo;
	}

	QString strCipher1, strCipher2;
	QDataStream licStream(&licFile);
	licStream >> strCipher1 >> strCipher2;

	auto _Cipher2Info = [&licInfo, &strError](const QString& strCipher, quint64 key, const QString& strType, bool bCheck = false)
	{
		SimpleCrypt sc(key);
		QString strInfo = sc.decryptToString(strCipher);
		QJsonObject jsonObj = QJsonDocument::fromJson(strInfo.toUtf8()).object();

		if (strType != jsonObj["version"].toString())
		{
			strError = "License type does not match.";
			return;
		}

		LicenseInfo licInfoFromJson;
		licInfoFromJson.apps = [](const QJsonObject& obj) {QStringList listApp; for (auto&& app : obj["apps"].toArray()) { listApp << app.toString(); } return listApp; }(jsonObj);
		licInfoFromJson.username = jsonObj["username"].toString();
		licInfoFromJson.pcname = jsonObj["pcname"].toString();
		licInfoFromJson.mac = jsonObj["mac"].toString();
		licInfoFromJson.begin = QDate::fromString(jsonObj["from"].toString(), Qt::ISODate);
		licInfoFromJson.end = QDate::fromString(jsonObj["to"].toString(), Qt::ISODate);
		licInfoFromJson.privilege = jsonObj.contains("privilege") ? jsonObj["privilege"].toString() : "";

		if (bCheck && licInfo != licInfoFromJson)
		{
			strError = "License cipher double check failed.";
			return;
		}

		licInfo = licInfoFromJson;
	};

	_Cipher2Info(strCipher1, KEY0, LICENSE_VERSION0);
	_Cipher2Info(strCipher2, KEY1, LICENSE_VERSION1, true);

	auto _CipherOldInfo = [&licInfo, &strError](const QString& strCipher, quint64 key, const QString& strType, bool bCheck = false)
	{
		SimpleCrypt sc(key);
		QString strInfo = sc.decryptToString(strCipher);
		QJsonObject jsonObj = QJsonDocument::fromJson(strInfo.toUtf8()).object();

		if (strType != jsonObj["type"].toString())
		{
			strError = "License(old) type does not match.";
			return;
		}

		LicenseInfo licInfoFromJson;
		licInfoFromJson.username = jsonObj["showname"].toString();
		licInfoFromJson.pcname = jsonObj["pcname"].toString();
		licInfoFromJson.mac = jsonObj["pcmac"].toString();
		licInfoFromJson.begin = QDate::fromString(jsonObj["timefrom"].toString(), Qt::ISODate);
		licInfoFromJson.end = QDate::fromString(jsonObj["timeend"].toString(), Qt::ISODate);
		licInfoFromJson.privilege = jsonObj.contains("privilege") ? jsonObj["privilege"].toString() : "";

		if (bCheck && licInfo != licInfoFromJson)
		{
			strError = "License cipher double check failed.";
			return;
		}

		licInfo = licInfoFromJson;
	};

	if (strError == "License type does not match.")
	{
		strError = "";

		// try to test old version license.
		_CipherOldInfo(strCipher1, KEY0, "CDlgLicOnCompute1");
		_CipherOldInfo(strCipher2, KEY1, "CDlgLicOnCompute2", true);
	}

	return licInfo;
}

bool CXLicenseChecker::CopyLicense(QWidget* parent)
{
	QString strFile = QFileDialog::getOpenFileName(parent, "license file", "", "license.lic(*.lic)");
	if (strFile.isEmpty())
		return false;

	if (strFile == QDir(CXLicenseChecker::LICENSE_FILE_NAME).absolutePath())
		return false;

	if (QFile::exists(CXLicenseChecker::LICENSE_FILE_NAME) && !QFile::remove(CXLicenseChecker::LICENSE_FILE_NAME))
	{
		QMessageBox::critical(parent, "Import Error", "Cannot remove old license.");
		return false;
	}

	if (!QFile::copy(strFile, CXLicenseChecker::LICENSE_FILE_NAME))
	{
		QMessageBox::critical(parent, "Import Error", "Cannot import new license.");
		return false;
	}

	return true;
}

QString CXLicenseChecker::GetLocalUsername()
{
	QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
	return QDir::toNativeSeparators(homePath.first()).split(QDir::separator()).last();
}

QString CXLicenseChecker::GetLocalHostname()
{
	return QSysInfo::machineHostName();
}

QStringList CXLicenseChecker::GetLocalMACAddress()
{
	QStringList listMac;

	for (QNetworkInterface netInterface : QNetworkInterface::allInterfaces())
	{
		QNetworkInterface::InterfaceFlags flags = netInterface.flags();

		if (flags & QNetworkInterface::IsLoopBack || flags & QNetworkInterface::IsPointToPoint)
			continue;

		listMac << netInterface.hardwareAddress().toUpper();
	}

	return listMac;
}

bool CXLicenseChecker::_CheckTime(LicenseInfo& info, QString& strError)
{
	auto _CheckFile = [](const QString& filename)
	{
		SimpleCrypt sc(7518259798791992195);
		QString strDateRecord = QDate::currentDate().toString(Qt::ISODate);

		QFile fileDate(filename);
		if (fileDate.exists())
		{
			fileDate.open(QFile::ReadOnly);
			QDataStream streamDate(&fileDate);
			streamDate >> strDateRecord;
			strDateRecord = sc.decryptToString(strDateRecord);
			fileDate.close();
		}

		QDate dateRecord = QDate::fromString(strDateRecord, Qt::ISODate);
		if (dateRecord > QDate::currentDate() || QDate(2015, 11, 12) > dateRecord)
			return false;
		
		fileDate.open(QFile::WriteOnly);
		QDataStream streamDate(&fileDate);
		streamDate << sc.encryptToString(QDate::currentDate().toString(Qt::ISODate)); // update timestamp
		return true;
	};

	auto _CheckRegedit = []()
	{
		SimpleCrypt sc(9518259798791992195);
		QSettings reg("HKEY_LOCAL_MACHINE\\Software\\XStudio\\", QSettings::NativeFormat);
		QString strRecord = reg.value("aff", QVariant()).toString();
		if (!strRecord.isEmpty())
		{
			strRecord = sc.decryptToString(strRecord);
			QDate dateRecord = QDate::fromString(strRecord, Qt::ISODate);
			if (dateRecord > QDate::currentDate() || QDate(2015, 11, 12) > dateRecord)
				return false;
		}

		reg.setValue("aff", sc.encryptToString(QDate::currentDate().toString(Qt::ISODate))); // update timestamp
		return true;
	};

	if (!_CheckFile("acf.db") || !_CheckRegedit() || !_CheckFile(QDir::toNativeSeparators("c:\\windows\\racf.db")))
	{
		strError = "system time error: before installation.";
		return false;
	}

	if (info.begin > QDate::currentDate() || QDate::currentDate() > info.end)
	{
		strError = "license expired.";
		return false;
	}

	return true;
}