#include <QVector3D>
#include "xwavelet.h"
//#include "xtemplate.h"
#include "xglobal.h"
#include "xdbio.h"
#include "xobjectfactory.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWavelet)
EXWavelet
END_REGISTER_OBJECT_TO_FACTORY(CXWavelet)

CXWavelet::CXWavelet(QString sName): CXObject(sName)
{
	this->SetObjectType(EXWavelet);
	SetIconName("Wavelet.png");
	m_dStep = 0.;
}

CXWavelet::~CXWavelet()
{
}

void CXWavelet::ResetData(double fStart, double dStep, unsigned int iNumPoints, double*pData)
{
	_LoadBaseData();

	if (m_pBaseData)
		delete m_pBaseData;

	m_dStart		= fStart;
	m_dStep			= dStep;
	m_nSamplingNum	= iNumPoints;
	m_pBaseData = pData;

	SetModifiedFlag();
}

void CXWavelet::GetDepthRange(double& fStart, double& fEnd)
{
	fStart = m_dStart;
	fEnd = m_dStart + (m_nSamplingNum - 1) * m_dStep;
}

double* CXWavelet::GetData()
{
	_LoadBaseData();
	return m_pBaseData;
}

void CXWavelet::GetData(double dStartDepth, double dEndDepth, vector<double> &vec)
{
	_LoadBaseData();

	if (!m_pBaseData || m_dStep == 0.) return;

	double dEnd = m_dStart + (m_nSamplingNum - 1) * m_dStep;
	if (dEndDepth < m_dStart || dStartDepth > dEnd) return;
	
	dStartDepth = qMax(dStartDepth, m_dStart);
	dEndDepth = qMin(dEndDepth, dEnd);

	int iStartIDX = (dStartDepth - m_dStart) / m_dStep;
	int iNumPoint = (dEndDepth - dStartDepth)/ m_dStep;

	for (int i=0; i<iNumPoint; ++i)
	{
		vec.push_back(m_pBaseData[iStartIDX + i]);
	}
}

//	Copy the data to the given pointer (space already allocated), INVALID value be used if beyond the data range.
bool CXWavelet::GetData(double* pData, double dStartDepth, unsigned int iNumPoints)
{
	_LoadBaseData();
	if (!pData || !m_pBaseData || m_dStep == 0.)
		return false;

	int i, iSouStartIDX = 0, iDesStartIDX = 0, iActureNumPoints = iNumPoints;

	//	First fill all the array by invalid value.
	for(i = 0; i < iNumPoints; i++)
		pData[i] = ::g_dInvalidData;

	if(dStartDepth < m_dStart)
	{
		iDesStartIDX = (m_dStart - dStartDepth) / m_dStep;
		iActureNumPoints -= iDesStartIDX;

		if(iActureNumPoints > m_nSamplingNum)
			iActureNumPoints = m_nSamplingNum;
	}
	else
	{
		iSouStartIDX = (dStartDepth - m_dStart) / m_dStep;

		if(iActureNumPoints > m_nSamplingNum - iSouStartIDX)
			iActureNumPoints = m_nSamplingNum - iSouStartIDX;
	}

	for(i = 0; i < iActureNumPoints; i++)
	{
		pData[i + iDesStartIDX] = m_pBaseData[i + iSouStartIDX];
	}

	return true;
}


QString CXWavelet::GetUnit()
{
	//CXTemplate *pTemplate = CXTemplate::GetTemplate(GetTemplateID());
	//if(pTemplate)
	//	return pTemplate->GetUnit();
	//else
		return "";
}

float * CXWavelet::_GetHistogramData(int & nDataNum, bool & bDeleted)
{
	nDataNum = m_nSamplingNum;
	bDeleted = true;
	if (nDataNum < 1)
		return nullptr;

	_LoadBaseData();
	float* pData = new float[m_nSamplingNum];
	for (int i = 0; i < m_nSamplingNum; ++i)
		pData[i] = (float)m_pBaseData[i];

	return pData;
}

