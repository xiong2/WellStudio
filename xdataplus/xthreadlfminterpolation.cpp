#pragma warning( push ,0 )
#include <QCoreApplication>
#include "xthreadlfminterpolation.h"
#include "xparameterlfminterpolation.h"
#include "xlfmgeometry.h"
#include "xlfmattribute.h"
#include "xlfmupscalingattribute.h"
#include "xlfmupscalinggeometry.h"

#include "xregulardatawriter.h"

#include "xmathmacro.h"
#include "xglobal.h"
#include <cmath>
#include <cassert>
#include "xkdtree.h"
#include "xutility.h"
#include "xfunctiontemplate.h"
#include "xblas.h"

#pragma warning( pop )

CXThreadLFMInterpolation::CXThreadLFMInterpolation(CXParameterLFMInterpolation* pPara, CXLFMUpscalingAttribute* pUpscalingAtt)
	:m_pPara(pPara), m_pUpscalingAtt(pUpscalingAtt)
{
	assert(m_pPara && m_pUpscalingAtt);

	// 1-D buffers
	m_pIndex = NULL;
	m_pSliceData = NULL;
	m_pGridIndex = NULL;
	m_pX = NULL;
	m_pY = NULL;
	m_pZ = NULL;
	m_pG = NULL;
	m_pZBar = NULL;
	m_pEigenValue = NULL;
	m_p1DTmp = NULL;

	// 2-D buffers
	m_p2DCov = NULL;
	m_p2DInv = NULL;
	m_p2DTmp = NULL;

	// k-d tree
	m_pKDTree = NULL;

	// writer and output
	m_pLFMAttribute = NULL;
	m_pWriter = NULL;
	m_pLFMGeometry = m_pUpscalingAtt->GetUpscalingGeometry()->GetLFMGeometry();
	if (m_pLFMGeometry)
	{
		_ParseParameter();

		m_pLFMAttribute = new CXLFMAttribute(m_pLFMGeometry, m_pUpscalingAtt->GetObjectName());
		m_pWriter = new CXRegularDataWriter<float>(m_pLFMAttribute->GetDataFileName(), m_nK, m_nI, m_nJ);
	}
}

CXThreadLFMInterpolation::~CXThreadLFMInterpolation()
{
	if (m_pKDTree)		{ delete m_pKDTree; m_pKDTree = NULL; }

	// Delete buffers
	if (m_pIndex)		{ delete[]m_pIndex; }
	if (m_pSliceData)	{ delete[]m_pSliceData; }
	if (m_pGridIndex)	{ delete[]m_pGridIndex; }

	if (m_pX)			{ delete[]m_pX; }
	if (m_pY)			{ delete[]m_pY; }
	if (m_pZ)			{ delete[]m_pZ; }
	if (m_pG)			{ delete[]m_pG; }
	if (m_pZBar)		{ delete[]m_pZBar; }
	if (m_pEigenValue)	{ delete[]m_pEigenValue; }
	if (m_p1DTmp)		{ delete[]m_p1DTmp; }

	if (m_p2DCov)		{ NXUtility::Free2DMatrix<double>(m_p2DCov); m_p2DCov = NULL; }
	if (m_p2DInv)		{ NXUtility::Free2DMatrix<double>(m_p2DInv); m_p2DInv = NULL; }
	if (m_p2DTmp)		{ NXUtility::Free2DMatrix<double>(m_p2DTmp); m_p2DTmp = NULL; }

	// Unlock objects
	if (m_pUpscalingAtt)
		UnlockRead(m_pUpscalingAtt);

	if (m_pWriter)
	{
		delete m_pWriter;
		m_pWriter = NULL;
	}

	if (IsStopped())
	{
		delete m_pLFMAttribute;
		m_pLFMAttribute = NULL;
	}
}

void CXThreadLFMInterpolation::_ParseParameter()
{
	if (m_pUpscalingAtt)
		LockWrite(m_pUpscalingAtt);

	m_utm = m_pLFMGeometry->GetUTM();

	m_nI = m_utm.GetNI();
	m_nJ = m_utm.GetNJ();
	m_nK = m_pLFMGeometry->GetNK();

	m_iMethod = m_pPara->GetAlgorithmType();
	m_iVariogramType = m_pPara->GetVariogramType();
	m_nMaxNum = qMax(30, m_pPara->GetMaxSampleNum());

	m_dRadius = m_pPara->GetRadius();
	m_dPower = m_pPara->GetPower();

	m_dSill = m_pPara->GetSill();
	m_dNugget = m_pPara->GetNugget();
	m_dRange = m_pPara->GetMaxRange();
	m_dRangeRatio = m_pPara->GetMinRange() / m_dRange;

	double dAzimuth = m_pPara->GetAzimuth();
	double dAngle = (90. - dAzimuth)*M_RAD;

	m_dAnis[0] = cos(dAngle);
	m_dAnis[1] = sin(dAngle);
	m_dAnis[2] = -sin(dAngle);
	m_dAnis[3] = cos(dAngle);
}

