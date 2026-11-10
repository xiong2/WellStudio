#pragma once
#include <qdialog.h>
#include "xguiplus_global.h"

enum EDialogType
{
	eDataSheetDialog
};

class CXDlgDataSheet;

class XGUIPLUS_EXPORT CXDlgFactory
{
public:
	static CXDlgFactory& Instance();

	QDialog* CreateDialog(QUuid, EDialogType);
	void CloseDialog(QUuid, EDialogType);

	CXDlgFactory(const CXDlgFactory&) = delete;
	CXDlgFactory& operator=(const CXDlgFactory&) = delete;

private:
	CXDlgFactory() {}

	QHash<QUuid, CXDlgDataSheet*> m_hashDataSheetDialog;
};