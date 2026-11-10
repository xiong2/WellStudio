#include "xbuttoncoloredit.h"
#include <QStyle>
#include <QPainter>
#include <QColorDialog>
#include <QLayout>
#include <QGridLayout>
#include <QFrame>
#include <QMouseEvent>
#include <QEvent>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QEvent>
#include <QVBoxLayout>
#include "xglobal.h"

#define COLORBUTTON_WIDTH_HEIGHT 15

CXColorBlock::CXColorBlock(QWidget* parent) : QFrame(parent)
{
	setFrameStyle(QFrame::Panel | QFrame::Sunken);
	setFixedSize(COLORBUTTON_WIDTH_HEIGHT, COLORBUTTON_WIDTH_HEIGHT);
	setLineWidth(2);
	setAutoFillBackground(true);
}

CXColorBlock::~CXColorBlock()
{
}

void CXColorBlock::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() != Qt::LeftButton)
	{
		e->ignore();
		return;
	}

	if (rect().contains(e->pos()))
	{
		emit ColorSelected(palette().color(QPalette::Window));
	}
}

void CXColorBlock::enterEvent(QEvent *e)
{
	setLineWidth(1);
	setFrameStyle(QFrame::Panel | QFrame::Raised);
	QFrame::enterEvent(e);
}

void CXColorBlock::leaveEvent(QEvent *e)
{
	setFrameStyle(QFrame::Panel | QFrame::Sunken);
	setLineWidth(2);
	QFrame::leaveEvent(e);
}

CXColorPalette::CXColorPalette(QWidget* parent, Qt::WindowFlags f)
	: QFrame(parent, f)
{
	int r[48]={255,255,128,128,64,0,255,255,255,255,128,128,128,128,0,0,0,128,0,0,0,0,0,128,128,0,0,0,0,64,0,0,128,0,0,192,255,128,128,128,64,64,255,255,255,128,64,255};
	int g[48]={128,0,64,0,0,0,255,255,128,128,64,128,255,255,255,128,64,128,255,255,128,128,64,128,255,255,64,0,0,128,128,128,128,0,0,192,128,128,0,0,0,0,128,0,0,0,0,255};
	int b[48]={128,0,64,0,0,0,128,0,64,0,0,0,128,0,0,0,0,64,128,64,128,64,64,128,255,255,128,255,128,128,255,192,255,160,64,192,192,192,64,128,64,64,255,255,128,255,128,255};
	this->setFrameStyle(QFrame::Panel|QFrame::Raised);
	m_topLayout=new QVBoxLayout(this);
	m_topLayout->setMargin(3);
	QGridLayout *colorLayout=new QGridLayout(this);
	
	int i,j,k;
	int nRowMax = 8;
	int nColumMax = 6;
	for(i=0;i<nRowMax;i++)
	{
		for(j=0;j<nColumMax;j++)
		{
			CXColorBlock *pColorBlock=new CXColorBlock(this);
			k=((i<<2)+(i<<1))+j;
			QPalette p(pColorBlock->palette());
			p.setColor(QPalette::Window,QColor(r[k],g[k],b[k]));
			//pColorBlock->setPaletteBackgroundColor(QColor(r[k],g[k],b[k]));
			pColorBlock->setPalette(p);
			QObject::connect(pColorBlock,SIGNAL(ColorSelected(const QColor&)),this,SIGNAL(ColorSelected(const QColor&)));
			colorLayout->addWidget(pColorBlock,i+i+1,j+j+1);
		}
		//colorLayout->setRowSpacing(i+i+2,3);
	}
	m_topLayout->addLayout(colorLayout);
	QPushButton *otherButton=new QPushButton(GetTr("Others..."),this);
	m_topLayout->addWidget(otherButton);
	m_topLayout->activate();
	connect( otherButton, SIGNAL(clicked()), this,SIGNAL(OtherButtonClicked()));
	connect( otherButton, SIGNAL(clicked()), this,SLOT(close()));

	setAttribute(Qt::WA_DeleteOnClose) ;
	 
	setMaximumSize( nColumMax * COLORBUTTON_WIDTH_HEIGHT,(nRowMax + 6 )* COLORBUTTON_WIDTH_HEIGHT );
}

CXColorPalette::~CXColorPalette()
{
}

CXButtonColorEdit::CXButtonColorEdit(QWidget* parent, QColor c, const char* name)
	: QPushButton(parent), m_nColorType(0), m_pColorPalette(NULL)
{
	m_Color = c;
	setToolTip(name);
	setMinimumWidth(60);
	setAcceptDrops(true);
	connect(this, SIGNAL(clicked()), SLOT(onEditor()));
}

CXButtonColorEdit::~CXButtonColorEdit()
{
}

