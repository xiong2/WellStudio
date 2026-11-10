#include <QString>
#include <QApplication>
#include "xobject.h"
#include "xthreadmake2dgrid.h"
#include "xparametermake2dgrid.h"
#include "xwelltops.h"
#include "x3dsurface.h"

#include "xmathmacro.h"
#include "xglobal.h"
#include <cmath>
#include <cassert>
#include "xkdtree.h"
#include "xutility.h"
#include "xblas.h"
#include "x3dpoints.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xgraphicsapi.h"
#include "xfunctiontemplate.h"
#include <qglobal.h>
#include "xproject.h"
#include <QFile>
#include <qtextstream.h>
#include "x3dpoints.h"

CXThreadMake2DGrid::CXThreadMake2DGrid(CXParameterMake2DGrid* pPara, CXObject* pObj)
:m_pPara(pPara),m_pSourceObj(pObj)
{
	assert(NULL != m_pPara);
	assert(NULL != m_pSourceObj);

	m_pKDTree = NULL;

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

	
	if (m_pSourceObj && m_pPara)
	{
		_ParseParameter();
		_InitLock();
		_CreateObj();
	}
}

CXThreadMake2DGrid::~CXThreadMake2DGrid()
{

	if (m_pSourceObj)
	{
		this->UnlockRead(m_pSourceObj);
	}

	// Delete buffers
	if (m_pIndex)		{delete []m_pIndex;}
	if (m_pSliceData)	{delete []m_pSliceData;}
	if (m_pGridIndex)	{delete []m_pGridIndex;}

	if (m_pX)			{delete []m_pX;}
	if (m_pY)			{delete []m_pY;}
	if (m_pZ)			{delete []m_pZ;}
	if (m_pG)			{delete []m_pG;}
	if (m_pZBar)		{delete []m_pZBar;}
	if (m_pEigenValue)	{delete []m_pEigenValue;}
	if (m_p1DTmp)		{delete []m_p1DTmp;}

	if (m_p2DCov)		{NXUtility::Free2DMatrix<double>(m_p2DCov); m_p2DCov = NULL;}
	if (m_p2DInv)		{NXUtility::Free2DMatrix<double>(m_p2DInv); m_p2DInv = NULL;}
	if (m_p2DTmp)		{NXUtility::Free2DMatrix<double>(m_p2DTmp); m_p2DTmp = NULL;}

	if (m_pKDTree)		{delete m_pKDTree; m_pKDTree=NULL;}

	if (IsStopped())
	{
		qDeleteAll(m_vecOutput);
		m_vecOutput.clear();
	}

}

void CXThreadMake2DGrid::_ParseParameter()
{
	m_nI = m_pPara->GetNI();
	m_nJ = m_pPara->GetNJ();
	m_nK = m_pPara->GetHorizonNameList().size();

	m_iMethod = m_pPara->GetAlgorithmType();
	m_iVariogramType = m_pPara->GetVariogramType();
	m_nMaxNum = qMax(30, m_pPara->GetMaxSampleNum());

	m_dRadius = m_pPara->GetRadius();
	m_dPower = m_pPara->GetPower();

	m_dSill = m_pPara->GetSill();
	m_dNugget = m_pPara->GetNugget();
	m_dRange = m_pPara->GetMaxRange();
	m_dRangeRatio = m_pPara->GetMinRange()/m_dRange;

	double dAzimuth = m_pPara->GetAzimuth();
	double dAngle = (90.- dAzimuth)*M_RAD;

	m_dAnis[0] = cos(dAngle);
	m_dAnis[1] = sin(dAngle);
	m_dAnis[2] = -sin(dAngle);
	m_dAnis[3] = cos(dAngle);

	// Init UTM
	std::vector<int> vecI = m_pPara->GetVecIIndex();
	std::vector<int> vecJ = m_pPara->GetVecJIndex();
	std::vector<double> vecX = m_pPara->GetVecXCoords();
	std::vector<double> vecY = m_pPara->GetVecYCoords();

	m_utm.InitSize(m_nI, m_nJ);
	m_utm.InitCoordinates(vecI[0], vecJ[0], vecX[0], vecY[0], 
		                  vecI[1], vecJ[1], vecX[1], vecY[1],
						  vecI[2], vecJ[2], vecX[2], vecY[2]);
}

