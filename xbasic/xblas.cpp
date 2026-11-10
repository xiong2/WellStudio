#pragma warning( push ,0 )
#include <QtGlobal>
#include <memory>
#include <cstring>
#include <cmath>
#include "xblas.h"
#include <limits>
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include <vector>

#pragma warning( pop )

#ifndef GMSIGNV
#define GMSIGNV(a,b) ((b) >= 0.0 ? qAbs(a) : -qAbs(a))
#endif

double NXBLAS::Pythag(const double a, const double b)
{
    double absa = qAbs(a);
    double absb = qAbs(b);

	return (absa > absb ? absa*sqrt(1.0+(absb/absa)*(absb/absa)) :
		(absb == 0.0 ? 0.0 : absb*sqrt(1.0+(absa/absb)*(absa/absb))));
}

float NXBLAS::Pythag(const float a, const float b)
{
    float absa = qAbs(a);
    float absb = qAbs(b);

	return (absa > absb ? absa*sqrt(1.0f+(absb/absa)*(absb/absa)) :
		(absb == 0.0f ? 0.0f : absb*sqrt(1.0f+(absa/absb)*(absa/absb))));
}

bool NXBLAS::SolveLinearEQU_LU(float **a, float *x, float *b, const int n, int* index, float* v)
{
	// The Beginning of LU Decomposition
	float big, temp;
	float d=1.0f;
		
	int i,j,k,imax=0;

	for (i=0;i<n;i++)
	{
		big=0.0f;

		for (j=0;j<n;j++)
		{
			if ((temp = qAbs(a[i][j])) > big) 
                big=temp;
		}
			
		if (big == 0.0)
            return false;

		v[i]= (float)1.0/big;
	}

	for (k=0;k<n;k++)
	{
		big=0.0;

		for (i=k;i<n;i++)
		{
			temp = v[i]*qAbs(a[i][k]);

			if (temp > big) 
			{
				big=temp;
				imax=i;
			}
		}

		if (k != imax) 
		{
			for (j=0;j<n;j++) 
			{
				temp = a[imax][j];
				a[imax][j] = a[k][j];
				a[k][j] = temp;
			}

			d = -d;
			v[imax] = v[k];
		}

		index[k]= imax;

		if (a[k][k] == 0.0) 
            a[k][k] = (float)M_TINY;

		for (i=k+1;i<n;i++)
		{
			temp = a[i][k] /= a[k][k];

			for (j=k+1;j<n;j++)
				a[i][j] -= temp*a[k][j];
		}
	}

	// The End of LU Decomposition
	//Solving The Linear Equation
	float sum;
	int ii=0,ip;

	for (i=0;i<n;i++) x[i] = b[i];

	for (i=0;i<n;i++) 
	{
		ip=index[i];

		sum=x[ip];

		x[ip]=x[i];

		if (ii != 0)
			for (j=ii-1;j<i;j++) sum -= a[i][j]*x[j];

		else if (sum != 0.0) ii=i+1;

		x[i]=sum;
	}

	for (i=n-1;i>=0;i--)
	{
		sum=x[i];

		for (j=i+1;j<n;j++) sum -= a[i][j]*x[j];

		if (qAbs(a[i][i]-M_TINY) < M_TINY) 
            return false;

		x[i]=sum/a[i][i];
	}

	return true;
}

bool NXBLAS::SolveLinearEQU_LU(double **a, double *x, float *b, const int n, int* index, double* v)
{
	// The Beginning of LU Decomposition
	double big, temp;
	double d=1.0;
		
	int i,j,k,imax=0;

	for (i=0;i<n;i++)
	{
		big=0.0f;

		for (j=0;j<n;j++)
		{
			if ((temp = qAbs(a[i][j])) > big) 
                big=temp;
		}
			
		if (big == 0.0)
            return false;

		v[i]= 1.0/big;
	}

	for (k=0;k<n;k++)
	{
		big=0.0;

		for (i=k;i<n;i++)
		{
			temp = v[i]*qAbs(a[i][k]);

			if (temp > big) 
			{
				big=temp;
				imax=i;
			}
		}

		if (k != imax) 
		{
			for (j=0;j<n;j++) 
			{
				temp = a[imax][j];
				a[imax][j] = a[k][j];
				a[k][j] = temp;
			}

			d = -d;
			v[imax] = v[k];
		}

		index[k]= imax;

		if (a[k][k] == 0.0) 
            a[k][k] = (float)M_TINY;

		for (i=k+1;i<n;i++)
		{
			temp = a[i][k] /= a[k][k];

			for (j=k+1;j<n;j++)
				a[i][j] -= temp*a[k][j];
		}
	}

	// The End of LU Decomposition
	//Solving The Linear Equation
	double sum;
	int ii=0,ip;

	for (i=0;i<n;i++) x[i] = b[i];

	for (i=0;i<n;i++) 
	{
		ip=index[i];

		sum=x[ip];

		x[ip]=x[i];

		if (ii != 0)
			for (j=ii-1;j<i;j++) sum -= a[i][j]*x[j];

		else if (sum != 0.0) ii=i+1;

		x[i]=sum;
	}

	for (i=n-1;i>=0;i--)
	{
		sum=x[i];

		for (j=i+1;j<n;j++) sum -= a[i][j]*x[j];

		if (qAbs(a[i][i]-M_TINY) < M_TINY) 
            return false;

		x[i]=sum/a[i][i];
	}

	return true;
}

