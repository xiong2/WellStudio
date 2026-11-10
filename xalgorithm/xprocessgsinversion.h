#ifndef XPROCESSGSINVERSION_H
#define XPROCESSGSINVERSION_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @brief The class provides a process to geostatistical inversion
*
* @author Xiong
* @date Dec 2016
* @see
*/
class XALGORITHM_EXPORT CXProcessGSInversion : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessGSInversion(void);
	virtual ~CXProcessGSInversion(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // KEPROCESSDETECTGEOBODY_H