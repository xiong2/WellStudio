#ifndef _CXAUTOGRID_H__
#define _CXAUTOGRID_H__

#include "xbasic_global.h"

#include <QFont>
#include <QRect>

///@brief	Used to automatically generate the unified start, stop and step of a given range..
///@author	Xiong Xiong
///@date	Jun, 2013
///@see		
class XBASIC_EXPORT CXAutoGrid
{
public:
	//! @brief	Auto calculate what a grid is the best choice.
	static void AutoGrid(double dStart, double dStop, int iNumGrid, double& dUniStart, double& dUniStop, double& dStep, bool bLog = false);
	static void AutoGrid(int iFirst, int iLast, int nNum, int& iUniFirst, int& iUniLast, int& iStep);
	static std::vector<double> AutoGrid(double dStart, double dStop, int iNumGridNeed);
	static double GetTickInterval(double totalSize, int count = 20);
	static double GetTickInterval(double start, double end, int totalSize, int markSize, bool bHorizontal);
	
	static QRect TextRect(QFont font, QString strText);
	static QString TrimToString(double value);
	static std::string TrimToStdString(double dValue);
	static double GetCeilBound(double dValue, double dInterval);
	static double GetFloorBound(double dValue, double dInterval);
	static double mapX(double dValue, double dMin, double dMax, bool bLog = false);
	static double Trunc(double dValue);
	static std::vector<double> AutoInterval(double dDistance);
};

#endif