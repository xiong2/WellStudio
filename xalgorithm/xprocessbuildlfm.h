#ifndef XPROCESSBUILDLFM_H
#define XPROCESSBUILDLFM_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;
class CXLFMGeometry;

/**
* @class CXProcessBuildLFM in the file "keprocessbuildlfm.h"
* @brief The class provides a process to build a low frequency model
*
* @author Yong Shu
* @date 11/19/2015
* @see
*/
class XALGORITHM_EXPORT CXProcessBuildLFM : public IKEProcess
{
public:
	///@brief Constructor and destructor
	CXProcessBuildLFM(void);
	virtual ~CXProcessBuildLFM(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate(CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();

private:
	CXLFMGeometry* m_pLFM;

};


#endif // KEPROCESSBUILDLFM_H
