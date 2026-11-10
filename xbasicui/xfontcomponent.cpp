#include <QLabel>
#include <QToolButton>
#include <QGridLayout>
#include "xbasecombobox.h"
#include "xcolorbutton.h"
#include "xfontcomponent.h"
#include "xbuttoncoloredit.h"
#include "xlinebox.h"

CXFontComponent::CXFontComponent(QWidget* pParent,QGridLayout* pParentLayout,int nRowIndex,int nColumnIndex,bool bObjectColorSupport)
{
	m_pWidget=NULL;
	setParent(pParent);
	_initLayout(pParent,pParentLayout,nRowIndex,nColumnIndex,bObjectColorSupport);
}
CXFontComponent::CXFontComponent(QWidget* pParent,bool bObjectColorSupport)
{
	setParent(pParent);
	m_pWidget=new QWidget(pParent);
	QGridLayout* pOwnLayout=new QGridLayout(m_pWidget);
	_initLayout(m_pWidget,pOwnLayout,0,0,bObjectColorSupport);
	m_pWidget->setLayout(pOwnLayout);
}
CXFontComponent::~CXFontComponent(void)
{
}
void CXFontComponent::_initLayout(QWidget* pParent,QGridLayout* pParentLayout,int nRowIndex,int nColumnIndex,bool bObjectColorSupport)
{
	int nNumSupport = 0 ;
	if(bObjectColorSupport)
		nNumSupport = 2 ;
	m_pLblColor=new QLabel(tr("Color:"),pParent);
	m_pBtnColor=new CXColorButton(pParent,nNumSupport);
	m_pLblFont=new QLabel(tr("Font:"),pParent);
	m_pCmbFont=new CXFontComboBox(pParent);
	m_pLblSize=new QLabel(tr("Size:"),pParent);
	m_pCmbSize=new CXBaseComboBox(pParent);
	for(int i=1;i<=10;i++)
	{
		m_pCmbSize->addItem(QString::number(i));
	}
	m_pTBtnBold=new QToolButton(pParent);
	m_pTBtnBold->setCheckable(true);
	m_pTBtnBold->setText(tr("B"));
	QFont font(tr(DEFAULT_FONTNAME),8);
	font.setBold(true);
	m_pTBtnBold->setFont(font);
	m_pTBtnItalic=new QToolButton(pParent);
	m_pTBtnItalic->setCheckable(true);
	m_pTBtnItalic->setText(tr("I"));
	font.setItalic(true);
	m_pTBtnItalic->setFont(font);
	if(bObjectColorSupport)
	{
		m_pBtnColor->AddButton("Object color",Qt::black);
	}

	pParentLayout->addWidget(m_pLblColor,nRowIndex,nColumnIndex);
	pParentLayout->addWidget(m_pBtnColor,nRowIndex,nColumnIndex+1);
	pParentLayout->addWidget(m_pLblSize,nRowIndex,nColumnIndex+2);
	pParentLayout->addWidget(m_pCmbSize,nRowIndex,nColumnIndex+3);
	pParentLayout->addWidget(m_pLblFont,nRowIndex,nColumnIndex+4);
	pParentLayout->addWidget(m_pCmbFont,nRowIndex,nColumnIndex+5);

	//QHBoxLayout* pLayout=new QHBoxLayout(pParent);
	//pLayout->addWidget(m_pTBtnBold);
	//pLayout->addWidget(m_pTBtnItalic);
	//pLayout->addStretch(10);

	//pParentLayout->addLayout(pLayout,nRowIndex,nColumnIndex+6);
	pParentLayout->addWidget(m_pTBtnBold, nRowIndex, nColumnIndex+6);
	pParentLayout->addWidget(m_pTBtnItalic, nRowIndex, nColumnIndex+7);
}
void CXFontComponent::SetFontName(const QString& strName)
{
	m_pCmbFont->setCurrentFont(QFont(strName));
}
void CXFontComponent::SetFontSize(const int& nSize)
{
	m_pCmbSize->SetCurrentText(QString::number(nSize));
}
void CXFontComponent::SetFontColor(const int& nColorType , const QColor& eColor , const QColor& eObjColor)
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
void CXFontComponent::SetBold(const bool& bBold)
{
	m_pTBtnBold->setChecked(bBold);
}
void CXFontComponent::SetItalic(const bool& bItalic)
{
	m_pTBtnItalic->setChecked(bItalic);
}

QString CXFontComponent::GetFontName() const
{
	return m_pCmbFont->currentText();
}
QString CXFontComponent::GetOIVFontName() const
{
	QString strStyle("");
	if(IsBold())
		strStyle+="Bold ";
	if(IsItalic())
		strStyle+="Italic";
	if(strStyle=="")strStyle="Regular";

	return m_pCmbFont->currentText()+" : "+strStyle.trimmed();
}
int     CXFontComponent::GetFontSize() const
{
	return m_pCmbSize->currentText().toInt();
}
QColor  CXFontComponent::GetFontColor() const
{
	return m_pBtnColor->GetColor();
}
int CXFontComponent::GetFontColorType() const
{
	return m_pBtnColor->ColorType() ;
}
bool    CXFontComponent::IsBold() const
{
	return m_pTBtnBold->isChecked();
}
bool    CXFontComponent::IsItalic() const
{
	return m_pTBtnItalic->isChecked();
}
void CXFontComponent::SetColorLabel(const QString& strColorLabel)
{
	m_pLblColor->setText(strColorLabel);
}
void CXFontComponent::SetObjectColor(const QColor& c,const bool& bSetCurrent)
{
	m_pBtnColor->SetButtonColor(1,c);

	if(bSetCurrent)
	{
		m_pBtnColor->SetColor(c);
		m_pBtnColor->SetColorType(1);
	}
}
void CXFontComponent::SetEnabled(const bool& bEnabled)
{
	m_pLblColor->setEnabled(bEnabled);
	m_pBtnColor->setEnabled(bEnabled);
	m_pLblSize->setEnabled(bEnabled);
	m_pCmbSize->setEnabled(bEnabled);
	m_pLblFont->setEnabled(bEnabled);
	m_pCmbFont->setEnabled(bEnabled);
	m_pTBtnBold->setEnabled(bEnabled);
	m_pTBtnItalic->setEnabled(bEnabled);
}
