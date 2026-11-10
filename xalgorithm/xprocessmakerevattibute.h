#ifndef CRLPROCESSMAKEREVATTRIBUTE_H_H
#define CRLPROCESSMAKEREVATTRIBUTE_H_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXProcessMakeRevAttribute:public IKEProcess
{
public:	
	///@brief Constructor and destructor
	CXProcessMakeRevAttribute(void);
	virtual ~CXProcessMakeRevAttribute(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate( CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

};

#endif