#ifndef XVERSION_H
#define XVERSION_H

#include "xbasic_global.h"
#include <qstring.h>
#include <qmap.h>
#include <qstringlist.h>

enum EVersion
{
	ERockLab = 1,
	ERockInv = 2,
	ERockFrac = 4,
	EKFC      = 8,
};

struct SVersion
{	
	SVersion(const QString& strVerName, const QString& strIconName, const QString& strDisableIconName)
	{
		m_strVerName = strVerName;
		m_strVerIconName = strIconName;
		m_strVerDisableIconName = strDisableIconName;
	}

	QString  m_strVerName;
	QString  m_strVerIconName;
	QString  m_strVerDisableIconName;
};

/**
* @ Class CXVersion in the file "xsversion.h"
* @brief The file provides data for version control.
*
* @author 
* @date 4/5/2017
* @see
* @bug	No Known bugs so far
*/

class XBASIC_EXPORT CXVersion
{
public:
	///@brief Get the unique instance of this factory
	static CXVersion& Instance();

	///@brief Get all versions
	QList<SVersion> GetAllVersions();

	///@brief Set the current version
	void SetCurrentVersion(const QStringList& strListVersionName);
	void SetCurrentVersion(EVersion eVersion);

	///@brief Tell if contains in the current version
	bool ContainsInVersion(int iVersionIndex);

private:
	CXVersion();

private:
	QMap<int, SVersion> m_mapAllVersion;

	int m_iCurrentVersion;

	
};

#endif // KEVERSION_H
