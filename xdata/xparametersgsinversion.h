#ifndef _CXPARAMETERSGSINVERSION_H__
#define _CXPARAMETERSGSINVERSION_H__

#include <quuid.h>
#include "xbaseparameter.h"
#include "xdata_global.h"

///@brief	The class represents parameters used to do a geostatistical inversion.
///@author	Xiong Xiong
///@date	Dec, 2016
class XDATA_EXPORT CXParametersGSInversion :public CXBaseParameter
{
public:
	CXParametersGSInversion();
	~CXParametersGSInversion() {}

	///	ID of original structure model.
	X_PROPERTY(QUuid, SMID);

	///	Zones selected.
	X_PROPERTY(std::vector<unsigned int>, VecZoneIDX);		//	Indice of selected zones.
	X_PROPERTY(std::vector<bool>, VecZoneReservoir);		//	Whether corresponding zone need discete properties.

	///	Parameters of plane dimension.
	X_PROPERTY(int, StartInline);
	X_PROPERTY(int, EndInline);
	X_PROPERTY(int, StartXline);
	X_PROPERTY(int, EndXline);
	X_PROPERTY(QUuid, QCSection);

	///	Selected Wells
	X_PROPERTY(std::vector<QUuid>, VecWellID);		//	ID of selected wells.

	///	Logs.
	X_PROPERTY(QString, DiscreteLog);
	X_PROPERTY(int, ContinuousPropety);	//	0: Zp, Vp/Vs, Rho;	1: Vp, Vs, Rho;	2: Zp, Zs, Rho.
	X_PROPERTY(QString, ContinuousLog1);	//	Zp, Vp, orZp.
	X_PROPERTY(QString, ContinuousLog2);	//	Vp/Vs, Vs, or Zs.
	X_PROPERTY(QString, ContinuousLog3);	//	Rho.

	///	Pdfs
	X_PROPERTY(bool, FitPriorPDFS);
	X_PROPERTY(int, FitOption);			//	0: Normal;	1: Log normal;	2: Binned;	3: Uniform.
	X_PROPERTY(int, NumOfBins);
};

#endif