#include "xdlgattachprofile.h"

#include <qfiledialog.h>
#include <qpixmap.h>
#include <qmessagebox.h>

#include "x3dsurvey.h"
#include "xseismicsection.h"
#include "xseismicutmtool.h"
#include "xseismicdatavolume.h"
#include "xtree.h"
#include "xglobal.h"

CXDlgAttachProfile::CXDlgAttachProfile(CXObject *pObj, QWidget *pParent): QDialog(pParent)
{
	ui.setupUi(this);

	m_pSurvey = dynamic_cast<CX3DSurvey *>(pObj);

	//	Get survey information to initialize the GUI.
	CXSeismicUTMTool& utm = m_pSurvey->GetUTM();
	int iLine, iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc;
	utm.GetLineNumRange(iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc);

	iLine = iFirstInline + (iLastInline - iFirstInline) / 2;
	ui.lineEditLineNumber->setText(QString::number(iLine));
	ui.lineEditStartTrace->setText(QString::number(iFirstCrossline));
	ui.lineEditEndTrace->setText(QString::number(iLastCrossline));

	QList<CXObject*> listDV = m_pSurvey->GetChildren(EXSeismicDataVolume, true);
		
	if(!listDV.isEmpty())
	{
		CXSeismicDataVolume* pDV = (CXSeismicDataVolume *)listDV[0];
		double dSTime, dETime, dSampleInv;
		pDV->GetSamplingRange(dSTime, dETime, dSampleInv);

		ui.lineEditStartTime->setText(QString::number(dSTime, 'g', 4));
		ui.lineEditEndTime->setText(QString::number(dETime, 'g', 4));
	}
	else
	{
		ui.lineEditStartTime->setText("0");
		ui.lineEditEndTime->setText("0");
	}

	connect(ui.pushButtonBrowser, SIGNAL(clicked()), this, SLOT(slotLoadPicture()));
}

void CXDlgAttachProfile::slotLoadPicture()
{
	QString strPictureFile = QFileDialog::getOpenFileName(this, "Select Profile Picture", "", 
		tr("Picture(*.BMP *.JPG *.JPEG *.TIFF *.TIF *.GIF *.PNG *.PPM *.PBM *.PGM *.XBM *.XPM)"));

    if(strPictureFile.isEmpty()) 
		return;

	ui.lineEditFile->setText(strPictureFile);
	ui.labelCanvas->setPixmap(QPixmap(strPictureFile));
}

void CXDlgAttachProfile::accept()
{
	if(ui.lineEditFile->text() == "" || ui.lineEditStartTime->text() == "" || ui.lineEditEndTime->text() == "")
	{
		QMessageBox::information(this, "Attaching seismic profile", "The given parameters wrong!");
		return;
	}

	CXSeismicSection *pSection = new CXSeismicSection(ui.lineEditFile->text(), ui.lineEditLineNumber->text().toInt(),
		ui.lineEditStartTrace->text().toInt(), ui.lineEditEndTrace->text().toInt(),
		ui.lineEditStartTime->text().toDouble(), ui.lineEditEndTime->text().toDouble());

	m_pSurvey->AddChild(pSection);
	::AddObjectEvent(pSection);

	QDialog::accept();
}