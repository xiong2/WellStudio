#ifndef XPARAMETERPCAFILTERING_H
#define XPARAMETERPCAFILTERING_H

#include <vector>
#include <QStringList>
#include "xdataplus_global.h"
#include "xparameterinversion.h"

/**
* @class CXParameterPCAFiltering provided in the file "keparameterpcafiltering.h"
* @brief The class provides parameters for PCA filtering
* @author Yong Shu
* @date 6/7/2016
*
*/

class XDATAPLUS_EXPORT CXParameterPCAFiltering : public CXParameterInversion
{
public:
	///@brief Default Constructor
	CXParameterPCAFiltering();

	///@brief Destructor
	virtual ~CXParameterPCAFiltering() {}

public:
	X_PROPERTY(int, WinNI);
	X_PROPERTY(int, WinNJ);
	X_PROPERTY(int, WinNK);

	X_PROPERTY(QUuid, DVID);
	X_PROPERTY(QString, DVName);



};

#endif // KEPARAMETERPCAFILTERING_H