void NXBLAS::SolveSVD(float** z, float* d, float* e, int n, bool hasVector)
{       
    // Tridiagonalization using Householder Method    
    int l,k,j,i;
	float scale,hh,h,g,f;      
    
	for (i=n-1;i>0;i--) 
    {
		l=i-1;
		h=scale=0.0;

		if (l > 0) 
        {
			for (k=0;k<i;k++)
				scale += qAbs(z[i][k]);

			if (scale == 0.0)
				e[i]=z[i][l];

			else 
            {
				for (k=0;k<i;k++)
                {
					z[i][k] /= scale;
					h += z[i][k]*z[i][k];
				}

				f=z[i][l];
				g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
				e[i]=scale*g;
				h -= f*g;
				z[i][l]=f-g;
				f=0.0;

				for (j=0;j<i;j++)
                {
					if (hasVector)
						z[j][i]=z[i][j]/h;
					g=0.0;
					for (k=0;k<j+1;k++)
						g += z[j][k]*z[i][k];

					for (k=j+1;k<i;k++)
						g += z[k][j]*z[i][k];

					e[j]=g/h;
					f += e[j]*z[i][j];
				}

				hh=f/(h+h);
				for (j=0;j<i;j++) 
                {
					f=z[i][j];
					e[j]=g=e[j]-hh*f;

					for (k=0;k<j+1;k++)
						z[j][k] -= (f*e[k]+g*z[i][k]);
				}
			}
		} 
        else
        {
			e[i]=z[i][l];
        }

		d[i]=h;
	}

	if (hasVector) d[0]=0.0;

	e[0]=0.0;
	for (i=0;i<n;i++) 
    {
		if (hasVector)
        {
			if (d[i] != 0.0)
            {
				for (j=0;j<i;j++)
                {
					g=0.0;
					for (k=0;k<i;k++)
						g += z[i][k]*z[k][j];
					for (k=0;k<i;k++)
						z[k][j] -= g*z[k][i];
				}
			}

			d[i]=z[i][i];
			z[i][i]=1.0;

			for (j=0;j<i;j++) 
                z[j][i]=z[i][j]=0.0;
		}
        else 
        {
			d[i]=z[i][i];
		}
	}


    // QL Decomposition
    int m,iter;
	float s,r,p,dd,c,b;

	for (i=1;i<n;i++) 
        e[i-1]=e[i];

	e[n-1]=0.0;

	for (l=0;l<n;l++)
    {
		iter=0;
		do {
			for (m=l;m<n-1;m++) 
            {
				dd = qAbs(d[m])+qAbs(d[m+1]);

				if (qAbs(e[m]) <= M_FEPS) break;
			}
			if (m != l)
            {
		///		if (iter++ == 30) throw("Too many iterations in tqli");
            	g=(d[l+1]-d[l])/(2.0f*e[l]);
				r= Pythag(g, 1.0f);
				g=d[m]-d[l]+e[l]/(g+GMSIGNV(r,g));
				s=c=1.0;
				p=0.0;

				for (i=m-1;i>=l;i--)
                {
					f=s*e[i];
					b=c*e[i];
					e[i+1]=(r=Pythag(f,g));
					if (r == 0.0) 
                    {
						d[i+1] -= p;
						e[m]=0.0;
						break;
					}
					s=f/r;
					c=g/r;
					g=d[i+1]-p;
					r= (d[i]-g)*s+2.0f*c*b;
					d[i+1]=g+(p=s*r);
					g=c*r-b;

					if (hasVector)
                    {
						for (k=0;k<n;k++) 
                        {
							f=z[k][i+1];
							z[k][i+1]=s*z[k][i]+c*f;
							z[k][i]=c*z[k][i]-s*f;
						}
					}
				}

				if (r == 0.0 && i >= l) continue;

				d[l] -= p;
				e[l]=g;
				e[m]=0.0;
			}

		} while (m != l);
	}
}

