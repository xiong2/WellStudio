#ifndef XPROCESSTRACETOSLICE_H
#define XPROCESSTRACETOSLICE_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CXProcessTraceToSlice in the file "rlprocesstracetoslice.h"
* @brief The class provides a process to convert trace file to slice file
* @breif 
* 
* @author Yong Shu 
* @date 5/27/2014
* @see 
*/
class XALGORITHM_EXPORT CXProcessTraceToSlice : public IKEProcess
{
public:	
	///@brief Constructor and destructor
	CXProcessTraceToSlice(void);
	virtual ~CXProcessTraceToSlice(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate( CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // RLPROCESSTRACETOSLICE_H
