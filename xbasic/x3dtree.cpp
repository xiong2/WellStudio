#include "x3dtree.h"
#include "xfunctiontemplate.h"

const double CX3dtree::BIG(1.0e99);

CX3dtree::CX3dtree(double *pX, double *pY, double *pZ, int nPtNum) :
	m_nPts(nPtNum), m_vecPtIndex(m_nPts), m_vecRptIndex(m_nPts)
{
	m_vecPts.reserve(m_nPts);
	for (int i = 0; i < nPtNum; ++i) {
		Point3D pt(pX[i], pY[i], pZ[i]);
		m_vecPts.push_back(pt);
	}

	Create3DTree();
}

CX3dtree::CX3dtree(double *pPts, int nPtNum) :
	m_nPts(nPtNum / 3), m_vecPtIndex(m_nPts), m_vecRptIndex(m_nPts)
{
	m_vecPts.reserve(m_nPts);
	for (int i = 0; i < nPtNum; i += 3) {
		Point3D pt(pPts[i], pPts[i + 1], pPts[i + 2]);
		m_vecPts.push_back(pt);
	}

	Create3DTree();
}

double CX3dtree::dist(const Point3D &p, const Point3D &q)
{
	double dd = 0.0;
	for (int i = 0; i < 3; ++i)
		dd += SQR(q.x[i] - p.x[i]);
	return sqrt(dd);
}

double CX3dtree::dist(const Box3D &b, const Point3D &p)
{
	double dd = 0.0;
	for (int i = 0; i < 3; ++i)
	{
		if (p.x[i] < b.lo.x[i]) dd += SQR(p.x[i] - b.lo.x[i]);
		if (p.x[i] > b.hi.x[i]) dd += SQR(p.x[i] - b.hi.x[i]);
	}
	return sqrt(dd);
}

int CX3dtree::selecti(const int k, int *indx, int n, double *arr)
{
	int i, ia, ir, j, l, mid;
	double a;

	l = 0;
	ir = n - 1;
	for (;;) {
		if (ir <= l + 1) {
			if (ir == l + 1 && arr[indx[ir]] < arr[indx[l]])
				qSwap(indx[l], indx[ir]);
			return indx[k];
		}
		else {
			mid = (l + ir) >> 1;
			qSwap(indx[mid], indx[l + 1]);
			if (arr[indx[l]] > arr[indx[ir]]) qSwap(indx[l], indx[ir]);
			if (arr[indx[l + 1]] > arr[indx[ir]]) qSwap(indx[l + 1], indx[ir]);
			if (arr[indx[l]] > arr[indx[l + 1]]) qSwap(indx[l], indx[l + 1]);
			i = l + 1;
			j = ir;
			ia = indx[l + 1];
			a = arr[ia];
			for (;;) {
				do i++; while (arr[indx[i]] < a);
				do j--; while (arr[indx[j]] > a);
				if (j < i) break;
				qSwap(indx[i], indx[j]);
			}
			indx[l + 1] = indx[j];
			indx[j] = ia;
			if (j >= k) ir = j - 1;
			if (j <= k) l = i;
		}
	}
}

double CX3dtree::disti(int jpt, int kpt)
{
	if (jpt == kpt) return BIG;
	else return dist(m_vecPts[jpt], m_vecPts[kpt]);
}

int CX3dtree::locate(Point3D pt)
{
	int nb, d1, jdim;
	nb = jdim = 0;
	while (m_pNodes[nb].dau1) {
		d1 = m_pNodes[nb].dau1;
		if (pt.x[jdim] <= m_pNodes[d1].hi.x[jdim]) nb = d1;
		else nb = m_pNodes[nb].dau2;
		jdim = ++jdim % 3;
	}
	return nb;
}

int CX3dtree::locate(int jpt)
{
	int nb, d1, jh;
	jh = m_vecRptIndex[jpt];
	nb = 0;
	while (m_pNodes[nb].dau1) {
		d1 = m_pNodes[nb].dau1;
		if (jh <= m_pNodes[d1].pthi) nb = d1;
		else nb = m_pNodes[nb].dau2;
	}
	return nb;
}

