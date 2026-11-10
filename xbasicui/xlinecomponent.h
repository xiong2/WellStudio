#ifndef XLINECOMPONENT_H
#define XLINECOMPONENT_H

#include "xbasicui_global.h"
#include "xbasecombobox.h"

class QGridLayout ;
class CXColorButton ;
class QLabel ;

//==========================line width===========================
class XBASICUI_EXPORT CXLineWidthListCombBox : public CXBaseComboBox  
{
public:	
	CXLineWidthListCombBox ( QWidget * parent = 0);
	virtual ~CXLineWidthListCombBox();

	int GetLineWidth();
	void SetLineWidth(int nLineWidth);
private:
	QPixmap _Pixmap(int nWidth);
	QIcon _Icon(int nWidth);
private:
	QSize m_pIconSize;
};

//=============================line type==============================
class XBASICUI_EXPORT CXLineTypeListCombBox : public CXBaseComboBox  
{
public:	
	CXLineTypeListCombBox ( QWidget * parent = 0);
	virtual ~CXLineTypeListCombBox();

	Qt::PenStyle GetLineType();
	void SetLineType(Qt::PenStyle eLineStyle);
private:
	QPixmap _Pixmap(Qt::PenStyle ePenStyle);
	QIcon _Icon(Qt::PenStyle ePenStyle);
private:
	QSize m_pIconSize;
};

class XBASICUI_EXPORT CXLineComponent : public QObject
{
public:
	CXLineComponent(QWidget * pParent,
					 QGridLayout * pParentLayout,
					 int nRowIndex,
					 int nColumnIndex,
					 bool bObjectColorSupport=true,
					 bool bColormapSupport=false);
	CXLineComponent(QWidget * pParent,bool bObjectColorSupport=true,bool bColormapSupport=false);
	~CXLineComponent();

	int GetLineWidth() const;
	Qt::PenStyle GetLineType() const ;
	QColor GetLineColor() const ;
	int GetLineColorType() const ;

	void SetLineWidth(const int nLineWidth) ;
	void SetLineType(const Qt::PenStyle & eStyle) ;
	void SetLineColor(const int nColorType,const QColor & eColor,const QColor& eObjColor = QColor()) ;

	QWidget* GetComponentWidget() const {return m_pWidget;}
	CXColorButton * GetColorButton() const { return m_pBtnLineColor ; }

	void SetComponentEnabled(const bool& bEnabled);
	void SetHidden(const bool& bHidden) ;

	void SetColorLblName(const QString & strName) ;
	void SetWidthLblName(const QString & strName) ;
	void SetTypeLblName(const QString & strName) ;

private:
	void _initLayout(QWidget* pParent,
					 QGridLayout* pParentLayout,
					 int nRowIndex,
					 int nColumnIndex,
					 bool bObjectColorSupport,
					 bool bColormapSupport);
private:
	QWidget * m_pWidget ;

	QLabel				*				m_pLblLineColor ;
	QLabel				*				m_pLblLineWidth ;
	QLabel				*				m_pLblLineType ;
	CXColorButton		*				m_pBtnLineColor ;
	CXLineWidthListCombBox			*				m_pCmbLineWidth;
	CXLineTypeListCombBox			*				m_pCmbLineType;
};

#endif // KELINECOMPONENT_H