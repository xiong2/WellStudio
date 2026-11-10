#ifndef XARCHIVE_H
#define XARCHIVE_H

#include "xdata_global.h"
#include <qdatastream.h>

/**
* @class CXArchive in the file "rlarchinve.h"
* @brief The class provides data structure for binary saving and loading
* 
* @author Yong Shu 
* @date 4/10/2014
*/
class XDATA_EXPORT CXArchive : public QDataStream
{
public:
	CXArchive(QByteArray* pByteArray, QIODevice::OpenMode eFlag, bool bSave);
	~CXArchive() {}

	///@brief Get saving flag
	bool IsSaving() {return m_bSave;}

private:
	bool m_bSave;
	
};

#endif // RLARCHIVE_H
