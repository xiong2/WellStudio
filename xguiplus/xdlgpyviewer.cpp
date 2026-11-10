#include <qvalidator.h>
#include "xdlgpyviewer.h"
#include "xthreadpyramid.h"
#include "xdlgpyramid.h"

XDlgPyViewer::XDlgPyViewer(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEdit->setValidator(new QIntValidator(0, 360, this));
	connect(ui.pushButtonBO, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.pushButtonBW, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.pushButtonFO, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.pushButtonFW, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.pushButtonStop, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.lineEdit, SIGNAL(textChanged()), this, SLOT(slotSetAng()));
	connect(&m_qTimer, SIGNAL(timeout()), this, SLOT(slotPlay()));
}

XDlgPyViewer::~XDlgPyViewer()
{
	if (!m_pData)
		delete[]m_pData;

	if (!m_pFData)
		delete[]m_pFData;

	if (!m_pImgData)
		delete[]m_pImgData;
}

void XDlgPyViewer::ResizeFrame(int iWWidth, int iWHeight, int iIWidth, int iIHeight, float *pData)
{
	m_iWidth = iIWidth;
	m_iHeight = iIHeight;
	if (m_pData)
		delete[]m_pData;
	m_pData = pData;

	if (m_pFData)
		delete[]m_pFData;
	m_pFData = new float[m_iWidth * m_iHeight];

	if (m_pImgData)
		delete[]m_pImgData;
	m_pImgData = new unsigned int[m_iWidth * m_iHeight];

	float fRatio = iWHeight * 1. / iWWidth;
	if (iWWidth < 280)
	{
		iWWidth = 280;
		iWHeight = iWWidth * fRatio;
	}
	this->resize(iWWidth + 20, 2 * iWHeight + 100);

	calVariance();
	//updateView();
}

void XDlgPyViewer::slotPlay()
{
	if (sender() == ui.pushButtonBO)
	{
		m_qTimer.stop();
		m_iAng -= qAbs(m_iAStep);
	}
	else if (sender() == ui.pushButtonBW)
	{
		m_iAStep = 0 - qAbs(m_iAStep);
		m_qTimer.start(m_iTimeIntv);
	}
	else if (sender() == ui.pushButtonFO)
	{
		m_qTimer.stop();
		m_iAng += qAbs(m_iAStep);
	}
	else if (sender() == ui.pushButtonFW)
	{
		m_iAStep = qAbs(m_iAStep);
		m_qTimer.start(m_iTimeIntv);
	}
	else if (sender() == ui.pushButtonStop)
	{
		m_qTimer.stop();
	}
	else if (sender() == &m_qTimer)
	{
		m_iAng += m_iAStep;
	}

	if (m_iAng > 360)
		m_iAng -= 360;
	else if (m_iAng < 0)
		m_iAng += 360;

	updateView();
}

void XDlgPyViewer::slotSetAng()
{
	m_qTimer.stop();

	m_iAng = ui.lineEdit->text().toInt();
	updateView();
}

void XDlgPyViewer::updateView()
{
	ui.lineEdit->blockSignals(true);
	ui.lineEdit->setText(QString::number(m_iAng));
	ui.lineEdit->blockSignals(false);

	Pyramid_Filter::S_Filtering(m_iWidth, m_iHeight, m_pData, m_pFData, (double)m_iAng);
	qint64 iLen = m_iWidth * m_iHeight;
	float dMin = m_pFData[0], dMax = m_pFData[0];
	for (qint64 k = 1; k < iLen; k++)
	{
		dMin = dMin < m_pFData[k] ? dMin : m_pFData[k];
		dMax = dMax > m_pFData[k] ? dMax : m_pFData[k];
	}
	float dSpan = dMax - dMin;
	if (dSpan == 0.)
		return;

	for (auto i = 0; i < m_iWidth; ++i)
	{
		for (auto k = 0; k < m_iHeight; ++k)
		{
			double dCurrValue = static_cast<double>(m_pFData[i * m_iHeight + k]);

			int index;
			index = static_cast<int>((dCurrValue - dMin) / dSpan * 254);
			index = 254 - qBound(0, index, 254);

			//m_pImgData[(m_iHeight - 1 - k) * m_iWidth + i] = QColor(index, index, index).rgba();
			m_pImgData[k * m_iWidth + i] = QColor(index, index, index).rgba();
		}
	}

	QImage image(reinterpret_cast<uchar*>(m_pImgData), m_iWidth, m_iHeight, QImage::Format_RGB32);
	ui.frameBro->SetImage(image);

	update();
}

void XDlgPyViewer::slotSpeed()
{
	m_iTimeIntv = ui.horizontalSlider->value() * 10;
	m_qTimer.setInterval(m_iTimeIntv);
}

void XDlgPyViewer::calVariance()
{
	for (int m = 0; m < 360; m++)
	{
		Pyramid_Filter::S_Filtering(m_iWidth, m_iHeight, m_pData, m_pFData, (double)m);
		qint64 iLen = m_iWidth * m_iHeight;
		float dMin = m_pFData[0], dMax = m_pFData[0];
		for (qint64 k = 1; k < iLen; k++)
		{
			dMin = dMin < m_pFData[k] ? dMin : m_pFData[k];
			dMax = dMax > m_pFData[k] ? dMax : m_pFData[k];
		}
		float dSpan = dMax - dMin;
		if (dSpan == 0.)
			return;

		qint64 iSum = 0;
		QVector<int> vecIDX;
		for (auto i = 0; i < m_iWidth; ++i)
		{
			for (auto k = 0; k < m_iHeight; ++k)
			{
				double dCurrValue = static_cast<double>(m_pFData[i * m_iHeight + k]);

				int index;
				index = static_cast<int>((dCurrValue - dMin) / dSpan * 254);
				index = 254 - qBound(0, index, 254);

				vecIDX << index;
				iSum += index;
			}
		}

		qint64 iNum = m_iWidth * m_iHeight;
		double dVar = 0., dAvg = iSum * 1. / iNum;
		for (qint64 n = 0; n < iNum; n++)
			dVar += (vecIDX[n] - dAvg) * (vecIDX[n] - dAvg);
		m_pVariance[m] = dVar;
	}

	int iMax = ui.frameStack->SetVar(m_pVariance);
	if (iMax > 180)
		iMax -= 180;
	int iMax2 = iMax + 180;

	QString str = QString::fromUtf8(u8"方差分析推荐最优滤波角度为 ") + QString::number(iMax);
	str = str + QString::fromUtf8(u8" 或 ") + QString::number(iMax2);
	ui.label->setText(str);
	ui.lineEdit->setText(QString::number(iMax));
	slotSetAng();
}

void XDlgPyViewer::accept()
{
	XDlgPyramid *pPDlg = (XDlgPyramid *)parent();
	pPDlg->SetSugAng(ui.lineEdit->text());

	QDialog::accept();
}