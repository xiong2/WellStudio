#include <QLabel>
#include <QGridLayout>
#include "x2dpointcomponent.h"
#include "xbuttoncoloredit.h"
#include "xcolorbutton.h"

CXPointShapeBox::CXPointShapeBox(QWidget * parent):CXBaseComboBox(parent)
{
	QIcon icon1  ( QPixmap ( ":/icon/1458.png" ) ) ;
	QIcon icon2  ( QPixmap ( ":/icon/1468.png" ) ) ;
	QIcon icon3  ( QPixmap ( ":/icon/1492.png" ) ) ;
	QIcon icon4  ( QPixmap ( ":/icon/1459.png" ) ) ;
	QIcon icon5  ( QPixmap ( ":/icon/1465.png" ) ) ;
	QIcon icon6  ( QPixmap ( ":/icon/1491.png" ) ) ;
	QIcon icon7  ( QPixmap ( ":/icon/1460.png" ) ) ;
	QIcon icon8  ( QPixmap ( ":/icon/1474.png" ) ) ;
	QIcon icon9  ( QPixmap ( ":/icon/1463.png" ) ) ;
	QIcon icon10  ( QPixmap ( ":/icon/1493.png" ) ) ;
	QIcon icon11  ( QPixmap (  ":/icon/1464.png" ) ) ;
	QIcon icon12  ( QPixmap (  ":/icon/1466.png" ) ) ;
	QIcon icon13  ( QPixmap (  ":/icon/1467.png" ) ) ;
	QIcon icon14  ( QPixmap (  ":/icon/1494.png" ) ) ;
	QIcon icon15  ( QPixmap (  ":/icon/1469.png" ) ) ;
	QIcon icon16  ( QPixmap (  ":/icon/1470.png" ) ) ;
	QIcon icon17  ( QPixmap (  ":/icon/1490.png" ) ) ;
	QStringList iconName;
	iconName<<":/icon/1458.png"<<":/icon/1468.png"<<":/icon/1492.png"<<":/icon/1459.png"<<":/icon/1465.png"<<":/icon/1491.png"
			<<":/icon/1460.png"<<":/icon/1474.png"<<":/icon/1463.png"<<":/icon/1493.png"<<":/icon/1464.png"<<":/icon/1464.png"
			<<"/icon/1467.png"<<"/icon/1494.png"<<"/icon/1469.png"<<"/icon/1470.png"<<"/icon/1490.png";
	QVector<QIcon> iconVec ;
	iconVec.push_back( icon1 ) ;
	iconVec.push_back( icon2 ) ;
	iconVec.push_back( icon3 ) ;
	iconVec.push_back( icon4 ) ;
	iconVec.push_back( icon5 ) ;
	iconVec.push_back( icon6 ) ;
	iconVec.push_back( icon7 ) ;
	iconVec.push_back( icon8 ) ;
	iconVec.push_back( icon9 ) ;
	iconVec.push_back( icon10 ) ;
	iconVec.push_back( icon11 ) ;
	iconVec.push_back( icon12 ) ;
	iconVec.push_back( icon13 ) ;
	iconVec.push_back( icon14 ) ;
	iconVec.push_back( icon15 ) ;
	iconVec.push_back( icon16 ) ;
	iconVec.push_back( icon17 ) ;

	QStringList PointsSymbolList ;
	PointsSymbolList.push_back( "Circle" ) ;
	PointsSymbolList.push_back( "Circle(Filled)" ) ;
	PointsSymbolList.push_back( "Circle(Contoured)" ) ;
	PointsSymbolList.push_back( "Up Triangle" ) ;
	PointsSymbolList.push_back( "Up Triangle(Filled)" ) ;
	PointsSymbolList.push_back( "Up Triangle(Contoured)" ) ;
	PointsSymbolList.push_back( "Cross" ) ;	
	PointsSymbolList.push_back( "Square" ) ;
	PointsSymbolList.push_back( "Square(Filled)" ) ;
	PointsSymbolList.push_back( "Square(Contoured)" ) ;
	PointsSymbolList.push_back( "Diagonal Cross" ) ;
	PointsSymbolList.push_back( "Down Triangle" ) ;
	PointsSymbolList.push_back( "Down Triangle(Filled)" ) ;
	PointsSymbolList.push_back( "Down Triangle(Contoured)" ) ;
	PointsSymbolList.push_back( "Diamond" ) ;
	PointsSymbolList.push_back( "Diamond(Filled)" ) ;
	PointsSymbolList.push_back( "Diamond(Contoured)" ) ;

	for ( int i = 0 ; i < PointsSymbolList.size() ; i++ )
	{
		insertItem( i , iconVec.at(i) , PointsSymbolList.at(i) ) ;
		setItemData ( i, iconName[i]);
	}
}

