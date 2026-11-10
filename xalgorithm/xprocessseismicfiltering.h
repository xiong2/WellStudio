#ifndef XPROCESSSEISMICFILTERING_H
#define XPROCESSSEISMICFILTERING_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessSeismicFiltering in the file "keprocessseismicfiltering.h"
* @brief The class provides a process to do seismic filtering
*
* @author Yong Shu
* @date 5/18/2016
* @see
*/
class XALGORITHM_EXPORT CXProcessSeismicFiltering : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessSeismicFiltering();
	virtual ~CXProcessSeismicFiltering();

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXSeismicDataVolume* m_pDV;

};

#endif // KEPROCESSSEISMICFILTERING_H
