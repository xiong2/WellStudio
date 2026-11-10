#include <qpainter.h>
#include "xpagediagram.h"
#include "xwavelet.h"

#ifndef PI
#define PI 3.141592653579798  
#endif 

#define MARGIN 30

CXPageDiagram::CXPageDiagram(QWidget *parent)
	:QFrame(parent)
{
}

CXPageDiagram::CXPageDiagram(CXObject *pObj, QWidget *parent)
	:QFrame(parent)
{
	m_pWavelet = dynamic_cast<CXWavelet *>(pObj);

	if (m_pWavelet)
		initialize();
}

CXPageDiagram::~CXPageDiagram()
{
	if (m_pAmpData)
		delete m_pAmpData;

	if (m_pPhcData)
		delete m_pPhcData;
}

void CXPageDiagram::SetWavelet(CXWavelet *pWavelet)
{
	m_pWavelet = pWavelet;
	initialize();
}

void CXPageDiagram::initialize()
{
	double dDMin, dDMax, dSTime;
	m_pWavelet->GetDataRange(dDMin, dDMax);
	dSTime = m_pWavelet->GetStartTime();

	m_iSTime = (int)(qAbs(dSTime) / 10.) * 10;
	if (qAbs(dDMax > 100))
	{
		m_iMinAmp = ((int)(dDMin / 100.) - 1) * 100;
		m_iMaxAmp = ((int)(dDMax / 100.) + 1) * 100;
	}
	else
	{
		m_iMinAmp = (int)(dDMin - 0.99);
		m_iMaxAmp = (int)(dDMax + 0.99);
	}

	int iMax = qMax(m_iMaxAmp, qAbs(m_iMinAmp));
	m_dBinAmp = iMax / 2.;
	m_iBinTime = m_iSTime / 4;

	calAmpPhc();
}

void CXPageDiagram::calAmpPhc()
{
	double *pData = m_pWavelet->GetData();
	if (m_pAmpData)
	{
		delete m_pAmpData;
		m_pAmpData = NULL;
	}
	if (m_pPhcData)
	{
		delete m_pPhcData;
		m_pPhcData = NULL;
	}
	m_iNumAmp = m_iNumPhc = 0;

	unsigned int iNum = m_pWavelet->GetPointNumber();
	if (iNum % 2 == 0)
	{
		iNum++;
	}

	int    i, fftNum, exponent;
	double mantissa;

	mantissa = frexp(double(iNum), &exponent);
	fftNum = int(pow(2.0, exponent));

	m_pAmpData = new double[fftNum];
	m_pPhcData = new double[fftNum];

	memset(m_pAmpData, 0, fftNum * sizeof(double));
	memset(m_pPhcData, 0, fftNum * sizeof(double));

	int zeroIndex = int(0. - m_pWavelet->GetStartTime() / m_pWavelet->GetStep());
	calSignalSpectrum(pData, iNum, zeroIndex, m_pAmpData, m_pPhcData);

	m_iNumAmp = m_iNumPhc = fftNum / 2;

	m_iMaxFrq = (int)m_pAmpData[0] + 1;
	for (i = 1; i < m_iNumPhc; i++)
	{
		m_iMaxFrq = m_iMaxFrq > m_pAmpData[i] ? m_iMaxFrq : (int)m_pAmpData[i] + 1;
	}

	if(m_iMaxFrq > 100)
		m_iMaxFrq = (m_iMaxFrq / 100 + 1) * 100;

	int iMF = m_iMaxFrq;
	m_iBinFrq = 1;
	while (iMF > 10)
	{
		iMF /= 10;
		m_iBinFrq *= 10;
	}

	double dStep = m_pWavelet->GetStep();
	m_dFreqInterval = 1000. / dStep / fftNum;

	double totalEnerge = 0.;
	for (int i = 0; i < fftNum / 2; i++)
	{
		totalEnerge += m_pAmpData[i] * m_pAmpData[i];
	}

	double sumEnerge = 0.;
	int ifreq;
	for (ifreq = 0; ifreq < fftNum / 2; ifreq++)
	{
		sumEnerge += m_pAmpData[ifreq] * m_pAmpData[ifreq];
		if (sumEnerge >= totalEnerge * 0.99999)
			break;
	}

	m_dFreqLow = 0.;
	m_dFreqHigh = double(ifreq)*m_dFreqInterval;
}

void CXPageDiagram::paintEvent(QPaintEvent *)
{
	if (!m_pWavelet)
		return;

	drawAmp();
	drawFre();
	drawPha();
}

