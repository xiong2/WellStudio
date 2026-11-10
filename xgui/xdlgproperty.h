#ifndef XDIALOGPROPERTIES_H
#define XDIALOGPROPERTIES_H

#include <QDialog>
#include <QUuid>
#include <QHash>

#include "xgui_global.h"
#include "ui_xdialogproperties.h"
#include "xview.h"

class QAbstractButton;
class CXObject;
class CXWindow;
class CXBasePropertyPage;
class CXDlgProperty;
class CXViewInfoSeismicDV;
class CXWindow;

/*!
 * @class	CXPropertyDialogFactory provided in the file "kedialogproperties.h"
 * @brief	Property dialog manager.
 * @author	pezy
 * @date	2016-09-19
 * @see
 */

class XGUI_EXPORT CXPropertyDialogFactory
{
public:
	static CXPropertyDialogFactory& Instance()
	{
		static CXPropertyDialogFactory instance;
		return instance;
	}

	CXDlgProperty* CreatePropertyDialog(CXObject* pObj);
	void ClosePropertyDialog(CXObject* pObj);

	CXPropertyDialogFactory(const CXPropertyDialogFactory&) = delete;
	CXPropertyDialogFactory& operator=(const CXPropertyDialogFactory&) = delete;
private:
	CXPropertyDialogFactory() {}

	QHash<QUuid, CXDlgProperty*> m_hashDialog;
};

/*!
* @class	CXDlgProperty provided in the file "kedialogproperties.h"
* @brief	Define a base dialog for object properties.
* @author	pezy
* @date		2017-01-10
* @see
*/

class XGUI_EXPORT CXDlgProperty :public QDialog, public IKEView
{
	Q_OBJECT
public:
	CXDlgProperty(QWidget *parent, CXObject *pObject, CXWindow* pWindow);
	~CXDlgProperty();

    void ShowColormapPage();

	void UpdateView(const CXEventParameter& eventPara) override;

protected:
	virtual void accept();

public slots:
	void slotButtonClicked(QAbstractButton*);
	void slotApply2All();
	void slotTabChanged(int);

	void slotApply();

private:
	void _AddGeneralPage();
	void _AddVisPage();
	void _AddHistogram();
	void _AddColormap();
	void _AddCalcParaPage();
	void _AddDiagramPage();

	bool _IsSeismicFoldMap(CXViewInfoSeismicDV* pViewInfoDV);
	void _Update();

private:
	Ui_RLDialogProperties m_ui;

	CXObject* m_pObj = nullptr;
	CXWindow* m_pWin = nullptr;

	CXBasePropertyPage* m_pGeneral = nullptr;
	CXBasePropertyPage* m_pVisPage = nullptr;
	CXBasePropertyPage* m_pColormapPage = nullptr;
};

#endif // KEDIALOGPROPERTIES_H