void NXBLAS::SolveSVD(double** z, double* d, double* e, int n, bool hasVector)
{       
    // Tridiagonalization using Householder Method    
    int l,k,j,i;
	double scale,hh,h,g,f;      
    
	for (i=n-1;i>0;i--) 
    {
		l=i-1;
		h=scale=0.0;

		if (l > 0) 
        {
			for (k=0;k<i;k++)
				scale += qAbs(z[i][k]);

			if (scale == 0.0)
				e[i]=z[i][l];

			else 
            {
				for (k=0;k<i;k++)
                {
					z[i][k] /= scale;
					h += z[i][k]*z[i][k];
				}

				f=z[i][l];
				g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
				e[i]=scale*g;
				h -= f*g;
				z[i][l]=f-g;
				f=0.0;

				for (j=0;j<i;j++)
                {
					if (hasVector)
						z[j][i]=z[i][j]/h;
					g=0.0;
					for (k=0;k<j+1;k++)
						g += z[j][k]*z[i][k];

					for (k=j+1;k<i;k++)
						g += z[k][j]*z[i][k];

					e[j]=g/h;
					f += e[j]*z[i][j];
				}

				hh=f/(h+h);
				for (j=0;j<i;j++) 
                {
					f=z[i][j];
					e[j]=g=e[j]-hh*f;

					for (k=0;k<j+1;k++)
						z[j][k] -= (f*e[k]+g*z[i][k]);
				}
			}
		} 
        else
        {
			e[i]=z[i][l];
        }

		d[i]=h;
	}

	if (hasVector) d[0]=0.0;

	e[0]=0.0;
	for (i=0;i<n;i++) 
    {
		if (hasVector)
        {
			if (d[i] != 0.0)
            {
				for (j=0;j<i;j++)
                {
					g=0.0;
					for (k=0;k<i;k++)
						g += z[i][k]*z[k][j];
					for (k=0;k<i;k++)
						z[k][j] -= g*z[k][i];
				}
			}

			d[i]=z[i][i];
			z[i][i]=1.0;

			for (j=0;j<i;j++) 
                z[j][i]=z[i][j]=0.0;
		}
        else 
        {
			d[i]=z[i][i];
		}
	}


    // QL Decomposition
    int m,iter;
	double s,r,p,dd,c,b;

	//double eps = std::numeric_limits<double>::epsilon();

	for (i=1;i<n;i++) 
        e[i-1]=e[i];

	e[n-1]=0.0;

	for (l=0;l<n;l++)
    {
		iter=0;
		do {
			for (m=l;m<n-1;m++) 
            {
				dd = qAbs(d[m])+qAbs(d[m+1]);


				if (qAbs(e[m]) <= M_DEPS) break;
			}
			if (m != l)
            {
		///		if (iter++ == 30) throw("Too many iterations in tqli");
            	g=(d[l+1]-d[l])/(2.0*e[l]);
				r= Pythag(g, 1.0);
				g=d[m]-d[l]+e[l]/(g+GMSIGNV(r,g));
				s=c=1.0;
				p=0.0;

				for (i=m-1;i>=l;i--)
                {
					f=s*e[i];
					b=c*e[i];
					e[i+1]=(r=Pythag(f,g));
					if (r == 0.0) 
                    {
						d[i+1] -= p;
						e[m]=0.0;
						break;
					}
					s=f/r;
					c=g/r;
					g=d[i+1]-p;
					r= (d[i]-g)*s+2.0f*c*b;
					d[i+1]=g+(p=s*r);
					g=c*r-b;

					if (hasVector)
                    {
						for (k=0;k<n;k++) 
                        {
							f=z[k][i+1];
							z[k][i+1]=s*z[k][i]+c*f;
							z[k][i]=c*z[k][i]-s*f;
						}
					}
				}

				if (r == 0.0 && i >= l) continue;

				d[l] -= p;
				e[l]=g;
				e[m]=0.0;
			}

		} while (m != l);
	}
}

