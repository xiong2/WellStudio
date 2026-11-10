#include <qmessagebox.h>
#include "xdlggatherflatten.h"
#include "xseismicdatavolume.h"
#include "xregulardatareader.h"
#include "xregulardatawriter.h"
#include "kelocalcrosscorr.h"
#include "xprogressbar.h"
#include "xalgorithmutility.h"
#include "xglobal.h"

#ifndef PI
#define PI 3.141592653589793
#endif

#ifndef DBL_EPSION
#define DBL_EPSION 2.220446049250313e-16
#endif

double sinc(double x) { return(x != 0.0) ? sin(PI*x) / (PI*x) : 1.0; }

void xindex(int nx, float ax[], float x, int *index)
{
	int lower, upper, middle, step;

	/* initialize lower and upper indices and step */
	lower = *index;
	if (lower < 0) lower = 0;
	if (lower >= nx) lower = nx - 1;
	upper = lower + 1;
	step = 1;

	/* if x values increasing */
	if (ax[nx - 1] > ax[0]) {

		/* find indices such that ax[lower] <= x < ax[upper] */
		while (lower > 0 && ax[lower] > x) {
			upper = lower;
			lower -= step;
			step += step;
		}
		if (lower < 0) lower = 0;
		while (upper < nx && ax[upper] <= x) {
			lower = upper;
			upper += step;
			step += step;
		}
		if (upper > nx) upper = nx;

		/* find index via bisection */
		while ((middle = (lower + upper) >> 1) != lower) {
			if (x >= ax[middle])
				lower = middle;
			else
				upper = middle;
		}

		/* else, if not increasing */
	}
	else {

		/* find indices such that ax[lower] >= x > ax[upper] */
		while (lower > 0 && ax[lower] < x) {
			upper = lower;
			lower -= step;
			step += step;
		}
		if (lower < 0) lower = 0;
		while (upper < nx && ax[upper] >= x) {
			lower = upper;
			upper += step;
			step += step;
		}
		if (upper > nx) upper = nx;

		/* find index via bisection */
		while ((middle = (lower + upper) >> 1) != lower) {
			if (x <= ax[middle])
				lower = middle;
			else
				upper = middle;
		}
	}

	/* return lower index */
	*index = lower;
}

void  intlin(int nin, float xin[], float yin[], float yinl, float yinr,
	int nout, float xout[], float yout[])
{
	static int idx;
	int jout;
	float x;

	/* if input x values are monotonically increasing, then */
	if (xin[0] <= xin[nin - 1]) {
		for (jout = 0; jout < nout; jout++) {
			x = xout[jout];
			if (x < xin[0])
				yout[jout] = yinl;
			else if (x > xin[nin - 1])
				yout[jout] = yinr;
			else if (x == xin[nin - 1] || nin == 1)
				yout[jout] = yin[nin - 1];
			else {
				xindex(nin, xin, x, &idx);
				yout[jout] = yin[idx] + (x - xin[idx])
					*(yin[idx + 1] - yin[idx])
					/ (xin[idx + 1] - xin[idx]);
			}
		}

		/* else, if input x values are monotonically decreasing, then */
	}
	else {
		for (jout = 0; jout < nout; jout++) {
			x = xout[jout];
			if (x > xin[0])
				yout[jout] = yinl;
			else if (x < xin[nin - 1])
				yout[jout] = yinr;
			else if (x == xin[nin - 1] || nin == 1)
				yout[jout] = yin[nin - 1];
			else {
				xindex(nin, xin, x, &idx);
				yout[jout] = yin[idx] + (x - xin[idx])
					*(yin[idx + 1] - yin[idx])
					/ (xin[idx + 1] - xin[idx]);
			}
		}
	}
}

