#ifndef XPROCESSLFMINTERPOLATION_H
#define XPROCESSLFMINTERPOLATION_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXLFMAttribute;

/**
* @class CXProcessLFMInterpolation in the file "keprocesslfminterpolation.h"
* @brief The class provides a process to generate upscaling geometry
*
* @author Yong Shu
* @date 11/24/2015
* @see
*/
class XALGORITHM_EXPORT CXProcessLFMInterpolation : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessLFMInterpolation(void);
	virtual ~CXProcessLFMInterpolation(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXLFMAttribute* m_pAttribute;

};

#endif // KEPROCESSLFMINTERPOLATION_H
