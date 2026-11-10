#include <QApplication>
#include "xutility.h"
#include "xglobal.h"
#include "xblas.h"
#include "gsthreadsurfacecurvature.h"
#include "x3dhorizon.h"

QStringList GSThreadSurfaceCurvature::m_sListAtt ={
	"Contour Curvature",
	"Curvedness",
	"Dip Curvature",
	"Gaussian Curvature",
	"Maximum Curvature",
	"Mean Curvature",
	"Minimum Curvature",
	"Most Negative Curvature",
	"Most Positive Curvature",
	"Shape Index",
	"Strike Curvature",
	"Azimuth Curvature",
	"Lambertian Reflectance",
	"Dip Angle Curvature",
	"Dip",
	"Dip Azimuth",
	"Strike"
};


GSThreadSurfaceCurvature::GSThreadSurfaceCurvature(CX3DHorizon *pHor, QVector<int> vecPara)
{
	m_pHorizon = pHor;
	m_nI = m_pHorizon->GetUTM().GetNI();
	m_nJ = m_pHorizon->GetUTM().GetNJ();

	m_pInputData = NULL;
	m_pOutputData = NULL;
	m_pWinBuff = NULL;
	m_pValidMap = NULL;

	m_p2DLineData = NULL;	

	// memory
	m_pX = NULL;
	m_pY = NULL;
	m_pZ = NULL;

	//2D matrix
	m_pA = NULL;
	m_pAInv = NULL;
	m_p2DTmp = NULL;
	m_p2DCoeff = NULL;

	// 1D 
	m_pB = NULL;
	m_pEigenValue = NULL;
	m_p1DTmp = NULL;

	m_nWinNI = vecPara.takeFirst();
	m_nWinNJ = vecPara.takeFirst();
	for(int i = 0; i < vecPara.size(); i++)
		m_vecAttType << vecPara[i];

	createOutputHor();
}

GSThreadSurfaceCurvature::~GSThreadSurfaceCurvature()
{
	this->wait();

	if (m_pInputData)		{delete []m_pInputData; m_pInputData = NULL;}
	if (m_pOutputData)		{delete []m_pOutputData; m_pOutputData = NULL;}
	if (m_pWinBuff)			{delete []m_pWinBuff; m_pWinBuff = NULL;}
	if (m_pValidMap)		{delete []m_pValidMap; m_pValidMap = NULL;}

	if (m_p2DLineData)		{delete []m_p2DLineData; m_p2DLineData = NULL;}	

	if (m_pX != NULL)		{delete []m_pX; m_pX = NULL;}	
	if (m_pY != NULL)		{delete []m_pY; m_pY = NULL;}	
	if (m_pZ != NULL)		{delete []m_pZ; m_pZ = NULL;}	

	if (m_pA != NULL)		{NXUtility::Free2DMatrix<double>(m_pA); m_pA = NULL;}
	if (m_pAInv != NULL)	{NXUtility::Free2DMatrix<double>(m_pAInv); m_pAInv = NULL;}
	if (m_p2DTmp != NULL)	{NXUtility::Free2DMatrix<double>(m_p2DTmp); m_p2DTmp = NULL;}
	if (m_p2DCoeff != NULL)	{NXUtility::Free2DMatrix<double>(m_p2DCoeff); m_p2DCoeff = NULL;}

	if (m_pB)				{delete []m_pB; m_pB = NULL;}
	if (m_pEigenValue)		{delete []m_pEigenValue; m_pEigenValue = NULL;}
	if (m_p1DTmp)			{delete []m_p1DTmp; m_p1DTmp = NULL;}

	if (IsStopped())
	{
		//qDeleteAll(m_vecOutputHor.begin(), m_vecOutputHor.end());
		m_vecOutputHor.clear();
	}
}

void GSThreadSurfaceCurvature::RunThread()
{
	if (IsStopped())
		return;

	QString strWindowName = "Calculating surface curvature";
	EmitSetWindowName (strWindowName);
	EmitStartComputing();
	qApp->processEvents();


	// Get input data
	if (!prepareInputData())
		return;

	calculate();
}