bool CXWavelet::Serialize(bool bSave)
{
 	// base object
 	if (!CXObject::Serialize(bSave))
 		return false;
 
 	QString strTable = "wellcurve";
 
 	// save
 	if (bSave)
 	{
 		QStringList strFieldList;
 		strFieldList<<"ID";
 		//strFieldList<<"AliasID";
 		strFieldList<<"Start";
 		strFieldList<<"Step";
 
 		QList<QVariant> vtList;
 
 		vtList.append(GetObjectID().toString());
 		//vtList.append(m_aliasID.toString());
 		vtList.append(m_dStart);
 		vtList.append(m_dStep);
 
 		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
 	}
 	else
 	{
 		QStringList strFieldList;
 		//strFieldList<<"AliasID";
 		strFieldList<<"Start";
 		strFieldList<<"Step";
 
 		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());
 
 		if( query.first() )
 		{
 			int nIndex = -1;
 			
 			//m_aliasID	= query.value(++nIndex).toString();
 			m_dStart	= query.value(++nIndex).toDouble();
 			m_dStep		= query.value(++nIndex).toDouble();
 		}
 
 		return true;
 	}
	return true;
}

void intt8r(int ntable, double table[][8],
	int nxin, double dxin, double fxin, double yin[], double yinl, double yinr,
	int nxout, double xout[], double yout[])
{
	int ioutb, nxinm8, ixout, ixoutn, kyin, ktable, itable;
	double xoutb, xoutf, xouts, xoutn, frac, fntablem1, yini, sum,
		*yin0, *table00, *pyin, *ptable;

	/* compute constants */
	ioutb = -3 - 8;
	xoutf = fxin;
	xouts = 1.0 / dxin;
	xoutb = 8.0 - xoutf*xouts;
	fntablem1 = (double)(ntable - 1);
	nxinm8 = nxin - 8;
	yin0 = &yin[0];
	table00 = &table[0][0];

	/* loop over output samples */
	for (ixout = 0; ixout < nxout; ixout++) {

		/* determine pointers into table and yin */
		xoutn = xoutb + xout[ixout] * xouts;
		ixoutn = (int)xoutn;
		kyin = ioutb + ixoutn;
		pyin = yin0 + kyin;
		frac = xoutn - (double)ixoutn;
		ktable = frac >= 0.0 ? frac*fntablem1 + 0.5 : (frac + 1.0)*fntablem1 - 0.5;
		ptable = table00 + ktable * 8;

		/* if totally within input array, use fast method */
		if (kyin >= 0 && kyin <= nxinm8) {
			yout[ixout] =
				pyin[0] * ptable[0] +
				pyin[1] * ptable[1] +
				pyin[2] * ptable[2] +
				pyin[3] * ptable[3] +
				pyin[4] * ptable[4] +
				pyin[5] * ptable[5] +
				pyin[6] * ptable[6] +
				pyin[7] * ptable[7];

			/* else handle end effects with care */
		}
		else {

			/* sum over 8 tabulated coefficients */
			for (itable = 0, sum = 0.0; itable < 8; itable++, kyin++) {
				if (kyin < 0)
					yini = yinl;
				else if (kyin >= nxin)
					yini = yinr;
				else
					yini = yin[kyin];
				sum += yini*(*ptable++);
			}
			yout[ixout] = sum;
		}
	}
}

#define LTABLE 8
#define NTABLE 513

