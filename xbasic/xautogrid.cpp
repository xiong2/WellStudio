#include "xautogrid.h"
#include "xaxis.h"

#include <QFontMetrics>

void CXAutoGrid::AutoGrid(double dStart, double dStop, int iNumGrid, double& dUniStart, double& dUniStop, double& dStep, bool bLog)
{
	if(bLog)
	{
		//	For logarithmic scale, use the defined range?
		dUniStart	= 0.2;
		dUniStop	= 2000;

		return;
	}

	double dScale	= 1.;
	double dDelta = dStop - dStart;

	if (dDelta < 0)
	{
		throw std::invalid_argument("dStart > dStop, invalid arguments.");
		return;
	}
	else if (dDelta == 0)
	{
		dUniStart = dStart;
		dUniStop = dStop;
		dStep = 0;
		return;
	}
	else if (iNumGrid == 0)
	{
		throw std::invalid_argument("iNumGrid == 0, invalid arguments.");
		return;
	}

	dDelta /= iNumGrid;

	//	Zoom delta to 1~10, and remember the scale.
	while(dDelta > 10)
	{
		dScale *= 10;
		dDelta /= 10;
	}
	while(dDelta < 1)
	{
		dScale /= 10;
		dDelta *= 10;
	}

	//	The step without scale should be 1, 2, 5, or 10.
	dStep = 10;
	if(dDelta < 1.5)
		dStep = 1.;
	else if(dDelta < 2.5)
		dStep = 2.;
	else if(dDelta < 7.5)
		dStep = 5;

	dStep *= dScale;

	//	Now unified the start and stop.
	dUniStart = static_cast<double>(static_cast<int>(dStart / dStep));
	dUniStart *= dStep;
	dUniStop = static_cast<double>(static_cast<int>(dStop / dStep + 0.99));
	dUniStop *= dStep;
}

void CXAutoGrid::AutoGrid(int iFirst, int iLast, int nNum, int& iUniFirst, int& iUniLast, int& iStep)
{
	int iScale = 1;
	double dDelta = iLast - iFirst;
	dDelta /= nNum;

	if (dDelta < 1)
	{
		throw std::out_of_range("The delta of integer should't less than 1.");
		return;
	}

	while (dDelta > 10)
	{
		iScale *= 10;
		dDelta /= 10;
	}

	if (dDelta < 1.5)
		iStep = 1;
	else if (dDelta < 2.5)
		iStep = 2;
	else if (dDelta < 7.5)
		iStep = 5;
	else
		iStep = 10;

	iStep *= iScale;
	iUniFirst = std::ceil(iFirst * 1.f / iStep) * iStep;
	iUniLast = std::floor(iLast * 1.f / iStep) * iStep;
}

std::vector<double> CXAutoGrid::AutoGrid(double dStart, double dStop, int iNumGridNeed)
{
	std::vector<double> vecRet;

	if (dStart > dStop || iNumGridNeed < 1)
	{
		return vecRet;
	}
	else if (dStart == dStop)
	{
		vecRet.push_back(dStart);
	}
	else
	{
		double dScale = 1.;
		double dDelta = (dStop - dStart) / iNumGridNeed;

		while (dDelta > 10)
		{
			dDelta /= 10;
			dScale *= 10;
		}
		while (dDelta < 1)
		{
			dDelta *= 10;
			dScale /= 10;
		}

		double dStep = (dDelta < 1.5 ? 1 : dDelta < 2.5 ? 2 : dDelta < 7.5 ? 5 : 10) * dScale;
		double dUniStart = std::ceil(dStart / dStep) * dStep;
		double dUniStop = std::floor(dStop / dStep) * dStep;

		while (dUniStart <= dUniStop)
		{
			vecRet.push_back(dUniStart);
			dUniStart += dStep;
		}
	}

	return vecRet;
}

