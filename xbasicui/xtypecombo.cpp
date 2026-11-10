#include <qpainter.h>
#include "xtypecombo.h"
#include "xglobal.h"

CXTypeCombo::CXTypeCombo(QWidget * parent) : CXTypeCombo(ePointType, parent)
{
}

CXTypeCombo::CXTypeCombo(EXComboType eType, QWidget *parent): QComboBox(parent)
{
	m_eType = eType;

	QStringList strListType ;

	if(eType == ePointType)
	{
		m_iconSize.setWidth(30);
		m_iconSize.setHeight(17);
		strListType << tr("Point") << tr("Cross") << tr("Triangle") << tr("Diamond") << tr("Square") << tr("Circle") << tr("Solid Triangle") << tr("Solid Diamond") << tr("Solid Square") << tr("Solid Circle");
	}
	else if(eType == ePatternType)
	{
		m_iconSize.setWidth(30);
		m_iconSize.setHeight(30);
		strListType << tr("No Fill") << tr("Pebble Sandstone") << tr("Coarse Sandstone") << tr("Middle Sandstone") << tr("Fine Sandstone") << tr("Siltstone") << tr("Shale") << tr("Mudstone") << tr("Folium Limestone") << tr("Dolimite") << tr("Gyprock") << tr("Salt Rock") << tr("Coal");
	}

	setIconSize(m_iconSize);
	for(int i = 0; i < strListType.size(); i++)
	{
		addItem(_GetIcon(i), strListType.at(i));
	}    
}

QPixmap CXTypeCombo::_GetPixmap(int i)
{
	QRect nRect(QPoint(0,0), m_iconSize);
	QPixmap Pixmap(nRect.size());
	Pixmap.fill();
	QPainter painter(&Pixmap);

	QPen pen(QColor("Black"));

	pen.setWidth(2);
	painter.setPen(pen);

	switch(i)
	{
	case 0:
	{
		painter.drawPoint(9, 9);
		break;
	}
	case 1:
	{
		painter.drawLine(2, 9, 16, 9);
		painter.drawLine(9, 2, 9, 16);
		break;
	}
	case 2:
	{
		QPoint points[3] = {QPoint(9, 2), QPoint(16, 16), QPoint(2, 16)};
		painter.drawPolygon(points, 3);
		break;
	}
	case 3:
	{
		QPoint points[4] = {QPoint(9, 2), QPoint(16, 9), QPoint(9, 16), QPoint(2, 9)};
		painter.drawPolygon(points, 4);
		break;
	}
	case 4:
	{
		QPoint points[4] = {QPoint(3, 3), QPoint(15, 3), QPoint(15, 15), QPoint(3, 15)};
		painter.drawPolygon(points, 4);
		break;
	}
	case 5:
	{
		painter.drawEllipse(2, 2, 14, 14);
		break;
	}
	case 6:
	{
		painter.setBrush(QBrush(QColor("Black")));
		QPoint points[3] = {QPoint(9, 2), QPoint(16, 16), QPoint(2, 16)};
		painter.drawPolygon(points, 3);
		break;
	}
	case 7:
	{
		painter.setBrush(QBrush(QColor("Black")));
		QPoint points[4] = {QPoint(9, 2), QPoint(16, 9), QPoint(9, 16), QPoint(2, 9)};
		painter.drawPolygon(points, 4);
		break;
	}
	case 8:
	{
		painter.setBrush(QBrush(QColor("Black")));
		QPoint points[4] = {QPoint(3, 3), QPoint(15, 3), QPoint(15, 15), QPoint(3, 15)};
		painter.drawPolygon(points, 4);
		break;
	}
	case 9:
	{
		painter.setBrush(QBrush(QColor("Black")));
		painter.drawEllipse(2, 2, 14, 14);
		break;
	}
	}

	return Pixmap;
}

QIcon CXTypeCombo::_GetIcon(int i)
{
	if(m_eType == ePointType)
		return QIcon(_GetPixmap(i));
	else
	{
		if(i > 12)
			i = 0;

		if(i == 0)
			return QIcon();

		QStringList sListFileName;
		sListFileName<<"227"<<"228"<<"229"<<"230"<<"231"<<"301"<<"309"<<"342"<<"365"<<"388"<<"393"<<"403";

		QString sFile = "../Icon/" + sListFileName[i - 1] + ".bmp";
		return QIcon(sFile);
	}
}

int CXTypeCombo::GetSelectedType()
{
	return currentIndex();
}

void CXTypeCombo::SetSelectedType(int i)
{
	setCurrentIndex(i);
}

QPixmap CXTypeCombo::GetPatternPixmap(int i)
{
	if(i < 1 || i > 12)
		i = 1;

	QStringList sListFileName;
	sListFileName<<"227"<<"228"<<"229"<<"230"<<"231"<<"301"<<"309"<<"342"<<"365"<<"388"<<"393"<<"403";

	QString sFile = "../Icon/" + sListFileName[i - 1] + ".bmp";
	
	return QPixmap(sFile);
}