#ifndef XPARAMETERANISOTROPYFORWARDING_H
#define XPARAMETERANISOTROPYFORWARDING_H

#include <QString>
#include "xdataplus_global.h"
#include "xparameterinversion.h"

/**
* @class CXParameterAnisotropyForwarding provided in the file "CXParameterAnisotropyForwarding.h"
* @brief The class provides base class for anisotropy forwarding
* @author Yong Shu
* @date 12/23/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterAnisotropyForwarding : public CXParameterInversion
{
public:
	///@brief Default Constructor
	CXParameterAnisotropyForwarding();

	///@brief Destructor
	virtual ~CXParameterAnisotropyForwarding() {}

public:
	///@brief Output Name
	X_PROPERTY(QString, OutputDVName)


	///@brief Different Data volumes
	X_PROPERTY(QUuid, VpDVID)
	X_PROPERTY(QUuid, VsDVID)
	X_PROPERTY(QUuid, RhoDVID)
	X_PROPERTY(QUuid, EpsilonDVID)
	X_PROPERTY(QUuid, DeltaDVID)
	X_PROPERTY(QUuid, GammaDVID)
	X_PROPERTY(QUuid, AziSymDVID)
	
	///@brief Azimuths
	X_PROPERTY(std::vector<double>, VecAzimuth)

	///@brief Incidence angles
	X_PROPERTY(std::vector<double>, VecIncidence)

	///@brief Wavelet ID
	X_PROPERTY(std::vector<QUuid>, VecWaveletID)

	///@brief Wavelet scaling factor
	X_PROPERTY(float, WaveletScalingFactor)


};

#endif // KEPARAMETERANISOTROPYFORWARDING_H
