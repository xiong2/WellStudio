#ifndef _CXLINESTYLECOMBO_H__
#define _CXLINESTYLECOMBO_H__

#include "xgui_global.h"
#include <qcombobox.h>

class XGUI_EXPORT CXLineStyleCombo: public QComboBox
{
public:	
	CXLineStyleCombo(QWidget * parent = 0);
	virtual ~CXLineStyleCombo();

	Qt::PenStyle GetLineType();
	void SetLineType(Qt::PenStyle eLineStyle);
private:
	QPixmap _Pixmap(Qt::PenStyle ePenStyle);
	QIcon _Icon(Qt::PenStyle ePenStyle);
private:
	QSize m_pIconSize;
};

#endif