void CXThreadMake2DGrid::_InitLock()
{
	if (m_pSourceObj)
		LockRead(m_pSourceObj);
}
void CXThreadMake2DGrid::_CreateObj()
{
	QStringList strListHorizonName = m_pPara->GetHorizonNameList();
	int nHorizonNum = strListHorizonName.size();
	for (int i=0; i<nHorizonNum; ++i)
	{
		CX3DSurface* p3DSurface = new CX3DSurface(m_utm, strListHorizonName.at(i));
		m_vecOutput.push_back(p3DSurface);
	}
}

void CXThreadMake2DGrid::RunThread()
{
	if (IsStopped())
		return;

	if (m_vecOutput.empty())
	{
		QString strErrorMsg = "Cannot create a 3-D surface.";
		EmitGeneralErrorMsg(strErrorMsg);
		return; 
	}

	this->EmitSetWindowName("Make 2-D Grid");
	this->EmitSetTaskName("Interpolating 3-D surface...");
	this->EmitStartComputing();
	qApp->processEvents();

	// Progress info
	m_nTotal = m_nK*m_nI;
	m_iCurrent = 0;

	// Initialization
	if (!_InitData())
		return;

	for (int k=0; k<m_nK; ++k)
	{
		if (m_iMethod == CXParameterMake2DGrid::eInverseDistance)
		{
			if (!_InterpolateOneSliceWithIDP(k))
				return;
		}
		else if (m_iMethod == CXParameterMake2DGrid::eKriging)
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

	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating intersection...");
	qApp->processEvents();

	//_CalcIntersection();
}


double CXThreadMake2DGrid::_CalcCov(double deltaX, double deltaY)
{
	// small distance
	if (deltaX*deltaX + deltaY*deltaY < M_FEPS)
		return m_dNugget;

	double dX1 = deltaX*m_dAnis[0] + deltaY*m_dAnis[1];
	double dY1 = deltaX*m_dAnis[2] + deltaY*m_dAnis[3]/m_dRangeRatio;

	double h = sqrt(dX1*dX1+dY1*dY1);
	double a = m_dRange;
	
	double dCov=0., ha;
	switch(m_iVariogramType)
	{
	case CXParameterMake2DGrid::Exponential:
		{
			dCov = (m_dSill-m_dNugget)*(1.0 - exp(-3.0*h/a)) + m_dNugget;			
		}
		break;

	case CXParameterMake2DGrid::Spherical:
		{
			ha = h/a;
			if (ha < 1.)
				dCov = (m_dSill-m_dNugget)*ha*(1.5 - 0.5*ha*ha) + m_dNugget;
		}
		break;

	case CXParameterMake2DGrid::Gaussian:
		{
			ha = h/a;
			dCov = (m_dSill-m_dNugget)*(1 - exp(-3.0*ha*ha)) + m_dNugget;
		}
		break;
	}
	return dCov;
}

bool CXThreadMake2DGrid::_InitData()
{
	try
	{
		m_pSliceData = new float [m_nI*m_nJ];

		m_pG = new double [m_nMaxNum+1];
		m_pZBar = new double [m_nMaxNum+1];

		m_pEigenValue = new double [m_nMaxNum+1];
		m_p1DTmp = new double [m_nMaxNum+1];
	}
	catch(std::bad_alloc)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	m_p2DCov = NXUtility::New2DMatrix<double>(m_nMaxNum+1, m_nMaxNum+1);
	m_p2DInv = NXUtility::New2DMatrix<double>(m_nMaxNum+1, m_nMaxNum+1);
	m_p2DTmp = NXUtility::New2DMatrix<double>(m_nMaxNum+1, m_nMaxNum+1);
	if (!m_p2DCov || !m_p2DInv || !m_p2DTmp)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	return true;
}

bool CXThreadMake2DGrid::_InitOneSlice(int iSlice)
{
	// support two formats
	CXWellTops* pSourceWellTops = dynamic_cast<CXWellTops*>(m_pSourceObj);
	CX3DPoints* pSourcePoints = dynamic_cast<CX3DPoints*>(m_pSourceObj);
	
	double* pData = NULL;
	CX3DPoints* p3DPoint = NULL;
	
	if (pSourceWellTops) // welltops
	{
		QString strFormation = m_pPara->GetHorizonNameList().at(iSlice);
		p3DPoint = pSourceWellTops->Get3DPointsFromFormation(strFormation);
		if (!p3DPoint)
		{
			this->EmitGeneralErrorMsg("Cannot get data from the well tops.");
			return false;
		}
		unsigned int nDataNum = 0;
		pData = p3DPoint->GetData(nDataNum);
		m_nInputNum = nDataNum/3;
		if (m_nInputNum == 0 || !pData)
		{
			delete p3DPoint;
			this->EmitGeneralErrorMsg("Cannot get data from the well tops.");
			return false;
		}
	}
	else if (pSourcePoints) // 3D points
	{
		unsigned int nDataNum = 0;
		pData = pSourcePoints->GetData(nDataNum);
		m_nInputNum = nDataNum/3;
		if (m_nInputNum == 0 || !pData)
		{
			delete p3DPoint;
			this->EmitGeneralErrorMsg("Cannot get data from the well tops.");
			return false;
		}
	}

	// allocate memory
	try
	{
		m_pX = new double [m_nInputNum];
		m_pY = new double [m_nInputNum];
		m_pZ = new double [m_nInputNum];

		m_pGridIndex = new int [m_nInputNum];
		m_pIndex = new int [m_nInputNum];
	}
	catch(std::bad_alloc)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	float fI, fJ;
	int iI, iJ;

	double dEPSInvalid = ::GetEPSofInvalidData(::g_dInvalidData);
	int nCount = -1;
	for (int i=0; i<m_nInputNum; ++i)
	{
		if (qAbs(pData[3*i    ] - g_dInvalidData ) < dEPSInvalid ||
			qAbs(pData[3*i + 1] - g_dInvalidData ) < dEPSInvalid ||
			qAbs(pData[3*i + 2] - g_dInvalidData ) < dEPSInvalid )
			continue;

		++nCount;


		m_pX[nCount] = pData[3*i    ];
		m_pY[nCount] = pData[3*i + 1];
		m_pZ[nCount] = pData[3*i + 2];

		m_pGridIndex[nCount] = -1;

		if (m_utm.XYToIJ(m_pX[nCount], m_pY[nCount], fI, fJ))
		{
			iI  = static_cast<int>(fI + 0.001);
			iJ  = static_cast<int>(fJ + 0.001);

			if (qAbs(fI - iI) < 0.00001 && qAbs(fJ - iJ) < 0.00001)
			{
				m_pGridIndex[nCount] = iI*m_nJ + iJ;
			}
		}
	}
	m_nInputNum = nCount+1;

	// delete 3D points
	if (pSourceWellTops)
	{
		delete p3DPoint;
	}

	if (m_nInputNum < 2)
	{
		this->EmitGeneralErrorMsg("You do not have enough data points to make the 2-D grid.");
		return false;
	}

	// Delete K-D tree
	if (m_pKDTree)
	{
		delete m_pKDTree; 
		m_pKDTree = NULL;
	}

	// Too many intput  points
	if (m_nInputNum > 30 && m_nInputNum > m_pPara->GetMaxSampleNum())
	{
		// Create 2-D tree
		m_pKDTree = new CXKDTree(m_pX, m_pY, m_nInputNum);
		if (!m_pKDTree->CreateKDTree())
		{
			this->EmitGeneralErrorMsg("Cannot create the K-D tree.");
			return false;
		}
	}

	return true;
}

bool CXThreadMake2DGrid::_InterpolateOneSliceWithIDP(int iSlice)
{
	if (!_InitOneSlice(iSlice))
	{
		return false;
	}

	double dIInterval = m_utm.GetIInterval();
	double dJInterval = m_utm.GetJInterval();
	double dInterval = sqrt(dIInterval*dIInterval + dJInterval*dJInterval)/2.;

	if (m_pKDTree == NULL)
	{
		int iInputIndex, nCount;
		double dX, dY, dRadius, dSumWeight, dSumValue, dWeight;
		for (int i=0; i<m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nTotal);
			}

			for (int j=0; j<m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ+j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ+j] = m_pZ[iInputIndex];
					continue;
				}

				// Loop all input points
				m_utm.IJToXY(i, j, dX, dY);

				nCount = 0;
				dSumValue = 0.;
				dSumWeight = 0.;
				for (int k=0; k<m_nInputNum; ++k)
				{
					dRadius = sqrt((dX-m_pX[k])*(dX-m_pX[k])+(dY-m_pY[k])*(dY-m_pY[k]));

					if (dRadius > m_dRadius)
						continue;
					else
						++nCount;

					if (dRadius < dInterval)
						dRadius = dInterval;

					dWeight = 1./dRadius;
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
					m_pSliceData[i*m_nJ+j]  = static_cast<float>(dSumValue/dSumWeight);
				}
			}//j
		}//i
	}
	else // Need K-D tree
	{
		int iInputIndex, nCount;		
		double dX, dY, dRadius, dSumWeight, dSumValue, dWeight;
		std::vector<double> vecDist(m_pPara->GetMaxSampleNum());
		for (int i=0; i<m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nTotal);
			}

			for (int j=0; j<m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ+j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ+j] = m_pZ[iInputIndex];
					continue;
				}

				m_utm.IJToXY(i, j, dX, dY);
				//m_nNPNum = m_pKDTree->NNearest(dX, dY, m_dRadius, m_pIndex,m_pPara->GetMaxSampleNum());

				int iResult = m_pKDTree->NNearest(dX, dY, m_pIndex, &vecDist[0], m_pPara->GetMaxSampleNum());

				if (iResult == 0)
				{
					m_pSliceData[i*m_nJ+j] = (float) m_pZ[m_pIndex[0]];
				}
				else if (iResult == -1 )
				{
					this->EmitGeneralErrorMsg("The search radius is too small.");
					return false;

				}
				else
				{
					// Loop all input points
					//m_utm.IJToXY(i, j, dX, dY);
					m_nNPNum = m_pPara->GetMaxSampleNum();

					nCount = 0;
					dSumValue = 0.;
					dSumWeight = 0.;
					for (int k=0; k<m_nNPNum; ++k)
					{
						dRadius = sqrt((dX-m_pX[m_pIndex[k]])*(dX-m_pX[m_pIndex[k]])+(dY-m_pY[m_pIndex[k]])*(dY-m_pY[m_pIndex[k]]));

						if (dRadius > m_dRadius)
							continue;
						else
							++nCount;

						if (dRadius < dInterval)
							dRadius = dInterval;

						dWeight = 1./dRadius;
						dWeight = pow(dWeight, m_dPower);
						dSumWeight += dWeight;
						dSumValue += dWeight*m_pZ[m_pIndex[k]];
					}
					if (nCount == 0)
					{
						this->EmitGeneralErrorMsg("The search radius is too small.");
						return false;
					}
					else
					{
						m_pSliceData[i*m_nJ+j]  = static_cast<float>(dSumValue/dSumWeight);
					}
				}
			} //j
		} //i
	}

	m_vecOutput.at(iSlice)->SetData(m_pSliceData);

	return true;

}

