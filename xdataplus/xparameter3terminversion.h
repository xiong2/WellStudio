#ifndef XPARAMETER3TERMINVERSION_H
#define XPARAMETER3TERMINVERSION_H

#include <QString>
#include "xdataplus_global.h"
#include "xparameterinversion.h"
#include "xdef.h"	

using std::vector;
/**
* @class CXParameter3TermInversion provided in the file "keparameter3terminversion.h"
* @brief The class provides parameters for doing 3-term AVO inversion
* @author Yong Shu
* @date 12/11/2015
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameter3TermInversion : public CXParameterInversion
{
public:
	enum EOutputType
	{
		eZpZsRho = 0,
		eZpVpVsRho,
		eVpVsRho
	};
public:
	///@brief Default Constructor
	CXParameter3TermInversion();

	///@brief Destructor
	virtual ~CXParameter3TermInversion() {}

public:
	///@brief Prestack seismic data
	X_PROPERTY(QUuid, PrestackDVID);
	X_PROPERTY(QString, PrestackDVName);

	///@brief Individual poststack data volumes
	X_PROPERTY(vector<QUuid>, VecDVID);
	X_PROPERTY(QStringList, ListDVName);

	///@brief Angle offset index
	X_PROPERTY(vector<int>, VecAngleIndex);

	///@brief Angle values
	X_PROPERTY(vector<float>, VecAngleValue);

	///@brief Azimuth vector (for anisotropy inversion)
	X_PROPERTY(vector<float>, VecAzimuth);

	///@brief Wavelet
	X_PROPERTY(vector<QUuid>, VecWaveletID);
	X_PROPERTY(QStringList, ListWaveletFileName);

	///@brief Zp, Zs and Rho
	X_PROPERTY(QUuid, ZpID);
	X_PROPERTY(QUuid, ZsID);
	X_PROPERTY(QUuid, RhoID);

	///@brief Thomson parameters (for anisotropy inversion)
	X_PROPERTY(QUuid, EpsilonID);
	X_PROPERTY(QUuid, DeltaID);
	X_PROPERTY(QUuid, GammaID);
	X_PROPERTY(QUuid, SymAziID);

	///@brief Inversion parameter
	X_PROPERTY(float, Gamma);
	X_PROPERTY(float, Lambda);
	X_PROPERTY(int, MaxLoopNum);
	X_PROPERTY(float, Tolerance);
	X_PROPERTY(float, Alpha);
	X_PROPERTY(float, Beta);
	X_PROPERTY(float, Sigma);
	
	X_PROPERTY(float, CutFrequency);
	
	///@brief Output option
	X_PROPERTY(int, OutputType);
	X_PROPERTY(bool, ExportReflectivity);
	X_PROPERTY(bool, ExportSeismic);

	// prior synthetics
	X_PROPERTY(bool, OutputInversion);
	X_PROPERTY(bool, OutputPrior);
	X_PROPERTY(bool, AkiRichards);

	// different parts
	X_PROPERTY(vector<float>, vecLambda);
	X_PROPERTY(vector<float>, vecAlpha);
	X_PROPERTY(vector<float>, vecSigma);
	X_PROPERTY(vector<float>, vecWaveletScale);

	// horizon constraints
	X_PROPERTY(bool, UseHorizon);
	X_PROPERTY(QUuid, TopHorizonID);
	X_PROPERTY(QUuid, BotHorizonID);


};

#endif // KEPARAMETER3TERMINVERSION_H
