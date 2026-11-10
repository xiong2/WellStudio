#ifndef _GSCOMPRESSIONPULSE_H__
#define _GSCOMPRESSIONPULSE_H__

#include <qstringlist.h>
#include <qvector.h>
#include "xdata_global.h"

class XDATA_EXPORT GSCompressionPulse
{
public:
	static QStringList GetAllPulses(bool bFullName = true);
	static QString GetOnePulse(unsigned int iID, bool bFullName = true);
	static int GetPulseIDByName(QString);
	static QColor GetPulseColor(QString);
	static bool GetPulsePeriod(QString, float& fStart, float& fEnd);

	static bool Initialize();

protected:
	static QStringList		m_sListPulseFullName;
	static QStringList		m_sListPulseAbName;
	static QVector<int>		m_vecRGB;
	static QVector<float>	m_vecAge;					//	Double size as pulses, start/end age in MA.
};

#endif