#include <qvalidator.h>
#include <qmath.h>
#include <qmessagebox.h>
#include "xdlgtheowavelet.h"
#include "xglobal.h"
#include "xwavelet.h"

#ifndef PI
#define PI 3.141592653579798  
#endif 

int nextpow2(int x)
{
	int y = 0;
	while (pow(2, y) < x)
	{
		y++;
	}
	return y;
}

void linspace(double start, double end, int nt, double* out)
{
	double step = (end - start) / (nt - 1.0);
	for (int i = 0; i < nt; i++)
	{
		out[i] = start + step * i;
	}
}

void tntamp(double fnot, double* f, int nf, int m, double* ampspec)
{
	for (int i = 0; i < nf; i++)
	{
		double gaus = exp(-(f[i] / fnot)*(f[i] / fnot));
		ampspec[i] = (1.0 - gaus) / (1.0 + pow(f[i] / fnot, m));
	}

}

void ifftrl(double* spec, int nSpec, double* &r, int &nr)
{
	int i;
	int nsamp = nSpec;
	int ntr = 1;
	int itr = 0;

	int nL1 = nsamp - 1 + 1;
	int nL2 = (nsamp - 1 - 2) + 1;
	double* symspec = new double[nL1 + nL2];
	for (i = 0; i < nL1; i++)
	{
		symspec[i] = spec[i];
	}
	for (i = 0; i < nL2; i++)
	{
		symspec[i + nL1] = spec[nsamp - 1 - i - 1];
	}

	// transform the array
	int n2 = pow(2, nextpow2(nL1 + nL2));
	double* fr = new double[n2];
	double* fi = new double[n2];
	memset(fr, sizeof(double)*(n2), 0);
	memset(fi, sizeof(double)*(n2), 0);
	memcpy(fr, symspec, sizeof(double)*(nL1 + nL2));
	fft(fr, fi, n2, 1);
	memcpy(symspec, fr, sizeof(double)*(nL1 + nL2));
	delete[] fi;
	delete[] fr;

	r = symspec;
	nr = nL1 + nL2;
}

void levrec(double* aa, double* b, int nb, double*& x)//xµÄcout = nb
{
	int i;
	int l = nb;
	double tempMax = aa[0];
	if (aa[0] != 1.0) {
		tempMax = aa[0];
		for (i = 0; i < l; i++)
		{
			tempMax = qMax(aa[i], tempMax);
		}
		for (i = 0; i < l; i++)
		{
			aa[i] = aa[i] / tempMax;
		}
		tempMax = aa[0];
		for (i = 0; i < l; i++)
		{
			tempMax = qMax(aa[i], tempMax);
		}
	}
	// check for valid autocorr
	if (aa[0] != tempMax) {
		qWarning(" Invalid autocorrelation: zero lag not maximum");
	}
	// initialize some stuff
	double* a = aa + 1;
	int n = l;
	x = new double[n];
	double* y = new double[n];
	double* z = new double[n];
	double* nu = new double[n];
	memset(x, 0, sizeof(double)*n);
	memset(y, 0, sizeof(double)*n);
	memset(z, 0, sizeof(double)*n);
	y[0] = -a[0];
	x[0] = b[0];
	double beta = 1;
	double alpha = -a[0];
	// main recursion loop
	double temp;
	for (int k = 0; k < n - 1; k++)
	{
		beta = (1. - alpha * alpha)*beta;

		temp = 0;
		for (i = 0; i <= k; i++)
		{
			temp += a[i] * x[k - i];
		}
		double mu = (b[k + 1] - temp) / beta;


		for (i = 0; i <= k; i++)
		{
			nu[i] = x[i] + mu * y[k - i];
		}
		for (i = 0; i <= k; i++)
		{
			x[i] = nu[i];
		}
		x[k + 1] = mu;
		if (k < (n - 1 - 1)) {

			temp = 0;
			for (i = 0; i <= k; i++)
			{
				temp += a[i] * y[k - i];
			}
			alpha = -(a[k + 1] + temp) / beta;


			for (i = 0; i <= k; i++)
			{
				z[i] = y[i] + alpha * y[k - i];
			}
			for (i = 0; i <= k; i++)
			{
				y[i] = z[i];
			}
			y[k + 1] = alpha;
		}
	}
	delete[]y;
	delete[]z;
	delete[]nu;
}

