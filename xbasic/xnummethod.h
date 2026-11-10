#ifndef XNXNUMMETHOD_H
#define XNXNUMMETHOD_H

#include <tuple>
#include "xbasic_global.h"
#include "xhistogram.h"
#include "xmathmacro.h"

namespace NXNumMethod
{
	// calculate the reflectivity in weakly anisotropic HTI media using Ruger's approximation
	// a1, b1, e1, g1, d1, rho1, a2, b2, e2, g2, d2, rho2
	double XBASIC_EXPORT Rruger(const double(&para)[12], double the, double phi);
	double XBASIC_EXPORT PP_coefficient2(const double(&para)[12], double i, double j);
};

#endif // KENXNUMMETHOD_H
