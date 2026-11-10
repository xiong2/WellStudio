#include <QMessageBox>
#include <QTableWidgetItem>
#include <QIntValidator>
#include "xpageloadsegy.h"
#include "xsegyloadparameters.h"
#include "xsegytraceheader.h"
#include "x3dsurvey.h"
#include "xseismicdatavolume.h"
#include "xseismicutmtool.h"
#include "xglobal.h"
#include "xproject.h"
#include "xdef.h"
#include "xtraceheaderscanthread.h"
#include "xpageloadsegyhistogram.h"
#include "xpageloadsegywiggle.h"
#include <QStackedLayout>
#include "xsegylineheader.h"
#include "xebcdicdialog.h"
#include "xdlgsegylineheader.h"
#include "xlinearitymap.h"
#include "xprestackgather.h"

CXPageLoadSegyStep1::CXPageLoadSegyStep1(QWizard *parent,QStringList  sListFiles)
	: QWizardPage(parent)
{
	m_pTraceData = NULL;
	m_page1.setupUi(this);
	m_pDataPara = new CXSEGYLoadParameters(sListFiles);
	m_listFile = sListFiles;
	
	QIntValidator *pEdtInvalidator = new QIntValidator(this);
	QDoubleValidator *pDoubleValidator = new QDoubleValidator(this);
	m_page1.m_EdtSampleInterval->setValidator(pDoubleValidator );
	m_page1.m_EdtSampleNumber->setValidator(pEdtInvalidator );
}

CXPageLoadSegyStep1::~CXPageLoadSegyStep1()
{
	delete m_pDataPara;
}

void CXPageLoadSegyStep1::_connect()
{
	QList<QRadioButton*>listRdo =  m_page1.m_GrpDisplayMode->findChildren<QRadioButton*>();
	foreach(QRadioButton * pRdo , listRdo)
	{
		connect(pRdo,SIGNAL(clicked()),this,SLOT(slotSelectDisplayMode()));
	}
	connect(m_page1.m_SldTraceTick,SIGNAL(valueChanged(int)),this,SLOT(slotCurrentTraceChanged(int )),Qt::UniqueConnection);
	connect(m_page1.m_EdtCurTraceValue,SIGNAL(valueChanged(int)),this,SLOT(slotCurrentTraceChanged(int)),Qt::UniqueConnection);
	connect(m_page1.m_CmbSampleFormat,SIGNAL(currentIndexChanged (int)),this,SLOT(slotSampleFormatChanged(int)),Qt::UniqueConnection);
	connect(m_page1.m_ChkFlipBytes,SIGNAL(clicked()),this,SLOT(slotFlipData()));
	connect(m_page1.m_EdtSampleInterval,SIGNAL(editingFinished()),this,SLOT(slotSampleIntervalChanged()),Qt::UniqueConnection);
	connect(m_page1.m_EdtSampleNumber,SIGNAL(textChanged(const QString &)),this,SLOT(slotSampleNumberChanged()),Qt::UniqueConnection);
	connect(m_page1.m_PtnLineHeader,SIGNAL(clicked()),this,SLOT(slotLineHeaderViewClicked()),Qt::UniqueConnection);
	connect(m_page1.m_PtnVolumeHeader,SIGNAL(clicked()),this,SLOT(slotVolumeHeaderViewClicked()),Qt::UniqueConnection);

}
void CXPageLoadSegyStep1::slotLineHeaderViewClicked()
{
	CXDlgSEGYLineHeader * pLineHeaderView = new CXDlgSEGYLineHeader(this);
	connect(pLineHeaderView,SIGNAL(lineHeaderDataFliped(bool)),this,SLOT(slotFlipData()));
	pLineHeaderView->setLineHeaderData(m_pDataPara->GetLineHeader());
	pLineHeaderView->initTreeView();
	pLineHeaderView->setWindowTitle("3-D SEG-Y File Line Header Information");
	pLineHeaderView->show();
}
void CXPageLoadSegyStep1::slotVolumeHeaderViewClicked()
{
	CXEBCDICDialog *pEBCDICDialog = new CXEBCDICDialog(this);
	pEBCDICDialog->setWindowTitle("3-D SEG-Y File Volume Header Information");
	pEBCDICDialog->SetEBCDIC(m_pDataPara->GetVolumeHeader());
	pEBCDICDialog->show();
}
void CXPageLoadSegyStep1::slotSampleIntervalChanged()
{
	int nSampleInterval = m_page1.m_EdtSampleInterval->text().toInt();
	m_pDataPara->SetSampleInterval(nSampleInterval);
	_refrashPreview();
}

void CXPageLoadSegyStep1::slotSampleNumberChanged()
{
	if(m_pTraceData)
	{
		delete[] m_pTraceData;
		m_pTraceData = NULL;
	}
	int nSampleNumber = m_page1.m_EdtSampleNumber->text().toInt();
	m_pDataPara->SetSampleNumber(nSampleNumber);
	m_pTraceData = new float[nSampleNumber];
	int nTraceDataIndex = m_page1.m_SldTraceTick->value();
	if(nTraceDataIndex == 0)
		nTraceDataIndex = 1;//Trace from 1.
	m_pDataPara->GetOneTraceData(nTraceDataIndex,m_pTraceData);
	_refrashPreview();
}
void CXPageLoadSegyStep1::slotSelectDisplayMode()
{	
	QRadioButton * pRdo = dynamic_cast<QRadioButton*>(sender());
	QString strRdoAccName = pRdo->accessibleName();
	QStackedLayout *pStackedLayout = dynamic_cast<QStackedLayout*>(m_page1.m_FramePreview->layout());

	if( strRdoAccName== "Wiggle")
	{
		pStackedLayout->setCurrentIndex(0);

	}
	if(strRdoAccName == "Histogram")
	{		
		pStackedLayout->setCurrentIndex(1);
	}
}

void CXPageLoadSegyStep1::slotFlipData()
{
	m_pDataPara->SetDataFlip(m_page1.m_ChkFlipBytes->isChecked());
	_refrashPreview();
}

void CXPageLoadSegyStep1::slotSampleFormatChanged(int nFormateType)
{
	if(nFormateType == 1)
	{
		m_page1.m_ChkFlipBytes->setChecked(true);
		m_page1.m_ChkFlipBytes->setEnabled(false);
	}
	else if(nFormateType == 4)
	{
		m_page1.m_ChkFlipBytes->setChecked(false);
		m_page1.m_ChkFlipBytes->setEnabled(false);
	}
	else
	{
		m_page1.m_ChkFlipBytes->setChecked(m_pDataPara->DataNeedFlip());
		m_page1.m_ChkFlipBytes->setEnabled(true);
	}
	m_pDataPara->SetDataType(nFormateType);
	_refrashPreview();
}

void CXPageLoadSegyStep1:: _refrashPreview()
{	
	int nSampleNumber = m_page1.m_EdtSampleNumber->text().toInt();
	int nTraceIndex = m_page1.m_SldTraceTick->value();
	m_pDataPara->GetOneTraceData(nTraceIndex,m_pTraceData);
	
	QStackedLayout *pStackedLayout = dynamic_cast<QStackedLayout *>(m_page1.m_FramePreview->layout());	
	CXPageLoadSegyHistogram *pPageHisto = dynamic_cast<CXPageLoadSegyHistogram*>(pStackedLayout->widget(1)); 
	CXPageLoadSegyWiggle *pPageWiggle = dynamic_cast<CXPageLoadSegyWiggle*>(pStackedLayout->widget(0)); 
	if(pPageHisto)
	{
		pPageHisto->SetTraceData(m_pTraceData,nSampleNumber);
	}
	if(pPageWiggle)
	{
		pPageWiggle->SetTraceData(m_pTraceData,nSampleNumber);
	}
}

void CXPageLoadSegyStep1::slotCurrentTraceChanged(int nValue)
{	
	int nSampleNumber = m_page1.m_EdtSampleNumber->text().toInt();
	m_page1.m_EdtCurTraceValue->blockSignals(true);
	m_page1.m_SldTraceTick->blockSignals(true);
	m_page1.m_EdtCurTraceValue->setValue(nValue);
	m_page1.m_SldTraceTick->setValue(nValue);
	m_page1.m_EdtCurTraceValue->blockSignals(false);
	m_page1.m_SldTraceTick->blockSignals(false);
	m_pDataPara->SetSampleNumber(nSampleNumber);
	m_pDataPara->GetOneTraceData(nValue,m_pTraceData);
	_refrashPreview();
}

void CXPageLoadSegyStep1::initializePage()
{
	//Add Stack page
	CXPageLoadSegyWiggle *pWiggleWidget = new CXPageLoadSegyWiggle(NULL);
	CXPageLoadSegyHistogram *pHistogramFrame = new CXPageLoadSegyHistogram(NULL);
	QStackedLayout *pStackedLayout = new QStackedLayout(m_page1.m_FramePreview);
	pStackedLayout->addWidget(pWiggleWidget);
	pStackedLayout->addWidget(pHistogramFrame);
	//init page 
	m_page1.m_LstFilePath->addItems(m_listFile);
	m_page1.m_ChkFlipBytes->setChecked(m_pDataPara->DataNeedFlip());
	m_page1.m_CmbSampleFormat->setCurrentIndex(m_pDataPara->GetDataType());
	m_page1.m_EdtSampleNumber->setText(QString::number(m_pDataPara->GetSampleNumber()));
	m_page1.m_EdtSampleInterval->setText(QString::number(m_pDataPara->GetSampleInterval()));
	m_pTraceData = new float[m_pDataPara->GetSampleNumber()];
	memset(m_pTraceData, 0, sizeof(float) * m_pDataPara->GetSampleNumber());
	m_page1.m_EdtCurTraceValue->setMinimum(1);
	m_page1.m_EdtCurTraceValue->setMaximum(m_pDataPara->GetTraceNumber());
	m_page1.label_4->setText("Current Trace (Total: "+QString::number(m_pDataPara->GetTraceNumber())+" )");
	m_page1.m_SldTraceTick->setMinimum(1);
	m_page1.m_SldTraceTick->setMaximum(m_pDataPara->GetTraceNumber());
	//set stack page data
	pHistogramFrame->SetTraceData(m_pTraceData,m_pDataPara->GetSampleNumber());
	pWiggleWidget->SetTraceData(m_pTraceData,m_pDataPara->GetSampleNumber());

	_connect();
	_refrashPreview();
}

