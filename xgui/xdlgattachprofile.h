#ifndef _CXDLGATTACHPROFILE_H__
#define _CXDLGATTACHPROFILE_H__

#include <qdialog.h>
#include "xgui_global.h"
#include "ui_xdlgattachprofile.h"

class CXObject;
class CX3DSurvey;

class XGUI_EXPORT CXDlgAttachProfile: public QDialog
{
	Q_OBJECT
public:
	CXDlgAttachProfile(CXObject *pObj, QWidget *parent = 0);

	void accept();

protected:
	Ui::AttachProfile ui;

	CX3DSurvey	*m_pSurvey;

protected slots:
	void slotLoadPicture();
};

#endif