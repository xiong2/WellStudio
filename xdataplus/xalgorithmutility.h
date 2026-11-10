#ifndef XALGORITHMUTILITY_H
#define XALGORITHMUTILITY_H

#include "xdataplus_global.h"
#include <QString>

class CXObject;
class CXWellCurve;



class XDATAPLUS_EXPORT CXAlgorithmUtility
{
public:
	static void CalculateHistogram(const QString& strFileName, int nK, CXObject* pbj);

	static bool GetFilteredData(CXWellCurve* pCurve, double* pBuffer, int nType, double lowPassFreq, double lowPassOvap, double highPassFreq, double highPassOvap);

};

#endif // KEALGORITHMUTILITY_H