bool NXBLAS::SolveGeneralSVD(const int m, const int n, double **u, double **v, double *w, double *mtmp, double *ntmp)
{	
	double eps = M_DEPS;

	bool flag;
	int i,its,j,jj,k,l,nm;
	double anorm,c,f,g,h,s,scale,x,y,z;
	double *rv1 = ntmp;
	g = scale = anorm = 0.0;
	for (i=0;i<n;i++) 
	{
		l=i+2;
		rv1[i]=scale*g;
		g=s=scale=0.0;
		if (i < m)
		{
			for (k=i;k<m;k++) scale += qAbs(u[k][i]);
			if (scale != 0.0) 
			{
				for (k=i;k<m;k++)
				{
					u[k][i] /= scale;
					s += u[k][i]*u[k][i];
				}
				f=u[i][i];
				g = -GMSIGNV(sqrt(s),f);
				h=f*g-s;
				u[i][i]=f-g;
				for (j=l-1;j<n;j++) 
				{
					for (s=0.0,k=i;k<m;k++) s += u[k][i]*u[k][j];
					f=s/h;
					for (k=i;k<m;k++) u[k][j] += f*u[k][i];
				}
				for (k=i;k<m;k++) u[k][i] *= scale;
			}
		}
		w[i]=scale *g;
		g=s=scale=0.0;
		if (i+1 <= m && i+1 != n) 
		{
			for (k=l-1;k<n;k++) scale += qAbs(u[i][k]);
			if (scale != 0.0) 
			{
				for (k=l-1;k<n;k++) 
				{
					u[i][k] /= scale;
					s += u[i][k]*u[i][k];
				}
				f=u[i][l-1];
				g = -GMSIGNV(sqrt(s),f);
				h=f*g-s;
				u[i][l-1]=f-g;
				for (k=l-1;k<n;k++) rv1[k]=u[i][k]/h;
				for (j=l-1;j<m;j++) {
					for (s=0.0,k=l-1;k<n;k++) s += u[j][k]*u[i][k];
					for (k=l-1;k<n;k++) u[j][k] += s*rv1[k];
				}
				for (k=l-1;k<n;k++) u[i][k] *= scale;
			}
		}
		anorm=qMax(anorm,(qAbs(w[i])+qAbs(rv1[i])));
	}
	for (i=n-1;i>=0;i--) 
	{
		if (i < n-1) 
		{
			if (g != 0.0)
			{
				for (j=l;j<n;j++)
					v[j][i]=(u[i][j]/u[i][l])/g;
				for (j=l;j<n;j++)
				{
					for (s=0.0,k=l;k<n;k++) s += u[i][k]*v[k][j];
					for (k=l;k<n;k++) v[k][j] += s*v[k][i];
				}
			}
			for (j=l;j<n;j++) v[i][j]=v[j][i]=0.0;
		}
		v[i][i]=1.0;
		g=rv1[i];
		l=i;
	}
	for (i=qMin(m,n)-1;i>=0;i--) 
	{
		l=i+1;
		g=w[i];
		for (j=l;j<n;j++) u[i][j]=0.0;
		if (g != 0.0) {
			g=1.0/g;
			for (j=l;j<n;j++) 
			{
				for (s=0.0,k=l;k<m;k++) s += u[k][i]*u[k][j];
				f=(s/u[i][i])*g;
				for (k=i;k<m;k++) u[k][j] += f*u[k][i];
			}
			for (j=i;j<m;j++) u[j][i] *= g;
		} 
		else for (j=i;j<m;j++) u[j][i]=0.0;
		++u[i][i];
	}
	for (k=n-1;k>=0;k--)
	{
		for (its=0;its<30;its++) 
		{
			flag=true;
			for (l=k;l>=0;l--) 
			{
				nm=l-1;
				if (l == 0 || qAbs(rv1[l]) <= eps*anorm) {
					flag=false;
					break;
				}
				if (qAbs(w[nm]) <= eps*anorm) break;
			}
			if (flag) 
			{
				c=0.0;
				s=1.0;
				for (i=l;i<k+1;i++) 
				{
					f=s*rv1[i];
					rv1[i]=c*rv1[i];
					if (qAbs(f) <= eps*anorm) break;
					g=w[i];
					h=Pythag(f,g);
					w[i]=h;
					h=1.0/h;
					c=g*h;
					s = -f*h;
					for (j=0;j<m;j++) 
					{
						y=u[j][nm];
						z=u[j][i];
						u[j][nm]=y*c+z*s;
						u[j][i]=z*c-y*s;
					}
				}
			}
			z=w[k];
			if (l == k) 
			{
				if (z < 0.0) 
				{
					w[k] = -z;
					for (j=0;j<n;j++) v[j][k] = -v[j][k];
				}
				break;
			}
			if (its == 29) return false;
			x=w[l];
			nm=k-1;
			y=w[nm];
			g=rv1[nm];
			h=rv1[k];
			f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
			g=Pythag(f,1.0);
			f=((x-z)*(x+z)+h*((y/(f+GMSIGNV(g,f)))-h))/x;
			c=s=1.0;
			for (j=l;j<=nm;j++) 
			{
				i=j+1;
				g=rv1[i];
				y=w[i];
				h=s*g;
				g=c*g;
				z=Pythag(f,h);
				rv1[j]=z;
				c=f/z;
				s=h/z;
				f=x*c+g*s;
				g=g*c-x*s;
				h=y*s;
				y *= c;
				for (jj=0;jj<n;jj++) 
				{
					x=v[jj][j];
					z=v[jj][i];
					v[jj][j]=x*c+z*s;
					v[jj][i]=z*c-x*s;
				}
				z=Pythag(f,h);
				w[j]=z;
				if (z) {
					z=1.0/z;
					c=f*z;
					s=h*z;
				}
				f=c*g+s*y;
				x=c*y-s*g;
				for (jj=0;jj<m;jj++)
				{
					y=u[jj][j];
					z=u[jj][i];
					u[jj][j]=y*c+z*s;
					u[jj][i]=z*c-y*s;
				}
			}
			rv1[l]=0.0;
			rv1[k]=f;
			w[k]=x;
		}
	}

	/// reorder

	int inc = 1;
	double sw;
	double *su = mtmp;
	double *sv = ntmp;

	do { inc *= 3; inc++; } while (inc <= n);
	do 
	{
		inc /= 3;
		for (i=inc;i<n;i++) 
		{
			sw = w[i];
			for (k=0;k<m;k++) su[k] = u[k][i];
			for (k=0;k<n;k++) sv[k] = v[k][i];
			j = i;
			while (w[j-inc] < sw) 
			{
				w[j] = w[j-inc];
				for (k=0;k<m;k++) u[k][j] = u[k][j-inc];
				for (k=0;k<n;k++) v[k][j] = v[k][j-inc];
				j -= inc;
				if (j < inc) break;
			}
			w[j] = sw;
			for (k=0;k<m;k++) u[k][j] = su[k];
			for (k=0;k<n;k++) v[k][j] = sv[k];

		}
	} while (inc > 1);

	for (k=0;k<n;k++) 
	{
		s=0;
		for (i=0;i<m;i++) if (u[i][k] < 0.) s++;
		for (j=0;j<n;j++) if (v[j][k] < 0.) s++;
		if (s > (m+n)/2) {
			for (i=0;i<m;i++) u[i][k] = -u[i][k];
			for (j=0;j<n;j++) v[j][k] = -v[j][k];
		}
	}

	return true;
}

bool NXBLAS::GaussJordanElimination(float **a, int n, float **b, int m, int* indxc, int* indxr, int* ipiv)
{
	int i,icol,irow,j,k,l,ll;
	float big,dum,pivinv;

	memset (ipiv, 0, sizeof(int)*n);
    
	for (i=0;i<n;i++) 
    {
		big=0.0f;

		for (j=0; j<n; j++)
        {
			if (ipiv[j] != 1)
            {
				for (k=0; k<n; k++) 
                {
					if (ipiv[k] == 0) 
                    {
						if (qAbs(a[j][k]) >= big)
                        {
							big = qAbs(a[j][k]);
							irow = j;
							icol = k;
						}
					} 
                    else if (ipiv[k] > 1)
                    {
						//error("gaussj: Singular Matrix-1");
						//return false;
					}
				}
            }
        }

		++(ipiv[icol]);

		if (irow != icol)
        {
			for (l=0; l<n; l++) 
                qSwap (a[irow][l],a[icol][l]);
			for (l=0; l<m; l++) 
                qSwap (b[irow][l],b[icol][l]);
		}

		indxr[i]=irow;
		indxc[i]=icol;
		if (qAbs  (a[icol][icol])< M_FEPS)
        {
			//error("gaussj: Singular Matrix-2");
			return false;
		}

		pivinv = 1.0f/a[icol][icol];
		a[icol][icol]=1.0f;

		for (l=0; l<n; l++) a[icol][l] *= pivinv;
		for (l=0; l<m; l++) b[icol][l] *= pivinv;
		for (ll=0;ll<n;ll++)
			if (ll != icol)
            {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for (l=0; l<n; l++) a[ll][l] -= a[icol][l]*dum;
				for (l=0; l<m; l++) b[ll][l] -= b[icol][l]*dum;
			}
	}
	for (l=n-1;l>=0;l--)
    {
		if (indxr[l] != indxc[l])
			for (k=0;k<n;k++)
				qSwap(a[k][indxr[l]],a[k][indxc[l]]);
	}
	
	return true;
}