bool CXPageLoadSegyStep1::validatePage ()
{
	m_pDataPara->SetDataFlip(m_page1.m_ChkFlipBytes->isChecked());
	m_pDataPara->SetDataType(m_page1.m_CmbSampleFormat->currentIndex());
	m_pDataPara->SetSampleInterval(m_page1.m_EdtSampleInterval->text().toFloat());
	m_pDataPara->SetSampleNumber(m_page1.m_EdtSampleNumber->text().toFloat());
	return true;
}

CXPageLoadSegyStep2::CXPageLoadSegyStep2(QWidget *parent):QWizardPage(parent)
{
	m_pTraceData = NULL;
	m_page2.setupUi(this);
	setButtonText(QWizard::NextButton,"Scan");
	m_page2.m_PrbScanProbar->setHidden(true);
	m_page2.m_PtnTreadCancel->setHidden(true);
	m_pScanHeaderThread = NULL;
	m_bScanned = false;

	m_page2.labelDX->setVisible(false);
	m_page2.m_EdtFileDX->setVisible(false);
	m_page2.labelDY->setVisible(false);
	m_page2.m_EdtFileDY->setVisible(false);
	m_page2.labelSE->setVisible(false);
	m_page2.m_EdtFileSE->setVisible(false);
	m_page2.labelDE->setVisible(false);
	m_page2.m_EdtFileDE->setVisible(false);
	m_page2.labelFB->setVisible(false);
	m_page2.m_EdtFileFB->setVisible(false);

	m_page2.m_EdtInline->setValidator(new QIntValidator(this));
	m_page2.m_EdtCrossLine->setValidator(new QIntValidator(this));
	m_page2.lineEditOffset->setValidator(new QIntValidator(this));
	m_page2.lineEditAzimuth->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileX->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileY->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileDX->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileDY->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileSE->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileDE->setValidator(new QIntValidator(this));
	m_page2.m_EdtFileFB->setValidator(new QIntValidator(this));
	m_page2.m_EdtStartLine->setValidator(new QIntValidator(this));
	m_page2.m_EdtEndLine->setValidator(new QIntValidator(this));
}

CXPageLoadSegyStep2::~CXPageLoadSegyStep2(void)
{
	if(m_pScanHeaderThread && m_pScanHeaderThread->isRunning())
	{
		m_pScanHeaderThread->wait();
	}
	delete 	m_pScanHeaderThread;
	m_pScanHeaderThread = NULL;
}

void CXPageLoadSegyStep2::_connect()
{
	//	SEGY type changed.
	connect(m_page2.comboBoxSEGYType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSEGYTypeChanged(int)), Qt::UniqueConnection);

	connect(m_page2.m_SldTrace,SIGNAL(valueChanged(int)),this,SLOT(slotTraceValueChanged(int)),Qt::UniqueConnection);
	connect(m_page2.m_RdoFormatIEEE,SIGNAL(clicked()),this,SLOT(slotFloatFormatChanged()),Qt::UniqueConnection);
	connect(m_page2.m_RdoFormatIBM,SIGNAL(clicked()),this,SLOT(slotFloatFormatChanged()),Qt::UniqueConnection);

	connect(m_page2.m_RdoInput3Points,SIGNAL(clicked()),this,SLOT(slotCoordinateFromChanged()),Qt::UniqueConnection);
	connect(m_page2.m_RdoScanSegyFile,SIGNAL(clicked()),this,SLOT(slotCoordinateFromChanged()),Qt::UniqueConnection);
	connect(m_page2.m_ChkOverrideXYScale,SIGNAL(clicked()),this,SLOT(slotOverrideScaleEnabled()),Qt::UniqueConnection);
	connect(m_page2.m_ChkAscIIFlip,SIGNAL(clicked()),this,SLOT(slotFlipData()),Qt::UniqueConnection);
	connect(m_page2.m_SpxCurrTrace,SIGNAL(valueChanged(int)),this,SLOT(slotTraceValueChanged(int)),Qt::UniqueConnection);

	//coordinate para changed.
	connect(m_page2.m_EdtOverrideScaleValue,SIGNAL(textChanged(const QString &)),this,SLOT(slotOverrideScaleChanged()),Qt::UniqueConnection);
	connect(m_page2.m_EdtInline,SIGNAL(textChanged (const QString &)),this,SLOT(slotNeedRescan()),Qt::UniqueConnection);
	connect(m_page2.m_EdtFileX,SIGNAL(textChanged (const QString &)),this,SLOT(slotNeedRescan()),Qt::UniqueConnection);
	connect(m_page2.m_EdtCrossLine,SIGNAL(textChanged (const QString &)),this,SLOT(slotNeedRescan()),Qt::UniqueConnection);
	connect(m_page2.m_EdtFileY,SIGNAL(textChanged (const QString &)),this,SLOT(slotNeedRescan()),Qt::UniqueConnection);
	connect(m_page2.m_CmbXyUnit,SIGNAL(currentIndexChanged(int)),this,SLOT(slotNeedRescan()),Qt::UniqueConnection);
	//Cancel Tread
	connect(m_page2.m_PtnTreadCancel,SIGNAL(clicked ()),this,SLOT(slotCancelThread()),Qt::UniqueConnection);
	//Edt Valid line number
	connect(m_page2.m_EdtStartLine,SIGNAL(editingFinished ()),this,SLOT(slotEditLineNumber()),Qt::UniqueConnection);
	connect(m_page2.m_EdtEndLine,SIGNAL(editingFinished ()),this,SLOT(slotEditLineNumber()),Qt::UniqueConnection);
}

void CXPageLoadSegyStep2::slotSEGYTypeChanged(int nValue)
{
	//	Source and detector coordinate.
	m_pDataPara->SetPrestackGather(false);
	m_page2.labelInline->setText("Inline:");
	m_page2.labelCrossline->setVisible(true);
	m_page2.m_EdtCrossLine->setVisible(true);
	m_page2.labelX->setText("X:");
	m_page2.labelY->setText("Y:");
	m_page2.labelDX->setVisible(false);
	m_page2.m_EdtFileDX->setVisible(false);
	m_page2.labelDY->setVisible(false);
	m_page2.m_EdtFileDY->setVisible(false);
	m_page2.labelSE->setVisible(false);
	m_page2.m_EdtFileSE->setVisible(false);
	m_page2.labelDE->setVisible(false);
	m_page2.m_EdtFileDE->setVisible(false);
	m_page2.labelFB->setVisible(false);
	m_page2.m_EdtFileFB->setVisible(false);

	if (nValue == 0)
	{
		//	Poststack.
		m_pDataPara->SetPrestack(false);
		m_pDataPara->SetAzimuth(false);

		//	Offset invisible.
		m_page2.labelOffset->setVisible(false);
		m_page2.lineEditOffset->setVisible(false);
		m_page2.checkBoxIrreOffset->setVisible(false);

		//	Azimuth invisible.
		m_page2.labelAzimuth->setVisible(false);
		m_page2.lineEditAzimuth->setVisible(false);
		m_page2.groupBoxAzimuth->setVisible(false);
	}
	else if (nValue == 1)
	{
		//	Prestack.
		m_pDataPara->SetPrestack(true);
		m_pDataPara->SetAzimuth(false);

		//	Offset visible.
		m_page2.lineEditOffset->setText(QString::number(m_pDataPara->GetOffsetPosition()));
		m_page2.labelOffset->setVisible(true);
		m_page2.lineEditOffset->setVisible(true);
		m_page2.checkBoxIrreOffset->setVisible(true);

		//	Azimuth invisible.
		m_page2.labelAzimuth->setVisible(false);
		m_page2.lineEditAzimuth->setVisible(false);
		m_page2.groupBoxAzimuth->setVisible(false);
	}
	else if (nValue == 2)
	{
		//	Azimuth prestack.
		m_pDataPara->SetPrestack(true);
		m_pDataPara->SetAzimuth(true);

		//	Offset visible.
		m_page2.lineEditOffset->setText(QString::number(m_pDataPara->GetOffsetPosition()));
		m_page2.labelOffset->setVisible(true);
		m_page2.lineEditOffset->setVisible(true);
		m_page2.checkBoxIrreOffset->setVisible(false);
		m_page2.checkBoxIrreOffset->setChecked(true);

		//	Azimuth visible.
		m_page2.lineEditAzimuth->setText(QString::number(m_pDataPara->GetAzimuthPosition()));
		m_page2.labelAzimuth->setVisible(true);
		m_page2.lineEditAzimuth->setVisible(true);
		m_page2.groupBoxAzimuth->setVisible(true);
	}
	else if (nValue == 3)
	{
		//	Prestack gather.
		m_pDataPara->SetPrestackGather(true);
		m_pDataPara->SetPrestack(true);
		m_pDataPara->SetAzimuth(false);

		m_page2.labelInline->setText("Field ID:");
		m_page2.labelCrossline->setVisible(false);
		m_page2.m_EdtCrossLine->setVisible(false);

		//	Offset invisible.
		m_page2.labelOffset->setVisible(false);
		m_page2.lineEditOffset->setVisible(false);
		m_page2.checkBoxIrreOffset->setVisible(false);

		//	Azimuth invisible.
		m_page2.labelAzimuth->setVisible(false);
		m_page2.lineEditAzimuth->setVisible(false);
		m_page2.groupBoxAzimuth->setVisible(false);

		//	Source and detector coordinate.
		m_page2.labelX->setText("Source X:");
		m_page2.labelY->setText("Source Y:");
		m_page2.labelDX->setVisible(true);
		m_page2.m_EdtFileDX->setVisible(true);
		m_page2.labelDY->setVisible(true);
		m_page2.m_EdtFileDY->setVisible(true);
		m_page2.labelSE->setVisible(true);
		m_page2.m_EdtFileSE->setVisible(true);
		m_page2.labelDE->setVisible(true);
		m_page2.m_EdtFileDE->setVisible(true);
		m_page2.labelFB->setVisible(true);
		m_page2.m_EdtFileFB->setVisible(true);

		m_page2.m_EdtFileX->setText("73");
		m_page2.m_EdtFileY->setText("77");
		m_page2.m_EdtFileDX->setText("81");
		m_page2.m_EdtFileDY->setText("85");
		m_page2.m_EdtFileSE->setText("45");
		m_page2.m_EdtFileDE->setText("41");
		m_page2.m_EdtFileFB->setText("113");
	}

	m_bScanned = false;
}

void CXPageLoadSegyStep2::slotNeedRescan()
{
	m_bScanned = false;
	bool bNeedRescan = m_page2.m_RdoInput3Points->isChecked();
	if(bNeedRescan)
		return;
	setButtonText(QWizard::NextButton,"Scan");
}

