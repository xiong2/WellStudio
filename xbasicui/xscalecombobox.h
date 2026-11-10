#ifndef GMSCALECOMBOBOX_H
#define GMSCALECOMBOBOX_H

#include "xbasicui_global.h"
#include "xbasecombobox.h"

/**
* @class CGmScaleComboBox gmscalecombobox.h
* @brief this class is for scale combobox
* 
* @author weifengliu 
* @date 2010/3/12
* @see 
*/
class XBASICUI_EXPORT CXScaleComboBox : public CXBaseComboBox
{
public:
	/**
	* @brief constructor of class CGmBaseComboBox
	* @param parent  parent widget
	* @return 
	* @date 2010/3/12
	* @see 
	*/
	CXScaleComboBox(QWidget *parent = NULL);
	~CXScaleComboBox();

	/**
	* @brief set text of combobox
	* @param & text text will be set
	* @return 
	* @date 2010/3/12
	* @see 
	*/
	void SetText(const QString & text) ;

	/**
	* @brief reset combobox content
	* @param & strList new contents
	* @return 
	* @date 2010/3/12
	* @see 
	*/
	void ResetComboBoxContent(const QStringList & strList) ;

private:
	// init combobox
	void _InitComboBox() ;

	/*
	* @brief set combobox default item count
	* @param nCount default item count
	* @return 
	* @date 2010/3/12
	* @see 
	*/
	void _SetDefaultItemCount(int nCount) ;

private:
	int m_nDefaultItemCount ;		// default item count of combobox
};

#endif // GMSCALECOMBOBOX_H