#define PI (3.141592653589793)
double dsinc(double x)
{
	double pix;

	if (x == 0.0) {
		return 1.0;
	}
	else {
		pix = PI*x;
		return sin(pix) / pix;
	}
}
void stoepd(int n, double r[], double g[], double f[], double a[])
{
	int i, j;
	double v, e, c, w, bot;

	if (r[0] == 0.0) return;

	a[0] = 1.0;
	v = r[0];
	f[0] = g[0] / r[0];

	for (j = 1; j < n; j++) {

		/* solve Ra=v as in Claerbout, FGDP, p. 57 */
		a[j] = 0.0;
		f[j] = 0.0;
		for (i = 0, e = 0.0; i < j; i++)
			e += a[i] * r[j - i];
		c = e / v;
		v -= c*e;
		for (i = 0; i <= j / 2; i++) {
			bot = a[j - i] - c*a[i];
			a[i] -= c*a[j - i];
			a[j - i] = bot;
		}

		/* use a and v above to get f[i], i = 0,1,2,...,j */
		for (i = 0, w = 0.0; i < j; i++)
			w += f[i] * r[j - i];
		c = (w - g[j]) / v;
		for (i = 0; i <= j; i++)
			f[i] -= c*a[j - i];
	}
}
void mksinc(double d, int lsinc, double sinc[])
{
	int j;
	double s[20], a[20], c[20], work[20], fmax;

	/* compute auto-correlation and cross-correlation arrays */
	fmax = 0.066 + 0.265*log((double)lsinc);
	fmax = (fmax<1.0) ? fmax : 1.0;
	for (j = 0; j<lsinc; j++) {
		a[j] = dsinc(fmax*j);
		c[j] = dsinc(fmax*(lsinc / 2 - j - 1 + d));
	}

	/* solve symmetric Toeplitz system for the sinc approximation */
	stoepd(lsinc, a, c, s, work);
	for (j = 0; j<lsinc; j++)
		sinc[j] = s[j];
}
void ints8r(int nxin, double dxin, double fxin, double yin[],
	double yinl, double yinr, int nxout, double xout[], double yout[])
{
	static double table[NTABLE][LTABLE];
	static int tabled = 0;
	int jtable;
	double frac;

	/* tabulate sinc interpolation coefficients if not already tabulated */
	if (!tabled) {
		for (jtable = 1; jtable < NTABLE - 1; jtable++) {
			frac = (double)jtable / (double)(NTABLE - 1);
			mksinc(frac, LTABLE, &table[jtable][0]);
		}
		for (jtable = 0; jtable < LTABLE; jtable++) {
			table[0][jtable] = 0.0;
			table[NTABLE - 1][jtable] = 0.0;
		}
		table[0][LTABLE / 2 - 1] = 1.0;
		table[NTABLE - 1][LTABLE / 2] = 1.0;
		tabled = 1;
	}

	/* interpolate using tabulated coefficients */
	intt8r(NTABLE, table, nxin, dxin, fxin, yin, yinl, yinr, nxout, xout, yout);
}
void  *alloc1(size_t n1, size_t size)
{
	void *p;

	if ((p = malloc(n1*size)) == NULL)
		return NULL;
	return p;
}
double  *alloc1double(size_t n1)
{
	return (double*)alloc1(n1, sizeof(double));
}