double CXAutoGrid::GetTickInterval(double totalSize, int count)
{
	if (totalSize <= 0.0) totalSize = 0.0;
	if (count <= 0) count = 1;

	for (auto i = 1; i <= 10; ++i)
	{
		auto result = CXAxis::GetBaseNum(totalSize / count) * i;
		if (result >= totalSize / count) return result;
	}

	return totalSize;
}

double CXAutoGrid::GetTickInterval(double start, double end, int totalSize, int markSize, bool bHorizontal)
{
	int nMarkSize = bHorizontal ?
		qMax(QString::number(start).length(), QString::number(end).length()) * markSize * 1.3 : markSize * 4;

	auto nIntervalQty = qAbs(totalSize) / nMarkSize;
	if (nIntervalQty < 1) nIntervalQty = 1;

	return GetTickInterval(end - start, nIntervalQty);
}

QRect CXAutoGrid::TextRect(QFont font, QString strText)
{
	QFontMetrics fontMetrics(font);
	return fontMetrics.tightBoundingRect(strText);
}

QString CXAutoGrid::TrimToString(double value)
{
	QString result = QString("%1").arg(value, 0, 'f');
	while (result.endsWith('0')) result.chop(1);
	if (result.endsWith('.')) result.chop(1);
	return result;
}

std::string CXAutoGrid::TrimToStdString(double dValue)
{
	std::string strRst = std::to_string(dValue);
	while (strRst.back() == '0')
	{
		strRst.pop_back();
	}
	if (strRst.back() == '.')
	{
		strRst.pop_back();
	}

	return strRst;
}

double CXAutoGrid::GetFloorBound(double dValue, double dInterval)
{
	if (fabs(dInterval) < 0.000001 || dInterval < 0.0) return dValue;

	double result = dValue;

	qint64 nLowerIndex = dValue / dInterval;
	if (result < 0) nLowerIndex = nLowerIndex - 1;
	result = nLowerIndex * dInterval;

	return result;
}

double CXAutoGrid::GetCeilBound(double dValue, double dInterval)
{
	if (fabs(dValue) < 0.00001 || dInterval < 0.0) return dValue;

	qint64 nLowerIndex = dValue / dInterval;
	if (dValue > 0) ++nLowerIndex;

	return nLowerIndex * dInterval;
}

double CXAutoGrid::mapX(double dValue, double dMin, double dMax, bool bLog)
{
	if (bLog)
	{
		dMin = dMin > 0 ? log10(dMin) : 0;
		dMax = log10(dMax);
		dValue = dValue > 0 ? log10(dValue) : 0;
	}
	auto dLength = dMax - dMin;
	// The curve will be displayed as a beeline in the middle of track
	if (dLength < 0.00001) return 0.5;// return 0.5 when minimum value equals to maximum value
	return (dValue - dMin) / dLength;
}

double CXAutoGrid::Trunc(double dValue)
{
	if (!dValue)
		return dValue;

	bool bNegative = dValue < 0;

	dValue = qAbs(dValue);

	int nZeroNum = 0;
	while (dValue > 10)
	{
		dValue /= 10;
		++nZeroNum;
	}

	int nPointNum = 0;
	while (dValue < 1)
	{
		dValue *= 10;
		++nPointNum;
	}

	if (nZeroNum) // > 10
	{
		dValue = qRound(dValue) * std::pow(10, nZeroNum);
	}
	else if (nPointNum) // < 1
	{
		dValue = qRound(dValue) / std::pow(10, nPointNum);
	}
	else
	{
		dValue = qRound(dValue);
	}

	return bNegative ? -dValue : dValue;
}

std::vector<double> CXAutoGrid::AutoInterval(double dDistance)
{
	std::vector<double> vecInterval;

	dDistance = Trunc(dDistance);

	QList<int> listDividend{ 1, 2, 4, 5, 10, 50, 100, 200 };

	for (int iDivide : listDividend)
	{
		vecInterval.push_back(dDistance / iDivide);
	}

	return vecInterval;
}
