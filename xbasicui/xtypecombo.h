#ifndef _CXPOINTTYPECOMBO_H__
#define _CXPOINTTYPECOMBO_H__

#include "xbasicui_global.h"
#include <qcombobox.h>

enum EXComboType
{
	ePointType			= 0,	//	Point symbol.
	ePatternType		= 1,	//	Fill pattern.
};

class XBASICUI_EXPORT CXTypeCombo: public QComboBox
{
public:
	CXTypeCombo(QWidget *parent = 0);
	CXTypeCombo(EXComboType eType, QWidget * parent = 0);

	int GetSelectedType();
	void SetSelectedType(int);

	static QPixmap GetPatternPixmap(int i);

private:
	QPixmap _GetPixmap(int);
	QIcon _GetIcon(int);

	QSize m_iconSize;
	EXComboType	m_eType;	
};

#endif