int CXThreadMake2DGrid::_SearchIndex(int index)
{
	for (int i=0; i<m_nInputNum; ++i)
	{
		if (index == m_pGridIndex[i])
		{
			return i;
		}
	}
	return -1;
}

bool CXThreadMake2DGrid::_InterpolateOneSliceWithKriging(int iSlice)
{
	if (!_InitOneSlice(iSlice))
		return false;

	// do not need K-D tree
	if (m_pKDTree == NULL)
	{	
		m_nCovNum = m_nInputNum + 1;

		// Calculate covariance matrix
		for (int ii=0; ii<m_nInputNum; ++ii)
		{
			for (int jj=0; jj<=ii; ++jj)
			{
				m_p2DCov[ii][jj] = _CalcCov(m_pX[ii]-m_pX[jj], m_pY[ii]-m_pY[jj]);
				m_p2DCov[jj][ii] = m_p2DCov[ii][jj];
			}
			m_p2DCov[m_nInputNum][ii] = 1.;
			m_p2DCov[ii][m_nInputNum] = 1.;
		}
		m_p2DCov[m_nInputNum][m_nInputNum] = 0.;

		// Calculate inverse covariance matrix
		_CalcInverseMatrix();

		double dX, dY, dSum;
		int iInputIndex;
		for (int i=0; i<m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nTotal);
			}

			for (int j=0; j<m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ+j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ+j] = m_pZ[iInputIndex];
					continue;
				}

				m_utm.IJToXY(i, j, dX, dY);

				// Calculate G vector
				for (int ii=0; ii<m_nInputNum; ++ii)
				{
					m_pG[ii] = _CalcCov(dX-m_pX[ii], dY-m_pY[ii]);
				}
				m_pG[m_nInputNum] = 1.0;

				// Calculate Z vector
				for (int ii=0; ii<m_nInputNum; ++ii)
				{
					m_pZBar[ii] = m_pZ[ii];
				}
				m_pZBar[m_nInputNum] = 0.;

				// Calculate the result	Z'*Inv*G			
				for (int ii=0; ii<m_nCovNum; ++ii)
				{
					dSum = 0.0;
					for (int jj=0; jj<m_nCovNum; ++jj)
					{
						dSum += m_p2DInv[ii][jj]*m_pG[jj];
					}
					m_p1DTmp[ii] = dSum;
				}
				dSum = 0.0;
				for (int ii=0; ii<m_nCovNum; ++ii)
				{
					dSum += m_pZBar[ii]*m_p1DTmp[ii];
				}		

				m_pSliceData[i*m_nJ+j] = (float)dSum;

			} //j
		}//i
	}
	else
	{
		double dX, dY, dSum;
		int iInputIndex;
		std::vector<double> vecDist(m_pPara->GetMaxSampleNum());
		for (int i=0; i<m_nI; ++i)
		{
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(++m_iCurrent, m_nTotal);
			}

			for (int j=0; j<m_nJ; ++j)
			{
				// The grid node matches an input node exactly.
				iInputIndex = _SearchIndex(i*m_nJ+j);
				if (iInputIndex > 0)
				{
					m_pSliceData[i*m_nJ+j] = m_pZ[iInputIndex];
					continue;
				}

				m_utm.IJToXY(i, j, dX, dY);
				//m_nNPNum = m_pKDTree->NNearest(dX, dY, m_dRange, m_pIndex,m_pPara->GetMaxSampleNum());

				int iResult = m_pKDTree->NNearest(dX, dY, m_pIndex, &vecDist[0], m_pPara->GetMaxSampleNum());

				if (iResult == 0)
				{
					m_pSliceData[i*m_nJ+j] = (float) m_pZ[m_pIndex[0]];
				}
				else if (m_nNPNum == -1 )
				{
					this->EmitGeneralErrorMsg("The search radius is too small.");
					return false;

				}
				else
				{
					m_nNPNum = m_pPara->GetMaxSampleNum();
					m_nCovNum = m_nNPNum + 1;

					// Calculate covariance matrix
					for (int ii=0; ii<m_nNPNum; ++ii)
					{
						for (int jj=0; jj<=ii; ++jj)
						{
							m_p2DCov[ii][jj] = _CalcCov(m_pX[m_pIndex[ii]]-m_pX[m_pIndex[jj]], m_pY[m_pIndex[ii]]-m_pY[m_pIndex[jj]]);
							m_p2DCov[jj][ii] = m_p2DCov[ii][jj];
						}
						m_p2DCov[m_nNPNum][ii] = 1.;
						m_p2DCov[ii][m_nNPNum] = 1.;
					}
					m_p2DCov[m_nNPNum][m_nNPNum] = 0.;

					// Calculate G vector
					for (int ii=0; ii<m_nNPNum; ++ii)
					{
						m_pG[ii] = _CalcCov(dX-m_pX[m_pIndex[ii]], dY-m_pY[m_pIndex[ii]]);
					}
					m_pG[m_nNPNum] = 1.0;

					// Calculate Z vector
					for (int ii=0; ii<m_nNPNum; ++ii)
					{
						m_pZBar[ii] = m_pZ[m_pIndex[ii]];
					}
					m_pZBar[m_nNPNum] = 0.;

					// Calculate inverse covariance matrix
					_CalcInverseMatrix();

					// Calculate the result	Z'*Inv*G			
					for (int ii=0; ii<m_nCovNum; ++ii)
					{
						dSum = 0.0;
						for (int jj=0; jj<m_nCovNum; ++jj)
						{
							dSum += m_p2DInv[ii][jj]*m_pG[jj];
						}
						m_p1DTmp[ii] = dSum;
					}
					dSum = 0.0;
					for (int ii=0; ii<m_nCovNum; ++ii)
					{
						dSum += m_pZBar[ii]*m_p1DTmp[ii];
					}		

					m_pSliceData[i*m_nJ+j] = (float)dSum;			
				}
			}//j
		}//i
	}

	m_vecOutput.at(iSlice)->SetData(m_pSliceData);

	return true;
}