int DFT000(int dir, int m, double *x1, double *y1, double *x3, double *y3)
{
	if (dir == 0)
	{
		dir = 1;
	}
	else {
		dir = -1;
	}
	double *x2 = new double[m];
	double *y2 = new double[m];
	long i, k;
	double arg;
	double cosarg, sinarg;
	if (x2 == NULL || y2 == NULL)return(false);
	for (i = 0; i < m; i++)
	{
		x2[i] = 0;
		y2[i] = 0;
		arg = dir * 2.0*3.141592654*(double)i / (double)m;
		for (k = 0; k < m; k++)
		{
			cosarg = cos(k*arg);
			sinarg = sin(k*arg);
			if (dir == 1)
			{
				x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
				y2[i] += -(x1[k] * sinarg + y1[k] * cosarg);
			}
			else {
				x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
				y2[i] += -(x1[k] * cosarg + y1[k] * sinarg);
			}
		}
	}
	/*Copythedataback*/
	if (dir == 1)
	{
		for (i = 0; i < m; i++)
		{
			x3[i] = x2[i];
			y3[i] = y2[i];
		}
	}
	else
	{
		x3[0] = x2[0] / (double)m;
		y3[0] = y2[0] / (double)m;
		for (i = 1; i < m; i++)
		{
			x3[i] = x2[m - i] / (double)m;
			y3[i] = y2[m - i] / (double)m;
		}
	}
	delete[]x2;
	delete[]y2;
	return(true);
}

XDlgTheoWavelet::XDlgTheoWavelet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	CXObject *pWaveletFolder = ::GetRootObjectFolder(EXWaveletFolder);
	QString sName = pWaveletFolder->GetUnallocatedName("Wavelet");
	ui.lineEditName->setText(sName);

	ui.lineEditSTime->setValidator(new QDoubleValidator);
	ui.lineEditLength->setValidator(new QIntValidator(10, 2000));
	ui.lineEditInterval->setValidator(new QDoubleValidator(0.1, 40, 0.1));
	ui.lineEditP1->setValidator(new QDoubleValidator);
	ui.lineEditP2->setValidator(new QDoubleValidator);
	ui.lineEditP3->setValidator(new QDoubleValidator);
	ui.lineEditP4->setValidator(new QDoubleValidator);

	slotWaveletType(0);

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotWaveletType(int)));
	connect(ui.pushButton, SIGNAL(clicked()), SLOT(slotPreview()));

	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

XDlgTheoWavelet::~XDlgTheoWavelet()
{
}

void XDlgTheoWavelet::slotWaveletType(int iIDX)
{
	if (iIDX == 0)
	{
		ui.labelP1->setText("Dominant Frequency (Hz)");
		ui.lineEditP1->setText("25");
		ui.labelP2->setVisible(false);
		ui.lineEditP2->setVisible(false);
		ui.labelP3->setVisible(false);
		ui.lineEditP3->setVisible(false);
		ui.labelP4->setVisible(false);
		ui.lineEditP4->setVisible(false);
	}
	else if (iIDX == 1)
	{
		ui.labelP1->setText("Lower-cut Frequency (Hz)");
		ui.lineEditP1->setText("5");
		ui.labelP2->setVisible(true);
		ui.lineEditP2->setVisible(true);
		ui.labelP2->setText("Lower-pass Frequency (Hz)");
		ui.lineEditP2->setText("10");
		ui.labelP3->setVisible(true);
		ui.lineEditP3->setVisible(true);
		ui.labelP3->setText("High-pass Frequency (Hz)");
		ui.lineEditP3->setText("40");
		ui.labelP4->setVisible(true);
		ui.lineEditP4->setVisible(true);
		ui.labelP4->setText("High-cut Frequency (Hz)");
		ui.lineEditP4->setText("45");
	}
	else if (iIDX == 2)
	{
		ui.labelP1->setText("Start Frequency (Hz)");
		ui.lineEditP1->setText("10");
		ui.labelP2->setVisible(true);
		ui.lineEditP2->setVisible(true);
		ui.labelP2->setText("End Frequency (Hz)");
		ui.lineEditP2->setText("40");
		ui.labelP3->setVisible(true);
		ui.lineEditP3->setVisible(true);
		ui.labelP3->setText("Sweep Length in Seconds (s)");
		ui.lineEditP3->setText("7");
		ui.labelP4->setVisible(false);
		ui.lineEditP4->setVisible(false);
	}
	else if (iIDX == 3)
	{
		ui.labelP1->setText("Dominant Frequency (Hz)");
		ui.lineEditP1->setText("30");
		ui.labelP2->setVisible(true);
		ui.lineEditP2->setVisible(true);
		ui.labelP2->setText("Exponent Controlling Spectral Shape");
		ui.lineEditP2->setText("3");
		ui.labelP3->setVisible(false);
		ui.lineEditP3->setVisible(false);
		ui.labelP4->setVisible(false);
		ui.lineEditP4->setVisible(false);
	}
	else if (iIDX == 4)
	{
		ui.labelP1->setText("Lower Limit Dominant Frequency (Hz)");
		ui.lineEditP1->setText("10");
		ui.labelP2->setVisible(true);
		ui.lineEditP2->setVisible(true);
		ui.labelP2->setText("Upper Limit Dominant Frequency (Hz)");
		ui.lineEditP2->setText("80");
		ui.labelP3->setVisible(false);
		ui.lineEditP3->setVisible(false);
		ui.labelP4->setVisible(false);
		ui.lineEditP4->setVisible(false);
	}
}

