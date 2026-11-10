#ifndef XPROCESSINTERPOLATEDV_H
#define XPROCESSINTERPOLATEDV_H


#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXSeismicDataVolume;

/**
* @class CXProcessInterpolateDV in the file "CXProcessInterpolateDV.h"
* @brief The class provides a process to interpolate data volume trace by trace
* @breif
*
* @author Yong Shu
* @date 12/27/2016
* @see
*/

class XALGORITHM_EXPORT CXProcessInterpolateDV : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessInterpolateDV(void);
	virtual ~CXProcessInterpolateDV(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXSeismicDataVolume* m_pDV;
};

#endif // KEPROCESSINTERPOLATEDV_H