void CXThreadMake2DGrid::_CalcInverseMatrix()
{
	if (!NXBLAS::CholeskyInverse(m_nCovNum, m_p2DCov, m_p2DTmp, m_p2DInv))
	{
		NXBLAS::SolveSVD(m_p2DCov, m_pEigenValue, m_p1DTmp, m_nCovNum);

		for (int i=0; i<m_nCovNum; ++i)
		{
			if (qAbs(m_pEigenValue[i]) < M_FEPS)
				m_pEigenValue[i] = 0.0;
			else
				m_pEigenValue[i] = 1./m_pEigenValue[i];
		}
		double dSum;
		for (int i=0; i<m_nCovNum; ++i)
		{
			for (int j=0; j<=i; ++j)
			{
				dSum = 0.0;
				for (int k=0; k<m_nCovNum; ++k)
				{
					dSum += m_pEigenValue[k]*m_p2DCov[i][k]*m_p2DCov[j][k];
				}
				m_p2DInv[i][j] = dSum;
				m_p2DInv[j][i] = dSum;
			}
		}
	}
}

void CXThreadMake2DGrid::_CalcIntersection()
{
	CXWell* pWell = dynamic_cast<CXWell*>(::GetObjectByID(m_pPara->GetWellID()));
	if (!pWell)
	{
		/// temporary codes
		QList<CXObject*> listObj = ::GetProject()->GetChildren(EXWell, true);
		for (int i=0; i<listObj.size(); ++i)
		{
			if (listObj.at(i)->GetObjectName() == "C4")
			{
				pWell = dynamic_cast<CXWell*>(listObj.at(i));
				break;
			}
		}
	}
	if (!pWell)
		return;

	CXWellPath* pWellPath = pWell->GetWellPath();
	if (!pWellPath)
		return;

	unsigned int nDataNum = 0;
	double* pPathData = pWellPath->GetData(nDataNum);
	if (nDataNum == 0 || !pPathData)
		return;

	// Get well top and bottom postion
	double x1, y1, x2, y2;
	x1 = pPathData[0];
	y1 = pPathData[1];

	x2 = pPathData[nDataNum-3];
	y2 = pPathData[nDataNum-2];

	// Calculate intersection
	std::vector<std::vector<double> > vecVecIntersect;
	for (int iSurface=0; iSurface<m_vecOutput.size(); ++iSurface)
	{
		std::vector<double> vecIntersect;
		float* pSurfaceData = m_vecOutput.at(iSurface)->GetData();
		assert(pSurfaceData);

		int iI1, iJ1, iI2, iJ2;
		float fI1, fJ1, fI2, fJ2;
		m_utm.XYToIJ(x1, y1, fI1, fJ1);
		m_utm.XYToIJ(x2, y2, fI2, fJ2);

		if (fI1 < fI2)
		{
			iI1 = static_cast<int>(ceil(fI1));
			iI2 = static_cast<int>(floor(fI2));
		}
		else
		{
			iI1 = static_cast<int>(floor(fI1));
			iI2 = static_cast<int>(ceil(fI2));
		}

		if (fJ1 < fJ2)
		{
			iJ1 = static_cast<int>(ceil(fJ1));
			iJ2 = static_cast<int>(floor(fJ2));
		}
		else
		{
			iJ1 = static_cast<int>(floor(fJ1));
			iJ2 = static_cast<int>(ceil(fJ2));
		}

		// Along I
		double x3, y3, x4, y4, x, y, z;
		if (qAbs(iI1 - iI2) > qAbs(iJ1 - iJ2))
		{
			int iSign = Sign(iI2 - iI1);
			int i = iI1;
			do
			{
				m_utm.IJToXY(i, 0, x3, y3);
				m_utm.IJToXY(i, m_nJ-1, x4, y4);
				
				if (!CXGraphicsAPI::IntersectionOfTwoLines(x1,y1, x2,y2, x3,y3,x4,y4,x,y))
				{
					x = x1;
					y = y1;
				}
				if (_CalcZ(x, y, pSurfaceData, z))
				{
					vecIntersect.push_back(x);
					vecIntersect.push_back(y);
					vecIntersect.push_back(z);
				}

				i += iSign;

			}while(i != iI2);
		}
		else
		{
			int jSign = Sign(iJ2 - iJ1);
			int j = iJ1;
			do
			{
				m_utm.IJToXY(0, j, x3, y3);
				m_utm.IJToXY(m_nI-1, j, x4, y4);

				if (!CXGraphicsAPI::IntersectionOfTwoLines(x1,y1, x2,y2, x3,y3,x4,y4,x,y))
				{
					x = x1;
					y = y1;
				}
				if (_CalcZ(x, y, pSurfaceData, z))
				{
					vecIntersect.push_back(x);
					vecIntersect.push_back(y);
					vecIntersect.push_back(z);
				}

				j += jSign;

			}while(j != iJ2);
		}

		vecVecIntersect.push_back(vecIntersect);
	}

	_WriteToFile(x1, y1, pWell, vecVecIntersect);
}


