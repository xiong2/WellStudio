#ifndef XDLGLFMUPSCALING_H
#define XDLGLFMUPSCALING_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlglfmupscaling.h"

class CXBaseParameter;
class CXObject;
class CXParameterUpscaling;
class CXLFMGeometry;
class QButtonGroup;

/**
*	@class	 CXDlgLFMIntersection in the file "kedlglfmintersection.h"
*	@brief	 The class provide a wizard to build the upscaling geometry
*	@author	Yong Shu
*	@date	 11/17/2015
*/

class XGUIPLUS_EXPORT CXDlgLFMUpscaling : public QDialog
{
	Q_OBJECT

public:
	CXDlgLFMUpscaling(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent = NULL);
	~CXDlgLFMUpscaling();

	virtual void accept();

private:
	void _Init();

private:
	Ui::DlgLFMUpscaling m_ui;

	CXParameterUpscaling* m_pPara;

	QButtonGroup* m_PBottonGroup;
};

#endif // KEDLGLFMUPSCALING_H