CXPointShapeBox::~CXPointShapeBox()
{

}
int CXPointShapeBox::GetMarkerSetIndex() const
{
	QMap<int,int> tmpMap;
	tmpMap.insert(0,10);
	tmpMap.insert(1,20);
	tmpMap.insert(2,20);
	tmpMap.insert(3,13);
	tmpMap.insert(4,23);
	tmpMap.insert(5,23);
	tmpMap.insert(6,1);
	tmpMap.insert(7,11);
	tmpMap.insert(8,21);
	tmpMap.insert(9,21);
	tmpMap.insert(10,0);
	tmpMap.insert(11,18);
	tmpMap.insert(12,28);
	tmpMap.insert(13,28);
	tmpMap.insert(14,12);
	tmpMap.insert(15,22);
	tmpMap.insert(16,22);
	int nIndex=tmpMap[currentIndex()];
	tmpMap.clear();
	return nIndex;
}
void CXPointShapeBox::SetMarkerSetIndex(const int& nIndex)
{
	QMap<int,int> tmpMap;
	tmpMap.insert(0,10);
	tmpMap.insert(1,20);
	tmpMap.insert(2,20);
	tmpMap.insert(3,13);
	tmpMap.insert(4,23);
	tmpMap.insert(5,23);
	tmpMap.insert(6,1);
	tmpMap.insert(7,11);
	tmpMap.insert(8,21);
	tmpMap.insert(9,21);
	tmpMap.insert(10,0);
	tmpMap.insert(11,18);
	tmpMap.insert(12,28);
	tmpMap.insert(13,28);
	tmpMap.insert(14,12);
	tmpMap.insert(15,22);
	tmpMap.insert(16,22);
	setCurrentIndex(tmpMap.key(nIndex));
	tmpMap.clear();
}

CXOIVMarkerShapeComboBox::CXOIVMarkerShapeComboBox(QWidget* parent)
: CXBaseComboBox(parent)
{
	_SetupUi();

	_setupData();
}

void CXOIVMarkerShapeComboBox::_SetupUi()
{
	// circle
	insertItem(0, QIcon(QPixmap(":/icon/1458.png")), tr("Circle"));
	insertItem(1, QIcon(QPixmap(":/icon/1468.png")), tr("Circle(Filled)"));
	
	// up triangle
	insertItem(2, QIcon(QPixmap(":/icon/1459.png")), tr("Up Triangle"));
	insertItem(3, QIcon(QPixmap(":/icon/1465.png")), tr("Up Triangle(Filled)"));

	// cross
	insertItem(4, QIcon(QPixmap(":/icon/1460.png")), tr("Cross"));

	// square
	insertItem(5, QIcon(QPixmap(":/icon/1474.png")), tr("Square"));
	insertItem(6, QIcon(QPixmap(":/icon/1463.png")), tr("Square(Filled)"));
	
	// diagnol cross
	insertItem(7, QIcon(QPixmap(":/icon/1464.png")), tr("Diagonal Cross"));

	// down triangle
	insertItem(8, QIcon(QPixmap(":/icon/1466.png")), tr("Down Triangle"));
	insertItem(9, QIcon(QPixmap(":/icon/1467.png")), tr("Down Triangle(Filled)"));

	// diamond
	insertItem(10, QIcon(QPixmap(":/icon/1469.png")), tr("Diamond"));
	insertItem(11, QIcon(QPixmap(":/icon/1470.png")), tr("Diamond(Filled)"));

	setCurrentIndex(0);
}

