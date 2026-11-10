#include <qpainter.h>
#include "xlinestylecombo.h"

CXLineStyleCombo::CXLineStyleCombo(QWidget *parent): QComboBox(parent), m_pIconSize(40,3)
{
	QStringList strLineTypeVec ;
	strLineTypeVec.clear() ;
	strLineTypeVec.push_back("Solid Line") ;
	strLineTypeVec.push_back("Dash Line") ;
	strLineTypeVec.push_back("Dot Line") ;
	strLineTypeVec.push_back("Dash Dot Line") ;
	strLineTypeVec.push_back("Dash Dot Dot Line") ;

	setIconSize(m_pIconSize);
	for(int i=0;i<5;i++)
	{
		addItem(_Icon((Qt::PenStyle)(i+1)),strLineTypeVec.at(i));
	}    
}

CXLineStyleCombo::~CXLineStyleCombo()
{
}

QPixmap CXLineStyleCombo::_Pixmap(Qt::PenStyle ePenStyle)
{
	QRect nRect(QPoint(0,0),m_pIconSize);
	QPixmap Pixmap(nRect.size());
	Pixmap.fill();
	QPainter Painter(&Pixmap);

	Painter.setPen(QPen(Qt::black,m_pIconSize.height(),(Qt::PenStyle)ePenStyle));
	Painter.drawLine(0,
					 nRect.center().y(),
					 nRect.width(),
					 nRect.center().y());

	return Pixmap;
}

QIcon CXLineStyleCombo::_Icon(Qt::PenStyle ePenStyle)
{
	return QIcon(_Pixmap(ePenStyle));
}

Qt::PenStyle CXLineStyleCombo::GetLineType()
{
	return (Qt::PenStyle)(currentIndex()+1);
}

void CXLineStyleCombo::SetLineType(Qt::PenStyle eLineType)
{
	setCurrentIndex((int)eLineType-1);
}