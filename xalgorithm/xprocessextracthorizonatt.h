#ifndef XPROCESSEXTRACTHORIZONATT_H
#define XPROCESSEXTRACTHORIZONATT_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessExtractHorizonAtt in the file "keprocessextracthorizonatt.h"
* @brief The class provides a process for extracting horizon attributes
*
* @author Yong Shu
* @date 9/28/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessExtractHorizonAtt : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessExtractHorizonAtt();
	virtual ~CXProcessExtractHorizonAtt();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

};


#endif // KEPROCESSEXTRACTHORIZONATT_H