bool CXThreadMake2DGrid::_CalcZ(double x, double y, float* pData, double& z)
{
	float fI, fJ;
	if (!m_utm.XYToIJ(x, y, fI, fJ))
		return false;

	int iMin, iMax, jMin, jMax;
	iMin = static_cast<int>(floor(fI));
	iMax = static_cast<int>(ceil(fI));
	jMin = static_cast<int>(floor(fJ));
	jMax = static_cast<int>(ceil(fJ));

	if (iMin == iMax)
	{
		if (iMin == 0)
			++iMax;
		else 
			--iMin;
	}
	if (jMin == jMax)
	{
		if (jMin == 0)
			++jMax;
		else
			--jMin;
	}

	double z1, z2, z3, z4;
	z1 = pData[iMin*m_nJ + jMin];
	z2 = pData[iMin*m_nJ + jMax];
	z3 = pData[iMax*m_nJ + jMin];
	z4 = pData[iMax*m_nJ + jMax];

	double z5 = (jMax - fJ)*z1 + (fJ - jMin)*z2;
	double z6 = (jMax - fJ)*z3 + (fJ - jMin)*z4;

	z = (iMax - fI)*z5 + (fI - iMin)*z6;

	return true;
}

void CXThreadMake2DGrid::_WriteToFile(double x0, double y0, CXWell* pWell, std::vector<std::vector<double> >& vecVecIntersect)
{
	// get output file name;
	QString strName = ::GetProject()->GetProjectDataPath() + pWell->GetObjectName(); 
	int i = 1;
	QString strFileName = strName + QString::number(i);
	while (QFile::exists(strFileName + ".txt"))
	{
		strFileName  = strName + QString::number(++i);
	} 

	// open file
	strFileName += ".txt";
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	QTextStream out(&qFile);
    out.setCodec("UTF-8");

	out<<"# Intersection Points of 3-D Horizons and the Vertical Well Profile." <<endl;
	out<<"# File Is Exported From RFGeosteering"<<endl<<endl;
	out<<GetTr("文件标识: ")<<"@RICHFIT@"<<endl<<endl;

    // number of horizons
	out<<GetTr("层位数目: ")<<QString::number(vecVecIntersect.size())<<endl<<endl;

	QStringList strHorizonNameList = m_pPara->GetHorizonNameList();
	QStringList strRockNameList = m_pPara->GetRockNameList();
	strRockNameList.append(GetTr("空"));

	for (int i=0; i<vecVecIntersect.size(); ++i)
	{
		int nPointNum = vecVecIntersect[i].size()/3;
		out<<GetTr("层位名称: ")<<strHorizonNameList.at(i)<<"; "
		   <<GetTr("岩性: ")<<strRockNameList.at(i)<<"; "
		   <<GetTr("点数: ")<<QString::number(nPointNum)<<endl;

		double x, y, z, dist;
		for (int j=0; j<nPointNum; ++j)
		{
			x = vecVecIntersect[i][3*j ];
			y = vecVecIntersect[i][3*j+1];
			z = vecVecIntersect[i][3*j+2];
			dist = sqrt(SQR(x-x0) + SQR(y-y0));

			out<<QString::number(dist, 'f', 6)<<","<<QString::number(z, 'f', 6)<<";";
		}

		out<<endl<<endl;
	}

}

