#ifndef XPROCESSPROPMODINCISION_H
#define XPROCESSPROPMODINCISION_H

#include "xprocess.h"
#include "xalgorithm_global.h"

/**
* @class CXProcessModelIntersection in the file "rlprocessmodelintersecion.h"
* @brief The class provides a process to intersect with GridModel
* 
* @author Pezy
* @date 3/10/2015
* @see 
*/

class CXBaseParameter;

class XALGORITHM_EXPORT CXProcessModelIntersection : public IKEProcess
{
public:
	CXProcessModelIntersection(void);
	virtual ~CXProcessModelIntersection();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate( CXObject* pParentObj, CXBaseParameter* pPara) override;

protected:
	virtual void slotFinishedComputing() override;
	
};

#endif // CRLPROCESSPROPMODINCISION_H
