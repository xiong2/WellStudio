#include <qfile.h>
#include <qpolygon.h>
#include "xthreadpyramid.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"

void Pyramid_Filter::conv3x3(int nx, int ny, double* pin, double* pout, double kernel[][3])
{
	int xmin, xmax, ymin, ymax;
	double data[3][3];
	int index = 0;
	for (int x = 0; x < nx; ++x)
	{
		for (int y = 0; y < ny; ++y)
		{
			xmin = x - 1;
			xmax = x + 1;
			ymin = y - 1;
			ymax = y + 1;
			for (int xx = xmin; xx <= xmax; ++xx)
			{
				for (int yy = ymin; yy <= ymax; ++yy)
				{
					if (xx >= 0 && xx < nx && yy >= 0 && yy < ny)
						data[xx - xmin][yy - ymin] = pin[xx*ny + yy];
					else
						data[xx - xmin][yy - ymin] = 0.;
				}
			}

			index = x * ny + y;
			pout[index] = 0.;
			for (int xx = 0; xx < 3; ++xx)
				for (int yy = 0; yy < 3; ++yy)
					pout[index] += data[xx][yy] * kernel[xx][yy];
		}
	}
}

void Pyramid_Filter::get_x_y_kernels(double kernel_x[][3], double kernel_y[][3])
{
	double gau_kernel[3][3] = { {0.075113607954111, 0.123841403152974, 0.075113607954111},
							 {0.123841403152974, 0.204179955571658, 0.123841403152974},
							 {0.075113607954111, 0.123841403152974, 0.075113607954111} };
	double x_coeff[3][3] = { {1, 0, -1},
						  {1, 0, -1},
						  {1, 0, -1} };

	double y_coeff[3][3] = { {1, 1, 1},
						  {0, 0, 0},
						  {-1, -1, -1} };

	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			kernel_x[x][y] = gau_kernel[x][y] * x_coeff[x][y];
			kernel_y[x][y] = gau_kernel[x][y] * y_coeff[x][y];
		}
	}

	// flip
	for (int x = 0; x < 3; ++x)
	{
		std::swap(kernel_x[x][0], kernel_x[x][2]);
		std::swap(kernel_y[x][0], kernel_y[x][2]);
	}

	for (int y = 0; y < 3; ++y)
	{
		std::swap(kernel_x[0][y], kernel_x[2][y]);
		std::swap(kernel_y[0][y], kernel_y[2][y]);
	}
}

void Pyramid_Filter::S_Filtering(int nx, int ny, float* pIn, float* pOut, double theta)
{
	if (nx * ny <= 0)
		return;

	const double pi = 3.14159265358979323846;
	double kernel_x[3][3], kernel_y[3][3];

	get_x_y_kernels(kernel_x, kernel_y);

	std::vector<double> vin(nx*ny), vout_x(nx*ny), vout_y(nx*ny);
	std::copy(pIn, pIn + nx * ny, vin.begin());

	conv3x3(nx, ny, &vin[0], &vout_x[0], kernel_x);
	conv3x3(nx, ny, &vin[0], &vout_y[0], kernel_y);

	theta = theta / 180.*pi;
	double cos_theta = cos(theta);
	double sin_theta = sin(theta);

	int index = 0;
	for (int x = 0; x < nx; ++x)
	{
		for (int y = 0; y < ny; ++y)
		{
			pOut[index] = static_cast<float>(cos_theta*vout_x[index] + sin_theta * vout_y[index]);
			++index;
		}
	}
}

void XThreadPyramid::RunThread()
{
	EmitSetWindowName(QString::fromUtf8(u8"金字塔滤波"));
	EmitStartComputing();

	EmitSetTaskName(QString::fromUtf8(u8"金字塔滤波计算"));
	EmitResetProgressBar();
	calculate();
}

