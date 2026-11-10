#include "xcolorbutton.h"
#include <QPainter>
#include <QPushButton>

CXColorButton::CXColorButton(QWidget *parent,int nNumOfButton,int minWidth)
	: CXButtonColorEdit(parent)
{
    this->setMinimumSize(QSize(minWidth, 20));
	
	if(nNumOfButton>1)
		AddButton("Object color",QColor(255,255,255));
	if(nNumOfButton>2)
		AddButton("Color map",QColor(-1,-1,-1));
	
	SetColorType((nNumOfButton>2?2:(nNumOfButton>1?1:0)));
}

void CXColorButton::SetButtonNum(int nButtonNum)
{
	if(nButtonNum<=0 || nButtonNum>5)
	{
		return;
	}
	int nCurButtonNum=m_lstBtnTexts.size();
	if(nCurButtonNum !=  nButtonNum )
	{
		m_lstBtnTexts.clear();
		m_lstBtnColors.clear();
		
		QString strButtonName[]={"Object color","Color map","Discrete contour fill","Bitmap"};
		QColor Color[]={QColor(255,255,255),QColor(-1,-1,-1),QColor(-1,-1,-1),QColor(-1,-1,-1)};
		for(int j =0;j<nButtonNum;++j)
		{
			AddButton(strButtonName[j],Color[j]);
		}
	}


	/*int i=0;
	int nCurButtonNum=m_lstBtnTexts.size();
	int nRemoveButton=nCurButtonNum-nButtonNum+1;
	for(;i<nRemoveButton;++i)
	{
		m_lstBtnTexts.removeLast();
		m_lstBtnColors.removeLast();
	}
	int nAddButton=-nRemoveButton;
	QString strButtonName[]={"Object color","Color map","Discrete contour fill","Customized color","Texture"};
	QColor Color[]={QColor(255,255,255),QColor(-1,-1,-1),QColor(-1,-1,-1),QColor(255,255,255),QColor(-1,-1,-1)};
	i=nCurButtonNum-1;
	for(;i<nAddButton;++i)
	{
		AddButton(strButtonName[nCurButtonNum],Color[nCurButtonNum]);
	}*/
}
CXColorButton::~CXColorButton()
{

}
void CXColorButton::SetObjectColor(const QColor& c)
{
	SetButtonColor(1,c);
}
void CXColorButton::SetObjectColorBuddyWidget(CXButtonColorEdit* pColorEdit)
{
	connect(pColorEdit,SIGNAL(ColorSelected(const QColor&)),this,SLOT(slotReplaceObjectColor(const QColor&)),Qt::UniqueConnection);
}
void CXColorButton::slotReplaceObjectColor(const QColor& c)
{
	this->ReplaceButtonColor("Object color",c);
}