bool NXBLAS::GaussJordanElimination(double **a, int n, double **b, int m, int* indxc, int* indxr, int* ipiv)
{
	int i,icol,irow,j,k,l,ll;
	double big,dum,pivinv,temp;

	memset (ipiv, 0, sizeof(int)*n);
    
	for (i=0;i<n;i++) 
    {
		big=0.0f;

		for (j=0; j<n; j++)
        {
			if (ipiv[j] != 1)
            {
				for (k=0; k<n; k++) 
                {
					if (ipiv[k] == 0) 
                    {
						if (qAbs(a[j][k]) >= big)
                        {
							big = qAbs(a[j][k]);
							irow = j;
							icol = k;
						}
					} 
                    else if (ipiv[k] > 1)
                    {
						//error("gaussj: Singular Matrix-1");
						//return false;
					}
				}
            }
        }

		++(ipiv[icol]);

		if (irow != icol)
        {
			for (l=0; l<n; l++) 
                qSwap (a[irow][l],a[icol][l]);
			for (l=0; l<m; l++) 
                qSwap (b[irow][l],b[icol][l]);
		}

		indxr[i]=irow;
		indxc[i]=icol;
		if (qAbs  (a[icol][icol])< M_DEPS)
        {
			//error("gaussj: Singular Matrix-2");
			return false;
		}

		pivinv = 1.0f/a[icol][icol];
		a[icol][icol]=1.0f;

		for (l=0; l<n; l++) a[icol][l] *= pivinv;
		for (l=0; l<m; l++) b[icol][l] *= pivinv;
		for (ll=0;ll<n;ll++)
			if (ll != icol)
            {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for (l=0; l<n; l++) a[ll][l] -= a[icol][l]*dum;
				for (l=0; l<m; l++) b[ll][l] -= b[icol][l]*dum;
			}
	}
	for (l=n-1;l>=0;l--)
    {
		if (indxr[l] != indxc[l])
			for (k=0;k<n;k++)
				qSwap(a[k][indxr[l]],a[k][indxc[l]]);
	}
	
	return true;
}

bool NXBLAS::CholeskyDecomposition (int n, float**a, float**el)
{
	if (NULL == a || NULL == el || n<= 0)
		return false;

	int i, j, k;
	float fSum;

	// Copy 
	for (i=0; i<n; ++i)
	{
		for (j=0; j<n; ++j)
		{
			el[i][j] = a[i][j];
		}
	}	

	// Decomposition
	for (i=0; i<n; ++i)
	{
		for (j=i; j<n; ++j)
		{
			fSum = el[i][j];
			for (k=i-1; k>=0; --k)
				fSum -= el[i][k]*el[j][k];

			if (i == j)
			{
				if (fSum <= M_FEPS)
					return false;
				else
				{
					el[i][i] = sqrt(fSum);
				}
			}
			else
			{
				el[j][i] = fSum/el[i][i];
			}
		}
	}

	// the rest
	for (i=0; i<n; ++i)
	{
		for (j=0; j<i; ++j)
		{
			el[j][i] = 0.0f;
		}
	}

	return true;
}


bool NXBLAS::CholeskyDecomposition (int n, double**a, double**el)
{
	if (NULL == a || NULL == el || n<= 0)
		return false;

	int i, j, k;
	double fSum;

	// Copy 
	for (i=0; i<n; ++i)
	{
		for (j=0; j<n; ++j)
		{
			el[i][j] = a[i][j];
		}
	}	

	// Decomposition
	for (i=0; i<n; ++i)
	{
		for (j=i; j<n; ++j)
		{
			fSum = el[i][j];
			for (k=i-1; k>=0; --k)
				fSum -= el[i][k]*el[j][k];

			if (i == j)
			{
				if (fSum <= M_FEPS)
					return false;
				else
				{
					el[i][i] = sqrt(fSum);
				}
			}
			else
			{
				el[j][i] = fSum/el[i][i];
			}
		}
	}

	// the rest
	for (i=0; i<n; ++i)
	{
		for (j=0; j<i; ++j)
		{
			el[j][i] = 0.0f;
		}
	}

	return true;
}

bool NXBLAS::CholeskySolver (int n, float**a, float **el, float*b, float*x)
{
	if (n <=0 || NULL == a || NULL == el || NULL == b || NULL == x)
		return false;

	if (!CholeskyDecomposition(n, a, el) )
		return false;

	int i, k;
	float fSum;

	// Ly = b;
	for (i=0; i<n; ++i)
	{
		fSum = b[i];
		for (k = i-1; k>=0; --k)
		{
			fSum -= el[i][k]*x[k];
		}
		x[i] = fSum/el[i][i];
	}

	// L'x = y;
	for (i=n-1; i>=0; --i)
	{
		fSum = x[i];
		for (k=i+1; k<n; ++k)
		{
			fSum -= el[k][i]*x[k];
		}
		x[i] = fSum/el[i][i];
	}

	return true;
}