void XThreadPyramid::calculate()
{
	CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(m_pPara->GetDVID()));

	CXSeismicUTMTool utm = pDV->GetUTM();
	int iInlineS = m_pPara->GetInputInlineS();
	int iInlineE = m_pPara->GetInputInlineE();
	int iXlineS = m_pPara->GetInputXlineS();
	int iXlineE = m_pPara->GetInputXlineE();
	double dZS = m_pPara->GetInputTimeS();
	double dZE = m_pPara->GetInputTimeE();
	double dDZS, dDZE, dZInv;
	pDV->GetSamplingRange(dDZS, dDZE, dZInv);
	int k1 = (dZS - dDZS) / dZInv;

	int i, j, i1, j1, i2, j2;
	utm.LineToIJ(iInlineS, iXlineS, i1, j1);
	utm.LineToIJ(iInlineE, iXlineE, i2, j2);
	int nSamples = (int)((dZE - dZS) / dZInv) + 1;
	
	CXSeismicUTMTool newUTM;
	newUTM.Copy(&utm);
	newUTM.Resize(iInlineS, iXlineS, i2 - i1 + 1, j2 - j1 + 1);
	m_pODV = new CXSeismicDataVolume(newUTM, dZS, dZE, dZInv, m_pPara->GetODVName());

	QFile qOFile;
	bool bRes = false;
	if (m_pPara->GetFDirection() < 2)
	{
		qOFile.setFileName(m_pODV->GetTraceFileName());
		bRes = qOFile.open(QIODevice::WriteOnly);
		if (bRes && m_pPara->GetFDirection() == 1)
		{
			qint64 iFSize = (i2 - i1 + 1) * (j2 - j1 + 1);
			iFSize *= (4 * nSamples);
			bRes = qOFile.resize(iFSize);
		}
	}
	else
	{
		qOFile.setFileName(m_pODV->GetSliceFileName());
		bRes = qOFile.open(QIODevice::WriteOnly);
	}

	if (!bRes)
	{
		EmitGeneralErrorMsg(QString("Unable to write output file!"));
		return;
	}

	float *pNDBuffer = NULL, *pRDBuffer = NULL;
	QPolygonF polygon;
	QRectF bRect;
	bool bPolygon = m_pPara->GetUsingPolygon();
	int iX, iY, iIWid, iIHei, iISize;
	double dDMin, dDMax, dDSpan, dRMin, dRMax;
	if (bPolygon)
	{
		std::vector<double> vecPoints = m_pPara->GetVecPoints();
		int iNum = vecPoints.size() / 2;
		for (i = 0; i < iNum; i++)
			polygon << QPointF(vecPoints[2 * i], vecPoints[2 * i + 1]);

		bRect = polygon.boundingRect();
		iIWid = bRect.width();
		iIHei = bRect.height();
		iISize = iIWid * iIHei;
		iX = bRect.x() - j1, iY = bRect.y() - k1;
		if (iX < 0 || iY < 0)
		{
			EmitGeneralErrorMsg(QString::fromUtf8(u8"输出数据范围未能完全包含目标区域！"));
			return;
		}

		pNDBuffer = new float[iISize];
		pRDBuffer = new float[iISize];
		if (m_pPara->GetFDirection() == 0)
		{
			//	Inline.
			polygon.translate(0 - bRect.left(), 0 - bRect.top());
		}

		pDV->GetDataRange(dDMin, dDMax);
		dDSpan = dDMax - dDMin;
	}
	
	float *pBuff = nullptr, *pRes = nullptr;
	qint64 iNumSec, nTrace, iSecSize;
	int nCurrentPer, nPercent = 0, iCurrentStep = 0;
	if (m_pPara->GetFDirection() == 0)
	{
		//	Inline.
		iNumSec = i2 - i1 + 1;
		nTrace = j2 - j1 + 1;
		iSecSize = nTrace * nSamples;
		pBuff = new float[iSecSize];
		pRes = new float[iSecSize];

		for (i = iInlineS; i <= iInlineE; i += utm.GetInlineIncrement())
		{
			pDV->ReadInline(i, iXlineS, iXlineE, dZS, dZE, pBuff);

			// Progress bar
			nCurrentPer = static_cast<int>((++iCurrentStep) * 100 / iNumSec);
			if (nCurrentPer > nPercent)
			{
				nPercent++;
				if (IsStopped())
					break;
				else
				{
					EmitUpdateProgress(nPercent, 100);
				}
			}

			if(!bPolygon)
				Pyramid_Filter::S_Filtering(nTrace, nSamples, pBuff, pRes, (double)m_pPara->GetFDegree());
			else
			{
				Pyramid_Filter::S_Filtering(nTrace, nSamples, pBuff, pRes, (double)m_pPara->GetODegree());

				int m, n;
				for (m = 0; m < iIWid; m++)
				{
					memcpy(pNDBuffer + m * iIHei, pBuff + (iX + m) * nSamples + iY, iIHei * sizeof(float));

					for (n = 0; n < iIHei; n++)
					{
						if (!polygon.containsPoint(QPointF(m, n), Qt::OddEvenFill))
							pNDBuffer[m * iIHei + n] = 0.;
					}
				}

				Pyramid_Filter::S_Filtering(iIWid, iIHei, pNDBuffer, pRDBuffer, (double)m_pPara->GetFDegree());

				//dRMin = dRMax = pRDBuffer[0];
				//for (m = 1; m < iISize; m++)
				//{
				//	if (dRMin > pRDBuffer[m])
				//		dRMin = pRDBuffer[m];
				//	if (dRMax < pRDBuffer[m])
				//		dRMax = pRDBuffer[m];
				//}
				//double dRatio = dDSpan / (dRMax - dRMin);

				//	Write the filtered.
				for (m = 0; m < iIWid; m++)
				{
					for (n = 0; n < iIHei; n++)
					{
						if (polygon.containsPoint(QPointF(m, n), Qt::OddEvenFill))
							//pRes[(iX + m) * nSamples + iY + n] = (pRDBuffer[m * iIHei + n] - dRMin) * dRatio + dDMin;
							pRes[(iX + m) * nSamples + iY + n] = pRDBuffer[m * iIHei + n];
					}
				}
			}

			qOFile.write((char *)(pRes), 4 * iSecSize);
		}
	}
	else if (m_pPara->GetFDirection() == 1)
	{
		//	Crossline.
		iNumSec = j2 - j1 + 1;
		nTrace = i2 - i1 + 1;
		iSecSize = nTrace * nSamples;
		pBuff = new float[iSecSize];
		pRes = new float[iSecSize];
		for (i = iXlineS; i <= iXlineE; i += utm.GetCrosslineIncrement())
		{
			pDV->ReadXline(i, iInlineS, iInlineE, dZS, dZE, pBuff);

			// Progress bar
			nCurrentPer = static_cast<int>((++iCurrentStep) * 100 / iNumSec);
			if (nCurrentPer > nPercent)
			{
				nPercent++;
				if (IsStopped())
					break;
				else
				{
					EmitUpdateProgress(nPercent, 100);
				}
			}

			if (!bPolygon)
				Pyramid_Filter::S_Filtering(nTrace, nSamples, pBuff, pRes, (double)m_pPara->GetFDegree());
			else
			{
				Pyramid_Filter::S_Filtering(nTrace, nSamples, pBuff, pRes, (double)m_pPara->GetODegree());

				int m, n;
				for (m = 0; m < iIWid; m++)
				{
					memcpy(pNDBuffer + m * iIHei, pBuff + (iX + m) * nSamples + iY, iIHei * sizeof(float));

					for (n = 0; n < iIHei; n++)
					{
						if (!polygon.containsPoint(QPointF(m, n), Qt::OddEvenFill))
							pNDBuffer[m * iIHei + n] = 0.;
					}
				}

				Pyramid_Filter::S_Filtering(iIWid, iIHei, pNDBuffer, pRDBuffer, (double)m_pPara->GetFDegree());

				//	Write the filtered.
				for (m = 0; m < iIWid; m++)
				{
					for (n = 0; n < iIHei; n++)
					{
						if (polygon.containsPoint(QPointF(m, n), Qt::OddEvenFill))
							pRes[(iX + m) * nSamples + iY + n] = pRDBuffer[m * iIHei + n];
					}
				}
			}

			for (j = 0; j < nTrace; j++)
			{
				qint64 iOffset = (j * iNumSec + (i - iXlineS)) * 4 * nSamples;
				qOFile.seek(iOffset);
				qOFile.write((char *)(pRes + j * nSamples), 4 * nSamples);
			}
		}
	}
	else
	{
		//	Time slice.
		iNumSec = nSamples;
		nTrace = i2 - i1 + 1;
		nSamples = j2 - j1 + 1;
		
		iSecSize = nTrace * nSamples;
		pBuff = new float[iSecSize];
		pRes = new float[iSecSize];
		for (i = 0; i < iNumSec; i ++)
		{
			pDV->ReadSlice(dZS + i * dZInv, iInlineS, iInlineE, iXlineS, iXlineE, pBuff);

			// Progress bar
			nCurrentPer = static_cast<int>((++iCurrentStep) * 100 / iNumSec);
			if (nCurrentPer > nPercent)
			{
				nPercent++;
				if (IsStopped())
					break;
				else
				{
					EmitUpdateProgress(nPercent, 100);
				}
			}

			if (!bPolygon)
				Pyramid_Filter::S_Filtering(nTrace, nSamples, pBuff, pRes, (double)m_pPara->GetFDegree());
			else
			{
				Pyramid_Filter::S_Filtering(nTrace, nSamples, pBuff, pRes, (double)m_pPara->GetODegree());

				int m, n;
				for (m = 0; m < iIWid; m++)
				{
					memcpy(pNDBuffer + m * iIHei, pBuff + (iX + m) * nSamples + iY, iIHei * sizeof(float));

					for (n = 0; n < iIHei; n++)
					{
						if (!polygon.containsPoint(QPointF(m, n), Qt::OddEvenFill))
							pNDBuffer[m * iIHei + n] = 0.;
					}
				}

				Pyramid_Filter::S_Filtering(iIWid, iIHei, pNDBuffer, pRDBuffer, (double)m_pPara->GetFDegree());

				//	Write the filtered.
				for (m = 0; m < iIWid; m++)
				{
					for (n = 0; n < iIHei; n++)
					{
						if (polygon.containsPoint(QPointF(m, n), Qt::OddEvenFill))
							pRes[(iX + m) * nSamples + iY + n] = pRDBuffer[m * iIHei + n];
					}
				}
			}

			qOFile.write((char *)(pRes), 4 * iSecSize);
		}
	}

	delete[]pBuff;
	delete[]pRes;

	if (pNDBuffer)
	{
		delete[]pNDBuffer;
		delete[]pRDBuffer;
	}

	qOFile.close();
	pDV->AddChild(m_pODV);
	::AddObjectEvent(m_pODV);
}