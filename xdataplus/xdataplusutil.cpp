#include "xdataplusutil.h"
#include <algorithm>
#include <vector>
#include "mkl.h"

void XDataPlusUtil::ConvolutionWavletandR(int nW, double* pW, int nR, double* pR, double* pSeismic)
{
	if (nW > nR)
		return;

	if (!pSeismic || !pW || !pR)
		return;

	int iPeakPos = std::distance(pW, std::max_element(pW, pW + nW));

	std::vector<double> vecW(nR*nR, 0);

	// wavelet matrix, column-major
	for (int j = 0, iStart = iPeakPos; j < nR; ++j, --iStart)
	{
		for (int i = qMax(0, iStart); i < nW && i - iStart < nR; ++i)
		{
			vecW[j*nR + i - iStart] = pW[i];
		}
	}

	cblas_dgemv(CblasColMajor, CblasNoTrans, nR, nR, 1., &vecW[0], nR, pR, 1, 0, pSeismic, 1);

}