void XDlgTheoWavelet::slotPreview()
{
	double dSTime = ui.lineEditSTime->text().toDouble();
	double dIntv = ui.lineEditInterval->text().toDouble();
	int i, iNum = ui.lineEditLength->text().toInt();

	double *pData = new double[iNum];

	int iType = ui.comboBox->currentIndex();
	if (iType == 0)
	{
		//	Ricker
		double dDF = ui.lineEditP1->text().toDouble();
		double dPF = PI * PI * dDF *dDF;

		for (i = 0; i < iNum; i++)
		{
			double dTW = (dSTime + dIntv * i) / 1000.;
			pData[i] = (1. - 2. * dPF * dTW * dTW) * exp(-dPF * dTW * dTW);
		}
	}
	else if (iType == 1)
	{
		//	Ormsby
		double f1 = ui.lineEditP1->text().toDouble();
		double f2 = ui.lineEditP2->text().toDouble();
		double f3 = ui.lineEditP3->text().toDouble();
		double f4 = ui.lineEditP4->text().toDouble();
		double f1sq = f1 * f1;
		double f2sq = f2 * f2;
		double f3sq = f3 * f3;
		double f4sq = f4 * f4;
		double f2m1 = f2 - f1;
		double f4m3 = f4 - f3;
		double dTW, dMaxAmp = 0., termf1, termf2, termf3, termf4;

		for (i = 0; i < iNum; i++)
		{
			dTW = (dSTime + dIntv * i) / 1000.;
			termf1 = dsinc(f1 * dTW);
			termf2 = dsinc(f2 * dTW);
			termf3 = dsinc(f3 * dTW);
			termf4 = dsinc(f4 * dTW);
			termf1 = termf1 * termf1*f1sq / f2m1;
			termf2 = termf2 * termf2*f2sq / f2m1;
			termf3 = termf3 * termf3*f3sq / f4m3;
			termf4 = termf4 * termf4*f4sq / f4m3;

			pData[i] = (termf4 - termf3) - (termf2 - termf1);
			if (qAbs(pData[i]) > dMaxAmp)
				dMaxAmp = qAbs(pData[i]);
		}

		for (i = 0; i < iNum; i++)
			pData[i] /= dMaxAmp;
	}
	else if (iType == 2)
	{
		//	Klauder
		double fmin = ui.lineEditP1->text().toDouble();
		double fmax = ui.lineEditP2->text().toDouble();
		double slength = ui.lineEditP3->text().toDouble();
		double f0 = (fmin + fmax) / 2;
		double k = (fmax - fmin) / slength;
		double tw, pikt, maxamp = 0, termk, termf0;

		for (i = 0; i < iNum; i++)
		{
			tw = (dSTime + dIntv * i) / 1000.;
			pikt = PI * k*tw;
			if (pikt != 0)
				termk = sin(pikt*(slength - tw)) / pikt;
			else
				termk = slength;

			termf0 = cos(2 * PI*f0*tw);
			pData[i] = termk * termf0;
			if (qAbs(pData[i]) > maxamp)
				maxamp = pData[i];

		}

		for (i = 0; i < iNum; i++)
			pData[i] /= maxamp;
	}
	else if (iType == 3)
	{
		double fdom = ui.lineEditP1->text().toDouble();
		double m = ui.lineEditP2->text().toDouble();

		double dt = dIntv *0.001;
		int zeroIndex = (0. - dSTime) / dIntv;
		double tlength = (iNum - zeroIndex) * dt;

		int nt2 = round(2.*tlength / dt) + 1;
		nt2 = pow(2., nextpow2(nt2));
		double tmax = dt * (nt2 - 1);

		double* tw = new double[nt2];

		for (i = 0; i < nt2; i++)
		{
			tw[i] = 0 + dt * i;
		}
		// create a frequency vector
		double fnyq = 1. / (2.0 * (tw[2 - 1] - tw[1 - 1]));
		double* f = new double[nt2 / 2 + 1];
		linspace(0., fnyq, 0.5*nt2 + 1.0, f);


		// create the power spectrum
		//powspec = tntamp(fdom, f, m). ^ 2;
		double* powspec = new double[nt2 / 2 + 1];
		tntamp(fdom, f, nt2 / 2 + 1, m, powspec);
		for (i = 0; i < nt2 / 2 + 1; i++)
		{
			powspec[i] = powspec[i] * powspec[i];
		}

		// create the autocorrelation
		double* auto0;
		int nw;
		ifftrl(powspec, nt2 / 2 + 1, auto0, nw);

		// run this through Levinson
		int nlags = round(tlength / dt) + 1;

		double* b = new  double[nlags];
		b[0] = 1;
		for (i = 1; i < nlags; i++)
		{
			b[i] = 0;
		}

		double* winv;
		levrec(auto0, b, nlags, winv);

		int n2 = pow(2, nextpow2(nlags));

		double* fi = new double[nlags];
		double* fi0 = new double[nlags];
		double* fr = new double[nlags];
		memset(fi0, 0, sizeof(double)*nlags);
		memset(fi, 0, sizeof(double)*nlags);
		DFT000(0, nlags, winv, fi0, fr, fi);

		double ab2;
		for (i = 0; i < nlags; i++)
		{
			ab2 = fr[i] * fr[i] + fi[i] * fi[i];
			fr[i] = fr[i] / ab2;
			fi[i] = -fi[i] / ab2;
		}
		DFT000(1, nlags, fr, fi, fr, fi);

		double maxamp = 0.;
		for (i = 0; i < zeroIndex; i++)
		{
			pData[i] = 0.;
		}
		for (i = zeroIndex; i < iNum; i++)
		{
			pData[i] = fr[i - zeroIndex];
			if (pData[i] > maxamp) maxamp = pData[i];
		}

		for (i = 0; i < iNum; i++)
			pData[i] /= maxamp;

		delete[] tw;
		delete[] fi;
		delete[] fr;
		delete[] winv;
	}
	else if (iType == 4)
	{
		// Yu's
		double p = ui.lineEditP1->text().toDouble();
		double q = ui.lineEditP2->text().toDouble();
		double tw;
		double maxamp = 0;
		double termp, termq;
		for (i = 0; i < iNum; i++)
		{
			tw = (dSTime + dIntv * i) / 1000.;

			termp = -(PI*p*tw)*(PI*p*tw);
			termq = -(PI*q*tw)*(PI*q*tw);

			pData[i] = (q*exp(termq) - p * exp(termp)) / (q - p);
			if (qAbs(pData[i]) > maxamp)
				maxamp = qAbs(pData[i]);
		}

		for (i = 0; i < iNum; i++)
			pData[i] /= maxamp;
	}

	if(!m_pWavelet)
		m_pWavelet = new CXWavelet(ui.lineEditName->text());
	m_pWavelet->ResetData(dSTime, dIntv, iNum, pData);
	m_pWavelet->SetNeedCalcDimension();

	CXPageDiagram *pPage = (CXPageDiagram *)ui.frame;
	pPage->SetWavelet(m_pWavelet);
	pPage->update();

	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void XDlgTheoWavelet::accept()
{
	if (!m_pWavelet)
	{
		QMessageBox::warning(NULL, "Generate theoretical wavelet", "No valid wavelet be generated!");
		return;
	}

	CXObject *pWaveletFolder = ::GetRootObjectFolder(EXWaveletFolder);
	if (pWaveletFolder != NULL)
	{
		m_pWavelet->SetObjectName(pWaveletFolder->GetUnallocatedName(ui.lineEditName->text()));
		pWaveletFolder->AddChild(m_pWavelet);
	}

	AddObjectEvent(m_pWavelet);

	QDialog::accept();
}