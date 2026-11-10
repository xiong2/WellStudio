#ifndef XBASEPARAMETER_H
#define XBASEPARAMETER_H

#include <QObject>
#include "xdata_global.h"
#include "xdef.h"
#include "xio.h"


/**
* @class CXBaseParameter in the file "rlbaseparameter.h"
* @brief The class is a base class for all parameters
* 
* @author Yong Shu 
* @date 5/13/2014
* @see 
*/
class XDATA_EXPORT CXBaseParameter : public QObject, public IKEIO
{
public:
	///@brief Constructor
	CXBaseParameter();
	///@brief Copy constructor
	CXBaseParameter(const CXBaseParameter&);

	///@brief Copy assignment operator
	CXBaseParameter& operator=(const CXBaseParameter&);

	///@brief  Destructor
	virtual ~CXBaseParameter();

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Define Set and Get functions
	///@ for example,   GM_PROPERTY(std::vector<QUuid>, VecOutputObjID) represents two functions:
	///@ void SetVecOutputObjID( std::vector<QUuid> vecOutputObjID) and 
	///@ std::vector<unsigned int> GetVecOutputObjID()  
	X_PROPERTY(std::vector<QUuid>, VecOutputObjID)	
	X_PROPERTY(std::vector<QUuid>, VecInputObjID)


	///@brief Get the true name. if the object corresponding to the object ID does not exit, 
	///@brief the given name is returned, otherwise return the object name
	static QString GetTrueName (const QUuid& ObjID, const QString& strName);

	///@brief Get the true name list. if the object corresponding to the object ID does not exit, 
	///@brief the given name is returned, otherwise return the object name
	static QStringList GetTrueNameList (const std::vector<QUuid>& vecObjID, const QStringList& strNameList);

private:
	void _CloneObj(const CXBaseParameter& Other);
};


///@brief Load/save functions to std::vector<T> parameters during QVariant conversion.
 template <typename T>
 QDataStream &operator<<(QDataStream &out, const std::vector<T> &myObj)
 {
	 int nSize= myObj.size();
	 out << nSize;
	 for(int i=0;i<nSize;i++)
	 {
		 out << myObj.at(i);
	 }
	 return out;
 }

 template <typename T>
 QDataStream &operator>>(QDataStream &in, std::vector<T> &myObj)
 {
	 int nSize;
	 in >> nSize;
	 for(int i=0;i<nSize;i++)
	 {
		 T tmpValue;
		 in >> tmpValue;
		 myObj.push_back(tmpValue);
	 }
	 return in;
 }




#endif // RLBASEPARAMETER_H
