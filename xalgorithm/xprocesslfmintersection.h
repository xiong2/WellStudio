#ifndef XPROCESSLFMINTERSECTION_H
#define XPROCESSLFMINTERSECTION_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CXProcessLFMIntersection in the file "keprocesslfmintersection.h"
* @brief The class provides a process to generate upscaling geometry
*
* @author Yong Shu
* @date 11/24/2015
* @see
*/
class XALGORITHM_EXPORT CXProcessLFMIntersection : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessLFMIntersection(void);
	virtual ~CXProcessLFMIntersection(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

};

#endif // KEPROCESSLFMINTERSECTION_H
