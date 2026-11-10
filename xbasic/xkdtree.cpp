#pragma warning( push ,0 )
#include "xkdtree.h"
#include "xmathmacro.h"
#include <QtGlobal>
#include <vector>
#include <cmath>
#include "xfunctiontemplate.h"


#pragma warning( pop )

CXKDTree::CXKDTree (double* pX, double* pY, int nPtNum)
: m_pX (pX), m_pY (pY), m_nPtNum (nPtNum)
{
	m_pBoxNode = NULL;
	m_pPtIndex = NULL;
	m_pRevPtIndex = NULL;
}

CXKDTree::~CXKDTree()
{
	if (NULL != m_pBoxNode)		delete []m_pBoxNode;
	if (NULL != m_pPtIndex)			delete []m_pPtIndex;
	if (NULL != m_pRevPtIndex)	delete []m_pRevPtIndex;
}

int CXKDTree::select(int k, int* index, int n, double* pArray)
{
	int i,ia,ir,j,l,mid;
	double a;

	l=0;
	ir=n-1;
	for (;;) 
	{
		if (ir <= l+1) 
		{
			if (ir == l+1 && pArray[index[ir]] < pArray[index[l]])
				qSwap(index[l],index[ir]);

			return index[k];
		} 
		else 
		{
			mid=(l+ir) >> 1;
			qSwap(index[mid],index[l+1]);

			if (pArray[index[l]] > pArray[index[ir]]) 
				qSwap(index[l],index[ir]);

			if (pArray[index[l+1]] > pArray[index[ir]]) 
				qSwap(index[l+1],index[ir]);

			if (pArray[index[l]] > pArray[index[l+1]]) 
				qSwap(index[l],index[l+1]);

			i=l+1;
			j=ir;
			ia = index[l+1];
			a=pArray[ia];
			for (;;)
			{
				do i++; while (pArray[index[i]] < a);
				do j--; while (pArray[index[j]] > a);
				if (j < i) 
					break;
				qSwap(index[i],index[j]);
			}
			index[l+1]=index[j];
			index[j]=ia;
			if (j >= k) ir=j-1;
			if (j <= k) l=i;
		}
	}
}

bool CXKDTree::CreateKDTree()
{
	// Get the total number of the boxes
	int m = 1;
	for (int i=m_nPtNum; i != 0; i >>= 1) 
	{
		m <<= 1;
	}
	m_nBoxNum = 2*m_nPtNum - (m >> 1);
	if ( m < m_nBoxNum) 
		m_nBoxNum = m;
	m_nBoxNum--;

	// Allocate memory
	try
	{
		m_pBoxNode = new BoxNode[m_nBoxNum];
		m_pPtIndex = new int [m_nPtNum];
		m_pRevPtIndex = new int [m_nPtNum];
	}
	catch(std::bad_alloc)
	{
		return false;
	}

	// Initialization
	for (int i=0; i<m_nPtNum; ++i)
		m_pPtIndex[i] = i;


	int k,kk,j,nowtask,jbox,np,tmom,tdim,ptlo,pthi;
	int *hp;
	double *cp;
	int taskmom[50], taskdim[50];	

	Point2D lo(M_FLT_NEGATIVEMAX, M_FLT_NEGATIVEMAX);
	Point2D hi(M_FLT_MAX, M_FLT_MAX);

	m_pBoxNode[0] = BoxNode(lo, hi, 0, 0, 0, 0, m_nPtNum-1);
	jbox = 0;
	taskmom[1] = 0;
	taskdim[1] = 0;
	nowtask = 1;
	while (nowtask)
	{
		tmom = taskmom[nowtask];
		tdim = taskdim[nowtask--];
		ptlo = m_pBoxNode[tmom].ptlo;
		pthi = m_pBoxNode[tmom].pthi;
		hp = &m_pPtIndex[ptlo];

		if (tdim == 0)
			cp = m_pX;
		else
			cp = m_pY;
		
		np = pthi - ptlo + 1;
		kk = (np-1)/2;
		select(kk,hp,np,cp);
		hi = m_pBoxNode[tmom].hi;
		lo = m_pBoxNode[tmom].lo;

		hi.x[tdim] = lo.x[tdim] = cp[ hp[kk]];

		m_pBoxNode[++jbox] = BoxNode(m_pBoxNode[tmom].lo,hi,tmom,0,0,ptlo,ptlo+kk);
		m_pBoxNode[++jbox] = BoxNode(lo, m_pBoxNode[tmom].hi,tmom,0,0,ptlo+kk+1,pthi);

		m_pBoxNode[tmom].dau1 = jbox-1;
		m_pBoxNode[tmom].dau2 = jbox;

		if (kk > 1) 
		{
			taskmom[++nowtask] = jbox-1;
			taskdim[nowtask] = (tdim+1) % 2;
		}
		if (np - kk > 3)
		{
			taskmom[++nowtask] = jbox;
			taskdim[nowtask] = (tdim+1) % 2;
		}
	}

	for (j=0; j<m_nPtNum; ++j) 
		m_pRevPtIndex[m_pPtIndex[j]] = j;

	return true;
}