void boxcarfilter(int n, int len, float *a, float *b)
{
	float sum = 0.;
	int j, lenh = len / 2;
	if (len <= 1) {
		for (j = 0; j < n; j++) b[j] = a[j];
		return;
	}
	for (j = 0; j < qMin(len, n); j++) sum += a[j];
	for (j = 0; j < qMin(lenh + 1, n); j++) b[j] = sum;
	for (j = lenh + 1; j < n - lenh; j++) {
		sum = sum + a[j + lenh] - a[j - lenh - 1];
		b[j] = sum;
	}
	for (j = qMax(0, n - lenh); j < n; j++) b[j] = sum;
	sum = 1. / len;
	for (j = 0; j < n; j++) b[j] *= sum;
	return;
}

void boxcarfilter3p(int n, float *a, float *b)
{
	int len = 3;
	float sum = 0.;
	int j, lenh = len / 2;
	if (len <= 1) {
		for (j = 0; j < n; j++) b[j] = a[j];
		return;
	}
	for (j = 0; j < qMin(len, n); j++) sum += a[j];
	for (j = 0; j < qMin(lenh + 1, n); j++) b[j] = sum;
	for (j = lenh + 1; j < n - lenh; j++) {
		sum = sum + a[j + lenh] - a[j - lenh - 1];
		b[j] = sum;
	}
	for (j = qMax(0, n - lenh); j < n; j++) b[j] = sum;
	sum = 1. / len;
	for (j = 0; j < n; j++) b[j] *= sum;
	//terminal
	b[0] = (a[0] + a[1]) / 2.;
	b[n - 1] = (a[n - 2] + a[n - 1]) / 2.;
	return;
}

float** alloc2DFloat(int n1, int n2)
{
	float **p = new float*[n2];
	p[0] = new float[n1 * n2];

	for (int i = 0; i < n2; i++)
		p[i] = (float *)(p[0] + n1 * i);

	return p;
}

void free2DFloat(float **p)
{
	delete[]p[0];
	delete[]p;
}

double ino(double x) 
{
	double s = 1.0;
	double ds = 1.0;
	double d = 0.0;
	do 
	{
		d += 2.0;
		ds *= (x*x) / (d*d);
		s += ds;
	} while (ds > s*DBL_EPSION);
	return s;
}

void KaiserWindow(double error, double length, double*alpha, double*scale, double*xxmax) 
{
	double a = -20 * log10(error);
	if (a <= 21.0) {
		*alpha = 0.0;
	}
	else if (a <= 50) {
		*alpha = 0.5842*pow(a - 21.0, 0.4) + 0.07886*(a - 21);
	}
	else {
		*alpha = 0.1102*(a - 8.7);
	}
	*scale = 1.0 / ino(*alpha);
	*xxmax = 0.25*length*length;
}

double evaluate(double x, int lsinc) {
	double xx = x * x;
	double alpha, scale, xxmax;
	KaiserWindow(0.1, lsinc, &alpha, &scale, &xxmax);
	return(xx <= xxmax) ? scale * ino(alpha*sqrt(1.0 - xx / xxmax)) : 0.0;
}

float interpolate(double xscale, double xshift, int nxum, int nxu, float* yu, double x, int lsinc, int nsinc, float**_asinc, int extrapolation) {
	int _ishift = -lsinc - lsinc / 2 + 1;
	// Which uniform samples?
	double xn = xshift + x * xscale;
	int ixn = (int)xn;
	int kyu = _ishift + ixn;
	int _nsincm1 = nsinc - 1;
	int _lsinc = lsinc;
	// Which sinc approximation?
	double frac = xn - ixn;
	if (frac < 0.0)
		frac += 1.0;
	int ksinc = (int)(frac*_nsincm1 + 0.5);
	float*asinc = new float[lsinc];
	float yr = 0.0f;
	for (int il = 0; il < lsinc; ++il)asinc[il] = _asinc[ksinc][il];

	if (kyu >= 0 && kyu <= nxum) {
		for (int isinc = 0; isinc < _lsinc; ++isinc, ++kyu)
			yr += yu[kyu] * asinc[isinc];
	}
	else if (extrapolation == 0) {
		for (int isinc = 0; isinc < _lsinc; ++isinc, ++kyu) {
			if (0 <= kyu && kyu < nxu)
				yr += yu[kyu] * asinc[isinc];
		}
	}
	else if (extrapolation == 1) {
		for (int isinc = 0; isinc < _lsinc; ++isinc, ++kyu) {
			int jyu = (kyu < 0) ? 0 : (nxu <= kyu) ? nxu - 1 : kyu;
			yr += yu[jyu] * asinc[isinc];
		}
	}
	delete[]asinc; asinc = NULL;
	return yr;
}

