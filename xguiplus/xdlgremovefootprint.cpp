#pragma warning (push,0)
#include "xdlgremovefootprint.h"
#include "xparameterremovefootprint.h"
#include <cassert>
#include <qvalidator.h>
#include "xglobal.h"
#include "xproject.h"
#include <QMessageBox>
#include <qsvgrenderer.h>
#include <qfile.h>
#include "xprocessfactory.h"
#include "xwaitcursor.h"

#include "xseismicdatavolume.h"
#include "xwidgetfpthreshold.h"
#include "xpythonprocess.h"
#include "xthreadpythonprocess.h"
#include "xdlgcalculatingprogress.h"
#include "xbaseconsole.h"
#include "xeventconsole.h"
#include "xalgorithmutility.h"
#pragma warning(pop)


CXDlgRemoveFootprint::CXDlgRemoveFootprint(CXParameterRemoveFootprint* para, CXSeismicDataVolume* pDV, QWidget *parent)
	: QDialog(parent), m_pDV(pDV), m_pPara(para)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Remove Footprint Of Post-stack Seismic Data");

	_Init();

	_InitConnections();

	_InitChart();

	m_PythonProcess = nullptr;
	m_pPythonThread = nullptr;

	m_pOutDV = nullptr;
}

CXDlgRemoveFootprint::~CXDlgRemoveFootprint()
{
	delete m_pChartWidget;

	delete m_PythonProcess;

	if (m_pPythonThread)
		m_pPythonThread->wait();

	delete m_pPythonThread;

	delete m_pPara;
}

void CXDlgRemoveFootprint::_InitConnections()
{
	connect(m_ui.m_pSliderSlice, &QSlider::valueChanged, this, &CXDlgRemoveFootprint::slotSliceChanged);
	connect(m_ui.m_pLineEdtSliceZ, &QLineEdit::editingFinished, this, &CXDlgRemoveFootprint::slotSliceLineEdtChanged);

	connect(m_ui.m_pSliderThreshold, &QSlider::valueChanged, this, &CXDlgRemoveFootprint::slotSliderThresholdChanged);
	connect(m_ui.m_pSpinThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CXDlgRemoveFootprint::slotSpinThresholdChanged);

	connect(m_ui.m_pButtonOne, &QPushButton::clicked, this, &CXDlgRemoveFootprint::slotComputeOne);
	connect(m_ui.m_pButtonAll, &QPushButton::clicked, this, &CXDlgRemoveFootprint::slotComputeAll);
}

void CXDlgRemoveFootprint::_InitChart()
{
	m_pChartWidget = new CXWidgetFPThreshold(m_nK, m_dSamplingStart, m_dSamplingRate);

	m_ui.graphicsView->setChart(m_pChartWidget->GetChart());
	m_ui.graphicsView->setRenderHint(QPainter::Antialiasing);
	m_pChartWidget->GetChart()->setVisible(true);
}


void CXDlgRemoveFootprint::slotSliceChanged(int v)
{
	disconnect(m_ui.m_pLineEdtSliceZ, &QLineEdit::editingFinished, this, &CXDlgRemoveFootprint::slotSliceLineEdtChanged);

	int sliceIndex = m_ui.m_pSliderSlice->value();
	double z = m_dSamplingStart + sliceIndex * m_dSamplingRate;
	m_ui.m_pLineEdtSliceZ->setText(QString::number(z, 'f', 2));

	connect(m_ui.m_pLineEdtSliceZ, &QLineEdit::editingFinished, this, &CXDlgRemoveFootprint::slotSliceLineEdtChanged);
}

