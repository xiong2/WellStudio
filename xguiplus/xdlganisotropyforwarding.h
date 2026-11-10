#ifndef XDLGANISOTROPYFORWARDING_H
#define XDLGANISOTROPYFORWARDING_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgfractureforwardmodeling.h"

class CXBaseParameter;
class CXObject;
class CXParameterAnisotropyForwarding;
class CXSeismicDataVolume;

/**
*	@class	 CXDlgAnisotropyForwarding in the file "kedlganisotropyforwarding.h"
*	@brief	 The class provide a dialog for seismic anisotropy forwarding
*	@author	Yong Shu
*	@date	 12/23/2016
*/

class XGUIPLUS_EXPORT CXDlgAnisotropyForwarding : public QDialog
{
	Q_OBJECT

public:
	CXDlgAnisotropyForwarding(CXBaseParameter* pPara, CXObject* pParentObj = NULL, QWidget *parent = NULL);
	~CXDlgAnisotropyForwarding();

	virtual void accept();

private:
	void _Init();

private slots:
	void slotUpdate();
	void slotFinishAzi();
	void slotFinishIncidence();
	void slotSelectDV();

private:
	Ui::DlgFractureForwardModeling m_ui;

	CXParameterAnisotropyForwarding* m_pPara;

	CXSeismicDataVolume* m_pDV;
};

#endif // KEDLGANISOTROPYFORWARDING_H
