#pragma once
#include "xbasic_global.h"
#include "xmatrix.h"

class XBASIC_EXPORT XLsq
{
public:
    XLsq(int noVar = 1, int order = 1);
    ~XLsq();

	void Add(double dVar, const std::vector<double>& vecVars, double weight = 1.0);
	bool Solve();
	bool IsValid() const;
	int Count() const;
	double Eval(const std::vector<double>& vecVars);
	double SumWeights() const;

	const XMatrix& Sums() const;
	const XMatrix& Rhs() const;
	const XMatrix& Solution() const;

private:
    bool m_isValid = false;    // Is the solution valid?
    int m_noVar    = 1;        // Independent variables
    int m_order    = 1;        // polynomal order
    int m_n        = 2;        // rows & columns in the sums matrix
    XMatrix m_sums;            // SUMS matrix
    XMatrix m_rhs;             // RHS vector
    XMatrix m_sol;             // solution vector
    double m_sumWeights = 0.0; // sum of the weights
    int m_count         = 0;   // samples added to the sums
};

class XBASIC_EXPORT XLsq3d
{
public:
	XLsq3d(int order = 1);

	void Add(double x, double y, double z, double w = 1.0);
	bool Solve();
	bool IsValid() const;
	int Count() const;
	double XMean();
	double YMean();
	double ZMean();
	double Eval(double x, double y);

private:
	XLsq m_lsq;
#ifndef NDEBUG
	double m_minX = std::numeric_limits<double>::max();
	double m_maxX = std::numeric_limits<double>::min();
	double m_minY = std::numeric_limits<double>::max();
	double m_maxY = std::numeric_limits<double>::min();
#endif
};