void CXOIVMarkerShapeComboBox::_setupData()
{
	// circle
	m_markerToUiMap.insert(std::pair<int, int>(10,0));
	m_markerToUiMap.insert(std::pair<int, int>(20,1));

	m_uiToMarkerMap.insert(std::pair<int, int>(0,10));
	m_uiToMarkerMap.insert(std::pair<int, int>(1,20));

	// up triangle
	m_markerToUiMap.insert(std::pair<int, int>(13,2));
	m_markerToUiMap.insert(std::pair<int, int>(23,3));

	m_uiToMarkerMap.insert(std::pair<int, int>(2,13));
	m_uiToMarkerMap.insert(std::pair<int, int>(3,23));

	// cross
	m_markerToUiMap.insert(std::pair<int, int>(1,4));

	m_uiToMarkerMap.insert(std::pair<int, int>(4,1));

	// square
	m_markerToUiMap.insert(std::pair<int, int>(11,5));
	m_markerToUiMap.insert(std::pair<int, int>(21,6));

	m_uiToMarkerMap.insert(std::pair<int, int>(5,11));
	m_uiToMarkerMap.insert(std::pair<int, int>(6,21));

	// diagnol cross
	m_markerToUiMap.insert(std::pair<int, int>(0,7));

	m_uiToMarkerMap.insert(std::pair<int, int>(7,0));

	// down triangle
	m_markerToUiMap.insert(std::pair<int, int>(18,8));
	m_markerToUiMap.insert(std::pair<int, int>(28,9));

	m_uiToMarkerMap.insert(std::pair<int, int>(8,18));
	m_uiToMarkerMap.insert(std::pair<int, int>(9,28));
	
	// diamond
	m_markerToUiMap.insert(std::pair<int, int>(12,10));
	m_markerToUiMap.insert(std::pair<int, int>(22,11));

	m_uiToMarkerMap.insert(std::pair<int, int>(10,12));
	m_uiToMarkerMap.insert(std::pair<int, int>(11,22));
}

int CXOIVMarkerShapeComboBox::GetMarkerType() const
{
	std::map<int, int>::const_iterator iter = m_uiToMarkerMap.find(currentIndex());
	if (iter != m_uiToMarkerMap.end())
		return iter->second;
	
	return 0;
}

void CXOIVMarkerShapeComboBox::SetMarkerType(int nType)
{
	std::map<int, int>::iterator iter = m_markerToUiMap.find(nType);
	if (iter != m_markerToUiMap.end())
	{
		int nUiIndex = iter->second;
		setCurrentIndex(nUiIndex);
	}
}