void CXPageLoadSegyStep2::slotCancelThread()
{	
	m_pScanHeaderThread->StopThread();
	QAbstractButton *pButton =  wizard()->button(QWizard::NextButton);
	pButton->setEnabled(true);
	pButton =  wizard()->button(QWizard::BackButton);
	pButton->setEnabled(true);
	pButton =  wizard()->button(QWizard::CancelButton);
	pButton->setEnabled(true);
}

void CXPageLoadSegyStep2::slotEditLineNumber()
{
	int nStartLine = m_page2.m_EdtStartLine->text().toInt();
	int nEndLine = m_page2.m_EdtEndLine->text().toInt();
	if(nStartLine <= 0 || nStartLine > nEndLine )
	{
		QMessageBox::warning(this, tr("My Application"),  tr("The valid line number is wrong!"));
		m_page2.m_EdtStartLine->setText(QString::number(1));
		m_page2.m_EdtEndLine->setText(QString::number(100000));
	}
}

void CXPageLoadSegyStep2::slotRefreshProgressBar(qint64 nValue)
{
	CXLinearityMap progressMap(0,100,0,m_pDataPara->GetTraceNumber());
	int nProgressValue = ::ceil(progressMap.GetInputValue(nValue));
	m_page2.m_PrbScanProbar->setValue(nProgressValue);
}

void CXPageLoadSegyStep2::slotCoordinateFromChanged()
{	
	m_page2.m_PrbScanProbar->setHidden(true);
	m_page2.m_PtnTreadCancel->setHidden(true);
	bool bFromScan = m_page2.m_RdoScanSegyFile->isChecked();
	m_page2.labelX->setEnabled(bFromScan);	
	m_page2.m_EdtFileX->setEnabled(bFromScan);	
	m_page2.labelY->setEnabled(bFromScan);	
	m_page2.m_EdtFileY->setEnabled(bFromScan);	
	m_page2.label_8->setEnabled(bFromScan);	
	m_page2.m_CmbXyUnit->setEnabled(bFromScan);	
	m_page2.m_ChkOverrideXYScale->setEnabled(bFromScan);	
	m_page2.m_EdtOverrideScaleValue->setEnabled(bFromScan && m_page2.m_ChkOverrideXYScale->isChecked());	
	if(bFromScan)
	{
		setButtonText(QWizard::NextButton,"Scan");
	}
	else
	{
		setButtonText(QWizard::NextButton,"Next");
	}
}

bool CXPageLoadSegyStep2::validatePage ()
{
	QWizard *pWizard = wizard();
	if(buttonText(QWizard::NextButton) == "Scan")
	{
		if(!m_bScanned)
		{
			m_page2.m_PrbScanProbar->setHidden(false);
			m_page2.m_PtnTreadCancel->setHidden(false);
			m_pDataPara->SetUnit(m_page2.m_CmbXyUnit->currentIndex()+1);
			m_pDataPara->SetInlinePosition(m_page2.m_EdtInline->text().toUShort());
			m_pDataPara->SetCrosslinePosition(m_page2.m_EdtCrossLine->text().toUShort());
			m_pDataPara->SetOffsetPosition(m_page2.lineEditOffset->text().toUShort());
			m_pDataPara->SetAzimuthPosition(m_page2.lineEditAzimuth->text().toUShort());
			m_pDataPara->SetXPosition(m_page2.m_EdtFileX->text().toUShort());
			m_pDataPara->SetYPosition(m_page2.m_EdtFileY->text().toUShort());
			m_pDataPara->SetDXPosition(m_page2.m_EdtFileDX->text().toUShort());
			m_pDataPara->SetDYPosition(m_page2.m_EdtFileDY->text().toUShort());

			//	Azimuth start and orentation.
			bool bEast = m_page2.radioButtonEast->isChecked();
			bool bCCW = m_page2.radioButtonCCW->isChecked();
			m_pDataPara->SetAzimuthInfo(bEast, bCCW);

			m_pDataPara->SetValidStartLine( m_page2.m_EdtStartLine->text().toInt());
			m_pDataPara->SetValidEndLine(m_page2.m_EdtEndLine->text().toInt());

			if(m_pScanHeaderThread != NULL)
			{
				delete m_pScanHeaderThread;
				m_pScanHeaderThread = NULL;
			}
			m_pScanHeaderThread = new CXTraceHeaderScanThread(m_pDataPara, m_page2.checkBoxIrreOffset->isChecked());
			connect(m_pScanHeaderThread, SIGNAL(signalUpdateProgress(qint64,qint64)), this, SLOT(slotRefreshProgressBar(qint64)), Qt::UniqueConnection);
			connect(m_pScanHeaderThread, SIGNAL(finished()), this, SLOT(slotThreadFinished()), Qt::UniqueConnection);
			m_pScanHeaderThread->start();

			QAbstractButton *pButton =  pWizard->button(QWizard::NextButton);
			pButton->setEnabled(false);
			pButton =  pWizard->button(QWizard::BackButton);
			pButton->setEnabled(false);
			pButton =  pWizard->button(QWizard::CancelButton);
			pButton->setEnabled(false);
			return false;
		}
		else
		{
			this->nextId();
			return true;
		}
	}
	else
	{
		this->nextId();
		return true;
	}
}

void CXPageLoadSegyStep2::slotThreadFinished()
{
	QWizard *pWizard = wizard();

	if(m_pScanHeaderThread->IsStopped())
	{
		QString strError = "";
		int iErrorCode = m_pScanHeaderThread->GetErrorCode();

		if (iErrorCode == 1)
		{
			strError = "Parameters setting error!";
		}
		else if (iErrorCode == 2)
		{
			strError = "Can not open the destination SEGY file!";
		}
		else if (iErrorCode == 3)
		{
			strError = "The offsets are irregular!";
		}
		else if (iErrorCode == 4)
		{
			strError = "The UTM of each SEGY file is not compatible!";
		}

		if (!strError.isEmpty())
			QMessageBox::critical(NULL, "Importing SEG-Y Data", strError);

		if (m_pScanHeaderThread->IsTerminated())
			m_pScanHeaderThread = NULL;
		m_page2.m_PrbScanProbar->setValue(0);
		QAbstractButton *pButton =  pWizard->button(QWizard::NextButton);
		pButton->setEnabled(true);
		pButton =  pWizard->button(QWizard::BackButton);
		pButton->setEnabled(true);
		pButton =  pWizard->button(QWizard::CancelButton);
		pButton->setEnabled(true);
		return ;
	}

	if (m_pDataPara->IsPrestackGather())
	{
		CXPreStackGather *pGather = m_pDataPara->GetPrestackGather();
		CXObject *pGFolder = ::GetRootObjectFolder(EXSeismicGatherFolder);
		pGather->SetObjectName(pGFolder->GetUnallocatedName(pGather->GetObjectName()));
		pGather->SetModifiedFlag();

		pGFolder->AddChild(pGather);
		::AddObjectEvent(pGather);

		wizard()->close();
	}

	//	Cut the 1st 2 digits if the X coordinates has 8 digits.
	if (m_page2.m_ChkWithoutZoneNumber->isChecked())
		m_pDataPara->GetUTMTool()->RemoveXStrip();
	m_page2.m_ChkWithoutZoneNumber->setEnabled(false);

	m_bScanned = true;
	m_page2.m_PrbScanProbar->setHidden(true); 
	m_page2.m_PtnTreadCancel->setHidden(true);
	QAbstractButton *pButton =  pWizard->button(QWizard::NextButton);
	pButton->setEnabled(true);
	pButton =  pWizard->button(QWizard::BackButton);
	pButton->setEnabled(true);
	pButton =  pWizard->button(QWizard::CancelButton);
	pButton->setEnabled(true);
	wizard()->next();
}

void CXPageLoadSegyStep2::slotOverrideScaleChanged()
{
	m_pDataPara->SetScale(m_page2.m_EdtOverrideScaleValue->text().toFloat());
	setButtonText(QWizard::NextButton,"Scan");
	m_bScanned = false;
}

void CXPageLoadSegyStep2::slotOverrideScaleEnabled()
{
	m_page2.m_EdtOverrideScaleValue->setEnabled(m_page2.m_ChkOverrideXYScale->isChecked());
	m_pDataPara->SetOverwriteScale(m_page2.m_ChkOverrideXYScale->isChecked());
	m_bScanned = false;
}

void CXPageLoadSegyStep2::_initUiFromPara()
{
	m_page2.m_SldTrace->setValue(1);
	m_page2.m_SldTrace->setMaximum(m_pDataPara->GetTraceNumber());
	m_page2.m_SldTrace->setMinimum(1);
	m_page2.m_SpxCurrTrace->setMaximum(m_pDataPara->GetTraceNumber());
	m_page2.m_SpxCurrTrace->setMinimum(1);
	m_pTraceHeader = m_pDataPara->GetOneTraceHeader(1);
	m_page2.m_LblTraceTotal->setText("Current Trace (Total: "+QString::number(m_pDataPara->GetTraceNumber())+" )");
	m_page2.m_ChkAscIIFlip->setChecked(m_pTraceHeader->NeedFlip());
	bool IsIEEEE = m_pTraceHeader->IsIEEEFloat();
	m_page2.m_RdoFormatIEEE->setChecked(IsIEEEE);
	m_page2.m_RdoFormatIBM->setChecked(!IsIEEEE);
	m_page2.m_TbAscIIView->SetData(m_pTraceHeader);
	m_page2.m_TbAscIIView->SetParentWidget(this);
	m_page2.m_EdtInline->setText(QString::number(m_pDataPara->GetInlinePosition()));
	m_page2.m_EdtCrossLine->setText(QString::number(m_pDataPara->GetCrosslinePosition()));

	m_page2.m_EdtFileX->setText(QString::number(m_pDataPara->GetXPosition()));
	m_page2.m_EdtFileY->setText(QString::number(m_pDataPara->GetYPosition()));
	m_page2.m_CmbXyUnit->setCurrentIndex(m_pDataPara->GetUnit()-1);//same to segy file rule .so operator- 1
	m_page2.m_ChkOverrideXYScale->setChecked(m_pDataPara->IsScaleOverwrited());
	m_page2.m_EdtOverrideScaleValue->setText(QString::number(m_pDataPara->GetScale()));

	m_page2.m_EdtStartLine->setText(QString::number(m_pDataPara->GetValidStartLine()));
	m_page2.m_EdtEndLine->setText(QString::number(m_pDataPara->GetValidEndLine()));	

	// Thread Is Finished
	if(m_bScanned)
	{
		setButtonText(QWizard::NextButton,"Next");
	}
	else
	{
		setButtonText(QWizard::NextButton,"Scan");
	}
	_connect();

	//	Offset invisible.
	m_page2.labelOffset->setVisible(false);
	m_page2.lineEditOffset->setVisible(false);
	m_page2.checkBoxIrreOffset->setVisible(false);

	//	Azimuth invisible.
	m_page2.labelAzimuth->setVisible(false);
	m_page2.lineEditAzimuth->setVisible(false);
	m_page2.groupBoxAzimuth->setVisible(false);
}

