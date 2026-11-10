
// gmlinelistbox.cpp: implementation of the CGmLineListBox class.
//
//////////////////////////////////////////////////////////////////////

#include <QPainter>
#include <QStyle> 
#include <QFontDatabase>
#include <QFont>
#include <QBitmap>
#include <QMap>
#include <cassert>
#include <QRegExpValidator>
#include <vector>
#include <QKeyEvent>
#include "x2dpointcomponent.h" 
#include "xlinebox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=========================marker size box===========================
CXMarkerSizeBox::CXMarkerSizeBox(QWidget * parent)
				: CXBaseComboBox(parent)
{
	setMinimumWidth( 80 ) ;
	_initItems() ;
}

CXMarkerSizeBox::~CXMarkerSizeBox()
{
}

void CXMarkerSizeBox::_initItems() 
{	
	insertItem(0, "Small");
	insertItem(1, "Medium");
	insertItem(2, "Large");
}

// ===========================font================
CXFontComboBox::CXFontComboBox(QWidget * parent)
:QFontComboBox(parent)
{
}

CXFontComboBox::~CXFontComboBox()
{
}

void CXFontComboBox::SetCurrentText(const QString& text)
{
	int i = findText(text);
	if (i != -1)
	{
		setCurrentIndex(i);
	}
	else if (isEditable())
	{
		setEditText(text);
	}
	else
	{
		setItemText(currentIndex(), text);
	}
}

//============================FontSize================================
CXFontSizeBox::CXFontSizeBox(QWidget *parent,const QFont& ):CXBaseComboBox(parent)
{
   for(int i=1;i<=12;i++)
   {
	   addItem(QString::number(i));
   }
}

CXFontSizeBox::~CXFontSizeBox()
{
}

//===================================================================
CXAlignBox::CXAlignBox(QWidget *parent):CXBaseComboBox(parent)
{
	addItem(tr("Horizontal"));
	addItem(tr("Vertical"));
	setEditable(false);
}
CXAlignBox::~CXAlignBox()
{
}

//===================================================================
CXUnitBox::CXUnitBox(QWidget *parent,int nStyle):CXBaseComboBox(parent)
{
	m_nStyle=nStyle;
	if(0==m_nStyle)
	{
		addItem(tr("ms"));
		addItem(tr("s"));
	}
	else
	{
		addItem(tr("feet"));
		addItem(tr("meter"));
	}
	setEditable(false);
}
CXUnitBox::~CXUnitBox()
{
}

CXRatioBox::CXRatioBox(QWidget *pParent):CXBaseComboBox(pParent),m_Validator(this)
{
    setEditable(true);
    QStringList strList;
    strList << "1:500" << "1:1000" << "1:5000" << "1:10000" << "1:15000" << "1:20000" << "1:25000"  
        << "1:30000" << "1:50000" << "1:100000" << "1:200000" << "1:500000" << "1:1000000";
    addItems(strList);
    
    connect(this,SIGNAL(editTextChanged(const QString&)),this,SLOT(OnTextChanged(const QString&)));
    connect(this,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(OnValidText(const QString&)));
}

void CXRatioBox::OnValidText(const QString& strText)
{
    QString strCur=strText;
    QString strTmp=strCur;
    m_Validator.setRegExp(QRegExp("1:[1-9]([0-9])*"));
    int nPos=0;
    if(QValidator::Acceptable==m_Validator.validate(strTmp,nPos))
    {
        QStringList strList=strCur.split(":");
        if(strList.count()>1)
        {
            QString strValue=strList.at(1);
            strValue=strValue.trimmed();
            bool bOK=false;
            int nValue=strValue.toInt(&bOK);
            if(bOK)
            {
                emit KeyReturnSignal(nValue);
            }
            else
            {
                assert(0);
            }
        }
        else
        {
            assert(0);
        }
    }
    else
    {
        //if valid failed we reset focus
        setFocus();
    }
}

void CXRatioBox::OnTextChanged(const QString& strText)
{
    disconnect(this,SIGNAL(editTextChanged(const QString&)),this,SLOT(OnTextChanged(const QString&)));
    QString strCur=strText;
    m_Validator.setRegExp(QRegExp("1:[1-9]([0-9])*"));
    int nLen=strText.length();
    int nPos=0;
    if(QValidator::Acceptable!=m_Validator.validate(strCur,nPos))
    {
        m_Validator.setRegExp(QRegExp("1:?"));
        if(QValidator::Acceptable!=m_Validator.validate(strCur,nPos))
        {
            if(strCur!="")
            {
                SetCurrentText(strCur.mid(0,nLen-1));
            }
        }
    }
    connect(this,SIGNAL(editTextChanged(const QString&)),this,SLOT(OnTextChanged(const QString&)));
}
CXRatioBox::~CXRatioBox()
{
}
void CXRatioBox::SetScale(int nScale)
{
    if(nScale<=0)
    {
        return;
    }
    disconnect(this,SIGNAL(editTextChanged(const QString&)),this,SLOT(OnTextChanged(const QString&)));
    QString strCur;
    strCur.sprintf("1:%ld",nScale);
    SetCurrentText(strCur);
    connect(this,SIGNAL(editTextChanged(const QString&)),this,SLOT(OnTextChanged(const QString&)));
}

void CXRatioBox::focusOutEvent(QFocusEvent *)
{
    OnValidText(currentText());
}

void CXRatioBox::keyReleaseEvent(QKeyEvent * pEvent)
{
    CXBaseComboBox::keyReleaseEvent(pEvent);

    if(Qt::Key_Return==pEvent->key() || Qt::Key_Enter == pEvent->key())
    {
        OnValidText(currentText());
    }
}