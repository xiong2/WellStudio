#ifndef XPROCESSFRACTUREATTRIBUTE_H
#define XPROCESSFRACTUREATTRIBUTE_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessFractureAttribute in the file "keprocessfractureattribute.h"
* @brief The class provides a process to calculate fracture attribute from VpVs
*
* @author Yong Shu
* @date 12/29/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessFractureAttribute : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessFractureAttribute();
	virtual ~CXProcessFractureAttribute();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	std::vector<CXSeismicDataVolume*> m_vecDV;

};

#endif // KEPROCESSFRACTUREATTRIBUTE_H
