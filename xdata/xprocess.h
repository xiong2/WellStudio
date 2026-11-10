#ifndef XPROCESS_H
#define XPROCESS_H

#include "xdata_global.h"
#include <vector>
#include <qobject.h>

class CXObject;
class CXBaseParameter;
class CXBaseThread;

/**
* @class IKEProcess in the file "IKEProcess.h"
* @brief The abstract class provides an interface to access all different processes.
* @breif 
* 
* @author Yong Shu 
* @date 5/16/2014
* @see 
*/
class XDATA_EXPORT IKEProcess : public QObject
{
	Q_OBJECT
public:	
	IKEProcess (void);
	virtual ~IKEProcess (void);

	/**
	* @brief Compute and create the new objects based on the parent object
	* @param[in] pCurrentObj : the parent object 
	* @param[in] pPara : the computation parameter
	* @return 
	* @date 12/16/2010
	* @see 
	*/
	virtual void Calculate( CXObject* pParentObj, CXBaseParameter* pPara) = 0;	

	/**
	* @brief Recalculate and upgrade the current object
	* @param[in] pTargetObj : the current object
	* @param[in] pPara : the computation parameter
	* @return 
	* @date 12/16/2010
	* @see 
	*/
	virtual void Recalculate(CXObject* pTargetObj, CXBaseParameter* pPara);

		/**
	* @brief Calculate and create the new objects based on the parent object and multiple parameters
	* @param[in] pTargetObj : the current object
	* @param[in] vecPara : the array of the computation parameters
	* @return 
	* @date 12/16/2010
	* @see 
	*/
	virtual void Calculate (CXObject* pTargetObj, std::vector<CXBaseParameter*> vecPara);

public slots:
	virtual void slotFinishedComputing (void);

protected:	
	CXBaseThread* m_pThread;
	CXObject* m_pParentObject;
	CXBaseParameter* m_pPara;
};

#endif // RLPROCESS_H