bool NXBLAS::CholeskySolver (int n, double**a, double**el, double*b, double*x)
{
	if (n <=0 || NULL == a || NULL == el || NULL == b || NULL == x)
		return false;

	if (!CholeskyDecomposition(n, a, el) )
		return false;

	int i, k;
	double fSum;

	// Ly = b;
	for (i=0; i<n; ++i)
	{
		fSum = b[i];
		for (k = i-1; k>=0; --k)
		{
			fSum -= el[i][k]*x[k];
		}
		x[i] = fSum/el[i][i];
	}

	// L'x = y;
	for (i=n-1; i>=0; --i)
	{
		fSum = x[i];
		for (k=i+1; k<n; ++k)
		{
			fSum -= el[k][i]*x[k];
		}
		x[i] = fSum/el[i][i];
	}

	return true;
}

bool NXBLAS::CholeskyInverse (int n, float**a, float**el, float**aInv)
{
	if (n <=0 || NULL == a || NULL == el || NULL == aInv)
		return false;

	if (!CholeskyDecomposition(n, a, el) )
		return false;

	int i, j, k;
	float fSum;

	for (i=0; i<n; ++i)
	{
		for (j=0; j<=i; ++j)
		{
			fSum = (i==j ? 1.f : 0.f);

			for (k=i-1; k>=j; --k)
			{
				fSum -= el[i][k]*aInv[j][k];
			}
			aInv[j][i] = fSum/el[i][i];
		}
	}

	for (i=n-1; i>=0; --i)
	{
		for (j=0; j<=i; ++j)
		{
			fSum = (i<j ? 0.f : aInv[j][i]);

			for (k=i+1; k<n; ++k)
			{
				fSum -= el[k][i]*aInv[j][k];
			}
			aInv[i][j] = aInv[j][i] = fSum/el[i][i];
		}
	}

	return true;
}

bool NXBLAS::CholeskyInverse (int n, double**a, double**el, double**aInv)
{
	if (n <=0 || NULL == a || NULL == el || NULL == aInv)
		return false;

	if (!CholeskyDecomposition(n, a, el) )
		return false;

	int i, j, k;
	double fSum;

	for (i=0; i<n; ++i)
	{
		for (j=0; j<=i; ++j)
		{
			fSum = (i==j ? 1. : 0.);

			for (k=i-1; k>=j; --k)
			{
				fSum -= el[i][k]*aInv[j][k];
			}
			aInv[j][i] = fSum/el[i][i];
		}
	}

	for (i=n-1; i>=0; --i)
	{
		for (j=0; j<=i; ++j)
		{
			fSum = (i<j ? 0. : aInv[j][i]);

			for (k=i+1; k<n; ++k)
			{
				fSum -= el[k][i]*aInv[j][k];
			}
			aInv[i][j] = aInv[j][i] = fSum/el[i][i];
		}
	}

	return true;
}

void NXBLAS::MultiplyMaxtrix(int m, int n, int p, double**a, double**b, double**c)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < p; ++j)
		{
			c[i][j] = 0.;
			for (int k = 0; k < n; ++k)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void NXBLAS::MultiplyMaxtrix(int m, int n, int p, float**a, float**b, float**c)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < p; ++j)
		{
			c[i][j] = 0.;
			for (int k = 0; k < n; ++k)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}


void NXBLAS::TransposeMaxtrix(int m, int n, double**a, double**b)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			b[j][i] = a[i][j];
		}
	}
}

void NXBLAS::TransposeMaxtrix(int m, int n, float**a, float**b)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			b[j][i] = a[i][j];
		}
	}
}

void NXBLAS::MultiplyRight(int n, double**a, double* b, double* c, bool bTranspose)
{
	if (bTranspose)
	{
		for (int i = 0; i < n; ++i)
		{
			c[i] = 0.;
			for (int j = 0; j < n; ++j)
			{
				c[i] += a[j][i] * b[j];
			}
		}
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			c[i] = 0.;
			for (int j = 0; j < n; ++j)
			{
				c[i] += a[i][j] * b[j];
			}
		}
	}
}
void NXBLAS::MultiplyRight(int n, float**a, float* b, float* c, bool bTranspose)
{
	if (bTranspose)
	{
		for (int i = 0; i < n; ++i)
		{
			c[i] = 0.f;
			for (int j = 0; j < n; ++j)
			{
				c[i] += a[j][i] * b[j];
			}
		}
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			c[i] = 0.f;
			for (int j = 0; j < n; ++j)
			{
				c[i] += a[i][j] * b[j];
			}
		}
	}
}