void sincInterpolator(int n1, int n2, double dxu, double fxu, float**gf, float**u, float**cp) {
	int _lsinc = 16;//default value of SincInterpolator
	int _nsinc = _lsinc / 2 + 1;
	double _dsinc = 1.0 / (_nsinc - 1);
	int nxu = n1;
	float**asinc = alloc2DFloat(_lsinc, _nsinc);
	for (int j = 0; j < _lsinc; ++j) 
	{
		asinc[0][j] = 0.0; 
		asinc[_nsinc - 1][j] = 0.0; 
	}
	asinc[0][_lsinc / 2 - 1] = 1.0;
	asinc[_nsinc - 1][_lsinc / 2] = 1.0;
	for (int isinc = 1; isinc < _nsinc - 1; ++isinc) 
	{
		double x = -_lsinc / 2 + 1 - _dsinc * isinc;
		for (int i = 0; i < _lsinc; ++i, x += 1.0) 
		{
			asinc[isinc][i] = (float)(sinc(x)*evaluate(x, _lsinc));
		}
	}
	for (int i2 = 0; i2 < n2; ++i2) 
	{
		double xscale = 1.0 / dxu;
		double xshift = _lsinc - fxu * xscale;
		int nxum = nxu - _lsinc;
		float*yu = new float[n1];
		for (int i1 = 0; i1 < n1; ++i1)yu[i1] = gf[i2][i1];
		for (int i1 = 0; i1 < n1; ++i1) {
			double x = double(i1 + u[i2][i1]);
			cp[i2][i1] = interpolate(xscale, xshift, nxum, nxu, yu, x, _lsinc, _nsinc, asinc, 1);
		}
		delete[]yu; 
		yu = NULL;
	}
	free2DFloat(asinc); asinc = NULL;
}

XDlgGatherFlatten::XDlgGatherFlatten(CXSeismicDataVolume *pObj, QWidget *parent)
	: QDialog(parent), m_pDV(pObj)
{
	ui.setupUi(this);

	initGUI();
}

XDlgGatherFlatten::~XDlgGatherFlatten()
{
}

