#ifndef XPAGEFILE3DSURFACE_H
#define XPAGEFILE3DSURFACE_H

#include <QWizardPage>
#include "ui_xpagefile3dsurface.h"
#include "xgui_global.h"
#include <QUuid>
#include "xobjecttype.h"

class CXASCIIFile;
class CXSeismicUTMTool;

///@brief	A wizard page for importing 3-D surfaces/ Fault sticks.
///@author	Yong Shu
///@date	Apr. 10th, 2014
///@see		
class XGUI_EXPORT CXPageFile3DSurface : public QWizardPage
{
	Q_OBJECT

public:
	CXPageFile3DSurface(CXASCIIFile *pASCIIFile, QWidget *parent = 0);
	~CXPageFile3DSurface();

	///@brief Reimplementation
	virtual void initializePage();

	///@brief Reimplementation
	virtual bool validatePage(); 

	CXSeismicUTMTool* GetSelectedUTM() {return m_pSelectedUTM;}


public slots:
	void slotSurfaceNameChange();
	void slotUtmChanged(int);

private:
	void _UpdateWidet();
	void _InitUTM();
	void _InsertSurfaceGeometry(EXObjectType eObjType);

private:
	Ui::RLPageFile3DSurface m_ui;

	CXASCIIFile* m_pDataFile;

	CXSeismicUTMTool* m_pSelectedUTM;
	QUuid m_uuidSurvey;

	bool m_bImportingFault;
};

#endif // RLPAGEFILE3DSURFACE_H