void NXBLAS::MultiplyRight(int m, int n, double**a, double* b, double* c, bool bTranspose)
{
	if (bTranspose)
	{
		for (int j = 0; j < n; ++j)
		{
			c[j] = 0.;
			for (int i = 0; i < m; ++i)
			{
				c[j] += a[i][j] * b[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < m; ++i)
		{
			c[i] = 0.;
			for (int j = 0; j < n; ++j)
			{
				c[i] += a[i][j] * b[j];
			}
		}
	}
}
void NXBLAS::MultiplyRight(int m, int n, float**a, float* b, float* c, bool bTranspose)
{
	if (bTranspose)
	{
		for (int j = 0; j < n; ++j)
		{
			c[j] = 0.f;
			for (int i = 0; i < m; ++i)
			{
				c[j] += a[i][j] * b[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < m; ++i)
		{
			c[i] = 0.f;
			for (int j = 0; j < n; ++j)
			{
				c[i] += a[i][j] * b[j];
			}
		}
	}
}


double NXBLAS::CalcNorm(int n, double* pData)
{
	double dSum = 0.;
	for (int i = 0; i < n; ++i)
	{
		dSum += SQR(pData[i]);
	}
	return sqrt(dSum);
}

float NXBLAS::CalcNorm(int n, float* pData)
{
	double dSum = 0.;
	for (int i = 0; i < n; ++i)
	{
		dSum += SQR(pData[i]);
	}
	return static_cast<float>(sqrt(dSum));
}

void NXBLAS::SolveDiagLinearEQU(int n, double** a, double* b, double* x)
{
	for (int i = 0; i < n; ++i)
	{
		if (a[i][i] != 0.)
			x[i] = b[i] / a[i][i];
		else
			x[i] = b[i];
	}
}

void NXBLAS::SolveDiagLinearEQU(int n, float** a, float* b, float* x)
{
	for (int i = 0; i < n; ++i)
	{
		if (a[i][i] != 0.f)
			x[i] = b[i] / a[i][i];
		else
			x[i] = b[i];
	}
}

void NXBLAS::SolveLinearEQUWithBICG(int n, double**a, double*x, double*b, double tol, int itmax, int& iter, double& err)
{
	double ak, akden, bk, bkden = 1.0, bknum, bnrm, dxnrm, xnrm, zm1nrm, znrm;
	const double EPS = 1.0e-14;
	int j;
	double *p = new double[n];
	double *pp = new double[n];
	double *r = new double[n];
	double *rr = new double[n];
	double *z = new double[n];
	double *zz = new double[n];

	iter = 0;

	// r = a*x
	MultiplyRight(n, a, x, r, false); 
	for (j = 0; j < n; j++)
	{
		r[j] = b[j] - r[j];
		rr[j] = r[j];
	}


	SolveDiagLinearEQU(n, a, b, z);
	bnrm = CalcNorm(n, z);

	SolveDiagLinearEQU(n, a, r, z);
	znrm = CalcNorm(n, z);

	while (iter < itmax)
	{
		++iter;

		SolveDiagLinearEQU(n, a, rr, zz);

		for (bknum = 0.0, j = 0; j < n; j++)
			bknum += z[j] * rr[j];

		if (iter == 1) 
		{
			for (j = 0; j < n; j++) 
			{
				p[j] = z[j];
				pp[j] = zz[j];
			}
		}
		else 
		{
			bk = bknum / bkden;
			for (j = 0; j < n; j++)
			{
				p[j] = bk*p[j] + z[j];
				pp[j] = bk*pp[j] + zz[j];
			}
		}
		bkden = bknum;

		MultiplyRight(n, a, p, z, false);

		for (akden = 0.0, j = 0; j < n; j++) 
			akden += z[j] * pp[j];
		ak = bknum / akden;

		MultiplyRight(n, a, pp, zz, true);

		for (j = 0; j<n; j++) 
		{
			x[j] += ak*p[j];
			r[j] -= ak*z[j];
			rr[j] -= ak*zz[j];
		}

		SolveDiagLinearEQU(n, a, r, z);

		zm1nrm = znrm;
		znrm = CalcNorm(n, z);
		if (qAbs(zm1nrm - znrm) > EPS*znrm)
		{
			dxnrm = qAbs(ak)*CalcNorm(n, p);
			err = znrm / qAbs(zm1nrm - znrm)*dxnrm;
		}
		else
		{
			err = znrm / bnrm;
			continue;
		}
		xnrm = CalcNorm(n, x);
		if (err <= 0.5*xnrm) 
			err /= xnrm;
		else 
		{
			err = znrm / bnrm;
			continue;
		}
		
		if (err <= tol) break;
	}

	delete[]p;
	delete[]pp;
	delete[]r;
	delete[]rr;
	delete[]z;
	delete[]zz;
}

void NXBLAS::SolveLinearEQUWithBICG(int n, float**a, float*x, float*b, float tol, int itmax, int& iter, float& err)
{
	double ak, akden, bk, bkden = 1.0, bknum, bnrm, dxnrm, xnrm, zm1nrm, znrm;
	const double EPS = 1.0e-14;
	int j;
	float *p = new float[n];
	float *pp = new float[n];
	float *r = new float[n];
	float *rr = new float[n];
	float *z = new float[n];
	float *zz = new float[n];

	iter = 0;

	// r = a*x
	MultiplyRight(n, a, x, r, false);
	for (j = 0; j < n; j++)
	{
		r[j] = b[j] - r[j];
		rr[j] = r[j];
	}


	SolveDiagLinearEQU(n, a, b, z);
	bnrm = CalcNorm(n, z);

	SolveDiagLinearEQU(n, a, r, z);
	znrm = CalcNorm(n, z);

	while (iter < itmax)
	{
		++iter;

		SolveDiagLinearEQU(n, a, rr, zz);

		for (bknum = 0.0, j = 0; j < n; j++)
			bknum += z[j] * rr[j];

		if (iter == 1)
		{
			for (j = 0; j < n; j++)
			{
				p[j] = z[j];
				pp[j] = zz[j];
			}
		}
		else
		{
			bk = bknum / bkden;
			for (j = 0; j < n; j++)
			{
				p[j] = bk*p[j] + z[j];
				pp[j] = bk*pp[j] + zz[j];
			}
		}
		bkden = bknum;

		MultiplyRight(n, a, p, z, false);

		for (akden = 0.0, j = 0; j < n; j++)
			akden += z[j] * pp[j];
		ak = bknum / akden;

		MultiplyRight(n, a, pp, zz, true);

		for (j = 0; j<n; j++)
		{
			x[j] += ak*p[j];
			r[j] -= ak*z[j];
			rr[j] -= ak*zz[j];
		}

		SolveDiagLinearEQU(n, a, r, z);

		zm1nrm = znrm;
		znrm = CalcNorm(n, z);
		if (qAbs(zm1nrm - znrm) > EPS*znrm)
		{
			dxnrm = qAbs(ak)*CalcNorm(n, p);
			err = znrm / qAbs(zm1nrm - znrm)*dxnrm;
		}
		else
		{
			err = znrm / bnrm;
			continue;
		}
		xnrm = CalcNorm(n, x);
		if (err <= 0.5*xnrm)
			err /= xnrm;
		else
		{
			err = znrm / bnrm;
			continue;
		}

		if (err <= tol) break;
	}

	delete[]p;
	delete[]pp;
	delete[]r;
	delete[]rr;
	delete[]z;
	delete[]zz;
}

void NXBLAS::SolveLinearEQUWithBICGTwo(int n, double**a, double*x, double*b, double tol, int itmax, int& iter, double& err)
{
	const double EPS = 1.0e-14;

	double n2b = CalcNorm(n, b);
	if (n2b == 0.)
	{
		iter = 0;
		err = 0.;
		memset(x, 0, sizeof(double)*n);
		return;
	}
	double tolb = tol * n2b;

	double *r = new double[n];
	double *xmin = new double[n];
	double *rt = new double[n];
	double *z = new double[n];
	double *zt = new double[n];
	double *p = new double[n];
	double *pt = new double[n];
	double *q = new double[n];
	double *qt = new double[n];

	double *resvec = new double[itmax + 1];	

	memcpy(xmin, x, sizeof(double)*n);

	// r = b - a*x
	int j;
	MultiplyRight(n, a, x, r, false);
	for (j = 0; j < n; j++)
		r[j] = b[j] - r[j];

	double normr = CalcNorm(n, r);
	double normr_act = normr;
	double normrmin = normr;
	if (normr < tolb)
	{
		iter = 0;
		return;
	}

	memcpy(rt, r, sizeof(double)*n);
	resvec[0] = normr;

	double rho = 1., rho1;
	double beta;
	int flag = 1;
	int stag = 0;                           //stagnation of the method

	int moresteps = 0;
	int	maxmsteps = qMin(qMin(n / 50, 5), n - itmax);
	int	maxstagsteps = 3;
		
	for ( iter = 0; iter < itmax; ++iter)
	{
		memcpy(z, r, sizeof(double)*n);
		memcpy(zt, rt, sizeof(double)*n);

		rho1 = rho;

		rho = 0.;
		for (int i = 0; i < n; ++i)
			rho += rt[i] * z[i];

		if (rho == 0.)
		{
			flag = 4;
			break;
		}

		if (iter == 0)
		{
			memcpy(p, z, sizeof(double)*n);
			memcpy(pt, zt, sizeof(double)*n);
		}
		else
		{
			beta = rho / rho1;
			if (beta == 0.)
			{
				flag = 4;
				break;
			}

			for (int i = 0; i < n; ++i)
			{
				p[i] = z[i] + beta * p[i];
				pt[i] = zt[i] + beta * pt[i];
			}
		}

		//
		MultiplyRight(n, a, p, q);

		MultiplyRight(n, a, pt, qt, true);

		double ptq = DotProduct(n, pt, q);

		double alpha;
		if (ptq == 0.)
		{
			flag = 4;
			break;
		}
		else
		{
			alpha = rho / ptq;
		}

		if (qAbs(alpha)*CalcNorm(n, p) < EPS*CalcNorm(n, x))
			++stag;
		else
			stag = 0;

		for (int i = 0; i < n; ++i)
		{
			x[i] += alpha*p[i];
			r[i] -= alpha*q[i];
			rt[i] -= alpha*qt[i];
		}

		normr = CalcNorm(n, r);
		normr_act = normr;
		resvec[iter + 1] = normr;

		// convergence
		if (normr <= tolb || stag >= maxstagsteps || moresteps != 0)
		{
			MultiplyRight(n, a, x, r, false);
			for (int i = 0; i < n; i++)
				r[i] = b[i] - r[i];

			normr_act = CalcNorm(n, r);
			resvec[iter + 1] = normr_act;

			if (normr_act <= tolb)
			{
				flag = 0;
				break;
			}
			else
			{
				if (stag >= maxstagsteps && moresteps == 0)
				{
					stag = 0;
				}
				++moresteps;

				if (moresteps >= maxmsteps)
				{
					flag = 3;
					break;
				}
			}

		}

		if (normr_act < normrmin)
		{
			normrmin = normr_act;
			memcpy(xmin, x, sizeof(double)*n);
		}

		if (stag >= maxstagsteps)
		{
			flag = 3;
			break;
		}

	} //end loop

	if (flag != 0)
	{
		MultiplyRight(n, a, xmin, r, false);
		for (int i = 0; i < n; i++)
			r[i] = b[i] - r[i];

		if (flag == 1)
		{
			MultiplyRight(n, a, x, zt, false);
			for (int i = 0; i < n; i++)
				zt[i] = b[i] - zt[i];

			normr_act = CalcNorm(n, zt);
		}

		if (CalcNorm(n, r) <= normr_act)
		{
			memcpy(x, xmin, sizeof(double)*n);
		}

	}

	delete[]r;
	delete[]xmin;
	delete[]rt;
	delete[]z;
	delete[]zt;
	delete[]p;
	delete[]pt;
	delete[]q;
	delete[]qt;

	delete[]resvec;
}