void CXPageLoadSegyStep2::slotFlipData()
{
	bool bFlip = m_page2.m_ChkAscIIFlip->isChecked();
	m_pTraceHeader->SetNeedFlip(bFlip);
	slotNeedRescan();
	_updateTableWidget();
	m_bScanned = false;
}

void CXPageLoadSegyStep2::slotFloatFormatChanged()
{
	bool bIsIEEEE = m_page2.m_RdoFormatIEEE->isChecked();
	m_pTraceHeader->SetIEEEFloat(bIsIEEEE);
	int nInline,nCrossline,nX,nY;
	GetCoordinatePara(nInline,nCrossline,nX,nY);
	bool bNeedScan = false;
	QString strItemText ;
	for(int i = 0 ;  i < m_page2.m_TbAscIIView->rowCount();++i)
	{
		strItemText = m_page2.m_TbAscIIView->item(i,0)->text().split("-").at(0);
		if(strItemText == QString::number(nX)||strItemText == QString::number(nY))
		{
			if(m_page2.m_TbAscIIView->item(i,2)->text() == "Float")
			{
				bNeedScan = true;
				break;
			}
		}
	}
	if(bNeedScan)
	{
		slotNeedRescan();
	}
	_updateTableWidget();
	m_bScanned = false;
}

void CXPageLoadSegyStep2::slotTraceValueChanged(int nValue)
{
	m_pDataPara->GetOneTraceData(nValue,m_pTraceData);
	m_pTraceHeader = m_pDataPara->GetOneTraceHeader(nValue);
	m_page2.m_SpxCurrTrace->blockSignals(true);
	m_page2.m_SldTrace->blockSignals(true);
	m_page2.m_SpxCurrTrace->setValue(nValue);
	m_page2.m_SldTrace->setValue(nValue);
	m_page2.m_SpxCurrTrace->blockSignals(false);
	m_page2.m_SldTrace->blockSignals(false);
	_updateTableWidget();
	m_bScanned = false;
}

void CXPageLoadSegyStep2::GetCoordinatePara(int &nInline,int &nCrossline,int &nX,int &nY)
{
	nInline = m_page2.m_EdtInline->text().toInt();
	nCrossline = m_page2.m_EdtCrossLine->text().toInt();
	nX = m_page2.m_EdtFileX->text().toInt();
	nY = m_page2.m_EdtFileY->text().toInt();
}

bool CXPageLoadSegyStep2::IsFromScan()
{
	return m_page2.m_RdoScanSegyFile->isChecked();
}

void CXPageLoadSegyStep2::_updateTableWidget()
{
	m_page2.m_TbAscIIView->UpdateTableValue();
}

void CXPageLoadSegyStep2::initializePage()
{
	CXPageLoadSegyStep1 * pPage1 = dynamic_cast<CXPageLoadSegyStep1*>( wizard()->page(0));
	m_pDataPara =pPage1->GetDataParameters();
	delete []m_pTraceData;
	m_pTraceData = new float[m_pDataPara->GetSampleNumber()];
	m_bScanned = false;
	_initUiFromPara();
}

CXPageLoadSegyStep3::CXPageLoadSegyStep3(QWidget *parent):QWizardPage(parent)
{
	m_nInline1 = 0;
	m_nInline2  = 0;
	m_nInline3  = 0;
	m_nXline1  = 0;
	m_nXline2  = 0;
	m_nXline3  = 0;

	m_pUTMTool = NULL;
	m_pOriUTMTool = NULL;
	m_page3.setupUi(this);
}

CXPageLoadSegyStep3::~CXPageLoadSegyStep3(void)
{
	delete m_pOriUTMTool;
}

void CXPageLoadSegyStep3::cleanupPage()
{
	CXPageLoadSegyStep2 *pWizardPage = dynamic_cast<CXPageLoadSegyStep2 *>(wizard()->page(1));
	bool bThreadIsFinished = pWizardPage->IsScaned();
	if(bThreadIsFinished)
	{
		pWizardPage->setButtonText(QWizard::NextButton,"Next");
	}
	else
	{
		pWizardPage->setButtonText(QWizard::NextButton,"Scan");
	}
}

void CXPageLoadSegyStep3::initializePage ()
{
	CXPageLoadSegyStep1 * pPage1 = dynamic_cast<CXPageLoadSegyStep1*>( wizard()->page(0));
	m_pDataPara =pPage1->GetDataParameters();
	m_pUTMTool = m_pDataPara->GetUTMTool();
	if(m_pOriUTMTool == NULL)
	{
		m_pOriUTMTool = new CXSeismicUTMTool;
	}
	m_pOriUTMTool->Copy(m_pUTMTool);
	initUI();
	initConnect();
	CXPageLoadSegyStep2 * pPage2 = dynamic_cast<CXPageLoadSegyStep2*>( wizard()->page(1));
	bool bFromScan = pPage2->IsFromScan();
	m_page3.m_BtnLoad->setHidden(bFromScan);
	m_page3.label_6->setHidden(bFromScan);
	m_page3.m_LblFilePath->setHidden(bFromScan);
	m_page3.label_6->setToolTip(
		"Load 3 points coordinate and data range from an ASCII file.\n \
		The file should contain below information:\n\n \
		Point1      =	inline1, crossline1, x1, y1\n \
		Point2      =	inline2, crossline2, x2, y2\n \
		Point3      =	inline3, crossline3, x3, y3\n \
		Inline       =	start inline, total inline number, inline increment\n \
		Crossline   =	start crossline, total crossline number, crossline increment");
	// set the fourth point visible.
	m_page3.m_Grp3PointsCoordinates->setTitle(bFromScan ? "Four Points Coordinates" : "Three Points Coordinates");
	m_page3.m_LblPoint4->setVisible(bFromScan);
	m_page3.m_EdtInlinePoint4->setVisible(bFromScan);
	m_page3.m_EdtCrossLinePoint4->setVisible(bFromScan);
	m_page3.m_EdtXPoint4->setVisible(bFromScan);
	m_page3.m_EdtYPoint4->setVisible(bFromScan);
}

