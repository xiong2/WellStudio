#ifndef GMPROCESSBRICKCONVERSION_H
#define GMPROCESSBRICKCONVERSION_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CGmProcessBrickConversion in the file "rlprocessbrickconversion.h"
* @brief The class provides a process to convert trace file to brick file
* @breif
*
* @author Yong Shu
* @date 11/5/2015
* @see
*/
class XALGORITHM_EXPORT CGmProcessBrickConversion : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CGmProcessBrickConversion(void);
	virtual ~CGmProcessBrickConversion(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // GMPROCESSBRICKCONVERSION_H
