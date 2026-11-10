#pragma warning( push ,0 )
#include "xthreadcalchistogram.h"
#include <QCoreApplication>
#include <cmath>
#include <cassert>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xrandomgenerator.h"
#include <cmath>

#pragma warning( pop )

CXThreadCalcHistogram::CXThreadCalcHistogram(const QString& strFileNam, int nK)
{
	m_qFile.setFileName(strFileNam);
	qint64 nFileSize = m_qFile.size();

	m_nK = nK;
	m_nTraceNum = nFileSize / m_nK / sizeof(float);
}

CXThreadCalcHistogram::~CXThreadCalcHistogram()
{
	wait();
}

void CXThreadCalcHistogram::RunThread()
{
	if (IsStopped())
		return;

	if (!m_qFile.open(QIODevice::ReadOnly))
	{
		this->EmitGeneralErrorMsg("Cannot read the data file.");
		return;
	}

	qint64 nCalcTraceNum = qMin((qint64)100, m_nTraceNum);

	QList<qint64> listTraceIndex;
	if (m_nTraceNum <= 100)
	{
		for (qint64 i = 0; i < nCalcTraceNum; ++i)
			listTraceIndex.append(i);
	}
	else
	{
		CXRandomGenerator randomGen;
		for (qint64 i = 0; i < nCalcTraceNum; ++i)
		{
			listTraceIndex.append(static_cast<qint64>(m_nTraceNum*randomGen.GetValue()));
		}
	}
	std::sort(listTraceIndex.begin(), listTraceIndex.end());

	this->EmitSetWindowName("Calculate Histogram");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	this->EmitCancelEnabled(false);
	QCoreApplication::instance()->processEvents();

	std::vector<float> vecBuffer(m_nK);
	double dInvalid = g_dInvalidData;
	double dEPSInvalid = ::GetEPSofInvalidData(dInvalid);
	qint64 nValidDataNum = 0;
	double dSum = 0, dMin = FLT_MAX, dMax = -FLT_MAX;
	for (qint64 i = 0; i < nCalcTraceNum; ++i)
	{
		if (IsStopped())
			return;
		else
		{
			this->EmitUpdateProgress(i, nCalcTraceNum * 2);
		}

		unsigned char* pMapData = m_qFile.map(listTraceIndex[i]*m_nK*sizeof(float), m_nK*sizeof(float));
		memcpy(&vecBuffer[0], (float*)pMapData, m_nK*sizeof(float));

		double dValue;
		for (qint64 ii = 0; ii < m_nK; ++ii)
		{
			dValue = vecBuffer[ii];
			if (std::isnan(dValue) || qAbs(dValue - dInvalid) < dEPSInvalid)
				continue;			

			dMin = qMin(dMin, dValue);
			dMax = qMax(dMax, dValue);

			dSum += dValue;
			++nValidDataNum;
		}
	}

	if (nValidDataNum == 0)
	{
		this->EmitGeneralErrorMsg("There is no valid data.");
		return;
	}

	// Mean, min, max
	m_histogram.m_nValidDataNum = nValidDataNum;
	m_histogram.m_dDataMin = dMin;
	m_histogram.m_dDataMax = dMax;
	m_histogram.m_dMean = dSum / nValidDataNum;

	// Histogram
	double dHistogramInterval = (m_histogram.m_dDataMax - m_histogram.m_dDataMin) / 256;
	if (dHistogramInterval == 0.)
	{
		m_histogram.m_vecHorizontal.resize(256, m_histogram.m_dDataMin);
		m_histogram.m_vecVertical.resize(256, 1.);

		m_histogram.m_dVariance = 0.;
		m_histogram.m_dStd = 0.;
	}
	else
	{
		std::vector<qint64> vecFrequency(256, 0);
		dSum = 0;
		for (qint64 i = 0; i < nCalcTraceNum; ++i)
		{
			if (IsStopped())
				return;
			else
			{
				this->EmitUpdateProgress(i + nCalcTraceNum, nCalcTraceNum * 2);
			}

			unsigned char* pMapData = m_qFile.map(listTraceIndex[i] * m_nK*sizeof(float), m_nK*sizeof(float));
			memcpy(&vecBuffer[0], (float*)pMapData, m_nK*sizeof(float));

			double dValue;
			int iInterval;
			for (qint64 ii = 0; ii < m_nK; ++ii)
			{
				dValue = vecBuffer[ii];
				if (std::isnan(dValue) || qAbs(dValue - dInvalid) < dEPSInvalid)
					continue;

				// frequency
				iInterval = static_cast<int>((dValue - dMin) / dHistogramInterval);
				
				iInterval = qBound(0, iInterval, 255);

				vecFrequency[iInterval]++;

				// variance
				dValue = qAbs(m_histogram.m_dMean - dValue);
				dSum += dValue*dValue;
			}
		}

		// frequency
		m_histogram.m_vecHorizontal.resize(256);
		m_histogram.m_vecVertical.resize(256);
		for (int i = 0; i < 256; ++i)
		{
			m_histogram.m_vecHorizontal[i] = m_histogram.m_dDataMin + i*dHistogramInterval;
			m_histogram.m_vecVertical[i] = 1.0*vecFrequency[i] / nValidDataNum;
		}

		//variance
		m_histogram.m_dVariance = dSum / nValidDataNum;

		// Std
		qint64 nNum = (nValidDataNum == 1 ? 1 : nValidDataNum - 1);
		m_histogram.m_dStd = sqrt(m_histogram.m_dVariance*nValidDataNum / nNum);
	}
}