void CXDlgRemoveFootprint::slotSliceLineEdtChanged()
{
	disconnect(m_ui.m_pSliderSlice, &QSlider::valueChanged, this, &CXDlgRemoveFootprint::slotSliceChanged);

	double z = m_ui.m_pLineEdtSliceZ->text().toDouble();
	int index = static_cast<int>((z - m_dSamplingStart) / m_dSamplingRate + 0.1);
	index = qBound(0, index, m_nK - 1);
	m_ui.m_pSliderSlice->setValue(index);

	z = m_dSamplingStart + index * m_dSamplingRate;
	m_ui.m_pLineEdtSliceZ->setText(QString::number(z, 'f', 2));

	connect(m_ui.m_pSliderSlice, &QSlider::valueChanged, this, &CXDlgRemoveFootprint::slotSliceChanged);
}

void CXDlgRemoveFootprint::slotSliderThresholdChanged(int v)
{
	disconnect(m_ui.m_pSpinThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CXDlgRemoveFootprint::slotSpinThresholdChanged);

	int index = m_ui.m_pSliderThreshold->value();
	double dValue = index * 0.01;
	m_ui.m_pSpinThreshold->setValue(dValue);
	
	connect(m_ui.m_pSpinThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CXDlgRemoveFootprint::slotSpinThresholdChanged);
}

void CXDlgRemoveFootprint::slotSpinThresholdChanged(double dval)
{
	disconnect(m_ui.m_pSliderThreshold, &QSlider::valueChanged, this, &CXDlgRemoveFootprint::slotSliderThresholdChanged);

	double d = m_ui.m_pSpinThreshold->value();
	int index = static_cast<int>(d * 100 + 0.1);
	m_ui.m_pSliderThreshold->setValue(index);

	connect(m_ui.m_pSliderThreshold, &QSlider::valueChanged, this, &CXDlgRemoveFootprint::slotSliderThresholdChanged);
}


void CXDlgRemoveFootprint::_Init()
{
	double dZStart, dZStep, dZEnd;
	m_pDV->GetSamplingRange(m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate);
	m_nI = m_pDV->GetInlineQty();
	m_nJ = m_pDV->GetXlineQty();
	m_nK = m_pDV->GetSamplingQty();

	m_ui.m_pSliderSlice->setRange(0, m_nK-1);
	m_ui.m_pLineEdtSliceZ->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtSliceZ->setText(QString::number(m_dSamplingStart, 'f', 2));
	m_ui.m_pSliderSlice->setValue(0);

	m_ui.m_pCombWavelet->setCurrentText(m_pPara->GetWavelet());
	m_ui.m_pCombDirection->setCurrentText(m_pPara->GetDirection());
	m_ui.m_pCombLevel->setCurrentText(QString::number(m_pPara->GetLevel()));
	m_ui.m_pCombWindow->setCurrentText(QString::number(m_pPara->GetWindow()));

	m_ui.m_pSliderThreshold->setRange(0, 400);
	m_ui.m_pSliderThreshold->setValue(100);
	m_ui.m_pSpinThreshold->setRange(0., 4.0);
	m_ui.m_pSpinThreshold->setSingleStep(0.01);
	m_ui.m_pSpinThreshold->setValue(1.0);
}

void CXDlgRemoveFootprint::_UpdatePara()
{
	m_pPara->SetWavelet(m_ui.m_pCombWavelet->currentText());
	m_pPara->SetDirection(m_ui.m_pCombDirection->currentText());
	m_pPara->SetLevel(m_ui.m_pCombLevel->currentText().toInt());
	m_pPara->SetWindow(m_ui.m_pCombWindow->currentText().toInt());
	m_pPara->SetThreshold(m_ui.m_pSpinThreshold->value());
}