#define ABS(x) ((x) < 0 ? -(x) : (x))
/* free a 1-d array */
void free1(void *p)
{
	free(p);
}
/* free a 1-d array of doubles */
void free1double(double *p)
{
	free1(p);
}
/*static*/ void unwrap_phase(int n, double w, double *phase)
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
	dphase = alloc1double(n);
	temp = alloc1double(n);

	/* initialize */
	temp[0] = phase[0];
	dphase[0] = 0.0;

	/* compute unwrapped phase at each time step */
	for (i = 1; i < n; ++i) {

		/* compute jump in phase */
		dphase[i] = ABS(phase[i] - phase[i - 1]);

		/* if dphase >= PI/w, use previous dphase value */
		if (ABS(dphase[i] - dphase[i - 1]) >= pibyw)
			dphase[i] = dphase[i - 1];

		/* sum up values in temporary vector */
		temp[i] = temp[i - 1] + dphase[i];
	}

	/* assign values of temporary vector to phase[i] */
	for (i = 0; i<n; ++i) phase[i] = temp[i];

	/* free space */
	free1double(temp);
	free1double(dphase);
}
void  convs(int lx, int ifx, double *x,
	int ly, int ify, double *y,
	int lz, int ifz, double *z)
{
	int ilx = ifx + lx - 1, ily = ify + ly - 1, ilz = ifz + lz - 1,
		i, j, ilow, ihigh, jlow, jhigh;
	double x0, x1, x2, x3, x4, x5, x6, x7, x8, x9,
		x10, x11, x12, x13, x14, x15, x16, x17, x18, x19,
		x20, x21, x22, x23, x24, x25, x26, x27, x28, x29,
		ya, yb, z0, z1, sum;

	x -= ifx;
	y -= ify;
	z -= ifz;


	/* OFF LEFT:  i < ifx+ify */
	ilow = ifz;
	ihigh = ify + ifx - 1;  if (ihigh > ilz) ihigh = ilz;
	for (i = ilow; i <= ihigh; ++i)
		z[i] = 0.0;

	/* ROLLING ON:  ify+ifx <= i < ify+ilx */
	ilow = ify + ifx;  if (ilow<ifz) ilow = ifz;
	ihigh = ify + ilx - 1;  if (ihigh>ilz) ihigh = ilz;
	jlow = ifx;
	jhigh = ilow - ify;
	for (i = ilow; i <= ihigh; ++i, ++jhigh) {
		for (j = jlow, sum = 0.0; j <= jhigh; ++j)
			sum += x[j] * y[i - j];
		z[i] = sum;
	}

	/* MIDDLE:  ify+ilx <= i <= ily+ifx */
	ilow = ify + ilx;  if (ilow < ifz) ilow = ifz;
	ihigh = ily + ifx;  if (ihigh > ilz) ihigh = ilz;
	if (lx == 1) {
		x0 = x[ifx];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 2) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 3) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 4) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 5) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 6) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 7) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 8) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 9) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 10) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 11) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 12) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 13) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 14) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 15) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 16) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 17) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 18) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 19) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 20) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 21) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 22) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 23) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 24) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 25) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		x24 = x[ifx + 24];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;  z1 += x24*ya;
			yb = y[i - ifx - 24];  z0 += x24*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 26) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		x24 = x[ifx + 24];
		x25 = x[ifx + 25];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;  z1 += x24*ya;
			yb = y[i - ifx - 24];  z0 += x24*yb;  z1 += x25*yb;
			ya = y[i - ifx - 25];  z0 += x25*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 27) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		x24 = x[ifx + 24];
		x25 = x[ifx + 25];
		x26 = x[ifx + 26];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;  z1 += x24*ya;
			yb = y[i - ifx - 24];  z0 += x24*yb;  z1 += x25*yb;
			ya = y[i - ifx - 25];  z0 += x25*ya;  z1 += x26*ya;
			yb = y[i - ifx - 26];  z0 += x26*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 28) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		x24 = x[ifx + 24];
		x25 = x[ifx + 25];
		x26 = x[ifx + 26];
		x27 = x[ifx + 27];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;  z1 += x24*ya;
			yb = y[i - ifx - 24];  z0 += x24*yb;  z1 += x25*yb;
			ya = y[i - ifx - 25];  z0 += x25*ya;  z1 += x26*ya;
			yb = y[i - ifx - 26];  z0 += x26*yb;  z1 += x27*yb;
			ya = y[i - ifx - 27];  z0 += x27*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 29) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		x24 = x[ifx + 24];
		x25 = x[ifx + 25];
		x26 = x[ifx + 26];
		x27 = x[ifx + 27];
		x28 = x[ifx + 28];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;  z1 += x24*ya;
			yb = y[i - ifx - 24];  z0 += x24*yb;  z1 += x25*yb;
			ya = y[i - ifx - 25];  z0 += x25*ya;  z1 += x26*ya;
			yb = y[i - ifx - 26];  z0 += x26*yb;  z1 += x27*yb;
			ya = y[i - ifx - 27];  z0 += x27*ya;  z1 += x28*ya;
			yb = y[i - ifx - 28];  z0 += x28*yb;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	else if (lx == 30) {
		x0 = x[ifx];
		x1 = x[ifx + 1];
		x2 = x[ifx + 2];
		x3 = x[ifx + 3];
		x4 = x[ifx + 4];
		x5 = x[ifx + 5];
		x6 = x[ifx + 6];
		x7 = x[ifx + 7];
		x8 = x[ifx + 8];
		x9 = x[ifx + 9];
		x10 = x[ifx + 10];
		x11 = x[ifx + 11];
		x12 = x[ifx + 12];
		x13 = x[ifx + 13];
		x14 = x[ifx + 14];
		x15 = x[ifx + 15];
		x16 = x[ifx + 16];
		x17 = x[ifx + 17];
		x18 = x[ifx + 18];
		x19 = x[ifx + 19];
		x20 = x[ifx + 20];
		x21 = x[ifx + 21];
		x22 = x[ifx + 22];
		x23 = x[ifx + 23];
		x24 = x[ifx + 24];
		x25 = x[ifx + 25];
		x26 = x[ifx + 26];
		x27 = x[ifx + 27];
		x28 = x[ifx + 28];
		x29 = x[ifx + 29];
		for (i = ilow; i <= ihigh - 1; i += 2) {
			ya = y[i + 1 - ifx];  z1 = x0*ya;
			yb = y[i - ifx];  z0 = x0*yb;  z1 += x1*yb;
			ya = y[i - ifx - 1];  z0 += x1*ya;  z1 += x2*ya;
			yb = y[i - ifx - 2];  z0 += x2*yb;  z1 += x3*yb;
			ya = y[i - ifx - 3];  z0 += x3*ya;  z1 += x4*ya;
			yb = y[i - ifx - 4];  z0 += x4*yb;  z1 += x5*yb;
			ya = y[i - ifx - 5];  z0 += x5*ya;  z1 += x6*ya;
			yb = y[i - ifx - 6];  z0 += x6*yb;  z1 += x7*yb;
			ya = y[i - ifx - 7];  z0 += x7*ya;  z1 += x8*ya;
			yb = y[i - ifx - 8];  z0 += x8*yb;  z1 += x9*yb;
			ya = y[i - ifx - 9];  z0 += x9*ya;  z1 += x10*ya;
			yb = y[i - ifx - 10];  z0 += x10*yb;  z1 += x11*yb;
			ya = y[i - ifx - 11];  z0 += x11*ya;  z1 += x12*ya;
			yb = y[i - ifx - 12];  z0 += x12*yb;  z1 += x13*yb;
			ya = y[i - ifx - 13];  z0 += x13*ya;  z1 += x14*ya;
			yb = y[i - ifx - 14];  z0 += x14*yb;  z1 += x15*yb;
			ya = y[i - ifx - 15];  z0 += x15*ya;  z1 += x16*ya;
			yb = y[i - ifx - 16];  z0 += x16*yb;  z1 += x17*yb;
			ya = y[i - ifx - 17];  z0 += x17*ya;  z1 += x18*ya;
			yb = y[i - ifx - 18];  z0 += x18*yb;  z1 += x19*yb;
			ya = y[i - ifx - 19];  z0 += x19*ya;  z1 += x20*ya;
			yb = y[i - ifx - 20];  z0 += x20*yb;  z1 += x21*yb;
			ya = y[i - ifx - 21];  z0 += x21*ya;  z1 += x22*ya;
			yb = y[i - ifx - 22];  z0 += x22*yb;  z1 += x23*yb;
			ya = y[i - ifx - 23];  z0 += x23*ya;  z1 += x24*ya;
			yb = y[i - ifx - 24];  z0 += x24*yb;  z1 += x25*yb;
			ya = y[i - ifx - 25];  z0 += x25*ya;  z1 += x26*ya;
			yb = y[i - ifx - 26];  z0 += x26*yb;  z1 += x27*yb;
			ya = y[i - ifx - 27];  z0 += x27*ya;  z1 += x28*ya;
			yb = y[i - ifx - 28];  z0 += x28*yb;  z1 += x29*yb;
			ya = y[i - ifx - 29];  z0 += x29*ya;
			z[i + 1] = z1;
			z[i] = z0;
		}
	}
	if (ihigh >= ilow && (ihigh - ilow) % 2 == 0) {
		ilow = ihigh;
		jlow = ifx;
		jhigh = ilx;
		for (i = ilow; i <= ihigh; ++i) {
			for (j = jlow, sum = 0.0; j <= jhigh; ++j)
				sum += x[j] * y[i - j];
			z[i] = sum;
		}
	}

	/* ROLLING OFF:  ily+ifx < i <= ily+ilx */
	ilow = ily + ifx + 1;  if (ilow < ifz) ilow = ifz;
	ihigh = ily + ilx;  if (ihigh > ilz) ihigh = ilz;
	jlow = ilow - ily;
	jhigh = ilx;
	for (i = ilow; i <= ihigh; ++i, ++jlow) {
		for (j = jlow, sum = 0.0; j <= jhigh; ++j)
			sum += x[j] * y[i - j];
		z[i] = sum;
	}

	/* OFF RIGHT:  ily+ilx < i */
	ilow = ily + ilx + 1;  if (ilow < ifz) ilow = ifz;
	ihigh = ilz;
	for (i = ilow; i <= ihigh; ++i)
		z[i] = 0.0;
}
void  conv(int lx, int ifx, double *x,
	int ly, int ify, double *y,
	int lz, int ifz, double *z)
{
	int ilx = ifx + lx - 1, ily = ify + ly - 1, ilz = ifz + lz - 1,
		i, j, ilow, ihigh, jlow, jhigh;
	double sa, sb, xa, xb, ya, yb, *t;

	/* if x is longer than y, swap x and y */
	if (lx > ly) {
		i = ifx;  ifx = ify;  ify = i;
		i = ilx;  ilx = ily;  ily = i;
		i = lx;  lx = ly;  ly = i;
		t = x;  x = y;  y = t;
	}

	/* handle short x with special code */
	if (lx >= 1 && lx <= 30) {
		convs(lx, ifx, x, ly, ify, y, lz, ifz, z);
		return;
	}

	/* adjust pointers for indices of first samples */
	x -= ifx;
	y -= ify;
	z -= ifz;

	/* OFF LEFT:  i < ify+ifx */

	/* zero output for all i */
	ilow = ifz;
	ihigh = ify + ifx - 1;  if (ihigh > ilz) ihigh = ilz;
	for (i = ilow; i <= ihigh; ++i)
		z[i] = 0.0;

	/* ROLLING ON:  ify+ifx <= i < ify+ilx */

	/* if necessary, do one i so that number of j in overlap is odd */
	if (i < ify + ilx && i <= ilz) {
		jlow = ifx;
		jhigh = i - ify;
		if ((jhigh - jlow) % 2) {
			sa = 0.0;
			for (j = jlow; j <= jhigh; ++j)
				sa += x[j] * y[i - j];
			z[i++] = sa;
		}
	}

	/* loop over pairs of i and j */
	ilow = i;
	ihigh = ilx + ify - 1;  if (ihigh > ilz) ihigh = ilz;
	jlow = ifx;
	jhigh = ilow - ify;
	for (i = ilow; i < ihigh; i += 2, jhigh += 2) {
		sa = sb = 0.0;
		xb = x[jhigh + 1];
		yb = 0.0;
		for (j = jhigh; j >= jlow; j -= 2) {
			sa += xb*yb;
			ya = y[i - j];
			sb += xb*ya;
			xa = x[j];
			sa += xa*ya;
			yb = y[i + 1 - j];
			sb += xa*yb;
			xb = x[j - 1];
		}
		z[i] = sa;
		z[i + 1] = sb;
	}

	/* if number of i is odd */
	if (i == ihigh) {
		jlow = ifx;
		jhigh = i - ify;
		sa = 0.0;
		for (j = jlow; j <= jhigh; ++j)
			sa += x[j] * y[i - j];
		z[i++] = sa;
	}

	/* MIDDLE:  ify+ilx <= i <= ily+ifx */

	/* determine limits for i and j */
	ilow = i;
	ihigh = ily + ifx;  if (ihigh > ilz) ihigh = ilz;
	jlow = ifx;
	jhigh = ilx;

	/* if number of j is even, do j in pairs with no leftover */
	if ((jhigh - jlow) % 2) {
		for (i = ilow; i < ihigh; i += 2) {
			sa = sb = 0.0;
			yb = y[i + 1 - jlow];
			xa = x[jlow];
			for (j = jlow; j < jhigh; j += 2) {
				sb += xa*yb;
				ya = y[i - j];
				sa += xa*ya;
				xb = x[j + 1];
				sb += xb*ya;
				yb = y[i - 1 - j];
				sa += xb*yb;
				xa = x[j + 2];
			}
			z[i] = sa;
			z[i + 1] = sb;
		}

		/* else, number of j is odd, so do j in pairs with leftover */
	}
	else {
		for (i = ilow; i < ihigh; i += 2) {
			sa = sb = 0.0;
			yb = y[i + 1 - jlow];
			xa = x[jlow];
			for (j = jlow; j < jhigh; j += 2) {
				sb += xa*yb;
				ya = y[i - j];
				sa += xa*ya;
				xb = x[j + 1];
				sb += xb*ya;
				yb = y[i - 1 - j];
				sa += xb*yb;
				xa = x[j + 2];
			}
			z[i] = sa + x[jhigh] * y[i - jhigh];
			z[i + 1] = sb + x[jhigh] * y[i + 1 - jhigh];
		}
	}

	/* if number of i is odd */
	if (i == ihigh) {
		sa = 0.0;
		for (j = jlow; j <= jhigh; ++j)
			sa += x[j] * y[i - j];
		z[i++] = sa;
	}

	/* ROLLING OFF:  ily+ifx < i <= ily+ilx */

	/* if necessary, do one i so that number of j in overlap is even */
	if (i <= ily + ilx && i <= ilz) {
		jlow = i - ily;
		jhigh = ilx;
		if (!((jhigh - jlow) % 2)) {
			sa = 0.0;
			for (j = jlow; j <= jhigh; ++j)
				sa += x[j] * y[i - j];
			z[i++] = sa;
		}
	}

	/* number of j is now even, so loop over both i and j in pairs */
	ilow = i;
	ihigh = ily + ilx;  if (ihigh > ilz) ihigh = ilz;
	jlow = ilow - ily;
	jhigh = ilx - 2; /* Dave's new patch */
	for (i = ilow; i < ihigh; i += 2, jlow += 2) {
		sa = sb = 0.0;
		xa = x[jlow];
		yb = 0.0;
		for (j = jlow; j < jhigh; j += 2) {
			sb += xa*yb;
			ya = y[i - j];
			sa += xa*ya;
			xb = x[j + 1];
			sb += xb*ya;
			yb = y[i - 1 - j];
			sa += xb*yb;
			xa = x[j + 2];
		}
		sb += xa*yb;
		ya = y[i - j];
		sa += xa*ya;
		xb = x[j + 1];
		sb += xb*ya;
		yb = y[i - 1 - j];
		sa += xb*yb;
		z[i] = sa;
		z[i + 1] = sb;
	}

	/* if number of i is odd */
	if (i == ihigh) {
		jlow = i - ily;
		jhigh = ilx;
		sa = 0.0;
		for (j = jlow; j <= jhigh; ++j)
			sa += x[j] * y[i - j];
		z[i++] = sa;
	}

	/* OFF RIGHT:  ily+ilx < i */

	/* zero output for all i */
	ilow = i;
	ihigh = ilz;
	for (i = ilow; i <= ihigh; ++i)
		z[i] = 0.0;
}

