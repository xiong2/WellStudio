#ifndef XFONTCOMPOENT_H
#define XFONTCOMPOENT_H

#include "xbasicui_global.h"
#include <QObject>
#include <QColor>

class CXButtonColorEdit;
class QGridLayout;
class QLabel;
class QWidget;
class CXBaseComboBox;
class QToolButton;
class CXFontComboBox;
class CXColorButton ;
/**
* @class CGmFontComponent gmfontcomponent.h
* @brief Widget components for font family, size, and color.
* 
* @author haidong 
* @date 2/28/2008
* @see 
*/
class XBASICUI_EXPORT CXFontComponent : public QObject
{
	Q_OBJECT
public:
	CXFontComponent(QWidget* pParent,QGridLayout* pParentLayout,int nRowIndex,int nColumnIndex=0,bool bObjectColorSupport=true);
	CXFontComponent(QWidget* pParent,bool bObjectColorSupport=true);
	~CXFontComponent(void);

	void SetFontName(const QString& strName);
	void SetFontSize(const int& nSize);
	void SetFontColor(const int& nColorType , const QColor& eColor , const QColor& eObjColor = QColor());
	void SetBold(const bool& bBold);
	void SetItalic(const bool& bItalic);

	QString GetFontName() const;
	int GetFontColorType() const ;
/**
* @brief OIV font name will be formated as 'fontname : style', style includes bold ,italic, or regular information. 
* @return 
* @date 2/28/2008
* @see 
*/
	QString GetOIVFontName() const;
	int     GetFontSize() const;
	QColor  GetFontColor() const;
	bool    IsBold() const;
	bool    IsItalic() const;

/**
* @brief Once user doesn't pass parent's GRID LAYOUT,that means the component must be a widget to be added somewhere else. 
* @return 
* @date 2/28/2008
* @see 
*/
	QWidget* GetWidget() const {return m_pWidget;};

	void SetColorLabel(const QString& strColorLabel);
/**
* @brief 
* @param color object color
* @param bSetCurrent whether set the ojbect color item as current selected color.
* @return 
* @date 2/29/2008
* @see 
*/
	void SetObjectColor(const QColor& color,const bool& bSetCurrent);

	void SetEnabled(const bool& bEnabled);
private:
	void _initLayout(QWidget* pParent,QGridLayout* pParentLayout,int nRowIndex,int nColumnIndex,bool bObjectColorSupport);
private:
	QWidget* m_pWidget;
	QLabel* m_pLblColor;
	QLabel* m_pLblSize;
	QLabel* m_pLblFont;
	CXColorButton* m_pBtnColor;
	CXFontComboBox* m_pCmbFont;
	CXBaseComboBox* m_pCmbSize;
	QToolButton* m_pTBtnBold;
	QToolButton* m_pTBtnItalic;

	
signals:
	//furture support
	void sizeChanged(const int&);
	void nameChanged(const QString&);
	void colorChanged(const QColor&);
	void boldItalicChanged(const bool&,const bool&);

};

#endif // KEFONTCOMPOENT_H