int CX3dtree::nearest(double x, double y, double z)
{
	int i, k, nrst = 0, ntask;
	int task[50];
	double dnrst = BIG, d;
	Point3D pt(x, y, z);
	k = locate(pt);
	for (i = m_pNodes[k].ptlo; i <= m_pNodes[k].pthi; i++) {
		d = dist(m_vecPts[m_vecPtIndex[i]], pt);
		if (d < dnrst) {
			nrst = m_vecPtIndex[i];
			dnrst = d;
		}
	}
	task[1] = 0;
	ntask = 1;
	while (ntask) {
		k = task[ntask--];
		if (dist(m_pNodes[k], pt) < dnrst) {
			if (m_pNodes[k].dau1) {
				task[++ntask] = m_pNodes[k].dau1;
				task[++ntask] = m_pNodes[k].dau2;
			}
			else {
				for (i = m_pNodes[k].ptlo; i <= m_pNodes[k].pthi; i++) {
					d = dist(m_vecPts[m_vecPtIndex[i]], pt);
					if (d < dnrst) {
						nrst = m_vecPtIndex[i];
						dnrst = d;
					}
				}
			}
		}
	}
	return nrst;
}

void CX3dtree::nnearest(int jpt, int *nn, double *dn, int n)
{
	int i, k, ntask, kp;
	int task[50];
	double d;
	if (n > m_nPts - 1) throw("too many neighbors requested");
	for (i = 0; i < n; i++) dn[i] = BIG;
	kp = m_pNodes[locate(jpt)].mom;
	while (m_pNodes[kp].pthi - m_pNodes[kp].ptlo < n) kp = m_pNodes[kp].mom;
	for (i = m_pNodes[kp].ptlo; i <= m_pNodes[kp].pthi; i++) {
		if (jpt == m_vecPtIndex[i]) continue;
		d = disti(m_vecPtIndex[i], jpt);
		if (d < dn[0]) {
			dn[0] = d;
			nn[0] = m_vecPtIndex[i];
			if (n > 1) sift_down(dn, nn, n);
		}
	}
	task[1] = 0;
	ntask = 1;
	while (ntask) {
		k = task[ntask--];
		if (k == kp) continue;
		if (dist(m_pNodes[k], m_vecPts[jpt]) < dn[0]) {
			if (m_pNodes[k].dau1) {
				task[++ntask] = m_pNodes[k].dau1;
				task[++ntask] = m_pNodes[k].dau2;
			}
			else {
				for (i = m_pNodes[k].ptlo; i <= m_pNodes[k].pthi; i++) {
					d = disti(m_vecPtIndex[i], jpt);
					if (d < dn[0]) {
						dn[0] = d;
						nn[0] = m_vecPtIndex[i];
						if (n > 1) sift_down(dn, nn, n);
					}
				}
			}
		}
	}
	return;
}

void CX3dtree::sift_down(double *heap, int *ndx, int nn)
{
	int n = nn - 1;
	int j, jold, ia;
	double a;
	a = heap[0];
	ia = ndx[0];
	jold = 0;
	j = 1;
	while (j <= n) {
		if (j < n && heap[j] < heap[j + 1]) j++;
		if (a >= heap[j]) break;
		heap[jold] = heap[j];
		ndx[jold] = ndx[j];
		jold = j;
		j = 2 * j + 1;
	}
	heap[jold] = a;
	ndx[jold] = ia;
}

