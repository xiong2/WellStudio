#ifndef XBASEPROPERTYPAGE_H
#define XBASEPROPERTYPAGE_H

#include <qwidget.h>
#include "xgui_global.h"

///@brief	The class provides the base class for all property pages
///@author	Yong Shu
///@date	Jun. 16th, 2014
///@see	

class CXButtonColorEdit;
class XGUI_EXPORT CXBasePropertyPage : public QWidget
{
	Q_OBJECT

public:
	CXBasePropertyPage(QWidget *parent);
	~CXBasePropertyPage();

	virtual void Apply();

	//@Brief: As the object color changed, we should notice the visualization page, and then update color buttons.
	virtual void SetObjectColorBuddyButton(CXButtonColorEdit*);
};

#endif // RLBASEPROPERTYPAGE_H