void XDlgGatherFlatten::initGUI()
{
	if (!m_pDV)
		return;

	ui.lineEditODV->setText(m_pDV->GetUnallocatedName(m_pDV->GetObjectName() + "_Flattening"));

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	m_pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);

	ui.m_pInlineWidget->SetSliderName("Inline");
	ui.m_pInlineWidget->SetRangeAndPrecision(iInlineMin, iInlineMax, iInlineInc, 0);

	ui.m_pXlineWidget->SetSliderName("Crossline");
	ui.m_pXlineWidget->SetRangeAndPrecision(iXlineMin, iXlineMax, iXlineInc, 0);

	int nI = m_pDV->GetInlineQty();
	int nJ = m_pDV->GetXlineQty();
	int nK = m_pDV->GetSamplingQty();
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	float fOffsetStart, fOffsetStep;
	int nOffsetNum;
	m_pDV->GetOffsetInfo(fOffsetStart, fOffsetStep, nOffsetNum);

	ui.dsbStartTime->setMinimum(dSamplingStart);
	ui.dsbStartTime->setMaximum(dSamplingEnd);
	ui.dsbStartTime->setSingleStep(dSamplingRate * 10);
	ui.dsbStartTime->setValue(dSamplingStart);

	ui.dsbEndTime->setMinimum(dSamplingStart);
	ui.dsbEndTime->setMaximum(dSamplingEnd);
	ui.dsbEndTime->setSingleStep(dSamplingRate * 10);
	ui.dsbEndTime->setValue(dSamplingEnd);

	ui.sbRefTraces->setMinimum(1);
	ui.sbRefTraces->setMaximum(nOffsetNum);
	ui.sbRefTraces->setSingleStep(1);
	ui.sbRefTraces->setValue(1);

	ui.dsbMaxShiftNear->setMinimum(0);
	ui.dsbMaxShiftNear->setMaximum(dSamplingEnd - dSamplingStart);
	ui.dsbMaxShiftNear->setSingleStep(dSamplingRate);
	ui.dsbMaxShiftNear->setValue(dSamplingRate * 4);

	ui.dsbMaxShiftFar->setMinimum(0);
	ui.dsbMaxShiftFar->setMaximum(dSamplingEnd - dSamplingStart);
	ui.dsbMaxShiftFar->setSingleStep(dSamplingRate);
	ui.dsbMaxShiftFar->setValue(dSamplingRate * 4);

	ui.dsbLCCWinLen->setMinimum(dSamplingRate * 5);
	ui.dsbLCCWinLen->setMaximum(dSamplingEnd - dSamplingStart);
	ui.dsbLCCWinLen->setSingleStep(dSamplingRate);
	ui.dsbLCCWinLen->setValue(dSamplingRate * 50);

	ui.dsbLCCThreshold->setMinimum(0.);
	ui.dsbLCCThreshold->setMaximum(1.);
	ui.dsbLCCThreshold->setSingleStep(0.1);
	ui.dsbLCCThreshold->setValue(0.7);

	ui.dsbShiftDiff->setMinimum(0);
	ui.dsbShiftDiff->setMaximum(10000);
	ui.dsbShiftDiff->setSingleStep(dSamplingRate);
	ui.dsbShiftDiff->setValue(dSamplingRate * 2);

	ui.dsbSmoothLen->setMinimum(0);
	ui.dsbSmoothLen->setMaximum(dSamplingEnd - dSamplingStart);
	ui.dsbSmoothLen->setSingleStep(dSamplingRate);
	ui.dsbSmoothLen->setValue(dSamplingRate * 10);
}

