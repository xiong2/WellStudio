#ifndef XVIEWINFOMANAGER_H
#define XVIEWINFOMANAGER_H

#include "xio.h"
#include "xdata_global.h"
#include <qmap.h>

class CXViewInfoObject;

/**
* @class CXViewInfoManager in the file "keviewinfomanager.h"
* @brief The class provide a manager for all default view info
*
* @author Yong Shu
* @date 11/13/2015
* @see
*/
class XDATA_EXPORT CXViewInfoManager : public IKEIO
{
public:
	///@brief Destructor
	~CXViewInfoManager();

	///@brief Get the unique instance of this class 
	static CXViewInfoManager& Instance()
	{
		static CXViewInfoManager object;
		return object;
	}

	///@brief Get default view info from object ID
	CXViewInfoObject* GetDefaultViewInfoByID(const QUuid& uuid);

	///@brief Remove the parameter according to the object ID
	void RemoveOneViewInfo(const QUuid& ObjID);


	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

private:
	// private constructor
	CXViewInfoManager();

	// Clear the map
	void _ClearMap();

private:
	QMap<QUuid, CXViewInfoObject*> m_mapIDToViewInfo;

};

#endif // KEVIEWINFOMANAGER_H
