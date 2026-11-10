#include "xdlgfactory.h"
#include "xglobal.h"
#include "xdlgdatasheet.h"
#include "xbaseconsole.h"

CXDlgFactory& CXDlgFactory::Instance()
{
	static CXDlgFactory factory;
	return factory;
}

QDialog* CXDlgFactory::CreateDialog(QUuid objID, EDialogType eType)
{
	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	if (eType == eDataSheetDialog)
	{
		CXDlgDataSheet* pDialog = m_hashDataSheetDialog.value(objID, nullptr);

		if (!pDialog)
		{
			pDialog = new CXDlgDataSheet(objID, pParentWidget);
			m_hashDataSheetDialog.insert(objID, pDialog);
		}

		return (QDialog *)pDialog;
	}

	return NULL;
}

void CXDlgFactory::CloseDialog(QUuid objID, EDialogType eType)
{
	if (eType == eDataSheetDialog)
		m_hashDataSheetDialog.remove(objID);
}