double CXKDTree::dist (double x0, double y0, double x1, double y1)
{
	double d = SQR(x0- x1);
	d += SQR(y0 - y1);

	return sqrt(d);
}

double CXKDTree::dist (const Box& b, double x, double y)
{
	double d = 0.;

	if (x < b.lo.x[0])
		d += SQR(x - b.lo.x[0]);

	if (x > b.hi.x[0])
		d += SQR(x - b.hi.x[0]);

	if (y < b.lo.x[1])
		d += SQR(y - b.lo.x[1]);

	if (y > b.hi.x[1])
		d += SQR(y - b.hi.x[1]);

	return sqrt (d);
}

double CXKDTree::disti (int i, int j)
{
	if (i == j)
		return M_FLT_MAX;
	else
	{
		return  dist (m_pX[i], m_pY[i], m_pX[j], m_pY[j]);
	}		
}

void CXKDTree::sift_down(double *heap, int *ndx, int nn) 
{
	int n = nn - 1;
	int j, jold, ia;
	double a;
	a = heap[0];
	ia = ndx[0];
	jold = 0;
	j = 1;
	while (j <= n) 
	{
		if (j < n && heap[j] < heap[j+1]) 
		{
			j++;
		}

		if (a >= heap[j]) 
		{
			break;
		}
		heap[jold] = heap[j];
		ndx[jold] = ndx[j];
		jold = j;
		j = 2*j + 1;
	}
	heap[jold] = a;
	ndx[jold] = ia;
}


int CXKDTree::locate(double dX, double dY) 
{
	int nb,d1,jdim;
	nb = jdim = 0;
	double dXY;
	while ( m_pBoxNode[nb].dau1)
	{
		d1 = m_pBoxNode[nb].dau1;

		if (jdim == 0)
			dXY = dX;
		else
			dXY = dY;

		if (dXY <= m_pBoxNode[d1].hi.x[jdim]) 
		{
			nb=d1;
		}
		else 
		{
			nb = m_pBoxNode[nb].dau2;
		}

		jdim = ++jdim % 2;
	}
	return nb;
}

