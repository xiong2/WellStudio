#include "xcolormapcombo.h"
#include "xcolormap.h"
#include <cassert>
#include <QPainter>
#include "xcolormap.h"

CXColormapCombo::CXColormapCombo(QWidget *parent)
	: CXBaseComboBox(parent)
{	
	setIconSize(QSize(55, 10));
	setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
	setMinimumWidth(170);

	UpdateColormapList();
}

void CXColormapCombo::UpdateColormapList()
{
	clear();
	for (const auto& strColormapName : CXColormap::GetAllColormapsName())
	{
		addItem(QIcon(CXColormap::GeneratePixmap(strColormapName)), strColormapName);
	}
}

void CXColormapCombo::UpdateCurrentColormapIcon()
{
	setItemIcon(currentIndex(), QIcon(CXColormap::GeneratePixmap(currentText())));
}
