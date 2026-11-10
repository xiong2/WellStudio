#ifndef IKEVIEW_H
#define IKEVIEW_H

#include "xdata_global.h"

class CXEventParameter;

///@brief	The class provides interface for abstract view
///@author	Yong Shu
///@date	July, 2014
///@see	

class XDATA_EXPORT IKEView
{
public:
	IKEView();
	virtual ~IKEView();

public:
	virtual void UpdateView(const CXEventParameter& eventPara) = 0;
	
};

#endif // IKEVIEW_H
