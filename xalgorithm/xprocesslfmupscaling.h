#ifndef XPROCESSLFMUPSCALING_H
#define XPROCESSLFMUPSCALING_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXLFMGeometry;

/**
* @class CXProcessLFMUpscaling in the file "keprocesslfmupscaling.h"
* @brief The class provides a process to upscale well curves
*
* @author Yong Shu
* @date 11/24/2015
* @see
*/
class XALGORITHM_EXPORT CXProcessLFMUpscaling : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessLFMUpscaling(void);
	virtual ~CXProcessLFMUpscaling(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

};

#endif // KEPROCESSLFMUPSCALING_H
