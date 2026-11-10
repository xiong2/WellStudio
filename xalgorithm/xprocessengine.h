#ifndef XPROCESSENGINE_H
#define XPROCESSENGINE_H

#include "xobjecttype.h"
#include "xalgorithm_global.h"

class CXObject;
class CXBaseParameter;
class QWidget;

/**
* @class CXProcessEngine in the file "keprocessengine.h"
* @brief The class is interface for calculation engine.
* 
* @author Yong Shu 
* @date 5/16/2015
* @see 
*/
class XALGORITHM_EXPORT CXProcessEngine 
{
public:
	///@brief Constructor
	CXProcessEngine(CXObject* pCurrentObj, EXObjectType eType);

	///@brief  Destructor
	~CXProcessEngine();

	///@brief The process to calculate the attribute
	///@para[in] bModal : Tell if the dialog to retrieve parameter is modal or not
	void Calculate(bool bModal = true);

	///@brief The process to calculate the attribute
	///@brief The dialog to retrieve the parameter is not required.
	void CalculateOnly();

	
private:
	void _SetWidgetSize(QWidget* pWidget);


private:
	EXObjectType  m_eGeneralObjectType;

	CXObject* m_pCurrentObject;

	CXBaseParameter* m_pParameter;
};

#endif // RLPROCESSENGINE_H
