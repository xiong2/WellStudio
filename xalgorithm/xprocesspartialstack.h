#ifndef XPROCESSPARTIALSTACK_H
#define XPROCESSPARTIALSTACK_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @brief The class provides a process to do a partial stack
*
* @author Xiong Xiong
* @date July 2016
* @see
*/
class XALGORITHM_EXPORT CXProcessPartialStack : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessPartialStack(void);
	virtual ~CXProcessPartialStack(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // KEPROCESSPARTIALSTACK_H
