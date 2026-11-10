#include "xversion.h"

CXVersion::CXVersion()
{
	m_iCurrentVersion = 0;

	m_mapAllVersion.insert(ERockLab,  SVersion("RockLab", "RockLab.png", "RockLab_gray.png"));
	m_mapAllVersion.insert(ERockInv,  SVersion("RockInv", "RockInv.png", "RockInv_gray.png"));
	m_mapAllVersion.insert(ERockFrac, SVersion("RockFrac", "RockFrac.png", "RockFrac_gray.png"));
	m_mapAllVersion.insert(EKFC,      SVersion("KFC", "KFC.png", "KFC_gray.png"));
}

CXVersion& CXVersion::Instance()
{
	static CXVersion object;
	return object;
}

QList<SVersion> CXVersion::GetAllVersions()
{
	return m_mapAllVersion.values();
}

void CXVersion::SetCurrentVersion(const QStringList& strListVersionName)
{
	m_iCurrentVersion = 0;

	for (auto it = m_mapAllVersion.begin(); it != m_mapAllVersion.end(); ++it)
	{
		if (strListVersionName.contains(it.value().m_strVerName))
		{
			m_iCurrentVersion |= it.key();
		}
	}
}

void CXVersion::SetCurrentVersion(EVersion eVersion)
{
	m_iCurrentVersion = eVersion;
}

bool CXVersion::ContainsInVersion(int iVersionIndex)
{
	if (m_iCurrentVersion == 0)
		return true;
	else
		return m_iCurrentVersion & iVersionIndex;
}