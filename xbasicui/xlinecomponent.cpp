#include <QPainter>
#include <QPen>
#include <QStringList>
#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QRect>
#include <QCheckBox>
#include <QGridLayout>
#include "xbuttoncoloredit.h"
#include "xcolorbutton.h"
#include "xlinebox.h"
#include "xlinecomponent.h"

//===========================line width==================================
CXLineWidthListCombBox::CXLineWidthListCombBox(QWidget *parent)
:CXBaseComboBox(parent)
,m_pIconSize(40,15)
{
	setIconSize(m_pIconSize);
	for(int i=1;i<11;i++)
	{
		addItem(_Icon(i),QString::number(i));
	}

	addItem(_Icon(11),QString::number(20)) ;
	addItem(_Icon(12),QString::number(30)) ;
	addItem(_Icon(12),QString::number(40)) ;
	addItem(_Icon(12),QString::number(50)) ;

	setMinimumWidth(minimumWidth()) ;
}
CXLineWidthListCombBox::~CXLineWidthListCombBox()
{
}
QPixmap CXLineWidthListCombBox::_Pixmap(int nWidth)
{
	QRect nRect(QPoint(0,0),m_pIconSize);
	QPixmap Pixmap(m_pIconSize);
	Pixmap.fill();
	QPainter Painter(&Pixmap);

	Painter.setPen(QPen(Qt::black,nWidth,Qt::SolidLine));
	Painter.drawLine(0,
					 nRect.center().y(),
					 nRect.width(),
					 nRect.center().y());

	return Pixmap;
}
QIcon CXLineWidthListCombBox::_Icon(int nWidth)
{
	return QIcon(_Pixmap(nWidth));
}
int CXLineWidthListCombBox::GetLineWidth()
{
	return currentText().toInt();
}
void CXLineWidthListCombBox::SetLineWidth(int nLineWidth)
{
	int nWidth ;;
	if(nLineWidth<0)
		nWidth = -nLineWidth;
	else if(nLineWidth == 0)
		nWidth = 1;
	else
		nWidth = nLineWidth ;

	SetCurrentText(QString::number(nWidth));
}
//============================line type====================================
CXLineTypeListCombBox::CXLineTypeListCombBox(QWidget *parent)
:CXBaseComboBox(parent)
,m_pIconSize(40,3)
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
CXLineTypeListCombBox::~CXLineTypeListCombBox()
{
}
QPixmap CXLineTypeListCombBox::_Pixmap(Qt::PenStyle ePenStyle)
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
QIcon CXLineTypeListCombBox::_Icon(Qt::PenStyle ePenStyle)
{
	return QIcon(_Pixmap(ePenStyle));
}
Qt::PenStyle CXLineTypeListCombBox::GetLineType()
{
	return (Qt::PenStyle)(currentIndex()+1);
}
void CXLineTypeListCombBox::SetLineType(Qt::PenStyle eLineType)
{
	setCurrentIndex((int)eLineType-1);
}
//==================================================Line Component=================================================
CXLineComponent::CXLineComponent(QWidget* pParent,
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
CXLineComponent::CXLineComponent(QWidget* pParent,bool bObjectColorSupport,bool bColormapSupport)
{
	setParent(pParent);
	m_pWidget=new QWidget(pParent);
	QGridLayout* pOwnLayout=new QGridLayout(m_pWidget);
	m_pWidget->setLayout(pOwnLayout);
	_initLayout(m_pWidget,pOwnLayout,0,0,bObjectColorSupport,bColormapSupport);
}

CXLineComponent::~CXLineComponent()
{
}
void CXLineComponent::_initLayout(QWidget* pParent,
								   QGridLayout* pParentLayout,
								   int nRowIndex,
								   int nColumnIndex,
								   bool bObjectColorSupport,
								   bool bColormapSupport)
{
	int nNumButton = 0 ;
	if(bObjectColorSupport)
	{
		nNumButton = 2 ;
		if(bColormapSupport)
			nNumButton = 3 ;
	}

	m_pLblLineColor	= new QLabel(tr("Color:"),pParent);
	m_pBtnLineColor	= new CXColorButton(pParent,nNumButton);
	m_pBtnLineColor->setMinimumWidth(80) ;
	m_pLblLineWidth	= new QLabel(tr("Size:"),pParent);
	m_pCmbLineWidth	= new CXLineWidthListCombBox(pParent);
	m_pCmbLineWidth->setMinimumWidth(85) ;
	m_pLblLineType	= new QLabel(tr("Style:"),pParent);
	m_pCmbLineType	= new CXLineTypeListCombBox(pParent);

	pParentLayout->addWidget(m_pLblLineColor,nRowIndex,nColumnIndex);
	pParentLayout->addWidget(m_pBtnLineColor,nRowIndex,nColumnIndex+1);
	pParentLayout->addWidget(m_pLblLineWidth,nRowIndex,nColumnIndex+2);
	pParentLayout->addWidget(m_pCmbLineWidth,nRowIndex,nColumnIndex+3);
	pParentLayout->addWidget(m_pLblLineType,nRowIndex,nColumnIndex+4);
	pParentLayout->addWidget(m_pCmbLineType,nRowIndex,nColumnIndex+5);

	pParentLayout->setColumnStretch(nColumnIndex+5,2) ;
}
int CXLineComponent::GetLineWidth() const
{
	return m_pCmbLineWidth->GetLineWidth() ;
}
Qt::PenStyle CXLineComponent::GetLineType() const
{
	return m_pCmbLineType->GetLineType() ;
}
QColor CXLineComponent::GetLineColor() const
{
	return m_pBtnLineColor->GetColor() ;
}
int CXLineComponent::GetLineColorType() const
{
	return m_pBtnLineColor->ColorType() ;
}
void CXLineComponent::SetLineWidth(const int nLineWidth)
{
	m_pCmbLineWidth->SetLineWidth(nLineWidth) ;
}
void CXLineComponent::SetLineType(const Qt::PenStyle & eStyle)
{
	m_pCmbLineType->SetLineType(eStyle) ;
}
void CXLineComponent::SetLineColor(const int nColorType,const QColor & eColor,const QColor& eObjColor)
{
	if(nColorType == 0)
	{
		m_pBtnLineColor->SetColor(eColor);
	}
	else if(nColorType == 1)
	{
	}
	else
	{
		m_pBtnLineColor->SetColor(QColor());
	}

	m_pBtnLineColor->SetButtonColor(1,eObjColor);
	m_pBtnLineColor->SetColorType(nColorType);
}
void CXLineComponent::SetComponentEnabled(const bool& bEnabled)
{
	m_pCmbLineWidth->setEnabled(bEnabled) ;
	m_pCmbLineType->setEnabled(bEnabled) ;
	m_pBtnLineColor->setEnabled(bEnabled) ;
}
void CXLineComponent::SetHidden(const bool& bHidden)
{
	m_pCmbLineWidth->setHidden(bHidden) ;
	m_pCmbLineType->setHidden(bHidden) ;
	m_pBtnLineColor->setHidden(bHidden) ;
	m_pLblLineColor->setHidden(bHidden) ;
	m_pLblLineWidth->setHidden(bHidden) ;
	m_pLblLineType->setHidden(bHidden) ;
}
void CXLineComponent::SetColorLblName(const QString & strName)
{
	m_pLblLineColor->setText(strName) ;
}
void CXLineComponent::SetWidthLblName(const QString & strName)
{
	m_pLblLineWidth->setText(strName) ;
}
void CXLineComponent::SetTypeLblName(const QString & strName)
{
	m_pLblLineType->setText(strName) ;
}