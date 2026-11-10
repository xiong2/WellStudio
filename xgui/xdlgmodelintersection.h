#ifndef XDLGPROPERTYMODELINCISION_H
#define XDLGPROPERTYMODELINCISION_H

#include <QDialog>
namespace Ui {class CXDlgPropertyModelIncision;};

#include "xgui_global.h"

///@brief	a dialog to calculate incision of property model.
///@author	Pezy
///@date	3/12/2015
///@see	

class CXBaseParameter;
class CXObject;
class CXParameterModelIntersection;

class XGUI_EXPORT CXDlgModelIntersection : public QDialog
{
	Q_OBJECT

public:
	CXDlgModelIntersection(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = nullptr);
	~CXDlgModelIntersection();

	virtual void accept() override;

private:
	void Init();
	void InitData();

	Ui::CXDlgPropertyModelIncision *m_pUi;
	CXParameterModelIntersection *m_pPara;
	QList<CXObject*> m_listObj;
};

#endif // RLDLGPROPERTYMODELINCISION_H
