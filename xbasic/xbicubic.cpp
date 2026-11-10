#include "xbicubic.h"

CXBicubic::CXBicubic(const std::array<std::array<double, 4>, 4>& G)
{
    std::array<std::array<double, 4>, 4> T;
	
	for (auto& arr : T)
		arr.fill(0.0);

	for (auto& arr : C)
		arr.fill(0.0);

    // T = G * M^T
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                T[i][j] += G[i][k] * M[j][k];

    // C = M * T
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                C[i][j] += M[i][k] * T[k][j];
}

double CXBicubic::Eval(double x, double y) const
{
    const std::array<double, 4>& X3 = C[0];
    const std::array<double, 4>& X2 = C[1];
    const std::array<double, 4>& X1 = C[2];
    const std::array<double, 4>& X0 = C[3];

    return x * (x * (x * (y * (y * (y * X3[0] + X3[1]) + X3[2]) + X3[3]) 
					   + (y * (y * (y * X2[0] + X2[1]) + X2[2]) + X2[3])) 
				       + (y * (y * (y * X1[0] + X1[1]) + X1[2]) + X1[3]))
                       + (y * (y * (y * X0[0] + X0[1]) + X0[2]) + X0[3]);
}

CXBilinear::CXBilinear(const std::array<std::array<double, 2>, 2>& g)
{
	m_z = g;
}

double CXBilinear::Eval(double u, double v) const
{
    return (1 - u) * (1 - v) * m_z[0][0] + (1 - u) * v * m_z[1][0] + u * (1 - v) * m_z[0][1] + u * v * m_z[1][1];
}
