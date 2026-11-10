#ifndef CRLCURSOR_H
#define CRLCURSOR_H

#include "xdata_global.h"
#include "xobject.h"

///@brief	The class provides a class for a cursor 
///@author	Yong Shu
///@date	July, 2014
///@see		
class XDATA_EXPORT CXCursor: public CXObject
{
public:
	CXCursor();
	~CXCursor();

	static CXCursor& Instance();


	///@brief Set and get the cursor position
	void SetPosition(double dX, double dY, double dZ);
	void GetPosition(double& dX, double& dY, double& dZ);

private:
	double m_dX, m_dY, m_dZ;
};

#endif // CRLCURSOR_H
