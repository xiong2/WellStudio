#ifndef XPROCESSRECALCHISTOGRAM_H
#define XPROCESSRECALCHISTOGRAM_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CXProcessRecalcHistogram in the file "keprocessrecalchistogram.h"
* @brief The class provides a process to recalculate histogram
*
* @author Yong Shu
* @date 8/17/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessRecalcHistogram : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessRecalcHistogram();
	virtual ~CXProcessRecalcHistogram();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};


#endif // KEPROCESSRECALCHISTOGRAM_H
