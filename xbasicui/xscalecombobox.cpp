#include "xscalecombobox.h"

CXScaleComboBox::CXScaleComboBox(QWidget *parent)
: CXBaseComboBox(parent)
, m_nDefaultItemCount(0)
{
	_InitComboBox() ;

	setMinimumWidth(60) ;
}

CXScaleComboBox::~CXScaleComboBox()
{

}

void CXScaleComboBox::_InitComboBox()
{
	QStringList strList ;
	strList.push_back("0.1") ;
	strList.push_back("0.2") ;
	strList.push_back("0.5") ;
	strList.push_back("1") ;
	strList.push_back("2") ;
	strList.push_back("3") ;
	strList.push_back("4") ;
	strList.push_back("5") ;
	strList.push_back("7.5") ;
	strList.push_back("10") ;
	strList.push_back("20") ;
	strList.push_back("50") ;
	strList.push_back("100") ;
	strList.push_back("200") ;
	strList.push_back("500") ;

	addItems(strList) ;

	_SetDefaultItemCount(strList.count()) ;
}

void CXScaleComboBox::ResetComboBoxContent(const QStringList & strList)
{
	clear() ;
	addItems(strList) ;
	_SetDefaultItemCount(strList.count()) ;
}

void CXScaleComboBox::SetText(const QString & text)
{
	int nIndex = findText(text) ;
	if(nIndex == -1)		// change the value of scale combobox according to other way (not change the index of combobox)
	{
		if(count() == m_nDefaultItemCount)		//no user defined item been inserted before
		{
			addItem(text) ;
		}
		else
		{
			setItemText(m_nDefaultItemCount, text) ;
		}
	}

	SetCurrentText(text) ;
}

void CXScaleComboBox::_SetDefaultItemCount(int nCount)
{
	m_nDefaultItemCount = nCount ;
}