void GSThreadSurfaceCurvature::createOutputHor()
{
	QString sWinSize = " (" + QString::number(m_nWinNI) + "X" + QString::number(m_nWinNJ) + ")";

	for (int i = 0; i < m_vecAttType.size(); i++)
	{
		int iType = m_vecAttType[i];
		if(iType >= m_sListAtt.size())
			continue;

		QString sHName = m_pHorizon->GetObjectName() + " - " + m_sListAtt[iType] + sWinSize;
		sHName = m_pHorizon->GetParent()->GetUnallocatedName(sHName);
        CX3DHorizon* pOHorizon = new CX3DHorizon(m_pHorizon->GetSurveyID(), m_pHorizon->GetUTM(), sHName);
        pOHorizon->SetObjectType(EXGS3DHorizonAtt);
        pOHorizon->SetModifiedFlag();

		m_vecOutputHor << pOHorizon;
	}
}

bool GSThreadSurfaceCurvature::prepareInputData()
{
	try
	{
		m_pInputData = new float [m_nI * m_nJ];
		m_pOutputData = new float [m_nI * m_nJ];
		m_pWinBuff = new float [m_nWinNI * m_nWinNJ];
		m_pValidMap = new bool [m_nI * m_nJ];
	}
	catch(std::bad_alloc)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	memcpy(m_pInputData, m_pHorizon->GetData(), sizeof(float) * m_nI * m_nJ);

	float fInvalidEPS = GetEPSofInvalidData(g_dInvalidData);
	int nSize = m_nI*m_nJ;
	for (int i=0; i<nSize; ++i)
	{
		if (qAbs(m_pInputData[i] - g_dInvalidData) < fInvalidEPS)
			m_pValidMap[i] = false;
		else
			m_pValidMap[i] = true;
	}

	return true;
}

bool GSThreadSurfaceCurvature::calculate()
{
	if (!m_pA)			m_pA = NXUtility::New2DMatrix<double>(6, 6);
	if (!m_pAInv)		m_pAInv = NXUtility::New2DMatrix<double>(6, 6);
	if (!m_p2DTmp)		m_p2DTmp = NXUtility::New2DMatrix<double>(6, 6);
	if (!m_p2DCoeff)	m_p2DCoeff = NXUtility::New2DMatrix<double>(m_nJ, 6);

	if (!m_pA || !m_pAInv || !m_p2DTmp || !m_p2DCoeff)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	try
	{
		if (!m_pX)          m_pX = new double [m_nWinNI * m_nWinNJ];
		if (!m_pY)          m_pY = new double [m_nWinNI * m_nWinNJ];
		if (!m_pZ)          m_pZ = new double [m_nWinNI * m_nWinNJ];

		if (!m_pB)			m_pB = new double [6];
		if (!m_pEigenValue)	m_pEigenValue = new double [6];
		if (!m_p1DTmp)		m_p1DTmp = new double [6];
	}
	catch(std::bad_alloc)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	// Get UTM
	CXSeismicUTMTool utmTool;
	utmTool.Copy(&m_pHorizon->GetUTM());

	QString strPartName  = "Calculating!";
	this->EmitSetTaskName(strPartName);
	qApp->processEvents();

	for (int n = 0; n < m_vecAttType.size(); n++)
	{
		for (int i = 0; i < m_nI; ++i)
		{
			// Progress info
			if (IsStopped())
				return false;
			else
			{
				this->EmitUpdateProgress(i, m_nI);
			}

			getLineBuffer(i, m_nWinNI);

			if (!calcOneLineCoef(i, m_nWinNI, m_nWinNJ, &utmTool))
				return false;

			calcOneLineCurvature(m_pOutputData + i * m_nJ, m_vecAttType[n]);
		}
		
		memcpy(m_vecOutputHor.at(n)->GetData(), m_pOutputData, sizeof(float) * m_nI * m_nJ);	
	}

	return true;
}

bool GSThreadSurfaceCurvature::getLineBuffer(int iIndex, int nWinNI)
{
	if (NULL == m_p2DLineData)
	{		
		try
		{
			m_p2DLineData = new float* [nWinNI];
		}
		catch(std::bad_alloc)
		{
			this->EmitMemoryNotEnough();
			return false;
		}
	}

	int iIMin = iIndex - nWinNI/2;
	int iIMax = iIndex + nWinNI/2;

	if (iIMin<0)
	{
		iIMin = 0;
		iIMax = nWinNI - 1;
	}
	if (iIMax >= m_nI)
	{
		iIMin = m_nI - nWinNI;
		iIMax = m_nI - 1;
	}

	for (int i=iIMin; i<=iIMax; ++i)
	{
		m_p2DLineData[i-iIMin] = m_pInputData + i*m_nJ;
	}

	return true;
}

