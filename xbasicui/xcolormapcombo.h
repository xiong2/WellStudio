#ifndef XCOLORMAPCOMBO_H
#define XCOLORMAPCOMBO_H

#include "xbasicui_global.h"
#include <QComboBox>
#include "xbasecombobox.h"

class XBASICUI_EXPORT CXColormapCombo : public CXBaseComboBox
{
public:
	CXColormapCombo(QWidget *parent = 0);

	void UpdateColormapList();
	void UpdateCurrentColormapIcon();
};

#endif // RLCOLORMAPCOMBO_H
