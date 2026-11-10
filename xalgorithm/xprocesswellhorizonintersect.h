#ifndef XPROCESSWELLHORIZONINTERSECT_H
#define XPROCESSWELLHORIZONINTERSECT_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CXProcessWellHorizonIntersect in the file "rlprocesswellhorizonintersect.h"
* @brief The class provides a process to calculate intersection between the well and horizon
* @breif 
* 
* @author Yong Shu 
* @date 6/6/2014
* @see 
*/
class XALGORITHM_EXPORT CXProcessWellHorizonIntersect : public IKEProcess
{
public:	
	///@brief Constructor and destructor
	CXProcessWellHorizonIntersect(void);
	virtual ~CXProcessWellHorizonIntersect(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate( CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // RLPROCESSWELLHORIZONINTERSECT_H
