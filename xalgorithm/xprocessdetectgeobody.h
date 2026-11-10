#ifndef XPROCESSDETECTGEOBODY_H
#define XPROCESSDETECTGEOBODY_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CXProcessDetectGeobody in the file "keprocessdetectgeobody.h"
* @brief The class provides a process to detect geobodies
*
* @author Yong Shu
* @date 11/18/2015
* @see
*/
class XALGORITHM_EXPORT CXProcessDetectGeobody : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessDetectGeobody(void);
	virtual ~CXProcessDetectGeobody(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // KEPROCESSDETECTGEOBODY_H