int CXKDTree::NNearest(double dX, double dY, int *nn, double *dn, int n)
{
	int i,k,ntask,kp;
	int task[50];
	double d;
	if (n > m_nPtNum-1)
	{
		return -1;
	}

	for (i=0; i<n; i++) 
	{
		dn[i] = M_FLT_MAX;
	}	

	// Tell if the point (dX, dY) is among the points
	int iBoxIndex = locate(dX, dY);
	for (i=m_pBoxNode[iBoxIndex].ptlo; i<=m_pBoxNode[iBoxIndex].pthi; ++i)
	{
		double xTmp = m_pX[m_pPtIndex[i]];
		double yTmp = m_pY[m_pPtIndex[i]];

		if (qAbs(dX-xTmp) < 0.001 && qAbs(dY-yTmp) < 0.001)
		{
			nn[0] = m_pPtIndex[i];
			return 0; 
		}
	}

	kp = m_pBoxNode[iBoxIndex].mom;

	while (m_pBoxNode[kp].pthi - m_pBoxNode[kp].ptlo < n) 
	{
		kp = m_pBoxNode[kp].mom;
	}

	for (i=m_pBoxNode[kp].ptlo; i<=m_pBoxNode[kp].pthi; ++i)
	{
		d = dist(dX, dY, m_pX[m_pPtIndex[i]], m_pY[m_pPtIndex[i]]);

		if (d < dn[0]) 
		{
			dn[0] = d;
			nn[0] = m_pPtIndex[i];
			if (n>1) 
				sift_down(dn, nn, n);
		}
	}
	task[1] = 0;
	ntask = 1;
	while (ntask)
	{
		k = task[ntask--];
		if (k == kp) 
			continue;
		if (dist(m_pBoxNode[k], dX, dY) < dn[0]) 
		{
			if (m_pBoxNode[k].dau1)
			{
				task[++ntask] = m_pBoxNode[k].dau1;
				task[++ntask] = m_pBoxNode[k].dau2;
			} 
			else
			{
				for (i=m_pBoxNode[k].ptlo; i<=m_pBoxNode[k].pthi; ++i)
				{
					d = dist(dX, dY, m_pX[m_pPtIndex[i]], m_pY[m_pPtIndex[i]]);
					if (d < dn[0])
					{
						dn[0] = d;
						nn[0] = m_pPtIndex[i];
						if (n>1)
							sift_down(dn,nn,n);
					}
				}
			}
		}
	}
	return 1;
}

int CXKDTree::NNearest(double dX, double dY, double dRadius, int *nn, int n)
{
	// Tell if the point (dX, dY) is among the points
	int iBoxIndex = locate(dX, dY);
	for (int i=m_pBoxNode[iBoxIndex].ptlo; i<=m_pBoxNode[iBoxIndex].pthi; ++i)
	{
		double xTmp = m_pX[m_pPtIndex[i]];
		double yTmp = m_pY[m_pPtIndex[i]];

		if (qAbs(dX-xTmp) < 0.001 && qAbs(dY-yTmp) < 0.001)
		{
			nn[0] = m_pPtIndex[i];
			return -1; 
		}
	}

	int k, i, nb, nbold, nret, ntask, jdim, d1, d2;
	int task[50];
	double dXY;

	nb = jdim = nret = 0;

	if (dRadius < 0.0)
		return -2;

	while(m_pBoxNode[nb].dau1)
	{
		nbold = nb;
		d1 = m_pBoxNode[nb].dau1;
		d2 = m_pBoxNode[nb].dau2;

		if (jdim == 0)
			dXY = dX;
		else
			dXY = dY;

		if (dXY + dRadius <= m_pBoxNode[d1].hi.x[jdim])
			nb = d1;
		else if (dXY - dRadius >= m_pBoxNode[d2].lo.x[jdim])
			nb = d2;

		jdim = ++jdim%2;
		if (nb == nbold)
			break;
	}

	task[1] = nb;
	ntask = 1;
	
	while(ntask)
	{
		k = task[ntask--];
		if (dist(m_pBoxNode[k], dX, dY) > dRadius)
			continue;

		if (m_pBoxNode[k].dau1)
		{
			task[++ntask] = m_pBoxNode[k].dau1;
			task[++ntask] = m_pBoxNode[k].dau2;
		}
		else
		{
			for (i=m_pBoxNode[k].ptlo; i<=m_pBoxNode[k].pthi; ++i)
			{
				if (dist(dX, dY, m_pX[m_pPtIndex[i]], m_pY[m_pPtIndex[i]]) <= dRadius && nret < n)
					nn[nret++] = m_pPtIndex[i];
				if (nret == n)
					return n;
			}
		}
	}

	return nret;
}