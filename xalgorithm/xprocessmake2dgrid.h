#ifndef XPROCESSMAKE2DGRID_H
#define XPROCESSMAKE2DGRID_H

#include "xprocess.h"
#include "xalgorithm_global.h"

class CXBaseParameter;

/**
* @class CXProcessMake2DGrid in the file "rlprocessmake2dgrid.h"
* @brief The class provides a process to make 2-D grid
* @breif 
* 
* @author Yong Shu 
* @date 5/22/2014
* @see 
*/
class XALGORITHM_EXPORT CXProcessMake2DGrid : public IKEProcess
{
public:	
	///@brief Constructor and destructor
	CXProcessMake2DGrid(void);
	virtual ~CXProcessMake2DGrid(void);

	///@brief Compute and create the new objects based on the parent object
	virtual void Calculate( CXObject* pParentObj, CXBaseParameter* pPara);

protected:
	virtual void slotFinishedComputing();
};

#endif // RLPROCESSMAKE2DGRID_H
