#ifndef XPROCESSFRACTUREINVERSION_H
#define XPROCESSFRACTUREINVERSION_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcess3TermAVOInversion in the file "keprocessfractureinversion.h"
* @brief The class provides a process to do fracture inversion
*
* @author Yong Shu
* @date 12/22/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessFractureInversion : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessFractureInversion();
	virtual ~CXProcessFractureInversion();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXSeismicDataVolume* m_pDV;

};

#endif // KEPROCESSFRACTUREINVERSION_H
