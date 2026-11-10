#ifndef XDLGEXPORTSEGY_H
#define XDLGEXPORTSEGY_H

#include <QDialog>
#include "xgui_global.h"
#include "ui_xdlgexportsegy.h"

class CXObject;
class CXSeismicDataVolume;
class CXSeismicDataLine;

class XGUI_EXPORT CXDlgExportSEGY : public QDialog
{
	Q_OBJECT

public:
	CXDlgExportSEGY(CXObject *pDV, QWidget *parent = 0);
	~CXDlgExportSEGY();
	
public slots:
	virtual void accept();

private:
	void initUI();
	void generateEBCDIC();

	void flipTH(char *);

	Ui::CXDlgExportSEGY ui;

	CXSeismicDataVolume	*m_pDV;
	CXSeismicDataLine		*m_p2DSection;
	char					m_charReelEBCDIC[3200];	//	EBCDIC formation 

private slots:
	void slotSelectFile();
	void slotSelectCopyFile();
	void slotEBCDICDialog();
	void slotDataTypeChanged(int);
};

#endif // KEDLGEXPORTSEGY_H
