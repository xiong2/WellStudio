#ifndef XPROCESSCSSINVERSION_H
#define XPROCESSCSSINVERSION_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessCSSInversion in the file "keprocesscssinversion.h"
* @brief The class provides a process to make CSSI
*
* @author Yong Shu
* @date 11/18/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessCSSInversion : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessCSSInversion();
	virtual ~CXProcessCSSInversion();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	std::vector<CXSeismicDataVolume*> m_vecDV;

};

#endif // KEPROCESSCSSINVERSION_H
