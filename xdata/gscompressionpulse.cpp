#include <qfile.h>
#include <qtextstream.h>
#include <qcolor.h>
#include "gscompressionpulse.h"

QStringList GSCompressionPulse::m_sListPulseFullName;
QStringList GSCompressionPulse::m_sListPulseAbName;
QVector<int> GSCompressionPulse::m_vecRGB;
QVector<float> GSCompressionPulse::m_vecAge;

QStringList GSCompressionPulse::GetAllPulses(bool bFullName)
{
	if (m_sListPulseFullName.empty())
		Initialize();

	if (bFullName)
		return m_sListPulseFullName;
	else
		return m_sListPulseAbName;
}

QString GSCompressionPulse::GetOnePulse(unsigned int iID, bool bFullName)
{
	QString sPulse = "";
	if (m_sListPulseFullName.empty())
		Initialize();

	if (bFullName)
	{
		if (iID < m_sListPulseFullName.count())
			sPulse = m_sListPulseFullName[iID];
	}
	else
	{
		if (iID < m_sListPulseAbName.count())
			sPulse = m_sListPulseAbName[iID];
	}

	return sPulse;
}

QColor GSCompressionPulse::GetPulseColor(QString sName)
{
	int iID = GetPulseIDByName(sName);
	return QColor(m_vecRGB[iID]);
}

bool GSCompressionPulse::GetPulsePeriod(QString sName, float& fStart, float& fEnd)
{
	int iID = GetPulseIDByName(sName);
	fStart = m_vecAge[2 * iID];
	fEnd = m_vecAge[2 * iID + 1];
	return true;
}

int GSCompressionPulse::GetPulseIDByName(QString sName)
{
	if (m_sListPulseFullName.empty())
		Initialize();

	for(int i = 0; i < m_sListPulseAbName.count(); i++)
	{
		if (m_sListPulseAbName[i].compare(sName, Qt::CaseInsensitive) == 0
			|| m_sListPulseFullName[i].compare(sName, Qt::CaseInsensitive) == 0)
			return i;
	}

	return 0;
}

bool GSCompressionPulse::Initialize()
{
	QFile qFile("CompressionPulse.dic");
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	m_sListPulseFullName.clear();
	m_sListPulseAbName.clear();
	m_vecRGB.clear();
	m_vecAge.clear();

	QString sLine;
	QStringList sList;
	QTextStream stream(&qFile);
	while (!stream.atEnd())
	{
		sLine = stream.readLine();
		if(sLine.startsWith("#"))
			continue;

		sList = sLine.split(",");
		if (sList.size() != 5)
			continue;

		m_sListPulseAbName << sList[0].simplified();
		m_sListPulseFullName << sList[1].simplified();
		m_vecAge<<sList[2].toFloat()<<sList[3].toFloat();
		m_vecRGB<<sList[4].toInt();
	}

	qFile.close();
	return true;
}