QString CXDlgRemoveFootprint::_RetrieveCurrentSliceData()
{
	double dZ = m_dSamplingStart + m_ui.m_pSliderSlice->value()* m_dSamplingRate;
	vector<float> vBuff(m_nI*m_nJ);
	if (!m_pDV->ReadSlice(dZ, &vBuff[0]))
		return "";

	QString sliceFileName = QUuid::createUuid().toString() + ".dat";

	QFile qFile(::GetProject()->GetProjectDataPath() + sliceFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return "";

	qFile.write((char*)&vBuff[0], sizeof(float)*m_nI*m_nJ);
	qFile.close();

	return sliceFileName;
	
}


void CXDlgRemoveFootprint::accept()
{

	QDialog::accept();
}


void CXDlgRemoveFootprint::slotComputeOne()
{
	_UpdatePara();

	QString inDataFileName = _RetrieveCurrentSliceData();
	if (inDataFileName == "")
	{
		QMessageBox::warning(0, ::g_strProductName, "Cannot read the seismic data.");
		return;
	}

	QString outputImageFileName = QUuid::createUuid().toString() + ".svg";
	m_strSVGFileName = outputImageFileName;

	QString strStopFileName = ::GetProject()->GetProjectDataPath() + QUuid::createUuid().toString() + ".dat";
	QString strProgressFileName = ::GetProject()->GetProjectDataPath() + QUuid::createUuid().toString() + ".dat";

	QJsonObject jsonObject;
	jsonObject.insert("nI", QJsonValue(m_nI));
	jsonObject.insert("nJ", QJsonValue(m_nJ));

	jsonObject.insert("ProjectDataPath", QJsonValue(::GetProject()->GetProjectDataPath()));

	jsonObject.insert("InDataFileName", QJsonValue(inDataFileName));
	jsonObject.insert("OutputImageFileName", QJsonValue(outputImageFileName));

	jsonObject.insert("stopFileName", QJsonValue(strStopFileName));
	jsonObject.insert("progressFileName", QJsonValue(strProgressFileName));

	jsonObject.insert("threshold", QJsonValue(m_pPara->GetThreshold()));
	jsonObject.insert("level", QJsonValue(m_pPara->GetLevel()));
	jsonObject.insert("window", QJsonValue(m_pPara->GetWindow()));
	jsonObject.insert("wavelet", QJsonValue(m_pPara->GetWavelet()));
	jsonObject.insert("direction", QJsonValue(m_pPara->GetDirection()));

	if (m_PythonProcess)
	{
		delete m_PythonProcess;
		m_PythonProcess = nullptr;
	}

	m_PythonProcess = new CXPythonProcess("compute_one_fp");
	if (!m_PythonProcess->StartProcessWithModel(jsonObject))
		return;

	QString strMng = "Remove Footprint";
	QList<CXObject*> listLocking, listDeleting;
	listLocking.append(m_pDV);

	if (m_pPythonThread)
	{
		m_pPythonThread->wait();
		delete m_pPythonThread;
		m_pPythonThread = nullptr;
	}
	
	m_pPythonThread = new CXThreadPythonProcess(listLocking, listDeleting, strStopFileName, strProgressFileName, strMng);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pPythonThread, pParentWidget);

	connect(pProgress, &CXDlgCalculatingProgress::signalFinishedComputing, this, &CXDlgRemoveFootprint::slotFinishedOneFP);

	pProgress->show();
	m_pPythonThread->start();
	pProgress->exec();
}
void CXDlgRemoveFootprint::slotComputeAll()
{
	_UpdatePara();

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	if (m_pOutDV != nullptr)
		delete m_pOutDV;

	m_pOutDV = new CXSeismicDataVolume(m_pDV->GetUTM(), dSamplingStart, dSamplingEnd, dSamplingRate, "Footprint removed");

	QString strStopFileName = ::GetProject()->GetProjectDataPath() + QUuid::createUuid().toString() + ".dat";
	QString strProgressFileName = ::GetProject()->GetProjectDataPath() + QUuid::createUuid().toString() + ".dat";

	QJsonObject jsonObject;
	jsonObject.insert("nI", QJsonValue(m_nI));
	jsonObject.insert("nJ", QJsonValue(m_nJ));
	jsonObject.insert("nK", QJsonValue(m_nK));

	jsonObject.insert("ProjectDataPath", QJsonValue(::GetProject()->GetProjectDataPath()));

	jsonObject.insert("InputDVSliceFileName", QJsonValue(m_pDV->GetSliceFileName()));
	jsonObject.insert("OutputDVTraceFileName", QJsonValue(m_pOutDV->GetTraceFileName()));

	jsonObject.insert("stopFileName", QJsonValue(strStopFileName));
	jsonObject.insert("progressFileName", QJsonValue(strProgressFileName));

	QList<double> listX, listY;
	m_pChartWidget->GetXYThresholdArray(listX, listY);

	QVariantList listXV, listYV;
	for (int i = 0; i < listX.size(); ++i)
	{
		listXV.append(listX[i]);
		listYV.append(listY[i]);
	}

	if (listXV.isEmpty())
	{
		QMessageBox::warning(0, ::g_strProductName, "Remove at least one slice first.");
		return;
	}

	jsonObject.insert("threshold_x_array", QJsonArray::fromVariantList(listXV));
	jsonObject.insert("threshold_y_array", QJsonArray::fromVariantList(listYV));


	jsonObject.insert("level", QJsonValue(m_pPara->GetLevel()));
	jsonObject.insert("window", QJsonValue(m_pPara->GetWindow()));
	jsonObject.insert("wavelet", QJsonValue(m_pPara->GetWavelet()));
	jsonObject.insert("direction", QJsonValue(m_pPara->GetDirection()));

	if (m_PythonProcess)
	{
		delete m_PythonProcess;
		m_PythonProcess = nullptr;
	}

	m_PythonProcess = new CXPythonProcess("compute_all_fp");
	if (!m_PythonProcess->StartProcessWithModel(jsonObject))
		return;

	QString strMng = "Remove Footprint";
	QList<CXObject*> listLocking, listDeleting;
	listLocking.append(m_pDV);

	if (m_pPythonThread)
	{
		m_pPythonThread->wait();
		delete m_pPythonThread;
		m_pPythonThread = nullptr;
	}

	m_pPythonThread = new CXThreadPythonProcess(listLocking, listDeleting, strStopFileName, strProgressFileName, strMng);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pPythonThread, pParentWidget);

	connect(pProgress, &CXDlgCalculatingProgress::signalFinishedComputing, this, &CXDlgRemoveFootprint::slotFinishedAllFP);

	pProgress->show();
	m_pPythonThread->start();
	pProgress->exec();
}