int CX3dtree::locatenear(double x, double y, double z, double r, int *list, int nmax)
{
	int k, i, nb, nbold, nret, ntask, jdim, d1, d2;
	int task[50];
	nb = jdim = nret = 0;
	Point3D pt(x, y, z);
	if (r < 0.0) throw("radius must be nonnegative");
	while (m_pNodes[nb].dau1) {
		nbold = nb;
		d1 = m_pNodes[nb].dau1;
		d2 = m_pNodes[nb].dau2;
		if (pt.x[jdim] + r <= m_pNodes[d1].hi.x[jdim]) nb = d1;
		else if (pt.x[jdim] - r >= m_pNodes[d2].lo.x[jdim]) nb = d2;
		jdim = ++jdim % 3;
		if (nb == nbold) break;
	}
	task[1] = nb;
	ntask = 1;
	while (ntask) {
		k = task[ntask--];
		if (dist(m_pNodes[k], pt) > r) continue;
		if (m_pNodes[k].dau1) {
			task[++ntask] = m_pNodes[k].dau1;
			task[++ntask] = m_pNodes[k].dau2;
		}
		else {
			for (i = m_pNodes[k].ptlo; i <= m_pNodes[k].pthi; i++) {
				if (dist(m_vecPts[m_vecPtIndex[i]], pt) <= r && nret < nmax)
					list[nret++] = m_vecPtIndex[i];
				if (nret == nmax) return nmax;
			}
		}
	}
	return nret;
}

bool CX3dtree::Create3DTree()
{
	int ntmp, m, k, kk, j, nowtask, jbox, np, tmom, tdim, ptlo, pthi;
	int *hp;
	double *cp;
	int taskmom[50], taskdim[50];	// Enough stack for 2^50 points! 
	for (k = 0; k < m_nPts; k++) m_vecPtIndex[k] = k;	// Initialize the index of points
	// Calculate the number of boxes and allocate memory for them.
	m = 1;
	for (ntmp = m_nPts; ntmp; ntmp >>= 1) {
		m <<= 1;
	}
	m_nBoxes = 2 * m_nPts - (m >> 1);
	if (m < m_nBoxes) m_nBoxes = m;
	m_nBoxes--;

	try {
		m_pNodes = new BoxNode[m_nBoxes];
		// Copy the point coordinates into a contiguous array
		m_pCoord = new double[3 * m_nPts];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	for (j = 0, kk = 0; j < 3; j++, kk += m_nPts) {
		for (k = 0; k < m_nPts; k++) m_pCoord[kk + k] = m_vecPts[k].x[j];
	}
	// Initialize the root box and put it on the task list for subdivision.
	Point3D lo(-BIG, -BIG, -BIG), hi(BIG, BIG, BIG);
	m_pNodes[0] = BoxNode(lo, hi, 0, 0, 0, 0, m_nPts - 1);
	jbox = 0;
	taskmom[1] = 0;	// Which box
	taskdim[1] = 0; // Which dimension
	nowtask = 1;
	while (nowtask) {		// Main loop over pending tasks
		tmom = taskmom[nowtask];
		tdim = taskdim[nowtask--];
		ptlo = m_pNodes[tmom].ptlo;
		pthi = m_pNodes[tmom].pthi;
		hp = &m_vecPtIndex[ptlo];	// Points to left end of subdivision. 
		cp = &m_pCoord[tdim*m_nPts];	// Points to coordinate list for current dim
		np = pthi - ptlo + 1;	// Number of points in the subdivision
		kk = (np - 1) / 2;	// Index of last point on left (boundary point). 
		(void)selecti(kk, hp, np, cp);	// Here is where all the work is done
		// Now create the daughters and push them onto the task list if they need further subdividing
		hi = m_pNodes[tmom].hi;
		lo = m_pNodes[tmom].lo;
		hi.x[tdim] = lo.x[tdim] = m_pCoord[tdim*m_nPts + hp[kk]];
		m_pNodes[++jbox] = BoxNode(m_pNodes[tmom].lo, hi, tmom, 0, 0, ptlo, ptlo + kk);
		m_pNodes[++jbox] = BoxNode(lo, m_pNodes[tmom].hi, tmom, 0, 0, ptlo + kk + 1, pthi);
		m_pNodes[tmom].dau1 = jbox - 1;
		m_pNodes[tmom].dau2 = jbox;
		if (kk > 1) {
			taskmom[++nowtask] = jbox - 1;
			taskdim[nowtask] = (tdim + 1) % 3;
		}
		if (np - kk > 3) {
			taskmom[++nowtask] = jbox;
			taskdim[nowtask] = (tdim + 1) % 3;
		}
	}
	for (j = 0; j < m_nPts; j++) m_vecRptIndex[m_vecPtIndex[j]] = j;	// Create reverse index
	delete[] m_pCoord;

	return true;
}