void CXPageDiagram::drawAmp()
{
	int i;
	float f;
	qreal x, y;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);
	painter.setPen("black");

	QRect rect = this->rect().adjusted(2 * MARGIN, MARGIN, -2 * MARGIN, -MARGIN - this->rect().height() / 2);

	//	Bin grid.
	QVector<QPointF> vecBP;
	for (f = 0; f <= m_iMaxAmp; f += m_dBinAmp)
	{
		y = rect.bottom() - rect.height() * (f - m_iMinAmp) / (m_iMaxAmp - m_iMinAmp);
		vecBP << QPointF(rect.x(), y) << QPointF(rect.right(), y);

		painter.drawText(rect.x() - 40, y - 10, 40, 20, Qt::AlignCenter, QString::number(f * 1. / m_iMaxAmp));
		painter.drawText(rect.right(), y - 10, 40, 20, Qt::AlignCenter, QString::number(f * 1. / m_iMaxAmp));
	}
	for (f = -m_dBinAmp; f >= m_iMinAmp; f -= m_dBinAmp)
	{
		y = rect.bottom() - rect.height() * (f - m_iMinAmp) / (m_iMaxAmp - m_iMinAmp);
		vecBP << QPointF(rect.x(), y) << QPointF(rect.right(), y);

		painter.drawText(rect.x() - 40, y - 10, 40, 20, Qt::AlignCenter, QString::number(f));
		painter.drawText(rect.right(), y - 10, 40, 20, Qt::AlignCenter, QString::number(f));
	}

	x = rect.x() + rect.width() * 0.5;
	vecBP << QPointF(x, rect.top()) << QPointF(x, rect.bottom());
	painter.drawText(x - 20, rect.bottom() + 10, 40, 20, Qt::AlignCenter, "0");

	for (i = m_iBinTime; i <= m_iSTime; i += m_iBinTime)
	{
		x = rect.x() + rect.width() * 0.5 + rect.width() * 0.5 * i / m_iSTime;
		vecBP << QPointF(x, rect.top()) << QPointF(x, rect.bottom());
		painter.drawText(x - 20, rect.bottom() + 10, 40, 20, Qt::AlignCenter, QString::number(i));

		x = rect.x() + rect.width() * 0.5 - rect.width() * 0.5 * i / m_iSTime;
		vecBP << QPointF(x, rect.top()) << QPointF(x, rect.bottom());
		painter.drawText(x - 20, rect.bottom() + 10, 40, 20, Qt::AlignCenter, QString::number(-i));
	}

	painter.setPen(QPen(Qt::lightGray, 1));
	painter.drawLines(vecBP);

	//	Wavelet.
	painter.setPen(QPen(Qt::gray, 2));
	painter.drawRect(rect);
	painter.setPen(QPen(Qt::blue, 2));

	double *pData = m_pWavelet->GetData();
	unsigned int iNum = m_pWavelet->GetPointNumber();
	double dSTime = m_pWavelet->GetStartTime();
	double dStep = m_pWavelet->GetStep();

	x = rect.x() + rect.width() * (dSTime + m_iSTime) / (2 * m_iSTime);
	y = rect.bottom() - rect.height() * (pData[0] - m_iMinAmp) / (m_iMaxAmp - m_iMinAmp);
	QPainterPath path(QPointF(x, y));
	for (i = 1; i < iNum; i++)
	{
		dSTime += dStep;
		x = rect.x() + rect.width() * (dSTime + m_iSTime) / (2 * m_iSTime);
		y = rect.bottom() - rect.height() * (pData[i] - m_iMinAmp) / (m_iMaxAmp - m_iMinAmp);
		path.lineTo(QPointF(x, y));
	}

	painter.drawPath(path);
}