void CXButtonColorEdit::SetColor(const QColor& c)
{
	//Modified by Lingyun Dai
	if (m_Color == c)
	{
		SetColorType(SelectColor);
		return;
	}


	m_Color = c;
	SetColorType(SelectColor);
	update();
	emit ColorSelected(c);
	emit ColorTypeChanged(0);
}

const QColor& CXButtonColorEdit::GetColor() const
{
	return m_nColorType == 0 ? m_Color : m_lstBtnColors.at(m_nColorType - 1);
}
void CXButtonColorEdit::paintEvent(QPaintEvent *e)
{
	QPushButton::paintEvent(e);
	QPainter painter(this);
	drawButton(&painter);
}
void CXButtonColorEdit::drawButton(QPainter *paint)
{
#define ADDITIONAL_WIDTH 16
	QStyleOptionButton opt;
	opt.initFrom(this);
	opt.rect = rect();
	//   style().drawPrimitive(QStyle::PE_ButtonBevel, paint, rect(), colorGroup(), QStyle::State_Raised );
	//style()->drawPrimitive( QStyle::PE_FrameButtonBevel, &opt, paint);

	paint->setBrush(QBrush(m_Color));
	//	QRect	rect= style().subRect(QStyle::SR_PushButtonFocusRect, this);
	QRect	rect = style()->subElementRect(QStyle::SE_PushButtonFocusRect, &opt, this);
	if (ColorType() == 0)
	{
		rect.setWidth(rect.width() - ADDITIONAL_WIDTH);
		rect.setHeight(rect.height() - 6);
		rect.setX(rect.x() + 4);
		rect.setY(rect.y() + 4);
		paint->drawRect(rect);
	}
	else
	{
		style()->drawControl(QStyle::CE_PushButtonLabel, &opt, paint, this);
	}
	if (!isEnabled())
	{
		opt.state |= QStyle::State_None;
	}
	QRect sepRect(rect.right() + 4, rect.top(), 1, rect.height());
	if (sepRect.height() <= 1)
		sepRect.setHeight(2);
	//	style().drawPrimitive(QStyle::PE_Separator, paint, sepRect, colorGroup(), QStyle::State_Sunken);
	opt.rect = sepRect;
	opt.state |= QStyle::State_Sunken;
	style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, paint, this);

	int abi = 4;
	QRect arrowRect(rect.right() + abi, rect.y() + 2, 11, rect.height());
	if (arrowRect.height() <= 1)
		arrowRect.setHeight(2);
	opt.rect = arrowRect;
	//	style().drawPrimitive(QStyle::PE_ArrowDown, paint, arrowRect, colorGroup(), arrowFlag, 0);
	style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &opt, paint, this);
	//    if (hasFocus())style().drawPrimitive(QStyle::PE_FocusRect, paint, style().subRect(QStyle::SR_PushButtonFocusRect, this),colorGroup(), QStyle::State_None);
	if (rect.height() <= 1)
		rect.setHeight(2);
	opt.rect = rect;
	if (hasFocus())style()->drawPrimitive(QStyle::PE_FrameFocusRect, &opt, paint, this);
}

void CXButtonColorEdit::onEditor()
{
	if (!m_pColorPalette)
	{
		m_pColorPalette = new CXColorPalette(this);
		_InitColorPalette(m_pColorPalette);
		QObject::connect(m_pColorPalette, SIGNAL(ColorSelected(const QColor&)), this, SLOT(SetColor(const QColor&)));
		QObject::connect(m_pColorPalette, SIGNAL(ColorSelected(const QColor&)), m_pColorPalette, SLOT(close()));
		QObject::connect(m_pColorPalette, SIGNAL(OtherButtonClicked()), this, SLOT(OnOtherButtonClicked()));
	}
	int y;
	QPoint pos(0, 0);
	QWidget* m_parent = this->parentWidget();

	if ((m_pColorPalette->height() < m_parent->height()) && (this->y() + this->height() + m_pColorPalette->height() > m_parent->height()))
		y = this->y() - m_pColorPalette->height();
	else
		y = this->y() + this->height();

	if (y < 0)y = this->y() + this->height();
	pos = m_parent->mapToGlobal(QPoint(this->x(), y));
	m_pColorPalette->move(pos);
	m_pColorPalette->show();
	m_pColorPalette->raise();
}
void CXButtonColorEdit::OnOtherButtonClicked()
{
	QColor c = QColorDialog::getColor(m_Color, this);
	if (c.isValid())
	{
		SetColor(c);
	}
}


int CXButtonColorEdit::ColorType()
{
	return m_nColorType;
}

void CXButtonColorEdit::SetColorType(int nColorType)
{
	m_nColorType = nColorType;
	if (nColorType == 0)
	{
		setText("");
		setIcon(QIcon());
	}
	else
	{
		setText(m_lstBtnTexts.at(nColorType - 1));
		QColor c = m_lstBtnColors.at(nColorType - 1);
		setIcon(_buildIcon(c));
	}
}