bool CXThreadLFMInterpolation::_IsEnoughPoints()
{
	QString strMng1 = "Cannot read data from the upscaling result.";

	QString strMng2 = "The framework of the low frequency model is too large \n"
		"or there is no enough valid well curves.";

	// Top
	if (!m_pUpscalingAtt->GetOneSliceInfo(0, m_pInputNum, m_pGridIndex, m_pX, m_pY, m_pZ))
	{
		this->EmitGeneralErrorMsg(strMng1);
		return false;
	}
	if (m_pInputNum < 2)
	{
		this->EmitGeneralErrorMsg(strMng2);
		return false;
	}

	// Bottom
	if (!m_pUpscalingAtt->GetOneSliceInfo(m_nK - 1, m_pInputNum, m_pGridIndex, m_pX, m_pY, m_pZ))
	{
		this->EmitGeneralErrorMsg(strMng1);
		return false;
	}
	if (m_pInputNum < 2)
	{
		this->EmitGeneralErrorMsg(strMng2);
		return false;
	}
	return true;
}

void CXThreadLFMInterpolation::RunThread()
{
	if (IsStopped())
		return;

	this->EmitSetWindowName("Make Low Frequency Model");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	// Initialization
	if (!_InitData())
		return;

	// Tell if there is enough data points for interpolation
	if (!_IsEnoughPoints())
		return;

	m_iCurrent = 5;
	if (IsStopped())
		return;
	else
		this->EmitUpdateProgress(m_iCurrent, m_nI*m_nK+5);

	for (int k = 0; k < m_nK; ++k)
	{
		if (m_iMethod == CXParameterLFMInterpolation::eInverseDistance)
		{
			if (!_InterpolateOneSliceWithIDP(k))
				return;
		}
		else if (m_iMethod == CXParameterLFMInterpolation::eOrdinaryKriging)
		{
			if (!_InterpolateOneSliceWithKriging(k))
				return;
		}
		else
		{
			this->EmitGeneralErrorMsg("Cannot find the selected interpolation method.");
			return;
		}
	}

	if (IsStopped())
		return;
	else
	{
		m_pWriter->Close();
	}
}



double CXThreadLFMInterpolation::_CalcCov(double deltaX, double deltaY)
{
	// small distance
	if (deltaX*deltaX + deltaY*deltaY < M_FEPS)
		return m_dNugget;

	double dX1 = deltaX*m_dAnis[0] + deltaY*m_dAnis[1];
	double dY1 = deltaX*m_dAnis[2] + deltaY*m_dAnis[3] / m_dRangeRatio;

	double h = sqrt(dX1*dX1 + dY1*dY1);
	double a = m_dRange;

	double dCov = 0., ha;
	switch (m_iVariogramType)
	{
	case CXParameterLFMInterpolation::Exponential:
	{
		dCov = (m_dSill - m_dNugget)*(1.0 - exp(-3.0*h / a)) + m_dNugget;
	}
	break;

	case CXParameterLFMInterpolation::Spherical:
	{
		ha = h / a;
		if (ha < 1.)
			dCov = (m_dSill - m_dNugget)*ha*(1.5 - 0.5*ha*ha) + m_dNugget;
	}
	break;

	case CXParameterLFMInterpolation::Gaussian:
	{
		ha = h / a;
		dCov = (m_dSill - m_dNugget)*(1 - exp(-3.0*ha*ha)) + m_dNugget;
	}
	break;
	}
	return dCov;
}

