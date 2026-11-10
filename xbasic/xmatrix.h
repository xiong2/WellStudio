#pragma once
#include "xbasic_global.h"
#include <vector>
#include <array>
#include <cassert>
#include <initializer_list>

class XBASIC_EXPORT XMatrix
{
public:
	XMatrix() = default;
	XMatrix(int rows, int cols, double init = 0.0);

	void Resize(int rows, int cols);
	void Fill(double v);
	void Set(int row, int col, double v);
	void Set(std::initializer_list<double>&& lst);
	void Set(const std::vector<double>& vec);
	void Scale(double factor);
	double Get(int row, int col) const;
	double Get(int idx) const;

	int Rows() const;
	int Cols() const;
	double* Array();

	XMatrix T() const;
	XMatrix Inv() const;

	void SmoothSavitzkyGolay(int order);

	friend XBASIC_EXPORT XMatrix operator*(const XMatrix& lhs, const XMatrix& rhs);
	friend bool XBASIC_EXPORT operator==(const XMatrix& lhs, const XMatrix& rhs);

	// Solve A * B = SOL
	static bool Gauss(const XMatrix& am, const XMatrix& ym, XMatrix* sol, double zeroTest = 1.e-8);
	static int GaussPivot(const XMatrix& m, int p, std::vector<int>* ord);

private:
	int m_rows;
	int m_cols;

#pragma warning(push)
#pragma warning(disable: 4251)
	std::vector<double> m_v;
#pragma warning(pop)
};
