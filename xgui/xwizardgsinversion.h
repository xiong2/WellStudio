#ifndef XWIZARDGSINVERSION_H
#define XWIZARDGSINVERSION_H

#include <QWizard>
#include "xgui_global.h"

class CXBaseParameter;
class CXObject;

class XGUI_EXPORT CXWizardGSInversion : public QWizard
{
	Q_OBJECT

public:
	CXWizardGSInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXWizardGSInversion();

private slots:
	void slotPageChanged(int pageIndex);

};

#endif