bool CXThreadLFMInterpolation::_InitData()
{
	try
	{
		m_pSliceData = new float[m_nI*m_nJ];
		m_pGridIndex = new int[m_nI*m_nJ];

		m_pIndex = new int[m_nI*m_nJ];

		m_pX = new double[m_nI*m_nJ];
		m_pY = new double[m_nI*m_nJ];
		m_pZ = new double[m_nI*m_nJ];

		m_pG = new double[m_nMaxNum + 1];
		m_pZBar = new double[m_nMaxNum + 1];

		m_pEigenValue = new double[m_nMaxNum + 1];
		m_p1DTmp = new double[m_nMaxNum + 1];
	}
	catch (std::bad_alloc)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	m_p2DCov = NXUtility::New2DMatrix<double>(m_nMaxNum + 1, m_nMaxNum + 1);
	m_p2DInv = NXUtility::New2DMatrix<double>(m_nMaxNum + 1, m_nMaxNum + 1);
	m_p2DTmp = NXUtility::New2DMatrix<double>(m_nMaxNum + 1, m_nMaxNum + 1);
	if (!m_p2DCov || !m_p2DInv || !m_p2DTmp)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	// Data writer	
	if (!m_pWriter->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the file to write data.");
		return false;
	}

	return true;
}

bool CXThreadLFMInterpolation::_InitOneSlice(int iSlice)
{
	if (!m_pUpscalingAtt->GetOneSliceInfo(iSlice, m_pInputNum, m_pGridIndex, m_pX, m_pY, m_pZ))
	{
		this->EmitGeneralErrorMsg("Cannot read data from the upscaling result.");
		return false;
	}

	if (m_pInputNum < 2)
	{
		this->EmitGeneralErrorMsg("You do not have enough data points to do interpolation");
		return false;
	}

	// Delete K-D tree
	if (m_pKDTree)
	{
		delete m_pKDTree;
		m_pKDTree = NULL;
	}

	// Too many input  points
	if (m_pInputNum > 30)
	{
		// Create 2-D tree
		m_pKDTree = new CXKDTree(m_pX, m_pY, m_pInputNum);
		if (!m_pKDTree->CreateKDTree())
		{
			this->EmitGeneralErrorMsg("Cannot create the K-D tree.");
			return false;
		}
	}

	return true;
}

bool CXThreadLFMInterpolation::_InterpolateOneSliceWithIDP(int iSlice)
{
	if (!_InitOneSlice(iSlice))
		return false;

	double dIInterval = m_utm.GetIInterval();
	double dJInterval = m_utm.GetJInterval();
	double dInterval = sqrt(dIInterval*dIInterval + dJInterval*dJInterval) / 2.;

	if (m_pKDTree == NULL)
	{
		int iInputIndex, nCount;
		double dX, dY, dRadius, dSumWeight, dSumValue, dWeight;
		for (int i = 0; i < m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nI*m_nK + 5);
			}

			for (int j = 0; j < m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ + j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ + j] = m_pZ[iInputIndex];
					continue;
				}

				// Loop all input points
				m_utm.IJToXY(i, j, dX, dY);

				nCount = 0;
				dSumValue = 0.;
				dSumWeight = 0.;
				for (int k = 0; k < m_pInputNum; ++k)
				{
					dRadius = sqrt((dX - m_pX[k])*(dX - m_pX[k]) + (dY - m_pY[k])*(dY - m_pY[k]));

					if (dRadius > m_dRadius)
						continue;
					else
						++nCount;

					if (dRadius < dInterval)
						dRadius = dInterval;

					dWeight = 1. / dRadius;
					dWeight = pow(dWeight, m_dPower);
					dSumWeight += dWeight;
					dSumValue += dWeight*m_pZ[k];
				}
				if (nCount == 0)
				{
					this->EmitGeneralErrorMsg("The search radius is too small.");
					return false;
				}
				else
				{
					m_pSliceData[i*m_nJ + j] = static_cast<float>(dSumValue / dSumWeight);
				}
			}//j
		}//i
	}
	else // Need K-D tree
	{
		int iInputIndex, nCount;
		double dX, dY, dRadius, dSumWeight, dSumValue, dWeight;
		for (int i = 0; i < m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nI*m_nK + 5);
			}

			for (int j = 0; j < m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ + j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ + j] = m_pZ[iInputIndex];
					continue;
				}

				m_utm.IJToXY(i, j, dX, dY);
				m_nNPNum = m_pKDTree->NNearest(dX, dY, m_dRadius, m_pIndex, m_pPara->GetMaxSampleNum());

				if (m_nNPNum == -1)
				{
					m_pSliceData[i*m_nJ + j] = (float)m_pZ[m_pIndex[0]];
				}
				else if (m_nNPNum < 2)
				{
					this->EmitGeneralErrorMsg("The search radius is too small.");
					return false;

				}
				else
				{
					// Loop all input points
					m_utm.IJToXY(i, j, dX, dY);

					nCount = 0;
					dSumValue = 0.;
					dSumWeight = 0.;
					for (int k = 0; k < m_nNPNum; ++k)
					{
						dRadius = sqrt((dX - m_pX[m_pIndex[k]])*(dX - m_pX[m_pIndex[k]]) + (dY - m_pY[m_pIndex[k]])*(dY - m_pY[m_pIndex[k]]));

						if (dRadius > m_dRadius)
							continue;
						else
							++nCount;

						if (dRadius < dInterval)
							dRadius = dInterval;

						dWeight = 1. / dRadius;
						dWeight = pow(dWeight, m_dPower);
						dSumWeight += dWeight;
						dSumValue += dWeight*m_pZ[k];
					}
					if (nCount == 0)
					{
						this->EmitGeneralErrorMsg("The search radius is too small.");
						return false;
					}
					else
					{
						m_pSliceData[i*m_nJ + j] = static_cast<float>(dSumValue / dSumWeight);
					}
				}
			} //j
		} //i
	}

	m_pWriter->WriteUSection(iSlice, m_pSliceData);

	return true;

}

