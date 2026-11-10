#pragma once

/*!
 * @class CXLicenseChecker in the file "xslicensechecker.h"
 * @brief The class provides a checker for RockLab license.
 * 
 * @author pezy
 * @date 2017-03-13
 * @see 
 */

#include "xbasic_global.h"
#include <QString>
#include <QDate>
class QWidget;

class XBASIC_EXPORT CXLicenseChecker
{
public:
	CXLicenseChecker() {}
	CXLicenseChecker(const CXLicenseChecker&) = delete;
	CXLicenseChecker& operator=(const CXLicenseChecker&) = delete;

	static CXLicenseChecker& GetInstance()
	{
		static CXLicenseChecker checker;
		return checker;
	}

	struct LicenseInfo
	{
		friend bool operator!=(const LicenseInfo& lic1, const LicenseInfo& lic2)
		{
			return !(lic1.apps == lic2.apps && lic1.username == lic2.username && lic1.pcname == lic2.pcname && lic1.mac == lic2.mac && lic1.begin == lic2.begin && lic1.end == lic2.end && lic1.privilege == lic2.privilege);
		}

		QStringList apps;
		QString username;
		QString pcname;
		QString mac;
		QDate begin;
		QDate end;
		QString privilege;
	};

	static const qint64 KEY0 = 7544825972271992195;
	static const qint64 KEY1 = 7544342972271992195;
	static const QString LICENSE_VERSION0;
	static const QString LICENSE_VERSION1;
	static const QString LICENSE_FILE_NAME;
	static const QString LICENSE_PRIVILEGE;

	static QString GetSystemInfo();
	static QString GetLocalUsername();
	static QString GetLocalHostname();
	static QStringList GetLocalMACAddress();
	static LicenseInfo DecryptoToInfo(const QString& filename, QString& strError);
	static bool CopyLicense(QWidget* parent);

	bool Check(const QString &app);
	QList<bool> Check(QStringList apps);
	const QString& GetErrorMsg() const { return m_strError; }
	const QString& GetUsername() const { return m_licInfo.username; }
	QString GetExpiredDate() { return m_licInfo.end.toString(Qt::ISODate); }

private:
	static bool _CheckTime(LicenseInfo& info, QString& strError);

private:
	QString m_strError;
	LicenseInfo m_licInfo;
};
