#ifndef XPARAMETERBUILDLFM_H
#define XPARAMETERBUILDLFM_H

#include <vector>
#include <QString>
#include "xdataplus_global.h"
#include "xbaseparameter.h"
#include "xdef.h"	

/**
* @class CXParameterBuildLFM provided in the file "keparameterbuildlfm.h"
* @brief The class provides parameters for building  a low frequency model
* @author Yong Shu
* @date 11/16/2015
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterBuildLFM : public CXBaseParameter
{
public:
	///@brief Contact type
	enum EContactType
	{
		eProportional,
		eTopConformable,
		eBottomConformable
	};
public:
	///@brief Default Constructor
	CXParameterBuildLFM();

	///@brief Destructor
	virtual ~CXParameterBuildLFM() {}

public:
	///@brief Set and get low frequency model name
	X_PROPERTY(QString, LFMName);

	///@brief Survey ID
	X_PROPERTY(QUuid, SurveyID);

	///@brief Top and Bottom shift
	X_PROPERTY(float, TopShift);
	X_PROPERTY(float, BottomShift);

	///@brief Ranges of inline and xline
	X_PROPERTY(int, MinInlineNum);
	X_PROPERTY(int, MaxInlineNum);
	X_PROPERTY(int, MinXlineNum);
	X_PROPERTY(int, MaxXlineNum);

	///@brief Polygon 
	X_PROPERTY(QUuid, PolygonID);
	X_PROPERTY(QString, PolygonName);

	X_PROPERTY(std::vector<QUuid>, VecHorizonID);
	X_PROPERTY(QStringList, HorizonNameList);

	X_PROPERTY(std::vector<int>, VecContactType);
	X_PROPERTY(std::vector<int>, VecSliceNum);
	X_PROPERTY(std::vector<float>, VecThickness);
	X_PROPERTY(QStringList, ZoneNameList);

	///@brief Initialize the contact type for each block
	void Initialize();

	///@brief Get the contact name
	static QString GetContactName(int nContactType);
};

#endif // KEPARAMETERBUILDLFM_H
