#ifndef CX2DPOINTCOMPONENT_H
#define CX2DPOINTCOMPONENT_H

#include "xbasicui_global.h"
#include "xbasecombobox.h"

class CXButtonColorEdit;
class QGridLayout;
class QLabel;
class CXColorButton ;

class XBASICUI_EXPORT CXPointShapeBox : public CXBaseComboBox
{
public:
	CXPointShapeBox(QWidget * parent = 0);
	virtual ~CXPointShapeBox();

	/**
	* @brief Get a SoMarkerSet index by current selected point shape
	* @author: Haidong Wang
	* @date:2007-8-30
	*/
	int GetMarkerSetIndex() const;
	/**
	* @brief Set current point shape by a SoMarkerSet index
	* @author: Haidong Wang
	* @date:2007-8-30
	*/
	void SetMarkerSetIndex(const int& nIndex);
};

/**
 * @class CGmOIVMarkerShapeBox gm2dpointcomponent.h
 * @brief combobox for Open Inventor marker set shape
 * @author junhui
 * @date 10/15/2009
 * @see CGmBaseComboBox
 */
class XBASICUI_EXPORT CXOIVMarkerShapeComboBox : public CXBaseComboBox
{
public:
	/**
	 * @brief Constructor
	 * @param [in] parent parent widget
	 */
	CXOIVMarkerShapeComboBox(QWidget* parent);
	/**
	 * @brief Get marker type index
	 * @return marker type index
	 */
	int GetMarkerType() const;
	/**
	 * @brief Set marker type index
	 * @param [in] nType marker type index
	 */
	void SetMarkerType(int nType);
private:
	// set up Ui
	void _SetupUi();
	// set up map between marker type and user interface
	void _setupData();
	// marker type to ui
	std::map<int, int> m_markerToUiMap;
	// ui to marker type
	std::map<int, int> m_uiToMarkerMap;
};

/**
* @class CGm2DPointComponent gm2dpointcomponent.h
* @brief 2d point style component
* 
* @author haidong 
* @date 3/5/2008
* @see 
*/
class XBASICUI_EXPORT CX2DPointComponent : public QObject
{
	Q_OBJECT
public:
	CX2DPointComponent(QWidget* pParent,
						QGridLayout* pParentLayout,
						int nRowIndex,
						int nColumnIndex=0,
						bool bObjectColorSupport=true,
						bool bColormapSupport=false);
	CX2DPointComponent(QWidget* pParent,bool bObjectColorSupport=true,bool bColormapSupport=false);
	~CX2DPointComponent(void);

	void SetPointShape(const int& nShapeIndex);
	void SetPointShapeIndex(const int& nIndex) ;
	void SetPointSize(const int& nSize);
	void SetPointColor(const int& nColorType,const QColor& eColor,const QColor& eObjColor = QColor());

	int GetPointShape() const;
	int GetPointShapeIndex() const ;
	int     GetPointSize() const;
	QColor  GetPointColor() const;
	int     GetPointColorType() const;

/**
* @brief Once user doesn't pass parent's GRID LAYOUT,that means the component must be a widget to be added somewhere else. 
* @return 
* @date 3/5/2008
* @see 
*/
	QWidget* GetWidget() const {return m_pWidget;};

	void SetColorLabel(const QString& strColorLabel);

	void SetEnabled(const bool& bEnabled);
	void SetHidden(const bool& bHidden) ;
	CXColorButton* GetColorButtom ()
	{
		return m_pBtnColor;
	}
	CXPointShapeBox* GetShapeBox()
	{
		return m_pCmbShape;
	}
	CXBaseComboBox* GetSizeBox()
	{
		return m_pCmbSize;
	}
private:
	void _initLayout(QWidget* pParent,
					 QGridLayout* pParentLayout,
					 int nRowIndex,
					 int nColumnIndex,
					 bool bObjectColorSupport,
					 bool bColormapSupport);
private:
	QWidget* m_pWidget;
	QLabel* m_pLblColor;
	QLabel* m_pLblSize;
	QLabel* m_pLblShape;
	CXColorButton* m_pBtnColor;
	CXPointShapeBox* m_pCmbShape;
	CXBaseComboBox* m_pCmbSize;
	
signals:
	//furture support
	void sizeChanged(const int&);
	void nameChanged(const QString&);
	void colorChanged(const QColor&);
};

#endif // CRL2DPOINTCOMPONENT_H