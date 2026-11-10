#ifndef XPROCESSANISOTROPYFORWARDING_H
#define XPROCESSANISOTROPYFORWARDING_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessAnisotropyForwarding in the file "CXProcessAnisotropyForwarding.h"
* @brief The class provides a process for seismic anisotropy forwarding
*
* @author Yong Shu
* @date 12/26/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessAnisotropyForwarding : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessAnisotropyForwarding();
	virtual ~CXProcessAnisotropyForwarding();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXSeismicDataVolume* m_pDV;

};

#endif // KEPROCESSANISOTROPYFORWARDING_H
