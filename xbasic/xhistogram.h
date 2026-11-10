#ifndef XHISTOGRAM_H
#define XHISTOGRAM_H

#include "xbasic_global.h"
#include <vector>
#include "xmathmacro.h"
#include <qdatastream.h>
#include <qvariant.h>
#include <qbytearray.h>

using std::vector;

///@brief Data structure for statistics of an object
class XBASIC_EXPORT CXHistogram
{
public:
	enum
	{
		HISTSIZE = 256
	};
public:
	CXHistogram()
	{
		m_dDataMin = M_FINVALID;
		m_dDataMax = M_FINVALID;
		m_dMean = 0.;
		m_dVariance = 0.;
		m_dStd = 0.;
		m_nValidDataNum = 0;		 
	}

public:
	QVariant SaveToBLOB()
	{
		QByteArray byteArray;
		QDataStream dataStream(&byteArray, QIODevice::WriteOnly);

		if (m_vecHorizontal.size() == HISTSIZE && m_vecVertical.size() == HISTSIZE)
		{
			for (int i = 0; i < HISTSIZE; ++i)
			{
				dataStream << m_vecHorizontal[i];
				dataStream << m_vecVertical[i];
			}

			dataStream << m_dDataMin;
			dataStream << m_dDataMax;
			dataStream << m_dMean;
			dataStream << m_dVariance;
			dataStream << m_dStd;
			dataStream << m_nValidDataNum;
		}

		return QVariant(byteArray);
	};

	void LoadFromBLOB(const QVariant& vtBlob)
	{
		if (vtBlob.isNull())
			return;

		QByteArray BlobArray = vtBlob.toByteArray();
		QDataStream dataStream(&BlobArray, QIODevice::ReadOnly);

		m_vecHorizontal.resize(HISTSIZE);
		m_vecVertical.resize(HISTSIZE);
		for (int i = 0; i < HISTSIZE; ++i)
		{
			dataStream >> m_vecHorizontal[i];
			dataStream >> m_vecVertical[i];
		}		

		dataStream >> m_dDataMin;
		dataStream >> m_dDataMax;
		dataStream >> m_dMean;
		dataStream >> m_dVariance;
		dataStream >> m_dStd;

		// for version compatibility
		if (dataStream.atEnd())
			m_nValidDataNum = 10000;
		else
			dataStream >> m_nValidDataNum;
	};
	

public:
	double m_dDataMin, m_dDataMax;
	double m_dMean, m_dVariance, m_dStd;	

	vector<double> m_vecHorizontal, m_vecVertical;

	qint64 m_nValidDataNum;
};

#endif // RLHISTOGRAM_H