void CXButtonColorEdit::SetColor(int nColorType, const QColor& c)
{
	if (c.isValid())
	{
		this->m_Color = c;
		emit ColorSelected(c);

	}
	SetColorType(nColorType);
	update();
}

void CXButtonColorEdit::_InitColorPalette(CXColorPalette* pColorPalette)
{
	int nColorPaletteWidth = pColorPalette->width();
	int nColorPaletteHeight = pColorPalette->height();
	for (int i = 0; i < m_lstBtnTexts.size(); ++i)
	{
		QPushButton* pSpecialButton = new QPushButton(m_lstBtnTexts.at(i), pColorPalette);
		if (m_lstBtnColors.at(i).isValid())
		{
			pSpecialButton->setIcon(_buildIcon(m_lstBtnColors.at(i)));
		}
		QObject::connect(pSpecialButton, SIGNAL(clicked()), this, SLOT(OnSpecialButtonClicked()));
		pColorPalette->GetTopLayout()->addWidget(pSpecialButton);
		nColorPaletteHeight += pSpecialButton->height();
	}
	pColorPalette->resize(nColorPaletteWidth, nColorPaletteHeight);
}
bool CXButtonColorEdit::AddButton(const QString& strName, const QColor& color)
{
	if (!m_lstBtnTexts.contains(strName))
	{
		m_lstBtnTexts << strName;
		m_lstBtnColors.append(color);
		return true;
	}
	return false;
}
void CXButtonColorEdit::ReplaceButtonColor(const QString& strName, const QColor& color)
{
	int nIndex = m_lstBtnTexts.indexOf(strName);
	if (nIndex >= 0)
	{
		m_lstBtnColors.replace(nIndex, color);
	}
	if (strName == this->text())
	{
		setIcon(this->_buildIcon(color));
	}
}
void CXButtonColorEdit::AddObjectColorButton(const QColor & objColor)
{
	AddButton("Object color", objColor);
}

void CXButtonColorEdit::AddColormapButton()
{
	AddButton("Color map", QColor::Invalid);
}

bool CXButtonColorEdit::IsObjectColor()
{
	return m_nColorType == 1;
}

void CXButtonColorEdit::SetButtonColor(const QString& strName, const QColor& color)
{
	int nIndex = m_lstBtnTexts.indexOf(strName);
	if (nIndex >= 0)
	{
		SetButtonColor(nIndex + 1, color);
	}
	else
	{
		SetColor(color);
	}
}
void CXButtonColorEdit::SetButtonColor(int nColorType, const QColor& color)
{
	int nSize = m_lstBtnColors.size();
	if (nColorType<0 || nColorType>nSize)return;

	if (nColorType > 0)
	{
		if (2 != nColorType)//if is color map ,we should color is invalid
		{
			m_lstBtnColors.replace(nColorType - 1, color);
		}
		SetColorType(nColorType);
	}
	else
	{
		SetColor(color);
	}
}

void CXButtonColorEdit::GetButtonColor(int &nColorType, QColor& color)
{
	nColorType = m_nColorType;
	if (nColorType > 0)
	{
		color = m_lstBtnColors.at(nColorType - 1);
	}
	else
	{
		color = m_Color;
	}
}
QColor CXButtonColorEdit::GetButtonColor(const QString& strName)
{
	int nIndex = m_lstBtnTexts.indexOf(strName);
	if (nIndex >= 0)
	{
		return m_lstBtnColors.at(nIndex);
	}
	return m_Color;
}

void CXButtonColorEdit::OnSpecialButtonClicked()
{
	if (sender() != NULL)
	{
		QPushButton* pSpecialButton = qobject_cast<QPushButton*>(sender());
		if (pSpecialButton != NULL)
		{
			int nOldColorType = ColorType();
			int nIndex = m_lstBtnTexts.indexOf(pSpecialButton->text());
			m_Color = m_lstBtnColors.at(nIndex);
			SetColorType(nIndex + 1);
			if (nOldColorType != ColorType())
			{
				emit ColorSelected(m_Color);
				emit ColorTypeChanged(nIndex + 1);
			}
			if (m_pColorPalette)m_pColorPalette->close();
		}
	}
}

void CXButtonColorEdit::slotObjectColorChanged(const QColor& color)
{
	ReplaceButtonColor("Object color", color);
}

QIcon CXButtonColorEdit::_buildIcon(const QColor& c)
{
	if (!c.isValid())return QIcon();
	QPixmap tmpPixmap(10, 10);
	tmpPixmap.fill(c);
	return QIcon(tmpPixmap);
}