void XDlgGatherFlatten::accept()
{
	QString sName = ui.lineEditODV->text();
	if (sName.isEmpty())
	{
		QMessageBox::warning(this, "Gather Flattening", "Please give the name of the output data volume!");
		return;
	}
	sName = m_pDV->GetParent()->GetUnallocatedName(sName);

	int nI = m_pDV->GetInlineQty();
	int nJ = m_pDV->GetXlineQty();
	int nK = m_pDV->GetSamplingQty();
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	float fOffsetStart, fOffsetStep;
	int nOffsetNum;
	m_pDV->GetOffsetInfo(fOffsetStart, fOffsetStep, nOffsetNum);
	CXSeismicUTMTool utm = m_pDV->GetUTM();

	int iFInlinePro = ui.m_pInlineWidget->GetMinValue();
	int iLInlinePro = ui.m_pInlineWidget->GetMaxValue();
	int iFXlinePro = ui.m_pXlineWidget->GetMinValue();
	int iLXlinePro = ui.m_pXlineWidget->GetMaxValue();
	int ifirst, iend, jfirst, jend;
	utm.LineToIJ(iFInlinePro, iFXlinePro, ifirst, jfirst);
	utm.LineToIJ(iLInlinePro, iLXlinePro, iend, jend);
	int nIPro = (iend - ifirst) + 1;
	int nJPro = (jend - jfirst) + 1;

	int refTrace = ui.sbRefTraces->value() - 1;
	refTrace = refTrace < 0 ? 0 : refTrace;
	refTrace = refTrace > nOffsetNum - 1 ? nOffsetNum - 1 : refTrace;
	int startTimeSam = int((ui.dsbStartTime->value() - dSamplingStart) / dSamplingRate);
	int endTimeSam = int((ui.dsbEndTime->value() - dSamplingStart) / dSamplingRate);

	CXRegularDataReader<float> reader(m_pDV->GetTraceFileName(), nI, nJ, nK, nOffsetNum);
	if (!reader.Open())
	{
		QMessageBox::warning(this, "Gather Flattening", "Can not open the original data volume to read!");
		return;
	}

	CXSeismicUTMTool *pNewUTM = utm.GenerateNewUTM(iFInlinePro, iFXlinePro, nIPro, nJPro, utm.GetInlineIncrement(), utm.GetCrosslineIncrement());
	CXSeismicDataVolume *pNewDV = new CXSeismicDataVolume(*pNewUTM, dSamplingStart, dSamplingEnd, dSamplingRate, sName, nOffsetNum, fOffsetStart, fOffsetStep);
	CXRegularDataWriter<float> writer(pNewDV->GetTraceFileName(), nIPro, nJPro, nK * nOffsetNum);
	if (!writer.Open())
	{
		QMessageBox::warning(this, "Gather Flattening", "Can not open the output data volume to write!");
		return;
	}

	float shiftmaxNear = ui.dsbMaxShiftNear->value() / dSamplingRate;
	float shiftmaxFar = ui.dsbMaxShiftFar->value() / dSamplingRate;
	int nwin = ui.dsbLCCWinLen->value() / dSamplingRate;
	float threshcc = ui.dsbLCCThreshold->value();
	float checkdiff = ui.dsbShiftDiff->value() / dSamplingRate;
	int lencar = int(ui.dsbSmoothLen->value() / dSamplingRate);

	int ilagmin = -qMax(shiftmaxNear, shiftmaxFar);
	int nlag = 2 * qAbs(ilagmin) + 1;
	float *pshiftmax = new float[nOffsetNum];
	for (int iffset = 0; iffset < nOffsetNum; iffset++)
		pshiftmax[iffset] = shiftmaxNear + (shiftmaxFar - shiftmaxNear) * iffset / nOffsetNum;

	float *pBuff1 = new float[nK * nOffsetNum];
	float *pBuff2 = new float[nK * nOffsetNum];

	float *data_a = new float[nK];
	float *data_b = new float[nK];

	float *shiftall = new float[nK * nOffsetNum];
	float *pshiftpre;
	float *pshift;
	int *controlall = new int[nK * nOffsetNum];
	int *pcontrol;

	float *shiftinterp = new float[nK];
	float *tinterp = new float[nK];
	float *tinterpall = new float[nK];
	float *shiftinterpall = new float[nK];

	float *timeslice = new float[nOffsetNum];
	float *timeslicemean = new float[nOffsetNum];

	float **tshift = alloc2DFloat(nK, nOffsetNum);
	float **pdata = alloc2DFloat(nK, nOffsetNum);
	float **pdata2 = alloc2DFloat(nK, nOffsetNum);

	int ii, jj, it, iffset;
	CKELocalCrossCorr LCCFlatPro;

	CXProgressBar progress("Auto Flattening", "Calculating...", nIPro * nJPro);

	for (ii = ifirst; ii <= iend; ii++)
	{
		for (jj = jfirst; jj <= jend; jj++)
		{
			if (progress.IsAborted())
			{
				delete[]pshiftmax;
				delete[]data_a;
				delete[]data_b;
				delete[]shiftall;
				delete[]controlall;
				delete[]shiftinterp;
				delete[]tinterp;
				delete[]tinterpall;
				delete[]shiftinterpall;
				delete[]timeslice;
				delete[]timeslicemean;

				free2DFloat(tshift);
				free2DFloat(pdata);
				free2DFloat(pdata2);

				delete pNewDV;
				
				return;
			}
			else
			{
				qint64 valuePro = (ii - ifirst)*nJPro + jj - jfirst;
				progress.SetValue(valuePro);
			}

			reader.ReadUVTrace(ii, jj, pBuff1);

			memset(controlall, 0, sizeof(int) * nK * nOffsetNum);
			for (it = 0; it < nK; it++)
			{
				tinterpall[it] = float(it);
				controlall[it] = 1;				
				shiftall[it] = 0.;				
			}

			for (iffset = 1; iffset < nOffsetNum; iffset++)
			{
				memcpy(data_a, pBuff1 + (iffset - 1) * nK, sizeof(float) * nK);
				memcpy(data_b, pBuff1 + iffset * nK, sizeof(float) * nK);

				LCCFlatPro.setData(nK, data_a, data_b);
				float shiftmax = pshiftmax[iffset];
				LCCFlatPro.setPara(nwin, ilagmin, nlag, threshcc);
				LCCFlatPro.setTimeGate(startTimeSam, endTimeSam);
				pshiftpre = &shiftall[(iffset - 1)*nK];
				pshift = &shiftall[iffset*nK];
				pcontrol = &controlall[iffset*nK];
				LCCFlatPro.getShifts(pshift);
				int numinterp = 0;
				int shift0;
				for (it = 0; it < nK; it++)
				{

					if (pshift[it] > -100000)
					{
						pcontrol[it] = 1;
						shift0 = pshift[it];
						if ((it - shift0) >= 0 && (it - shift0) >= 0)
							pshift[it] = pshiftpre[it - shift0] + shift0;
						else
							pshift[it] = shift0;
					}
				}
				for (it = 0; it < nK; it++)
				{
					if (pcontrol[it] = 1)
					{
						if (qAbs(pshift[it]) < shiftmax)
						{
							shiftinterp[numinterp] = pshift[it];
							tinterp[numinterp] = float(it);
							numinterp++;
						}
						else
						{
							pcontrol[it] = 0;
						}
					}
				}

				intlin(numinterp, tinterp, shiftinterp, 0, 0, nK, tinterpall, pshift);
			}

			//	slice check
			for (it = 0; it < nK; it++)
			{
				for (iffset = 1; iffset < nOffsetNum; iffset++)
				{
					timeslice[iffset] = shiftall[iffset*nK + it];

				}
				boxcarfilter3p(nOffsetNum - 1, &timeslice[1], &timeslicemean[1]);
				for (iffset = 1; iffset < nOffsetNum; iffset++)
				{
					if (abs(timeslice[iffset] - timeslicemean[iffset]) > checkdiff)
						controlall[iffset*nK + it] = 0;
				}
			}

			//second interpolation
			for (iffset = 0; iffset < nOffsetNum; iffset++)
			{
				pshift = &shiftall[iffset*nK];
				pcontrol = &controlall[iffset*nK];
				int numinterp = 0;
				for (it = 0; it < nK; it++)
				{
					if (pcontrol[it] == 1)
					{
						pcontrol[it] = 1;
						shiftinterp[numinterp] = pshift[it];
						tinterp[numinterp] = float(it);
						numinterp++;
					}
				}
				intlin(numinterp, tinterp, shiftinterp, 0, 0, nK, tinterpall, shiftinterpall);
				boxcarfilter(nK, lencar, shiftinterpall, pshift);
			}

			int itnew, indxnew;
			for (iffset = 0; iffset < nOffsetNum; iffset++)
			{
				for (it = 0; it < nK; it++)
				{
					tshift[iffset][it] = shiftall[iffset*nK + it] - shiftall[refTrace*nK + it];
					pdata[iffset][it] = pBuff1[iffset*nK + it];
				}
			}
			sincInterpolator(nK, nOffsetNum, 1.0, 0.0, pdata, tshift, pdata2);
			for (int iffset = 0; iffset < nOffsetNum; iffset++)
			{
				for (int it = 0; it < nK; it++)
				{
					pBuff2[iffset*nK + it] = pdata2[iffset][it];
					//vecTime[iffset*nK + it] = shiftall[iffset*nK + it];
				}
			}

			writer.Append(nK*nOffsetNum, pBuff2);
		}
	}

	delete[]pshiftmax;
	delete[]data_a;
	delete[]data_b;
	delete[]shiftall;
	delete[]controlall;
	delete[]shiftinterp;
	delete[]tinterp;
	delete[]tinterpall;
	delete[]shiftinterpall;
	delete[]timeslice;
	delete[]timeslicemean;

	free2DFloat(tshift);
	free2DFloat(pdata);
	free2DFloat(pdata2);

	m_pDV->GetParent()->AddChild(pNewDV);

	CXAlgorithmUtility::CalculateHistogram(pNewDV->GetTraceFileName(), pNewDV->GetSamplingQty(), pNewDV);

	::AddObjectEvent(pNewDV);

	QDialog::accept();
}