bool GSThreadSurfaceCurvature::calcOneLineCoef(int iIndex, int nWinNI, int nWinNJ, CXSeismicUTMTool* pUTM)
{
	float fInvalidEPS = GetEPSofInvalidData(g_dInvalidData);
	
	int nHalfWinNI = nWinNI/2;
	int nHalfWinNJ = nWinNJ/2;
	int iIMin, iIMax, iJMin, iJMax;

	float fFactor = 0.01f;

	// I range
	iIMin = iIndex - nHalfWinNI;
	iIMax = iIndex + nHalfWinNI;
	if (iIMin<0)
	{
		iIMin = 0;
		iIMax = nWinNI - 1;
	}
	if (iIMax >= m_nI)
	{
		iIMin = m_nI - nWinNI;
		iIMax = m_nI - 1;
	}
	
	for (int j=0; j<m_nJ; ++j)
	{
		iJMin = j-nHalfWinNJ;
		iJMax = j+nHalfWinNJ;
		if (iJMin < 0)
		{
			iJMin = 0;
			iJMax = nWinNJ - 1;
		}
		if (iJMax >= m_nJ)
		{
			iJMin = m_nJ - nWinNJ;
			iJMax = m_nJ -1;
		}

		unsigned int count = 0;
		float fValue;
		double dX0, dY0, dX, dY;
		pUTM->IJToXY((iIMax+iIMin)/2, (iJMax+iJMin)/2, dX0, dY0);
		for (int iI=iIMin; iI<=iIMax; ++iI)
		{
			for (int iJ=iJMin; iJ<=iJMax; ++iJ)
			{
				fValue = m_p2DLineData[iI-iIMin][iJ];
				if (qAbs( fValue - g_dInvalidData) < fInvalidEPS)
					continue;

				pUTM->IJToXY(iI, iJ, dX, dY);

				m_pX[count] = (dX - dX0) * 0.1;
				m_pY[count] = (dY - dY0) * 0.1;
				m_pZ[count++] = fValue * fFactor;	
			}
		}

		if (!quadSurfaceFitting(count,  m_p2DCoeff[j]))
		{
			for (int iii=0; iii<6; ++iii)
				m_p2DCoeff[j][iii] = g_dInvalidData;
		}
	}

	return true;
}

