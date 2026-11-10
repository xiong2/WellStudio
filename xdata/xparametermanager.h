#ifndef XPARAMETERMANAGER_H
#define XPARAMETERMANAGER_H

#include "xio.h"
#include "xdata_global.h"
#include <qmap.h>

class CXBaseParameter;

/**
* @class CXParameterManager in the file "rlparametermanager.h"
* @brief The class provide a manager for all parameters
* 
* @author Yong Shu 
* @date 5/15/2014
* @see 
*/
class XDATA_EXPORT CXParameterManager : public IKEIO
{
public:
	///@brief Destructor
	~CXParameterManager();

	///@brief Get the unique instance of this class 
	static CXParameterManager& Instance()
	{
		static CXParameterManager object;
		return object;
	}

	///@brief Add one attribute parameter with the specific object ID
	void AddParameter(const QUuid& ObjID, const CXBaseParameter& parameter);

	///@brief Get the attribute parameter according to the object ID
	CXBaseParameter* GetParameterByID(const QUuid& ObjID);

	///@brief Remove the parameter according to the object ID
	void RemoveOneParameter (const QUuid& ObjID);
	
	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Clear the map
	void ClearMap();

private:
	// private constructor
	CXParameterManager();

private:
	QMap<QUuid, CXBaseParameter*> m_mapIDToParameter;	
	
};

#endif // RLPARAMETERMANAGER_H