void _xcor_(int lx, int ifx, double *x,
	int ly, int ify, double *y,
	int lz, int ifz, double *z)
{
	int i, j;
	double *xr;

	xr = (double *)calloc(lx, sizeof(double));
	//xr = new double(lx);
	for (i = 0, j = lx - 1; i<lx; ++i, --j)
		xr[i] = x[j];
	conv(lx, 1 - ifx - lx, xr, ly, ify, y, lz, ifz, z);
	free(xr);
}
int fft(double *fr, double *fi, int n, int flag)
{
	int     mp, arg, cntl, p1, p2;
	int     i, j, k, a, b;
	double   sign, pr, pi, harm, t;
	double   *ca, *sa;
	ca = (double*)calloc(n, sizeof(double));
	sa = (double*)calloc(n, sizeof(double));
	if (ca == NULL || sa == NULL) return(0);
	j = 0;
	if (flag != 0)
	{
		sign = 1.0;
		for (i = 0; i<n; ++i)
		{
			fr[i] /= n;
			fi[i] /= n;
		}
	}
	else
		sign = -1.0;
	for (i = 0; i <= n - 2; ++i)
	{
		if (i<j)
		{
			t = fr[i];
			fr[i] = fr[j];
			fr[j] = t;
			t = fi[i];
			fi[i] = fi[j];
			fi[j] = t;
		}
		k = n / 2;
		while (k <= j)
		{
			j -= k;
			k /= 2;
		}
		j += k;
	}
	mp = 0;
	i = n;
	while (i != 1)
	{
		mp += 1;
		i /= 2;
	}
	harm = 2 * PI / n;
	for (i = 0; i<n; ++i)
	{
		sa[i] = sign*sin(harm*i);
		ca[i] = cos(harm*i);
	}
	a = 2;
	b = 1;
	for (cntl = 1; cntl <= mp; ++cntl)
	{
		p1 = n / a;
		p2 = 0;
		for (k = 0; k<b; ++k)
		{
			i = k;
			while (i<n)
			{
				arg = i + b;
				if (k == 0)
				{
					pr = fr[arg];
					pi = fi[arg];
				}
				else
				{
					pr = fr[arg] * ca[p2] - fi[arg] * sa[p2];
					pi = fr[arg] * sa[p2] + fi[arg] * ca[p2];
				}
				fr[arg] = fr[i] - pr;
				fi[arg] = fi[i] - pi;
				fr[i] += pr;
				fi[i] += pi;
				i += a;
			}
			p2 += p1;
		}
		a *= 2;
		b *= 2;
	}
	free(ca);
	free(sa);
	return(1);
}
int calSignalSpectrum(double *pData, int sampleNum, int zeroIndex, double *pAmp, double *pPhase)
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

	memset(fr, 0, fftNum*sizeof(double));
	memset(fi, 0, fftNum*sizeof(double));

	memcpy(fr, pData + zeroIndex, (sampleNum - zeroIndex)*sizeof(double));
	for (i = 0; i < zeroIndex; i++)
	{
		fr[fftNum - i - 1] = pData[zeroIndex - i - 1];
	}

	//frequency domain
	fft(fr, fi, fftNum, 0);

	//calculate amplitude spectrum
	double ampmax = 0.;
	double ampsum = 0.;
	int ampMaxIndex = 0;
	for (i = 0; i < fftNum; i++)
	{
		pAmp[i] = (sqrt(fr[i] * fr[i] + fi[i] * fi[i]))/2./PI;
		if (pAmp[i] > ampmax)
		{
			ampmax = pAmp[i];
			ampMaxIndex = i;
		}
		ampsum += pAmp[i];
	}

	//normalize the amplitude
	// 	for (i = 0; i < fftNum; i++)
	// 		pAmp[i] = pAmp[i] / ampmax;

	ampsum /= ampmax;

	//calculate phase spectrum

	double epsamp = 1e-6*ampmax;
	for (i = 0; i < fftNum; ++i)
	{
		double re = fr[i];
		double im = fi[i];
		if ((re*re + im*im) >= epsamp)
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
	double percamp2 = (1. - percamp/100.) / 2.;
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
		for (i = fftNum/2-1; i >= 0; i--)
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

QStringList CXWavelet::GetDescription()
{
	QStringList strListDesc;

	strListDesc << "Points number is" << QString::number(m_nSamplingNum);
	strListDesc << "Data range is " << QString::number(m_dStart) + " to " +
		QString::number(m_dStart + m_dStep * (m_nSamplingNum - 1));
	strListDesc << "Sample interval is" << QString::number(m_dStep);

	return strListDesc;
}