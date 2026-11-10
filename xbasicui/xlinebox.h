// gmlinelistbox.h: interface for the CGmLineListBox class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _CGmLineBox_H_
#define _CGmLineBox_H_

#include "xbasicui_global.h"
#include <QFontComboBox>
#include "xbasecombobox.h"
#define DEFAULT_FONTNAME "Arial"

class QIcon;
class QFont;

class XBASICUI_EXPORT CXMarkerSizeBox : public CXBaseComboBox
{
public:
	/**
	* @ setting marker size to three types: "Small", "Medium", "Large" 
	*/
	CXMarkerSizeBox(QWidget * parent = 0);
	virtual ~CXMarkerSizeBox();

private:
	void _initItems() ;
};

class CXFontComboBox : public QFontComboBox
{
public:
	CXFontComboBox(QWidget *parent = 0);
	~CXFontComboBox();

	void SetCurrentText(const QString& text) ;
};

class XBASICUI_EXPORT CXFontSizeBox : public CXBaseComboBox
{
public:
	CXFontSizeBox(QWidget *parent=0,const QFont& font=QFont(DEFAULT_FONTNAME));
	~CXFontSizeBox();
};

class XBASICUI_EXPORT CXAlignBox : public CXBaseComboBox
{
public :
	CXAlignBox(QWidget *parent=0);
	~CXAlignBox();
};

class XBASICUI_EXPORT CXUnitBox : public CXBaseComboBox
{
public :
	CXUnitBox(QWidget *parent=0,int nStyle=0);
	~CXUnitBox();
protected:
	int m_nStyle;
};

/**
* @class CGmRatioBox gmlinebox.h
* @brief ratio box for basemap window to set scale
* 
* @author fangqiang 
* @date 4/29/2009
* @see 
*/
class XBASICUI_EXPORT CXRatioBox : public CXBaseComboBox
{
    Q_OBJECT
public: 
    CXRatioBox(QWidget *pParent=NULL);
    ~CXRatioBox();
/**
* @brief set scale
* @param nScale ,scale
* @return 
* @date 4/29/2009
* @see 
*/
    void SetScale(int nScale);
protected:
    void focusOutEvent(QFocusEvent *pEvent);
    void keyReleaseEvent(QKeyEvent * pEvent);
    QRegExpValidator m_Validator;
protected slots:
    void OnTextChanged(const QString& strText);
    void OnValidText(const QString& strText);
signals:
    //event when release return or enter key
    void KeyReturnSignal(int nScale);
};
#endif 





