void CXPageDiagram::drawFre()
{
	int i;
	qreal x, y;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);
	painter.setPen("black");

	QRect rect = this->rect().adjusted(2 * MARGIN, MARGIN + this->rect().height() / 2, (-MARGIN - this->rect().width()) / 2, -MARGIN);

	//	Bin grid.
	QVector<QPointF> vecBP;
	int iTopF = (int)(m_dFreqHigh / 20. + 0.99) * 20, iStep = 20;
	if (iTopF > 200)
		iStep = 40;
	for (i = 0; i <= iTopF; i += iStep)
	{
		x = rect.x() +  rect.width() * i / iTopF;
		vecBP << QPointF(x, rect.top()) << QPointF(x, rect.bottom());
		painter.drawText(x - 20, rect.bottom() + 10, 40, 20, Qt::AlignCenter, QString::number(i));
	}

	for (i = 0; i <= m_iMaxFrq; i += m_iBinFrq)
	{
		y = rect.bottom() - rect.height() * i / m_iMaxFrq;
		vecBP << QPointF(rect.x(), y) << QPointF(rect.right(), y);
		painter.drawText(rect.x() - 40, y - 10, 40, 20, Qt::AlignCenter, QString::number(i));
	}

	painter.setPen(QPen(Qt::gray, 2));
	painter.drawRect(rect);

	painter.setPen(QPen(Qt::lightGray, 1));
	painter.drawLines(vecBP);

	//	Curve.
	painter.setPen(QPen(Qt::blue, 2));
	x = rect.x();
	y = rect.bottom() - rect.height() * m_pAmpData[0] / m_iMaxFrq;
	QPainterPath path(QPointF(x, y));
	for (i = 1; i < m_iNumPhc; i++)
	{
		x = rect.x() + i * m_dFreqInterval * rect.width() / iTopF;
		if (x > rect.right())
			break;

		y = rect.bottom() - rect.height() * m_pAmpData[i] / m_iMaxFrq;
		path.lineTo(QPoint(x, y));
	}

	painter.drawPath(path);
}

void CXPageDiagram::drawPha()
{
	int i;
	qreal x, y;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	QFont font = painter.font();
	font.setPixelSize(12);
	painter.setFont(font);
	painter.setPen("black");

	QRect rect = this->rect().adjusted((MARGIN + this->rect().width()) / 2, MARGIN + this->rect().height() / 2, -2 * MARGIN, -MARGIN);

	//	Bin grid.
	QVector<QPointF> vecBP;
	int iTopF = (int)(m_dFreqHigh / 20. + 0.99) * 20, iStep = 20;
	if (iTopF > 200)
		iStep = 40;
	for (i = 0; i <= iTopF; i += iStep)
	{
		x = rect.x() + rect.width() * i / iTopF;
		vecBP << QPointF(x, rect.top()) << QPointF(x, rect.bottom());
		painter.drawText(x - 20, rect.bottom() + 10, 40, 20, Qt::AlignCenter, QString::number(i));
	}

	y = rect.y() + 2 * rect.height() / 9;
	vecBP << QPointF(rect.x(), y) << QPointF(rect.right(), y);
	painter.drawText(rect.right(), y - 10, 40, 20, Qt::AlignCenter, "100");
	y = rect.y() + rect.height() / 2;
	vecBP << QPointF(rect.x(), y) << QPointF(rect.right(), y);
	painter.drawText(rect.right(), y - 10, 40, 20, Qt::AlignCenter, "0");
	y = rect.y() + 7 * rect.height() / 9;
	vecBP << QPointF(rect.x(), y) << QPointF(rect.right(), y);
	painter.drawText(rect.right(), y - 10, 40, 20, Qt::AlignCenter, "-100");

	painter.setPen(QPen(Qt::gray, 2));
	painter.drawRect(rect);

	painter.setPen(QPen(Qt::lightGray, 1));
	painter.drawLines(vecBP);

	//	Curve.
	painter.setPen(QPen(Qt::blue, 2));
	x = rect.x();
	y = rect.y() + rect.height() / 2 - rect.height() * m_pPhcData[0] / 360;
	QPainterPath path(QPointF(x, y));
	for (i = 1; i < m_iNumPhc; i++)
	{
		x = rect.x() + i * m_dFreqInterval * rect.width() / iTopF;
		if (x > rect.right())
			break;

		y = rect.y() + rect.height() / 2 - rect.height() * m_pPhcData[i] / 360;
		path.lineTo(QPoint(x, y));
	}

	painter.drawPath(path);
}

