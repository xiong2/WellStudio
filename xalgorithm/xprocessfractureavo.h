#ifndef XPROCESSFRACTUREAVO_H
#define XPROCESSFRACTUREAVO_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessFractureAVO in the file "keprocessfractureavo.h"
* @brief The class provides a process for AVO fracture analysis
*
* @author Yong Shu
* @date 9/28/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessFractureAVO : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessFractureAVO();
	virtual ~CXProcessFractureAVO();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	std::vector<CXSeismicDataVolume*> m_vecDV;

};


#endif // KEPROCESSFRACTUREAVO_H
