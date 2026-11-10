#include "xnummethod.h"

double XBASIC_EXPORT NXNumMethod::Rruger(const double(&para)[12], double the, double phi)
{
//% function R=Rruger(a1,b1,e1,g1,d1,rho1,a2,b2,e2,g2,d2,rho2,the,phi)
//% Rruger - calculate the reflectivity in weakly anisotropic HTI media using Ruger's
//%  approximation
//%
//% a1, b1: P- and S-wave velocities of upper medium perpendicular to
//% symmetry axis (vertical velocities for HTI)
//% e1, g1, d1: epsilon gamma delta, Thomsen weakly anisotropic parameters of the uper medium
//% a2, b2: P- and S-wave velocities perpendicular to symmetry axis in the lower medium
//% e3,g2,d2: thomsen's aniso parameters of lower medium
//% the, phi: the incidence angle and azimuth of seismic waves
//% phi=0 is the azimuth perpendicular to the fracture plane
//%
//% R reflectivity as a function of incidence angle and azimuth
//%
//% reference:
//% Ruger, A., 1998, Variation of P-wave reflectivity coefficients with
//% offset and azimuth in anisotropic media
//%    Geophysics, Vol 63, No 3, p935
//%
//
//% written by Li Teng 07/20/98 / modified by Diana Sava 09/2000

	double a1 = para[0];
	double b1 = para[1];
	double e1 = para[2];
	double g1 = para[3];
	double d1 = para[4];
	double rho1 = para[5];
	double a2 = para[6];
	double b2 = para[7];
	double e2 = para[8];
	double g2 = para[9];
	double d2 = para[10];
	double rho2 = para[11];

	double Z1 = rho1*a1;
	double Z2 = rho2*a2;
	double G1 = rho1*b1*b1;
	double G2 = rho2*b2*b2;
	double G = (G1 + G2) / 2;
	double dG = G2 - G1;
	double a = (a1 + a2) / 2;
	double da = a2 - a1;
	double b = (b1 + b2) / 2;
	double db = b2 - b1;
	double a01 = a1 / sqrt(1 + 2 * e1);
	double b01 = b1 / sqrt(1 + 2 * g1);
	double a02 = a2 / sqrt(1 + 2 * e2);
	double b02 = b2 / sqrt(1 + 2 * g2);
	double ev1 = -e1 / (1 + 2 * e1);
	double ev2 = -e2 / (1 + 2 * e2);
	double f1 = 1 - pow(b01 / a01, 2);
	double f2 = 1 - pow(b02 / a02, 2);

	double dv1 = (d1 - 2*e1*(1 + e1/ f1))/ ((1 + 2*e1)*(1 + 2*e1/ f1));
	double dv2 = (d2 - 2*e2*(1 + e2/ f2))/ ((1 + 2*e2)*(1 + 2*e2/ f2));

	the = the*M_PI / 180;
	phi = phi*M_PI / 180;

	double cphi2 = pow(cos(phi), 2);
	double sphi2 = 1 - cphi2;
	double cphi4 = pow(cphi2, 2);
	double sthe2 = pow(sin(the), 2);
	double tthe2 = pow(tan(the), 2);

	double f = pow(2*b/ a, 2);
	double R = (Z2 - Z1)/ (Z2 + Z1) + 0.5*(da/ a - f*dG/ G + ((dv2 - dv1) + 2*f*(g2 - g1))*cphi2)*sthe2 + 0.5*(da/ a + (ev2 - ev1)*cphi4 + (dv2 - dv1)*sphi2*cphi2)*sthe2*tthe2;

	return R;
}

double XBASIC_EXPORT NXNumMethod::PP_coefficient2(const double(&para)[12], double i, double j)
{
	//%Purpose:
	//%  This program solves the pp wave coefficient.
	//%  Plot the relation of incident angle & pp_coefficient
	//%Record of revisions:
	//%  Date        Programmer         Description of change
	//% =======    ===============     =========================
	//% 09/11/2011    Min Yang         Original code


	//%vp1=3800;vs1=2160;e1=0.085;deta1=-0.003;g1=-0.088;rho1=2650;

	//%vp1=parameter(20,4);vs1=parameter(20,5);rho1,e1,deta1,g1

	//%vp0=3850;vs0=2150;e0=0;deta0=0;g0=0;rho0=2500;
	//%vp0=4338;vs0=2370;e0=0;deta0=0;g0=0;rho0=2424;
	//%vp0=3.600;vs0=2.000;e0=0;deta0=0;g0=0;rho0=2.410;

	double vp0 = para[0];
	double vs0 = para[1];
	double e0 = para[2];
	double g0 = para[3];
	double deta0 = para[4];
	double rho0 = para[5];
	double vp1 = para[6];
	double vs1 = para[7];
	double e1 = para[8];
	double g1 = para[9];
	double deta1 = para[10];
	double rho1 = para[11];

	double dif_vp = (vp1 - vp0) * 2. / (vp1 + vp0);
	double dif_vs = (vs1 - vs0) * 2. / (vs1 + vs0);
	double dif_rho = (rho1 - rho0) * 2. / (rho1 + rho0);
	double del_e = (e1 - e0);
	double del_deta = (deta1 - deta0);
	double del_g = (g1 - g0);
	double del_rho = (rho1 - rho0);
	double f = (vs0 + vs1) / (vp0 + vp1);

	// i: theta, j : aizmuth

	double A = 1. / 2 * (dif_rho + dif_vp);
	double Rpp_0 = A;

	double Biso = 1. / 2 * (dif_vp - pow(2 * f, 2)*(dif_rho + 2 * dif_vs));
	double Bani = 1. / 2 * (del_deta + 2 * pow(2 * f, 2)*del_g);
	double B = Biso + Bani*pow(cos(j*M_PI / 180.0), 2.0);
	double Rpp_1 = B*pow(sin(i*M_PI / 180), 2);


	double Ciso = 1. / 2 * dif_vp;
	double Cani = 1. / 2 * (del_e*pow(cos(j / 180 * M_PI), 4) + del_deta*pow(sin(j / 180 * M_PI),2) * pow(cos(j / 180 * M_PI),2));
	double C = Ciso + Cani;
	double Rpp_2 = C*pow(sin(i / 180 * M_PI), 2)* pow(tan(i / 180 * M_PI), 2);

	return Rpp_0 + Rpp_1 + Rpp_2;
}
