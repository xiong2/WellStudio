#ifndef XPROCESSPCAFILTERING_H
#define XPROCESSPCAFILTERING_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessPCAFiltering in the file "keprocesspcafiltering.h"
* @brief The class provides a process to do seismic PCA filtering
*
* @author Yong Shu
* @date 6/8/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessPCAFiltering : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessPCAFiltering();
	virtual ~CXProcessPCAFiltering();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXSeismicDataVolume* m_pDV;

};

#endif // KEPROCESSPCAFILTERING_H