void CXPageLoadSegyStep3::initUI()
{
	int nXLine = m_pOriUTMTool->GetCrosslineNum();;
	int nInline= m_pOriUTMTool->GetInlineNum();

	double  p1x, p1y, p2x, p2y, p3x, p3y,p4x, p4y;
	m_pOriUTMTool->IJToXY(0, 0, p1x, p1y);
	m_pOriUTMTool->IJToXY(0, nXLine - 1, p2x,  p2y );
	m_pOriUTMTool->IJToXY(nInline - 1, 0, p3x,  p3y );
	m_pOriUTMTool->IJToXY(nInline - 1, nXLine - 1, p4x,  p4y );

	std::vector<QPointF> vec;
	vec.push_back(QPointF(p1x, p1y));
	vec.push_back(QPointF(p2x, p2y));
	vec.push_back(QPointF(p3x, p3y));
	vec.push_back(QPointF(p4x, p4y));

	m_page3.m_UtmToolView->SetPoints(vec);
	m_page3.m_UtmToolView->update();

	m_pOriUTMTool->IJToLine(0, 0, m_nInline1, m_nXline1);
	m_pOriUTMTool->IJToLine(0, nXLine - 1, m_nInline2, m_nXline2);
	m_pOriUTMTool->IJToLine(nInline - 1, 0,  m_nInline3, m_nXline3);

	int nInline4 = 0, nXline4 = 0;
	m_pOriUTMTool->IJToLine(nInline - 1, nXLine - 1, nInline4, nXline4);

	//Point 1
	m_page3.m_EdtInlinePoint1->setText(QString::number(m_nInline1));
	m_page3.m_EdtCrossLinePoint1->setText(QString::number(m_nXline1));
	m_page3.m_EdtXPoint1->setText(QString::number(p1x, 'f', 2));
	m_page3.m_EdtYPoint1->setText(QString::number(p1y, 'f', 2));

	//Point 2
	m_page3.m_EdtInlinePoint2->setText(QString::number(m_nInline2));
	m_page3.m_EdtCrossLinePoint2->setText(QString::number(m_nXline2));
	m_page3.m_EdtXPoint2->setText(QString::number(p2x, 'f', 2));
	m_page3.m_EdtYPoint2->setText(QString::number(p2y, 'f', 2));

	//Point 3
	m_page3.m_EdtInlinePoint3->setText(QString::number(m_nInline3));
	m_page3.m_EdtCrossLinePoint3->setText(QString::number(m_nXline3));
	m_page3.m_EdtXPoint3->setText(QString::number(p3x, 'f', 2));
	m_page3.m_EdtYPoint3->setText(QString::number(p3y, 'f', 2));

	//Point 4
	m_page3.m_EdtInlinePoint4->setText(QString::number(nInline4));
	m_page3.m_EdtCrossLinePoint4->setText(QString::number(nXline4));
	m_page3.m_EdtXPoint4->setText(QString::number(p4x, 'f', 2));
	m_page3.m_EdtYPoint4->setText(QString::number(p4y, 'f', 2));

	//Grid information

	m_page3.m_EdtFirstInline->setText(QString::number(m_pOriUTMTool->GetFirstInline()));
	m_page3.m_EdtInlineIncrement->setText(QString::number(m_pOriUTMTool->GetInlineIncrement()));
	m_page3.m_EdtInlineNumber->setText(QString::number(m_pOriUTMTool->GetInlineNum()));
	m_page3.m_EdtFirstCrossLine->setText(QString::number(m_pOriUTMTool->GetFirstCrossline()));
	m_page3.m_EdtCrossLineIncrement->setText(QString::number(m_pOriUTMTool->GetCrosslineIncrement()));
	m_page3.m_EdtCrosslineNumber->setText(QString::number(m_pOriUTMTool->GetCrosslineNum()));
	m_page3.m_EdtInlineSpace->setText(vtos(m_pOriUTMTool->GetInlineInterval(),4));
	m_page3.m_EdtCrossSpace->setText(vtos(m_pOriUTMTool->GetCrosslineInterval(),4));

	if (m_pDataPara->IsAzimuth())
	{
		m_page3.lineEditStartOffset->setText(QString::number(m_pDataPara->GetStartOffset()));
		m_page3.labelOffsetInc->setText("Farest Offset (m)");
		m_page3.lineEditOffsetInc->setText(QString::number(m_pDataPara->GetEndOffset()));
		m_page3.labelOffsetNumber->setVisible(false);
		m_page3.lineEditOffsetNumber->setVisible(false);
		m_page3.lineEditMinAzim->setText(QString::number(m_pDataPara->GetMinAzim()));
		m_page3.lineEditMaxAzim->setText(QString::number(m_pDataPara->GetMaxAzim()));
	}
	else if (m_pDataPara->IsPrestack())
	{
		m_page3.labelMinAzim->setVisible(false);
		m_page3.labelMaxAzim->setVisible(false);
		m_page3.lineEditMinAzim->setVisible(false);
		m_page3.lineEditMaxAzim->setVisible(false);

		if (m_pDataPara->IsIrregular())
		{
			m_page3.lineEditStartOffset->setText(QString::number(m_pDataPara->GetStartOffset()));
			m_page3.labelOffsetInc->setText("Farest Offset (m)");
			m_page3.lineEditOffsetInc->setText(QString::number(m_pDataPara->GetEndOffset()));
			m_page3.labelOffsetNumber->setVisible(false);
			m_page3.lineEditOffsetNumber->setVisible(false);
		}
		else
		{
			float fStartOffset, fOffsetInc;
			m_pDataPara->GetOffsetInfo(fStartOffset, fOffsetInc);

			m_page3.lineEditStartOffset->setText(QString::number(fStartOffset));
			m_page3.lineEditOffsetInc->setText(QString::number(fOffsetInc));
			m_page3.lineEditOffsetNumber->setText(QString::number(m_pDataPara->GetOffsetNumber()));
		}
	}
	else
	{
		m_page3.labelMinAzim->setVisible(false);
		m_page3.labelMaxAzim->setVisible(false);
		m_page3.lineEditMinAzim->setVisible(false);
		m_page3.lineEditMaxAzim->setVisible(false);

		m_page3.labelStartOffset->setVisible(false);
		m_page3.lineEditStartOffset->setVisible(false);
		m_page3.labelOffsetInc->setVisible(false);
		m_page3.lineEditOffsetInc->setVisible(false);
		m_page3.labelOffsetNumber->setVisible(false);
		m_page3.lineEditOffsetNumber->setVisible(false);
		m_page3.labelMinAzim->setVisible(false);
		m_page3.lineEditMinAzim->setVisible(false);
		m_page3.labelMaxAzim->setVisible(false);
		m_page3.lineEditMaxAzim->setVisible(false);
	}

	m_page3.lineEditMaxFold->setText(QString::number(m_pDataPara->GetMaxFold()));

	//QString strUnitNameXY = GetProjectUnitNameXY();

	//m_page3.m_LblInLineUnit->setText("Inline Space("+strUnitNameXY +"):");
	//m_page3.m_LblCrossSpaceUnit->setText("Crossline Space("+strUnitNameXY+"):");
	//m_page3.label_11->setText("X("+strUnitNameXY+"):");
	//m_page3.label_12->setText("Y("+strUnitNameXY+"):");

	//Set Data range editor read only when it from scan file.
	CXPageLoadSegyStep2 * pPage2 = dynamic_cast<CXPageLoadSegyStep2*>( wizard()->page(1));
	bool bFromScanFile = pPage2->IsFromScan();

	//Point 1
	m_page3.m_EdtInlinePoint1->setReadOnly(bFromScanFile);
	m_page3.m_EdtCrossLinePoint1->setReadOnly(bFromScanFile);
	//Point 2
	m_page3.m_EdtInlinePoint2->setReadOnly(bFromScanFile);
	m_page3.m_EdtCrossLinePoint2->setReadOnly(bFromScanFile);
	m_page3.m_EdtInlinePoint3->setReadOnly(bFromScanFile);
	m_page3.m_EdtCrossLinePoint3->setReadOnly(bFromScanFile);

	m_page3.m_EdtFirstInline->setReadOnly(bFromScanFile);
	m_page3.m_EdtInlineIncrement->setReadOnly(bFromScanFile);
	m_page3.m_EdtInlineNumber->setReadOnly(bFromScanFile);
	m_page3.m_EdtFirstCrossLine->setReadOnly(bFromScanFile);
	m_page3.m_EdtCrossLineIncrement->setReadOnly(bFromScanFile);
	m_page3.m_EdtCrosslineNumber->setReadOnly(bFromScanFile);
	m_page3.m_EdtInlineSpace->setReadOnly(bFromScanFile);
	m_page3.m_EdtInlineSpace->setReadOnly(bFromScanFile);


	// set input data validator
	QDoubleValidator *pDoubleValidator = new QDoubleValidator(this);
	QIntValidator *pIntValidator = new QIntValidator(this);
	//Point 1
	m_page3.m_EdtInlinePoint1->setValidator(pIntValidator);
	m_page3.m_EdtCrossLinePoint1->setValidator(pIntValidator);
	m_page3.m_EdtXPoint1->setValidator(pDoubleValidator);
	m_page3.m_EdtYPoint1->setValidator(pDoubleValidator);

	//Point 2
	m_page3.m_EdtInlinePoint2->setValidator(pIntValidator);
	m_page3.m_EdtCrossLinePoint2->setValidator(pIntValidator);
	m_page3.m_EdtXPoint2->setValidator(pDoubleValidator);
	m_page3.m_EdtYPoint2->setValidator(pDoubleValidator);

	//Point 3
	m_page3.m_EdtInlinePoint3->setValidator(pIntValidator);
	m_page3.m_EdtCrossLinePoint3->setValidator(pIntValidator);
	m_page3.m_EdtXPoint3->setValidator(pDoubleValidator);
	m_page3.m_EdtYPoint3->setValidator(pDoubleValidator);

	//Grid information

	m_page3.m_EdtFirstInline->setValidator(pIntValidator);
	m_page3.m_EdtInlineIncrement->setValidator(pIntValidator);
	m_page3.m_EdtInlineNumber->setValidator(pIntValidator);
	m_page3.m_EdtFirstCrossLine->setValidator(pIntValidator);
	m_page3.m_EdtCrossLineIncrement->setValidator(pIntValidator);
	m_page3.m_EdtCrosslineNumber->setValidator(pIntValidator);
	m_page3.m_EdtInlineSpace->setValidator(pDoubleValidator);
	m_page3.m_EdtInlineSpace->setValidator(pDoubleValidator);
}

void CXPageLoadSegyStep3::UpdateUiPara()
{
	int nInline1    = m_page3.m_EdtInlinePoint1->text().toInt();
	int nInline2    = m_page3.m_EdtInlinePoint2->text().toInt();
	int	nInline3    = m_page3.m_EdtInlinePoint3->text().toInt();
	int nXline1   = m_page3.m_EdtCrossLinePoint1->text().toInt();
	int nXline2   = m_page3.m_EdtCrossLinePoint2->text().toInt();
	int nXline3   = m_page3.m_EdtCrossLinePoint3->text().toInt();

	float fUtmX1      = m_page3.m_EdtXPoint1->text().toDouble();
	float fUtmX2      = m_page3.m_EdtXPoint2->text().toDouble();
	float fUtmX3      = m_page3.m_EdtXPoint3->text().toDouble();
	float fUtmY1      = m_page3.m_EdtYPoint1->text().toDouble();
	float fUtmY2      = m_page3.m_EdtYPoint2->text().toDouble();
	float fUtmY3      = m_page3.m_EdtYPoint3->text().toDouble();

	int nLineInc		= m_page3.m_EdtInlineIncrement->text().toInt();
	int nCrossLineInc	= m_page3.m_EdtCrossLineIncrement->text().toInt();

	int nXLineNumber =	m_page3.m_EdtCrosslineNumber->text().toInt();
	int nInlineNumber=	m_page3.m_EdtInlineNumber->text().toInt();

	m_pUTMTool->InitCoordinates(nInline1, nXline1, fUtmX1, fUtmY1,nInline2, nXline2, fUtmX2, fUtmY2, nInline3, nXline3, fUtmX3, fUtmY3); 
	double  p1x, p1y, p2x, p2y, p3x, p3y,p4x, p4y;
	m_pUTMTool->IJToXY(0, 0, p1x, p1y);
	m_pUTMTool->IJToXY(0, nXLineNumber - 1, p2x,  p2y );
	m_pUTMTool->IJToXY(nInlineNumber - 1, 0, p3x,  p3y );
	m_pUTMTool->IJToXY(nInlineNumber - 1, nXLineNumber - 1, p4x,  p4y );

	std::vector<QPointF> vec;
	vec.push_back(QPointF(p1x, p1y));
	vec.push_back(QPointF(p2x, p2y));
	vec.push_back(QPointF(p3x, p3y));
	vec.push_back(QPointF(p4x, p4y));
	m_page3.m_UtmToolView->SetPoints(vec);
	m_page3.m_UtmToolView->update();
}

void CXPageLoadSegyStep3::initConnect()
{
	QList<QLineEdit*> listLineEdit = findChildren<QLineEdit*>();
	foreach(QLineEdit *pLineEdit, listLineEdit)
	{
		connect(pLineEdit,SIGNAL(textChanged (const QString &)),this,SLOT(UpdateUiPara()),Qt::UniqueConnection);
	}
}

