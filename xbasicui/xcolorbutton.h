#ifndef CRLCOLORBUTTON_H
#define CRLCOLORBUTTON_H

#include "xbasicui_global.h"
#include "xbuttoncoloredit.h"

class XBASICUI_EXPORT CXColorButton : public CXButtonColorEdit
{
	Q_OBJECT
public:
	CXColorButton(QWidget *parent,int nNumOfButton=3,int minWidth=80);
	virtual~CXColorButton();
	void SetButtonNum(int nButtonNum);

	void SetObjectColor(const QColor& c);
	/**
	* @brief Set a color edit control as the source of the object color,once the sourece object color changed, the control reset object color.
	* @param pColorEdit the source object color control.
	* @return 
	* @date 7/1/2010
	* @see 
	*/
	void SetObjectColorBuddyWidget(CXButtonColorEdit* pColorEdit);
public slots:
	void slotReplaceObjectColor(const QColor& c);//replace object color and it's icon but did not change the color type.

};

#endif // GMCOLORBUTTON_H