void CXDlgRemoveFootprint::slotFinishedOneFP()
{
	delete m_pPythonThread;
	m_pPythonThread = nullptr;

	QString strFileName = ::GetProject()->GetProjectDataPath() + m_strSVGFileName;
	if (!QFile::exists(strFileName))
		return;

	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	QByteArray arr = qFile.readAll();
	if (arr.isEmpty())
		return;

	m_ui.m_pSvgWidget->load(arr);

	auto size = m_ui.m_pSvgWidget->sizeHint();

	auto size2 = m_ui.m_pSvgWidget->size();
	
	if (m_ui.m_pSvgWidget->renderer())
	{
		
	}

	double x = m_ui.m_pLineEdtSliceZ->text().toDouble();
	double y = m_ui.m_pSpinThreshold->value();

	m_pChartWidget->AddPoint(x, y);

	m_ui.graphicsView->repaint();


}

void CXDlgRemoveFootprint::slotFinishedAllFP()
{
	if (!m_pOutDV)
		return;


	m_pOutDV->SetObjectName(m_pDV->GetUnallocatedName(m_pOutDV->GetObjectName()));
	m_pDV->AddChild(m_pOutDV);

	m_pOutDV->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	if (m_pOutDV)
		CXAlgorithmUtility::CalculateHistogram(m_pOutDV->GetTraceFileName(), m_pOutDV->GetSamplingQty(), m_pOutDV);

	// Delete the thread
	delete m_pPythonThread;
	m_pPythonThread = nullptr;


}