bool GSThreadSurfaceCurvature::quadSurfaceFitting(unsigned int n, double* pOneCoef)
{
	// pOneCoef: fitted coefficients for the equation of z = ax^2+by^2+cxy+dx+ey+f
	if (n < 6 )
		return false;

	double dSum = 0.0;
	for (int i=0; i<n; ++i)
		dSum += m_pZ[i];
	dSum /= n;
	for (int i=0; i<n; ++i)
		m_pZ[i] -= dSum;

    double fFactor = 1.;

    // Multiply by the factor
	for (int i=0; i<n; ++i)
	{
		m_pX[i] *= fFactor;
		m_pY[i] *= fFactor;
		m_pZ[i] *= fFactor;
	}

	// A'*A
	for (int i=0; i<6; ++i)
	for (int j=i; j<6; ++j)
		m_pA[i][j] = 0.;

	for (int i=0; i<n; ++i) {m_pA[0][0] += m_pX[i]*m_pX[i]*m_pX[i]*m_pX[i];}
	for (int i=0; i<n; ++i) {m_pA[0][1] += m_pX[i]*m_pX[i]*m_pY[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[0][2] += m_pX[i]*m_pX[i]*m_pX[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[0][3] += m_pX[i]*m_pX[i]*m_pX[i];}
	for (int i=0; i<n; ++i) {m_pA[0][4] += m_pX[i]*m_pX[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[0][5] += m_pX[i]*m_pX[i];}

	for (int i=0; i<n; ++i) {m_pA[1][1] += m_pY[i]*m_pY[i]*m_pY[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[1][2] += m_pX[i]*m_pY[i]*m_pY[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[1][3] += m_pX[i]*m_pY[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[1][4] += m_pY[i]*m_pY[i]*m_pY[i];}
	for (int i=0; i<n; ++i) {m_pA[1][5] += m_pY[i]*m_pY[i];}

	m_pA[2][2] = m_pA[0][1];
	m_pA[2][3] = m_pA[0][4];
	m_pA[2][4] = m_pA[1][3];
	for (int i=0; i<n; ++i) {m_pA[2][5] += m_pX[i]*m_pY[i];}

	m_pA[3][3] = m_pA[0][5];
	m_pA[3][4] = m_pA[2][5];		
	for (int i=0; i<n; ++i) {m_pA[3][5] += m_pX[i];}

	m_pA[4][4] = m_pA[1][5];
	for (int i=0; i<n; ++i) {m_pA[4][5] += m_pY[i];}

	m_pA[5][5] = n;

	// symmetrical contents
	for (int i=0; i<6; ++i)
	{
		for (int j=0; j<i; ++j)
			m_pA[i][j] = m_pA[j][i];
	}

	// B
	for (int i=0; i<6; ++i)
		m_pB[i] = 0.;

	for (int i=0; i<n; ++i)
	{
		m_pB[0] += m_pX[i]*m_pX[i]*m_pZ[i];
		m_pB[1] += m_pY[i]*m_pY[i]*m_pZ[i];
		m_pB[2] += m_pX[i]*m_pY[i]*m_pZ[i];
		m_pB[3] += m_pX[i]*m_pZ[i];
		m_pB[4] += m_pY[i]*m_pZ[i];
		m_pB[5] += m_pZ[i];
	}

	// Get inverse
	if (!NXBLAS::CholeskyInverse(6, m_pA, m_p2DTmp, m_pAInv))
	{
		NXBLAS::SolveSVD(m_pA, m_pEigenValue, m_p1DTmp, 6);

		for (int i=0; i<6; ++i)
		{
			if (m_pEigenValue[i] < M_FEPS)
				m_pEigenValue[i] = 0.0;
			else
				m_pEigenValue[i] = 1.0/m_pEigenValue[i];
		}
		double fSum;
		for (int i=0; i<6; ++i)
		{
			for (int j=0; j<=i; ++j)
			{
				fSum = 0.0;
				for (int k=0; k<6; ++k)
				{
					fSum += m_pEigenValue[k]*m_pA[i][k]*m_pA[j][k];
				}
				m_pAInv[i][j] = fSum;
				m_pAInv[j][i] = fSum;
			}
		}
	}

	// Get the coef
	double fSum;
	for (int i=0; i<6; ++i)
	{
		fSum = 0.0;
		for (int j=0; j<6; ++j)
			fSum += m_pAInv[i][j]*m_pB[j];

		pOneCoef[i] = fSum;
	}

	return true;
}

void GSThreadSurfaceCurvature::calcOneLineCurvature(float* pData, int nType)
{
	float a, b, c, d, e;
	float kMean, kGauss, kMin, kMax, tmp1, tmp2;
	float alpha	= 0.78539816339745f;
	float phi = 0.78539816339745f;	
	float fInvalidEPS = GetEPSofInvalidData(g_dInvalidData);

	for (int j=0; j<m_nJ; ++j)
	{
		a = static_cast<float>(m_p2DCoeff[j][0]);
		b = static_cast<float>(m_p2DCoeff[j][1]);
		c = static_cast<float>(m_p2DCoeff[j][2]);
		d = static_cast<float>(m_p2DCoeff[j][3]);
		e = static_cast<float>(m_p2DCoeff[j][4]);

		if (qAbs(a - g_dInvalidData) < fInvalidEPS)
		{
			pData[j] = M_FINVALID;
			continue;
		}

		if(nType == 0)//  Contour
		{
			tmp1 = 2.0*(a*e*e + b*d*d - c*d*e);
			tmp2 = pow((float)d*d + e*e, (float)1.5);
			if (qAbs(tmp2) > M_DEPS)
				pData[j] = tmp1/tmp2;
			else
				pData[j] =  0.0f;
		}
		else if(nType == 1)//  Curvedness
		{
			kMean= (a*(1 + e*e) + b*(1 + d*d) - c*d*e)/sqrt(1 + d*d + e*e);
			kGauss = (4*a*b - c*c)/((1 + d*d + e*e)*(1 + d*d + e*e));
			kMin = kMean - sqrt(qAbs(kMean*kMean - kGauss));
			kMax = kMean + sqrt(qAbs(kMean*kMean-kGauss));

			pData[j] = sqrt((kMax*kMax + kMin*kMin)*0.5);
		}
		else if(nType == 2)//  Dip
		{
			tmp1 = 2.0*(a*e*e + b*d*d - c*d*e);
			if (qAbs(2*(a*d*d + b*e*e + c*d*e)) > M_DEPS)
			{
				tmp2=(d*d + e*e)*pow(((float)1 + d*d + e*e),(float)1.5);
				if (qAbs(tmp2) < M_DEPS)
					pData[j] = tmp1>0?2:-2;
				else 
					pData[j] = tmp1/tmp2;
			}
			else
				pData[j] = 0.0f;
		}
		else if(nType == 3)//  Gaussian
		{
			pData[j] = (4*a*b - c*c)/((1 + d*d + e*e)*(1 + d*d + e*e));
		}
		else if(nType == 4)//  Maximum
		{
			kMean= (a*(1 + e*e) + b*(1 + d*d) - c*d*e)/sqrt(1 + d*d + e*e);
			kGauss= (4*a*b - c*c)/((1 + d*d + e*e)*(1 + d*d + e*e));
			pData[j] = kMean + sqrt(qAbs(kMean*kMean-kGauss));
		}
		else if(nType == 5)//  Mean
		{
			pData[j] = (a*(1 + e*e) + b*(1 + d*d) - c*d*e)/sqrt(1+d*d+e*e);
		}
		else if(nType == 6)//  Minimum
		{
			kMean= (a*(1 + e*e) + b*(1 + d*d) - c*d*e)/sqrt(1 + d*d + e*e);
			kGauss= (4*a*b - c*c)/((1 + d*d + e*e)*(1 + d*d + e*e));
			pData[j] = kMean - sqrt(qAbs(kMean*kMean - kGauss));
		}
		else if(nType == 7)//  most negative
		{
			pData[j] = (a + b - sqrt((a - b)*(a - b) + c*c));
		}
		else if(nType == 8)//  most postive
		{			
			pData[j] = (a + b + sqrt((a - b)*(a - b) + c*c));	
		}
		else if(nType == 9)//  Shapeindex
		{
			kMean = (a*(1 + e*e) + b*(1 + d*d) - c*d*e)/sqrt(1 + d*d + e*e);
			kGauss = (4*a*b - c*c)/((1 + d*d + e*e)*(1 + d*d + e*e));
			kMin = kMean - sqrt(qAbs(kMean*kMean - kGauss));
			kMax = kMean + sqrt(qAbs(kMean*kMean-kGauss));

			if (qAbs(kMin - kMax) > M_FEPS)
				pData[j] = M_2_PI*atan((kMin + kMax)/(kMin - kMax));
			else
				pData[j] = 0.5;
		}
		else if(nType == 10)//  Strike
		{					
			if (qAbs (2*(a*e*e + b*d*d - c*d*e)) > M_DEPS)
				pData[j] = 2*(a*e*e + b*d*d - c*d*e)/((d*d + e*e)*sqrt(1 + d*d + e*e));
			else
				pData[j] = 0.0f;
		}
		else if (nType == 11) //Azimuth
		{
			pData[j] = (float) atan2(e,d)*180.0f/M_PI;
		}
		else if (nType == 12)// Lambertian Reflectance
		{
			pData[j] = (d*sin(alpha)*cos(phi)+ e*cos(alpha)*cos(phi)+sin(phi))/sqrt(d*d + e*e + 1.0f);
		}
		else if (nType == 13)// Dip angle
		{
			pData[j] = (float) atan(sqrt(d*d+e*e))*180.0f/M_PI;
		}
		else if (nType == 14) //dip
		{
			pData[j] = (float) atan(sqrt(d*d+e*e))*180.0f/M_PI;
		}
		else if (nType == 15) //dip-azimuth
		{
			pData[j] = (float) (float) atan2(e,d)*180.0f/M_PI;
		}
		else if (nType == 16) //dip-azimuth
		{
			tmp1 = (float) (float) atan2(e,d)*180.0f/M_PI;
			tmp1 += 180.0f;
			pData[j] = (tmp1 > 180 ? tmp1-180.0f : tmp1);
		}		
		else
		{
			//assert(false);
		}
	}
}