bool CXPageLoadSegyStep3::validatePage()
{
	if(m_pUTMTool->GetNI() != 0)
	{
		//	Already scanned the data and UTM be initialized.
		int nInline1    = m_page3.m_EdtInlinePoint1->text().toInt();
		int nInline2    = m_page3.m_EdtInlinePoint2->text().toInt();
		int	nInline3    = m_page3.m_EdtInlinePoint3->text().toInt();
		int nXline1   = m_page3.m_EdtCrossLinePoint1->text().toInt();
		int nXline2   = m_page3.m_EdtCrossLinePoint2->text().toInt();
		int nXline3   = m_page3.m_EdtCrossLinePoint3->text().toInt();

		float fUtmX1      = m_page3.m_EdtXPoint1->text().toDouble();
		float fUtmX2      = m_page3.m_EdtXPoint2->text().toDouble();
		float fUtmX3      = m_page3.m_EdtXPoint3->text().toDouble();
		float fUtmY1      = m_page3.m_EdtYPoint1->text().toDouble();
		float fUtmY2      = m_page3.m_EdtYPoint2->text().toDouble();
		float fUtmY3      = m_page3.m_EdtYPoint3->text().toDouble();

		int nLineInc		= m_page3.m_EdtInlineIncrement->text().toInt();
		int nCrossLineInc	= m_page3.m_EdtCrossLineIncrement->text().toInt();

		int nXLine = m_pUTMTool->GetCrosslineNum();;
		int nInline= m_pUTMTool->GetInlineNum();
		bool bInitResult =  m_pUTMTool->InitSize( nInline1, nInline, nLineInc, nXline1, nXLine, nCrossLineInc);
		if(!bInitResult)
		{
			QMessageBox::information(this,"Load 3D Segy Data...","Input line numbers are invalid.",QMessageBox::Ok);
			return bInitResult;
		}
		bInitResult =  m_pUTMTool->InitCoordinates(nInline1, nXline1, fUtmX1, fUtmY1, 
			nInline2, nXline2, fUtmX2, fUtmY2, nInline3, nXline3, fUtmX3, fUtmY3);

		if(!bInitResult)
		{
			QMessageBox::information(this,"Load 3D Segy Data...","Input coordinate numbers are invalid",QMessageBox::Ok);		
			return bInitResult;
		}
	}
	else
	{
		//	Not scanned the data, UTM has not be initialized yet.
		int nInline1    = m_page3.m_EdtInlinePoint1->text().toInt();
		int nInline2    = m_page3.m_EdtInlinePoint2->text().toInt();
		int	nInline3    = m_page3.m_EdtInlinePoint3->text().toInt();
		int nXline1   = m_page3.m_EdtCrossLinePoint1->text().toInt();
		int nXline2   = m_page3.m_EdtCrossLinePoint2->text().toInt();
		int nXline3   = m_page3.m_EdtCrossLinePoint3->text().toInt();

		float fUtmX1      = m_page3.m_EdtXPoint1->text().toDouble();
		float fUtmX2      = m_page3.m_EdtXPoint2->text().toDouble();
		float fUtmX3      = m_page3.m_EdtXPoint3->text().toDouble();
		float fUtmY1      = m_page3.m_EdtYPoint1->text().toDouble();
		float fUtmY2      = m_page3.m_EdtYPoint2->text().toDouble();
		float fUtmY3      = m_page3.m_EdtYPoint3->text().toDouble();

		int nFLine		= m_page3.m_EdtFirstInline->text().toInt();
		int nLineInc	= m_page3.m_EdtInlineIncrement->text().toInt();
		int nInline		= m_page3.m_EdtInlineNumber->text().toInt();
		int	nFXLine		= m_page3.m_EdtFirstCrossLine->text().toInt();
		int nXLineInc	= m_page3.m_EdtCrossLineIncrement->text().toInt();
		int nXLine		= m_page3.m_EdtCrosslineNumber->text().toInt();

		bool bInitResult =  m_pUTMTool->InitSize( nFLine, nInline, nLineInc, nFXLine, nXLine, nXLineInc);
		if(!bInitResult)
		{
			QMessageBox::information(this,"Load 3D Segy Data...","Input line numbers are invalid.",QMessageBox::Ok);
			return bInitResult;
		}
		bInitResult =  m_pUTMTool->InitCoordinates(nInline1, nXline1, fUtmX1, fUtmY1, 
			nInline2, nXline2, fUtmX2, fUtmY2, nInline3, nXline3, fUtmX3, fUtmY3);

		if(!bInitResult)
		{
			QMessageBox::information(this,"Load 3D Segy Data...","Input coordinate numbers are invalid",QMessageBox::Ok);		
			return bInitResult;
		}
	}

	return true;
}

CXPageLoadSegyStep4::CXPageLoadSegyStep4(QWidget *parent):QWizardPage(parent)
{
	m_pDataPara = NULL;
	m_pUTMTool = NULL;
	m_pOriUTMTool = NULL;
	m_dOrgTimeStart = 0;
	m_dOrgTimeEnd = 0;
	m_dOrgTimeStep = 0;

	m_dImpTimeStart = 0;
	m_dImpTimeEnd = 0;
	m_dImpTimeStep = 0;
	m_page4.setupUi(this);
	this->setButtonText(QWizard::FinishButton,"Finish");
}

CXPageLoadSegyStep4::~CXPageLoadSegyStep4(void)
{
	delete m_pOriUTMTool;
}

void CXPageLoadSegyStep4::initializePage ()
{
	CXPageLoadSegyStep1 * pPage1 = dynamic_cast<CXPageLoadSegyStep1*>( wizard()->page(0));
	m_pDataPara =pPage1->GetDataParameters();
	m_pUTMTool = m_pDataPara->GetUTMTool();
	if(m_pOriUTMTool == NULL)
	{
		m_pOriUTMTool = new CXSeismicUTMTool;
	}
	m_pOriUTMTool->Copy(m_pUTMTool);
	InitUI();
	initConnect();
}

void CXPageLoadSegyStep4::InitUI()
{
	// tooltip

	//Data Volume
	/*GetTemplateFacade().InitTemplatesComboBoxByFilter( m_page4.m_CmbSeismicAttribute,m_pDataPara->GetTemplate(), NULL,NULL, ESeismicAttributeCommonUse );
	m_page4.m_EdtVolumeName->setText(m_page4.m_CmbSeismicAttribute->currentText());*/
	//Original Range Can not Edit
	//Inline
	m_page4.m_EdtOrgInlineStart->setText(QString::number(m_pOriUTMTool->GetFirstInline()));
	m_page4.m_EdtOrgInlineNumber->setText(QString::number(m_pOriUTMTool->GetInlineNum()));
	m_page4.m_EdtOrgInlineStep->setText(QString::number(m_pOriUTMTool->GetInlineIncrement()));
	int nInlineEnd = m_pOriUTMTool->GetFirstInline() + (m_pOriUTMTool->GetInlineNum()-1)*m_pOriUTMTool->GetInlineIncrement();
	m_page4.m_EdtOrgInlineEnd->setText(QString::number(nInlineEnd));
	//Cross Line
	m_page4.m_EdtOrgCrossStart->setText(QString::number(m_pOriUTMTool->GetFirstCrossline()));
	m_page4.m_EdtOrgCrossNumber->setText(QString::number(m_pOriUTMTool->GetCrosslineNum()));
	m_page4.m_EdtOrgCrossStep->setText(QString::number(m_pOriUTMTool->GetCrosslineIncrement()));
	int nCrosslineEnd = m_pOriUTMTool->GetFirstCrossline() + (m_pOriUTMTool->GetCrosslineNum()-1)*m_pOriUTMTool->GetCrosslineIncrement();
	m_page4.m_EdtOrgCrossEnd->setText(QString::number(nCrosslineEnd));
	//Time
	m_dOrgTimeStart = m_pDataPara->GetStartTime();
	m_page4.m_EdtOrgTimeStart->setText(QString::number(m_dOrgTimeStart));
	m_page4.m_EdtOrgTimeNumber->setText(QString::number(m_pDataPara->GetSampleNumber()));
	m_dOrgTimeStep = m_pDataPara->GetSampleInterval();
	m_page4.m_EdtOrgTimeStep->setText(QString::number(m_dOrgTimeStep));
	m_dOrgTimeEnd = m_dOrgTimeStart + (m_pDataPara->GetSampleNumber()-1)*m_dOrgTimeStep;
	m_page4.m_EdtOrgTimeEnd->setText(QString::number(m_dOrgTimeEnd));

	if (m_pOriUTMTool->GetNI() == 1 || m_pOriUTMTool->GetNJ() == 1)
		m_page4.checkBoxDataLine->setVisible(true);
	else
		m_page4.checkBoxDataLine->setVisible(false);

	//Import Range 
	//Init Step combobox.

	int nStep = 0;
	//if(m_page4.m_EdtImpInlineStep->count() == 0)
	{
		m_page4.m_EdtImpInlineStep->blockSignals(true);
		m_page4.m_EdtImpInlineStep->clear();
		nStep = m_pOriUTMTool->GetInlineIncrement();
		m_page4.m_EdtImpInlineStep->addItem(QString::number(nStep));
		m_page4.m_EdtImpInlineStep->addItem(QString::number(nStep*2));
		m_page4.m_EdtImpInlineStep->addItem(QString::number(nStep*4));
		m_page4.m_EdtImpInlineStep->blockSignals(false);
	}

	//if(m_page4.m_EdtImpCrossStep->count() == 0)
	{
		m_page4.m_EdtImpCrossStep->blockSignals(true);
		m_page4.m_EdtImpCrossStep->clear();
		nStep = m_pOriUTMTool->GetCrosslineIncrement();
		m_page4.m_EdtImpCrossStep->addItem(QString::number(nStep));
		m_page4.m_EdtImpCrossStep->addItem(QString::number(nStep*2));
		m_page4.m_EdtImpCrossStep->addItem(QString::number(nStep*4));
		m_page4.m_EdtImpCrossStep->blockSignals(false);
	}
	//if(m_page4.m_EdtImpTimeStep->count() == 0)
	{
		m_page4.m_EdtImpTimeStep->blockSignals(true);
		m_page4.m_EdtImpTimeStep->clear();
		float fTimeStep = m_pDataPara->GetSampleInterval();
		m_page4.m_EdtImpTimeStep->addItem(QString::number(fTimeStep));
		m_page4.m_EdtImpTimeStep->addItem(QString::number(fTimeStep*2));
		m_page4.m_EdtImpTimeStep->addItem(QString::number(fTimeStep*4));
		m_page4.m_EdtImpTimeStep->blockSignals(false);
	}
	//default Import value is Same to Original Range
	//Inline
	m_page4.m_EdtImpInlineStart->setText(QString::number(m_pOriUTMTool->GetFirstInline()));
	m_page4.m_EdtImpInlineNumber->setText(QString::number(m_pOriUTMTool->GetInlineNum()));
	m_page4.m_EdtImpInlineStep->setCurrentIndex(m_page4.m_EdtImpInlineStep->findText(QString::number(m_pOriUTMTool->GetInlineIncrement())));
	m_page4.m_EdtImpInlineEnd->setText(QString::number(nInlineEnd));
	//Cross Line
	m_page4.m_EdtImpCrossStart->setText(QString::number(m_pOriUTMTool->GetFirstCrossline()));
	m_page4.m_EdtImpCrossNumber->setText(QString::number(m_pOriUTMTool->GetCrosslineNum()));
	m_page4.m_EdtImpCrossStep->setCurrentIndex(m_page4.m_EdtImpCrossStep->findText(QString::number(m_pOriUTMTool->GetCrosslineIncrement())));
	m_page4.m_EdtImpCrossEnd->setText(QString::number(nCrosslineEnd));
	//Time 
	m_dImpTimeStart = m_pDataPara->GetStartTime();
	m_page4.m_EdtImpTimeStart->setText(QString::number(m_dImpTimeStart));
	m_page4.m_EdtImpTimeNumber->setText(QString::number(m_pDataPara->GetSampleNumber()));
	m_dImpTimeStep = m_pDataPara->GetSampleInterval();
	m_page4.m_EdtImpTimeStep->setCurrentIndex(m_page4.m_EdtImpTimeStep->findText(QString::number(m_dImpTimeStep)));
	m_dImpTimeEnd = m_dOrgTimeEnd;
	m_page4.m_EdtImpTimeEnd->setText(QString::number(m_dImpTimeEnd));

	m_pDataPara->SetImportStartTime(m_pDataPara->GetStartTime());
	m_pDataPara->SetImportEndTime(m_dImpTimeEnd);
	m_pDataPara->SetImportSampleInterval(m_pDataPara->GetSampleInterval());

	m_page4.m_CmbDomainUnit->setCurrentIndex(m_page4.m_CmbDomainUnit->findText(m_pDataPara->GetZUnit()));
	//qint64  nAvailableSpace = CXSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	//m_page4.m_LblDiskSpaceAva->setText(CGmSystemInfo::GetSpaceSizeString(nAvailableSpace));

	m_page4.m_DiskSpaceRep->setText(m_pDataPara->GetRequiredSpaceString());
	QString strSeisTime = "ms";
	m_page4.label_24->setText("Time("+strSeisTime+"):");
	m_page4.label_28->setText("Time("+strSeisTime+"):");
	m_page4.m_EdtStartTimeToValue->setText(QString::number(m_dImpTimeStart));
	m_page4.m_ChkShiftStartTime->setText("Shift Start Time to (" +strSeisTime +"):");
	m_page4.m_CmbDomainUnit->setCurrentIndex(m_page4.m_CmbDomainUnit->findText(strSeisTime));

	//Survey para 
	if(m_page4.m_EdtNewSureyName->text().isEmpty())
	{		
		QString strSurName = ::GetProject()->GetUnallocatedName(m_pDataPara->GetDVName());
		m_page4.m_EdtNewSureyName->setText(strSurName);
	}

	//DV para 
	if(m_page4.m_EdtVolumeName->text().isEmpty())
	{		
		m_page4.m_EdtVolumeName->setText(m_pDataPara->GetDVName());
	}

	CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume* >(m_pDataPara->GetParentObject());

	if(!pDV)
	{
		//	No parent.
		m_page4.m_RdoCreateNew->setChecked(true);
		m_page4.m_CmbExistSurvey->setEnabled(false);

		//	Prepare the combo-box.
		QList<CXObject *> listSurvey = ::GetProject()->GetChildren(EX3DSurvey);
		for(int nIdx = 0 ; nIdx < listSurvey.size(); ++nIdx )
		{
			CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(listSurvey[nIdx]);
			if(pSurvey != NULL )
			{
				CXSeismicUTMTool& utm = pSurvey->GetUTM();
				if(utm.IsCompatible(m_pDataPara->GetUTMTool()))
				{
					m_page4.m_CmbExistSurvey->addItem(dynamic_cast<CX3DSurvey*>(listSurvey[nIdx])->GetObjectName(), QVariant(listSurvey[nIdx]->GetObjectID()));
				}
			}
		}
	}
	else
	{
		m_page4.m_RdoSavetoExist->setChecked(true);
		m_page4.m_RdoCreateNew->setEnabled(false);
		m_page4.m_EdtNewSureyName->setEnabled(false);
		QUuid surveyID = pDV->GetSurveyID();
		CXObject *pObj = ::GetObjectByID(surveyID);
		if(pObj)
			m_page4.m_CmbExistSurvey->addItem(pObj->GetObjectName(), QVariant(surveyID));
		m_page4.m_CmbExistSurvey->setCurrentIndex(0);
		slotSurveChanged(0);
	}

	if(m_page4.m_CmbExistSurvey->count() == 0)
	{
		m_page4.m_RdoSavetoExist->setDisabled(true);
		m_page4.m_CmbExistSurvey->setEnabled(false);
	}

	if (m_pDataPara->IsPrestack())
	{
		m_page4.m_ChkCreateBrickFile->setDisabled(true);
		m_page4.m_ChkCreateSliceFile->setDisabled(true);
	}
}