CX2DPointComponent::CX2DPointComponent(QWidget* pParent,
										 QGridLayout* pParentLayout,
										 int nRowIndex,
										 int nColumnIndex,
										 bool bObjectColorSupport,
										 bool bColormapSupport)
{
	m_pWidget=NULL;
	setParent(pParent);
	_initLayout(pParent,pParentLayout,nRowIndex,nColumnIndex,bObjectColorSupport,bColormapSupport);
}
CX2DPointComponent::CX2DPointComponent(QWidget* pParent,bool bObjectColorSupport,bool bColormapSupport)
{
	setParent(pParent);
	m_pWidget=new QWidget(pParent);
	QGridLayout* pOwnLayout=new QGridLayout(m_pWidget);
	_initLayout(m_pWidget,pOwnLayout,0,0,bObjectColorSupport,bColormapSupport);
	m_pWidget->setLayout(pOwnLayout);
}
CX2DPointComponent::~CX2DPointComponent(void)
{
}
void CX2DPointComponent::_initLayout(QWidget* pParent,
									  QGridLayout* pParentLayout,
									  int nRowIndex,
									  int nColumnIndex,
									  bool bObjectColorSupport,
									  bool bColormapSupport)
{
	int nNumSupport = 0 ;
	if(bObjectColorSupport)
	{
		nNumSupport = 2 ;
		if(bColormapSupport)
			nNumSupport = 3 ;
	}
	m_pLblColor=new QLabel(tr("Color:"),pParent);
	m_pBtnColor=new CXColorButton(pParent,nNumSupport);
	m_pLblShape=new QLabel(tr("Symbol:"),pParent);
	m_pCmbShape=new CXPointShapeBox(pParent);
	m_pLblSize=new QLabel(tr("Size:"),pParent);
	m_pCmbSize=new CXBaseComboBox(pParent);

	m_pCmbSize->addItem(tr("Small"));
	m_pCmbSize->addItem(tr("Medium"));
	m_pCmbSize->addItem(tr("Large"));

	pParentLayout->addWidget(m_pLblColor,nRowIndex,nColumnIndex);
	pParentLayout->addWidget(m_pBtnColor,nRowIndex,nColumnIndex+1);
	pParentLayout->addWidget(m_pLblSize,nRowIndex,nColumnIndex+2);
	pParentLayout->addWidget(m_pCmbSize,nRowIndex,nColumnIndex+3);
	pParentLayout->addWidget(m_pLblShape,nRowIndex,nColumnIndex+4);
	pParentLayout->addWidget(m_pCmbShape,nRowIndex,nColumnIndex+5);

}
void CX2DPointComponent::SetPointShape(const int& nShapeIndex)
{
	m_pCmbShape->SetMarkerSetIndex(nShapeIndex);
}
void CX2DPointComponent::SetPointShapeIndex(const int& nIndex)
{
	m_pCmbShape->setCurrentIndex(nIndex) ;
}
void CX2DPointComponent::SetPointSize(const int& nSize)
{
	m_pCmbSize->setCurrentIndex(nSize);
}
void CX2DPointComponent::SetPointColor(const int& nColorType,const QColor& eColor,const QColor& eObjColor)
{
	if(nColorType == 0)
	{
		m_pBtnColor->SetColor(eColor);
	}
	else if(nColorType == 1)
	{
	}
	else
	{
		m_pBtnColor->SetColor(QColor());
	}

	m_pBtnColor->SetButtonColor(1,eObjColor);
	m_pBtnColor->SetColorType(nColorType);
}
int CX2DPointComponent::GetPointShapeIndex() const
{
	return m_pCmbShape->currentIndex() ;
}

int CX2DPointComponent::GetPointShape() const
{
	return m_pCmbShape->GetMarkerSetIndex();
}

int     CX2DPointComponent::GetPointSize() const
{
	return m_pCmbSize->currentIndex() ;
}
QColor  CX2DPointComponent::GetPointColor() const
{
	return m_pBtnColor->GetColor();
}
void CX2DPointComponent::SetColorLabel(const QString& strColorLabel)
{
	m_pLblColor->setText(strColorLabel);
}
void CX2DPointComponent::SetEnabled(const bool& bEnabled)
{
	m_pLblColor->setEnabled(bEnabled);
	m_pBtnColor->setEnabled(bEnabled);
	m_pLblSize->setEnabled(bEnabled);
	m_pCmbSize->setEnabled(bEnabled);
	m_pLblShape->setEnabled(bEnabled);
	m_pCmbShape->setEnabled(bEnabled);
}
int CX2DPointComponent::GetPointColorType() const
{
	return m_pBtnColor->ColorType();
}
void CX2DPointComponent::SetHidden(const bool& bHidden)
{
	m_pLblColor->setHidden(bHidden);
	m_pBtnColor->setHidden(bHidden);
	m_pLblSize->setHidden(bHidden);
	m_pCmbSize->setHidden(bHidden);
	m_pLblShape->setHidden(bHidden);
	m_pCmbShape->setHidden(bHidden);
}