int CXPageDiagram::calSignalSpectrum(double *pData, int sampleNum, int zeroIndex, double *pAmp, double *pPhase)
{
	int    exponent;
	double mantissa;
	int    fftNum;
	int    halfSampleNum = int(sampleNum / 2.0);
	int i;

	mantissa = frexp(double(sampleNum), &exponent);
	fftNum = int(pow(2.0, exponent));
	double *fr = new double[fftNum];
	double *fi = new double[fftNum];

	memset(fr, 0, fftNum * sizeof(double));
	memset(fi, 0, fftNum * sizeof(double));

	memcpy(fr, pData + zeroIndex, (sampleNum - zeroIndex) * sizeof(double));
	for (i = 0; i < zeroIndex; i++)
	{
		fr[fftNum - i - 1] = pData[zeroIndex - i - 1];
	}

	int halfFFTNum = fftNum / 2;
	for (i = sampleNum - zeroIndex; i < halfFFTNum; ++i)
		fr[i] = fr[sampleNum - zeroIndex - 1];

	for (i = halfFFTNum; i < fftNum - zeroIndex; ++i)
		fr[i] = fr[fftNum - zeroIndex];

	//frequency domain
	fft(fr, fi, fftNum, 0);

	//calculate amplitude spectrum
	double ampmax = 0.;
	double ampsum = 0.;
	int ampMaxIndex = 0;
	for (i = 0; i < fftNum; i++)
	{
		pAmp[i] = (sqrt(fr[i] * fr[i] + fi[i] * fi[i])) / 2. / PI;
		if (pAmp[i] > ampmax)
		{
			ampmax = pAmp[i];
			ampMaxIndex = i;
		}
		ampsum += pAmp[i];
	}

	ampsum /= ampmax;

	//calculate phase spectrum

	double epsamp = 1e-6*ampmax;
	for (i = 0; i < fftNum; ++i)
	{
		double re = fr[i];
		double im = fi[i];
		if ((re*re + im * im) >= epsamp)
		{
			pPhase[i] = atan2(im, re);
		}
		else
		{
			pPhase[i] = 0.0;
		}
	}

	//extrapolate the phase out of range[eps, eps] amplitude
	double eps = 0.;
	if (eps)
	{
		double phaseEps = 0.;
		for (i = ampMaxIndex; i >= 0; i--)
		{
			if (pAmp[i] > eps)
				phaseEps = pPhase[i];
			else
				pPhase[i] = phaseEps;
		}
		for (i = ampMaxIndex; i < fftNum; i++)
		{
			if (pAmp[i] > eps)
				phaseEps = pPhase[i];
			else
				pPhase[i] = phaseEps;
		}
	}
	//extrapolate the phase out of range (1-percamp) (*%) SUM(amplitude)
	double percamp = 0.;
	double percamp2 = (1. - percamp / 100.) / 2.;
	double percampsum;
	if (percamp)
	{
		double ratioamp;
		percampsum = 0.;
		for (i = 0; i < fftNum / 2; i++)
		{
			percampsum += pAmp[i];
			if (percampsum / ampsum > percamp2)
			{
				pPhase[i] = pPhase[i - 1];
			}
		}

		percampsum = 0.;
		for (i = fftNum / 2 - 1; i >= 0; i--)
		{
			percampsum += pAmp[i];
			if (percampsum / ampsum > percamp2)
			{
				pPhase[i] = pPhase[i + 1];
			}
		}

		for (i = 0; i < fftNum / 2; i++)
		{
			pPhase[fftNum - 1 - i] = pPhase[i];
		}

	}



	/* phase unwrapping */
	int unwrap = 0;
	if (unwrap != 0)
	{
		unwrap_phase(fftNum, unwrap, pPhase);
	}

	for (i = 0; i < fftNum; ++i)
	{
		pPhase[i] = pPhase[i] * 180.0 / PI;
		//qDebug()<<__FUNCTION__<<__LINE__<<i<<pPhase[i];
	}

	if (fr)
	{
		delete fr;
		fr = NULL;
	}

	if (fi)
	{
		delete fi;
		fi = NULL;
	}

	return(0);
}

void CXPageDiagram::unwrap_phase(int n, double w, double *phase)
{
	int i;
	double pibyw = 0.0;
	double *dphase;
	double *temp;

	/* prevent division by zero in PI/w */
	//	if (w==0)  err("wrapping parameter is zero");
	//	else       pibyw = PI/w;
	pibyw = PI / w;

	/* allocate space */
	dphase = new double[n];
	temp = new double[n];

	/* initialize */
	temp[0] = phase[0];
	dphase[0] = 0.0;

	/* compute unwrapped phase at each time step */
	for (i = 1; i < n; ++i) {

		/* compute jump in phase */
		dphase[i] = qAbs(phase[i] - phase[i - 1]);

		/* if dphase >= PI/w, use previous dphase value */
		if (qAbs(dphase[i] - dphase[i - 1]) >= pibyw)
			dphase[i] = dphase[i - 1];

		/* sum up values in temporary vector */
		temp[i] = temp[i - 1] + dphase[i];
	}

	/* assign values of temporary vector to phase[i] */
	for (i = 0; i < n; ++i) phase[i] = temp[i];

	/* free space */
	delete[]temp;
	delete []dphase;
}