void CXPageLoadSegyStep4::slotSurveyNameChanged()
{
	QList<CXObject *> listSurvey = ::GetProject()->GetChildren(EX3DSurvey);
	for(int nIdx = 0 ; nIdx < listSurvey.size(); ++nIdx )
	{
		CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(listSurvey[nIdx]);
		QString strName = pSurvey->GetObjectName();
		if(strName == m_page4.m_EdtNewSureyName->text())
		{
			QMessageBox::information(this, "Importing SEGY", "The survey name already exist, please give another one.");
			return;
		}

	}
}

void CXPageLoadSegyStep4::slotSurveChanged(int nIdx)
{
	QUuid surveyID = m_page4.m_CmbExistSurvey->itemData(nIdx).toString();
	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(::GetObjectByID(surveyID));
	if(!pSurvey)
		return;

	QString strDvName = pSurvey->GetUnallocatedName(m_pDataPara->GetDVName());
	m_page4.m_EdtVolumeName->setText(strDvName);

}

void CXPageLoadSegyStep4::slotSurveModeChanged()
{
	slotSurveChanged(m_page4.m_CmbExistSurvey->currentIndex());
}

void CXPageLoadSegyStep4::initConnect()
{
	connect(m_page4.m_ChkShiftStartTime,SIGNAL(clicked()),this,SLOT(slotEnabledShiftTime()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpInlineStep,SIGNAL(currentIndexChanged( const QString &)),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpCrossStep,SIGNAL(currentIndexChanged( const QString &)),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpTimeStep,SIGNAL(currentIndexChanged( const QString &)),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);

	connect(m_page4.m_EdtImpInlineStart,SIGNAL(editingFinished ()),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpInlineEnd,SIGNAL(editingFinished ()),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpCrossStart,SIGNAL(editingFinished ()),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpCrossEnd,SIGNAL(editingFinished ()),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpTimeStart,SIGNAL(editingFinished ()),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_EdtImpTimeEnd,SIGNAL(editingFinished ()),this,SLOT(slotImportDataChanged()),Qt::UniqueConnection);
	connect(m_page4.m_CmbDomainUnit,SIGNAL(currentIndexChanged (int)),this,SLOT(slotZUnitChanged()),Qt::UniqueConnection);

	connect(m_page4.m_ChkCreateSliceFile,SIGNAL(clicked()),this,SLOT(slotEnableCreateSliceFileState()),Qt::UniqueConnection);
	connect(m_page4.m_ChkCreateBrickFile,SIGNAL(clicked()),this,SLOT(slotEnableCreateBrickFileState()),Qt::UniqueConnection);

	connect(m_page4.m_RdoTime,SIGNAL(toggled(bool)),this,SLOT(slotDomainTypeChanged()));
	connect(m_page4.m_RdoDepth,SIGNAL(toggled(bool)),this,SLOT(slotDomainTypeChanged()));

	connect(m_page4.m_EdtNewSureyName,SIGNAL(editingFinished ()),this,SLOT(slotSurveyNameChanged()),Qt::UniqueConnection);
	connect(m_page4.m_CmbExistSurvey,SIGNAL(currentIndexChanged (int)),this,SLOT(slotSurveChanged(int)),Qt::UniqueConnection);

	connect(m_page4.m_RdoSavetoExist,SIGNAL(toggled(bool)),this,SLOT(slotSurveModeChanged()));

	connect(m_page4.m_CmbSeismicAttribute,SIGNAL(currentIndexChanged(int)),this,SLOT(slotCmbTextChanged(int)));
}

void CXPageLoadSegyStep4::slotCmbTextChanged (int index)
{
	m_page4.m_EdtVolumeName->setText(m_page4.m_CmbSeismicAttribute->itemText(index));
}


bool CXPageLoadSegyStep4::validatePage ()
{
	//qint64 nDiskAva =  CGmSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	//qint64 nDiskRep =  m_pDataPara->GetRequiredSpaceValue();
	//if(nDiskAva < nDiskRep)
	//{
	//	QMessageBox::information(this,"Warning","There is no enough disk space!");
	//	return false;
	//}

	if(m_page4.m_ChkShiftStartTime->isChecked())
	{
		m_pDataPara->SetTimeShiftTo(m_page4.m_EdtStartTimeToValue->text().toFloat());
	}
	//bool isTime = m_page4.m_RdoTime->isChecked();
	//EGmUnit eProjectUnit = isTime?(::GetProject()->GetUnitSeisTime()):(::GetProject()->GetUnitZ());
	//int nCurUnit = m_page4.m_CmbDomainUnit->currentIndex();
	//EGmUnit eCurUnit;

	//if(isTime)
	//	eCurUnit = eMilliSecond;
	//else if(nCurUnit == 0)
	//{
	//	eCurUnit = eMeter;
	//}
	//else if(nCurUnit == 1)
	//{
	//	eCurUnit = eFoot;
	//}
	//else
	//{
	//	eCurUnit = eCentiMeter;
	//}
	//m_pDataPara->SetUnitZ(eCurUnit);

	m_pDataPara->SetCreateBrickFile(m_page4.m_ChkCreateBrickFile->isChecked());
	m_pDataPara->SetCreateSliceFile(m_page4.m_ChkCreateSliceFile->isChecked());
	m_pDataPara->SetDVName(m_page4.m_EdtVolumeName->text());
	//m_pDataPara->SetTemplate(GetTemplateFacade().GetCurrentTemplateIDFromComboBox( m_page4.m_CmbSeismicAttribute));
	QString strSurveyName = "";
	if(m_page4.m_RdoCreateNew->isChecked())
		strSurveyName = m_page4.m_EdtNewSureyName->text();
	else
		strSurveyName = m_page4.m_CmbExistSurvey->currentText();
	m_pDataPara->SetDestSurveyName(strSurveyName);

	m_pDataPara->SetDataLine(m_page4.checkBoxDataLine->isChecked());

	return true;
}

void CXPageLoadSegyStep4::slotDomainTypeChanged()
{
	bool isTime = m_page4.m_RdoTime->isChecked();
	QStringList list ;
	m_page4.m_CmbDomainUnit->clear();
	QString strUnitName, strDomain ;
	if(isTime)
	{
		strUnitName	= "ms";
		list <<"ms";
		m_page4.m_CmbDomainUnit->addItems(list);
		m_pDataPara->SetDomainType(eTimeDomain);
		strDomain = "Time";
	}
	else
	{
		strUnitName ="m";
		list << "m"<<"ft"<<"cm";
		m_page4.m_CmbDomainUnit->addItems(list);
		m_pDataPara->SetDomainType(eDepthDomain);
		strDomain = "Depth";
	}
	int nIndex  = m_page4.m_CmbDomainUnit->findText(strUnitName);
	m_page4.m_CmbDomainUnit->setCurrentIndex(nIndex);
	m_page4.m_ChkShiftStartTime->setText("Shift Start " + strDomain + " to (" +strUnitName +"):");
	m_page4.label_24->setText(strDomain+"("+strUnitName+"):");
	m_page4.label_28->setText(strDomain+"("+strUnitName+"):");
}

void CXPageLoadSegyStep4:: slotEnabledShiftTime()
{
	bool bIsShift = m_page4.m_ChkShiftStartTime->isChecked();
	m_page4.m_EdtStartTimeToValue->setEnabled(bIsShift);
	if(!bIsShift)
	{

	}
}

void CXPageLoadSegyStep4::slotImportDataChanged()
{
	int nInlineStep = m_page4.m_EdtImpInlineStep->currentText().toInt();
	int nCrossLineStep = m_page4.m_EdtImpCrossStep->currentText().toInt();
	double nTimeStep = m_page4.m_EdtImpTimeStep->currentText().toDouble();
	m_pDataPara->SetImportSampleInterval(nTimeStep);

	//Original Value
	int nUtmInlineStart = m_page4.m_EdtOrgInlineStart->text().toInt();
	int nUtmInlineEnd   = m_page4.m_EdtOrgInlineEnd->text().toInt();

	int nUtmCrossLineStart = m_page4.m_EdtOrgCrossStart->text().toInt();
	int nUtmCrossLineEnd = m_page4.m_EdtOrgCrossEnd->text().toInt();

	double dUtmTimeStart = m_page4.m_EdtOrgTimeStart->text().toDouble();
	double dUtmTimeEnd   = m_page4.m_EdtOrgTimeEnd->text().toDouble();

	//Import Range
	int nInLineStart = m_page4.m_EdtImpInlineStart->text().toInt();
	int nInLineEnd	 = m_page4.m_EdtImpInlineEnd->text().toInt();

	int nCrosstart = m_page4.m_EdtImpCrossStart->text().toInt();
	int nCorssEnd  = m_page4.m_EdtImpCrossEnd->text().toInt();

	double dTimeStart	 = m_page4.m_EdtImpTimeStart->text().toDouble();
	double dTimeEnd = m_page4.m_EdtImpTimeEnd->text().toDouble();

	if(	   nInLineStart < nUtmInlineStart || nInLineEnd > nUtmInlineEnd||nInLineEnd < nInLineStart //Inline valid
		|| nCrosstart < nUtmCrossLineStart || nCorssEnd > nUtmCrossLineEnd||nCorssEnd<nCrosstart//cross valid
		|| dTimeStart <dUtmTimeStart||dTimeEnd>dUtmTimeEnd||dTimeEnd<dTimeStart)
	{
		if(nInLineStart < nUtmInlineStart)
		{
			m_page4.m_EdtImpInlineStart->setText(::vtos(dUtmTimeStart,8));
		}
		if(nInLineEnd > nUtmInlineEnd )
		{
			m_page4.m_EdtImpInlineEnd->setText(QString::number(nUtmInlineEnd));
		}
		if(nInLineEnd < nInLineStart)
		{
			m_page4.m_EdtImpInlineStart->setText(::vtos(dUtmTimeStart,8));
			m_page4.m_EdtImpInlineEnd->setText(QString::number(nUtmInlineEnd));
		}
		if(nCrosstart < nUtmCrossLineStart)
		{
			m_page4.m_EdtImpCrossStart->setText(QString::number(nUtmCrossLineStart));
		}
		if(nCorssEnd > nUtmCrossLineEnd)
		{
			m_page4.m_EdtImpCrossEnd->setText(QString::number(nUtmCrossLineEnd));
		}
		if(nCorssEnd<nCrosstart)
		{
			m_page4.m_EdtImpCrossStart->setText(QString::number(nUtmCrossLineStart));
			m_page4.m_EdtImpCrossEnd->setText(QString::number(nUtmCrossLineEnd));
		}
		if(dTimeStart <dUtmTimeStart)
		{
			m_page4.m_EdtImpTimeStart->setText(::vtos(dUtmTimeStart,8));
		}
		if(dTimeEnd>dUtmTimeEnd)
		{
			m_page4.m_EdtImpTimeEnd->setText(::vtos(dUtmTimeEnd,8));
		}
		if(dTimeEnd<dTimeStart)
		{
			m_page4.m_EdtImpTimeStart->setText(::vtos(dUtmTimeStart,8));
			m_page4.m_EdtImpTimeEnd->setText(::vtos(dUtmTimeEnd,8));
		}
	}		
	else
	{
		//Adjust Import range end value.
		if((nInLineEnd - nInLineStart )%nInlineStep != 0)
		{
			nInLineEnd -= (nInLineEnd - nInLineStart )%nInlineStep;
		}
		if((nCorssEnd - nCrosstart) %nCrossLineStep != 0)
		{
			nCorssEnd -= (nCorssEnd - nCrosstart)%nCrossLineStep;
		}
		int iSamplingEndIndex = static_cast<int>((dTimeEnd - dTimeStart)/nTimeStep + 0.01);
		dTimeEnd = nTimeStep*iSamplingEndIndex + dTimeStart;

		int nInLineNumber = (nInLineEnd - nInLineStart)/nInlineStep + 1;
		int nCrossLineNumber = (nCorssEnd - nCrosstart)/nCrossLineStep + 1;
		int nTimeNumber = iSamplingEndIndex + 1;

		m_pDataPara->SetImportStartTime(dTimeStart);
		m_pDataPara->SetImportEndTime(dTimeEnd);
		m_pUTMTool->Resize(nInLineStart,nCrosstart,nInLineNumber,nCrossLineNumber,nInlineStep,nCrossLineStep);


		//qint64  nAvailableSpace = CGmSystemInfo::GetFreeDiskSpace(::GetProjectPath());
		//m_page4.m_LblDiskSpaceAva->setText(CGmSystemInfo::GetSpaceSizeString(nAvailableSpace));

		m_page4.m_DiskSpaceRep->setText(m_pDataPara->GetRequiredSpaceString());


		m_page4.m_EdtImpInlineEnd->setText(QString::number(nInLineEnd));
		m_page4.m_EdtImpCrossEnd->setText(QString::number(nCorssEnd));
		m_page4.m_EdtImpTimeEnd->setText(::vtos(dTimeEnd,8));

		m_page4.m_EdtImpInlineNumber->setText(QString::number(nInLineNumber));
		m_page4.m_EdtImpCrossNumber->setText(QString::number(nCrossLineNumber));
		m_page4.m_EdtImpTimeNumber->setText(QString::number(nTimeNumber));
	}
}

void CXPageLoadSegyStep4::slotEnableCreateSliceFileState()
{
	bool bEnabled = m_page4.m_ChkCreateSliceFile->isChecked();
	m_pDataPara->SetCreateSliceFile(bEnabled);
	//qint64  nAvailableSpace = CGmSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	//m_page4.m_LblDiskSpaceAva->setText(CGmSystemInfo::GetSpaceSizeString(nAvailableSpace));
	m_page4.m_DiskSpaceRep->setText(m_pDataPara->GetRequiredSpaceString());

}
void CXPageLoadSegyStep4::slotEnableCreateBrickFileState()
{
	bool bEnabled = m_page4.m_ChkCreateBrickFile->isChecked();
	m_pDataPara->SetCreateBrickFile(bEnabled);
	//qint64  nAvailableSpace = CGmSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	//m_page4.m_LblDiskSpaceAva->setText(CGmSystemInfo::GetSpaceSizeString(nAvailableSpace));
	m_page4.m_DiskSpaceRep->setText(m_pDataPara->GetRequiredSpaceString());
}

void CXPageLoadSegyStep4::slotZUnitChanged()
{
	bool isTime = m_page4.m_RdoTime->isChecked();

	/*EGmUnit eProjectUnit = isTime?(::GetProject()->GetUnitSeisTime()):(::GetProject()->GetUnitZ());
	int nCurUnit = m_page4.m_CmbDomainUnit->currentIndex();
	EGmUnit eCurUnit;
	if(nCurUnit == 0)
	{
		eCurUnit = isTime?eSecond:eMeter;
	}
	if(nCurUnit == 1)
	{
		eCurUnit = isTime?eMilliSecond:eFoot;
	}
	if(nCurUnit == 2)
	{
		eCurUnit = isTime?eMicroSecond:eCentiMeter;
	}*/
	QString strDomain = isTime? "Time":"Depth";
	strDomain =strDomain+"(" +(m_page4.m_CmbDomainUnit->currentText())+"):";
	m_page4.m_EdtOrgTimeStart->setText(::vtos(m_dOrgTimeStart,8));
	m_page4.m_EdtImpTimeStart->setText(::vtos(m_dImpTimeStart,8));

	int nOrgIntevalNum = m_page4.m_EdtOrgTimeNumber->text().toInt();
	double  nOrgTimeStep= m_page4.m_EdtOrgTimeStep->text().toDouble();
	double nOrgTimeEnd= m_dOrgTimeStart +(nOrgIntevalNum -1)* m_dOrgTimeStep;

	int nImpTimeStep= m_page4.m_EdtImpTimeStep->currentText().toInt();
	double nImpIntevalNum = m_page4.m_EdtImpTimeNumber->text().toDouble();
	double dOrgTimeEnd= m_dImpTimeStart +(nImpIntevalNum -1)* m_dImpTimeStep;	

	m_page4.m_EdtOrgTimeEnd->setText(::vtos(nOrgTimeEnd,8));
	m_page4.m_EdtImpTimeEnd->setText(::vtos(dOrgTimeEnd,8));
	m_page4.label_24->setText(strDomain);
	m_page4.label_28->setText(strDomain);
}