int CXThreadLFMInterpolation::_SearchIndex(int index)
{
	for (int i = 0; i < m_pInputNum; ++i)
	{
		if (index == m_pGridIndex[i])
		{
			return i;
		}
	}
	return -1;
}

bool CXThreadLFMInterpolation::_InterpolateOneSliceWithKriging(int iSlice)
{
	if (!_InitOneSlice(iSlice))
		return false;

	// do not need K-D tree
	if (m_pKDTree == NULL)
	{
		if (m_iMethod == CXParameterLFMInterpolation::eGLobalKriging)
		{
			m_nCovNum = m_pInputNum;
			m_dGlobalMean = std::accumulate(m_pZ, m_pZ + m_pInputNum, 0.) / m_pInputNum;
		}
		else
		{
			m_nCovNum = m_pInputNum + 1;
			m_dGlobalMean = 0.;
		}		

		// Calculate covariance matrix
		for (int ii = 0; ii < m_pInputNum; ++ii)
		{
			for (int jj = 0; jj <= ii; ++jj)
			{
				m_p2DCov[ii][jj] = _CalcCov(m_pX[ii] - m_pX[jj], m_pY[ii] - m_pY[jj]);
				m_p2DCov[jj][ii] = m_p2DCov[ii][jj];
			}
			if (m_iMethod == CXParameterLFMInterpolation::eOrdinaryKriging)
			{
				m_p2DCov[m_pInputNum][ii] = 1.;
				m_p2DCov[ii][m_pInputNum] = 1.;
			}
		}

		if (m_iMethod == CXParameterLFMInterpolation::eOrdinaryKriging)
		{
				m_p2DCov[m_pInputNum][m_pInputNum] = 0.;
		}

		// Calculate inverse covariance matrix
		_CalcInverseMatrix();

		double dX, dY, dSum;
		int iInputIndex;
		for (int i = 0; i < m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nI*m_nK + 5);
			}

			for (int j = 0; j < m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ + j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ + j] = m_pZ[iInputIndex];
					continue;
				}

				m_utm.IJToXY(i, j, dX, dY);

				// Calculate G vector
				for (int ii = 0; ii < m_pInputNum; ++ii)
				{
					m_pG[ii] = _CalcCov(dX - m_pX[ii], dY - m_pY[ii]);
				}
				m_pG[m_pInputNum] = 1.0;

				// Calculate Z vector
				for (int ii = 0; ii < m_pInputNum; ++ii)
				{
					m_pZBar[ii] = m_pZ[ii] - m_dGlobalMean;
				}
				m_pZBar[m_pInputNum] = 0.;

				// Calculate the result	Z'*Inv*G			
				for (int ii = 0; ii < m_nCovNum; ++ii)
				{
					dSum = 0.0;
					for (int jj = 0; jj < m_nCovNum; ++jj)
					{
						dSum += m_p2DInv[ii][jj] * m_pG[jj];
					}
					m_p1DTmp[ii] = dSum;
				}
				dSum = 0.0;
				for (int ii = 0; ii < m_nCovNum; ++ii)
				{
					dSum += m_pZBar[ii] * m_p1DTmp[ii];
				}

				dSum += m_dGlobalMean;

				m_pSliceData[i*m_nJ + j] = (float)dSum;

			} //j
		}//i
	}
	else
	{
		double dX, dY, dSum;
		int iInputIndex;
		for (int i = 0; i < m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nI*m_nK + 5);
			}

			for (int j = 0; j < m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ + j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ + j] = m_pZ[iInputIndex];
					continue;
				}

				m_utm.IJToXY(i, j, dX, dY);
				m_nNPNum = m_pKDTree->NNearest(dX, dY, m_dRange, m_pIndex, m_pPara->GetMaxSampleNum());

				if (m_nNPNum == -1)
				{
					m_pSliceData[i*m_nJ + j] = (float)m_pZ[m_pIndex[0]];
				}
				else if (m_nNPNum < 2)
				{
					this->EmitGeneralErrorMsg("The search radius is too small.");
					return false;

				}
				else
				{
					if (m_iMethod == CXParameterLFMInterpolation::eGLobalKriging)
					{
						m_nCovNum = m_nNPNum;
					}
					else
					{
						m_nCovNum = m_nNPNum + 1;
					}

					// Calculate covariance matrix
					for (int ii = 0; ii < m_nNPNum; ++ii)
					{
						for (int jj = 0; jj <= ii; ++jj)
						{
							m_p2DCov[ii][jj] = _CalcCov(m_pX[m_pIndex[ii]] - m_pX[m_pIndex[jj]], m_pY[m_pIndex[ii]] - m_pY[m_pIndex[jj]]);
							m_p2DCov[jj][ii] = m_p2DCov[ii][jj];
						}
						if (m_iMethod == CXParameterLFMInterpolation::eOrdinaryKriging)
						{
							m_p2DCov[m_nNPNum][ii] = 1.;
							m_p2DCov[ii][m_nNPNum] = 1.;
						}
					}
					if (m_iMethod == CXParameterLFMInterpolation::eOrdinaryKriging)
					{
						m_p2DCov[m_nNPNum][m_nNPNum] = 0.;
					}

					// Calculate G vector
					for (int ii = 0; ii < m_nNPNum; ++ii)
					{
						m_pG[ii] = _CalcCov(dX - m_pX[m_pIndex[ii]], dY - m_pY[m_pIndex[ii]]);
					}
					m_pG[m_nNPNum] = 1.0;

					// Calculate Z vector
					for (int ii = 0; ii < m_nNPNum; ++ii)
					{
						m_pZBar[ii] = m_pZ[m_pIndex[ii]];
					}
					m_pZBar[m_nNPNum] = 0.;

					if (m_iMethod == CXParameterLFMInterpolation::eGLobalKriging)
					{
						m_dGlobalMean = std::accumulate(m_pZBar, m_pZBar + m_nNPNum, 0.) / m_nNPNum;

						for (int ii = 0; ii < m_nNPNum; ++ii)
						{
							m_pZBar[ii] -= m_dGlobalMean;
						}
					}
					else
					{
						m_dGlobalMean = 0.;
					}


					// Calculate inverse covariance matrix
					_CalcInverseMatrix();

					// Calculate the result	Z'*Inv*G			
					for (int ii = 0; ii < m_nCovNum; ++ii)
					{
						dSum = 0.0;
						for (int jj = 0; jj < m_nCovNum; ++jj)
						{
							dSum += m_p2DInv[ii][jj] * m_pG[jj];
						}
						m_p1DTmp[ii] = dSum;
					}
					dSum = 0.0;
					for (int ii = 0; ii < m_nCovNum; ++ii)
					{
						dSum += m_pZBar[ii] * m_p1DTmp[ii];
					}

					dSum += m_dGlobalMean;

					m_pSliceData[i*m_nJ + j] = (float)dSum;
				}
			}//j
		}//i
	}

	m_pWriter->WriteUSection(iSlice, m_pSliceData);

	return true;
}

void CXThreadLFMInterpolation::_CalcInverseMatrix()
{
	if (!NXBLAS::CholeskyInverse(m_nCovNum, m_p2DCov, m_p2DTmp, m_p2DInv))
	{
		NXBLAS::SolveSVD(m_p2DCov, m_pEigenValue, m_p1DTmp, m_nCovNum);

		for (int i = 0; i < m_nCovNum; ++i)
		{
			if (qAbs(m_pEigenValue[i]) < M_FEPS)
				m_pEigenValue[i] = 0.0;
			else
				m_pEigenValue[i] = 1. / m_pEigenValue[i];
		}
		double dSum;
		for (int i = 0; i < m_nCovNum; ++i)
		{
			for (int j = 0; j <= i; ++j)
			{
				dSum = 0.0;
				for (int k = 0; k < m_nCovNum; ++k)
				{
					dSum += m_pEigenValue[k] * m_p2DCov[i][k] * m_p2DCov[j][k];
				}
				m_p2DInv[i][j] = dSum;
				m_p2DInv[j][i] = dSum;
			}
		}
	}
}