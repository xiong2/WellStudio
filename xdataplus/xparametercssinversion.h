#ifndef XPARAMETERCSSINVERSION_H
#define XPARAMETERCSSINVERSION_H

#include <QString>
#include "xdataplus_global.h"
#include "xparameterinversion.h"
#include "xdef.h"	

using std::vector;
/**
* @class CXParameterCSSInversion provided in the file "keparametercssinversion.h"
* @brief The class provides parameters for for CSSI
* @author Yong Shu
* @date 1/15/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterCSSInversion : public CXParameterInversion
{
public:
	///@brief Default Constructor
	CXParameterCSSInversion();

	///@brief Destructor
	virtual ~CXParameterCSSInversion() {}

public:
	///@brief poststack seismic data
	X_PROPERTY(QUuid, DVID);
	X_PROPERTY(QString, DVName);

	///@brief Impedance data volume
	X_PROPERTY(QUuid, ImpedanceID);
	X_PROPERTY(QString, ImpedanceName);

	///@brief Wavelet
	X_PROPERTY(QUuid, WaveletID);
	X_PROPERTY(QString, WaveletFileName);

	///@brief Inversion parameter
	X_PROPERTY(float, Alpha);
	X_PROPERTY(float, Beta);
	X_PROPERTY(float, Mu);
	X_PROPERTY(float, Sigma);
	X_PROPERTY(float, WaveletFactor);
	X_PROPERTY(int, MaxLoopNum);
	X_PROPERTY(float, Tolerance);

	///@brief Output option
	X_PROPERTY(int, ExportReflectivity);
	X_PROPERTY(int, ExportSeismic);
};

#endif // KEPARAMETERCSSINVERSION_H
