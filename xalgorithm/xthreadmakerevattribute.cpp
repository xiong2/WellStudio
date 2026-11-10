#include "xthreadmakerevattribute.h"
#include <QApplication>
//#include "xmathmacro.h"
#include "xglobal.h"
//#include <cmath>
#include <cassert>
//#include "xutility.h"
//#include "xblas.h"
//#include "x3dpoints.h"
#include "xwell.h"
#include "xwellpath.h"
//#include "xgraphicsapi.h"
//#include "xfunctiontemplate.h"
#include <qglobal.h>
#include "xproject.h"
//#include "myfile.h"
//#include <qtextstream.h>

#include "xwellcondition.h"
#include "xwellcells.h"
#include "xwellcurvecells.h"
#include "xreservoirmodel.h"
#include "xgridmodel.h"
#include "xgridcell.h"
#include "xpropertymodel.h"
#include "xlog.h"

#include <GsTL/kriging/kriging_weights.h>
#include <GsTL/kriging/SK_constraints.h>
#include <GsTL/kriging/OK_constraints.h>
#include <GsTL/kriging/KT_constraints.h>
#include <GsTL/kriging/linear_combination.h>
#include <GsTL/kriging/cokriging_weights.h>

#include <GsTL/cdf_estimator/gaussian_cdf_Kestimator.h>
#include <GsTL/cdf/gaussian_cdf.h>

#include <GsTL/geometry/covariance.h>

#include <GsTL/kriging/kriging_constraints.h>
#include <GsTL/kriging/kriging_combiner.h>


CRLThreadMakeRevAttribute::CRLThreadMakeRevAttribute(CXParameterMakeRevInterpolation* pPara,CXObject* pCurveCells):m_pSourceObj(pCurveCells)
{
	assert(NULL != m_pSourceObj);

	m_pPara=pPara;
	m_pKDTree = NULL;
	m_pPropObj = NULL;
	// 1-D buffers
	m_pIndex = NULL;
	m_pSliceData = NULL;
	m_pGridIndex = NULL;
	m_pX = NULL;
	m_pY = NULL;
	m_pZ = NULL;
	m_pAtt=NULL;
	m_pG = NULL;
	m_pZBar = NULL;
	m_pEigenValue = NULL;
	m_p1DTmp = NULL;

	// 2-D buffers
	m_p2DCov = NULL;
	m_p2DInv = NULL;
	m_p2DTmp = NULL;

}
CRLThreadMakeRevAttribute::~CRLThreadMakeRevAttribute()
{
	if (m_pIndex)		{delete []m_pIndex;}
	if (m_pSliceData)	{delete []m_pSliceData;}
	if (m_pGridIndex)	{delete []m_pGridIndex;}

	if (m_pX)			{delete []m_pX;}
	if (m_pY)			{delete []m_pY;}
	if (m_pZ)			{delete []m_pZ;}
	if (m_pAtt)			{delete []m_pAtt;}
	if (m_pG)			{delete []m_pG;}
	if (m_pZBar)		{delete []m_pZBar;}
	if (m_pEigenValue)	{delete []m_pEigenValue;}
	if (m_p1DTmp)		{delete []m_p1DTmp;}

	/*if (m_p2DCov)		{NXUtility::Free2DMatrix<double>(m_p2DCov); m_p2DCov = NULL;}
	if (m_p2DInv)		{NXUtility::Free2DMatrix<double>(m_p2DInv); m_p2DInv = NULL;}
	if (m_p2DTmp)		{NXUtility::Free2DMatrix<double>(m_p2DTmp); m_p2DTmp = NULL;}*/

	if (m_pKDTree)		{delete m_pKDTree; m_pKDTree=NULL;}

}

bool CRLThreadMakeRevAttribute::_InitData()
{
	
	QList<QList<double> >allWellCurveCellAtt;
	QList<QList<unsigned int> >allWellCellId;
	vector<int> numOfCellofOneCurve;
	int numofSampleAttr=0;
	int numofSampleCell=0;
	
	m_dSill=m_pPara->GetSill();
	m_dNugget=m_pPara->GetNugget();
	m_dRange=m_pPara->GetMaxRange();
	m_nMaxNum=m_pPara->GetMaxSampleNum();
	m_iVariogramType=m_pPara->GetVariogramType();

	CXReservoirModel *pRevObj=dynamic_cast<CXReservoirModel*>(m_pSourceObj->GetParent()->GetParent());
	if(!pRevObj)
		return false;
	CXGridModel *pGridMode=pRevObj->GetGridModel();
	QList<CXGridCell*> pAllGridCell=pGridMode->GetAllCells();
	QList<QUuid> WellIdList;
	
	QList<CXObject*> ListObj=(m_pSourceObj->GetChildren(EXWellCurveCells));
	foreach(CXObject* pRl,ListObj)
	{
		CXWellCurveCells *pWellCurveCells=dynamic_cast<CXWellCurveCells*>(pRl);
		QUuid wellID=pWellCurveCells->GetWellID();
		WellIdList.push_back(wellID);
		allWellCurveCellAtt.push_back(pWellCurveCells->GetValueList());
		numofSampleAttr=numofSampleAttr+(int)(pWellCurveCells->GetValueList().size());
	}

	if(m_pSourceObj)
	{
		CXWellCondition *pWellCondition=dynamic_cast<CXWellCondition*>(m_pSourceObj->GetParent());
		QList<CXObject *> listWellCells =pWellCondition-> GetChildren(EXWellCells);
		for(int i=0;i<listWellCells.size();i++)
		{
			CXWellCells *pCells=dynamic_cast<CXWellCells*>(listWellCells[i]);
			QUuid wellID=pCells->GetWellID();
			if(!WellIdList.contains(wellID))
			{
				continue;
			}
			int indexWell=WellIdList.indexOf(wellID,0);
			QList<unsigned int > cellIds= pCells->GetCellList();
			allWellCellId.insert(indexWell,cellIds);	
			numOfCellofOneCurve.push_back(numofSampleCell);
			numofSampleCell=numofSampleCell+cellIds.size();
		}

	}
	assert(allWellCurveCellAtt.size()==allWellCellId.size());
	assert(numofSampleAttr==numofSampleCell);

	try
	{
		m_pSliceData = new double [pAllGridCell.size()];
		m_pX=new double[numofSampleCell];
		m_pY=new double[numofSampleCell];
		m_pZ=new double[numofSampleCell];
		m_pAtt=new double[numofSampleCell];
		m_pGridIndex=new int[numofSampleCell];
		m_pIndex=new int[numofSampleCell];

		m_pEigenValue = new double [m_nMaxNum+1];
		m_p1DTmp = new double [m_nMaxNum+1];
		m_pG = new double [m_nMaxNum+1];
		m_pZBar = new double [m_nMaxNum+1];
	}
	catch(std::bad_alloc)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	/*m_p2DCov = NXUtility::New2DMatrix<double>(m_nMaxNum+1, m_nMaxNum+1);
	m_p2DInv = NXUtility::New2DMatrix<double>(m_nMaxNum+1, m_nMaxNum+1);
	m_p2DTmp = NXUtility::New2DMatrix<double>(m_nMaxNum+1, m_nMaxNum+1);*/
	//if (!m_p2DCov || !m_p2DInv || !m_p2DTmp)
	//{
	//	this->EmitMemoryNotEnough();
	//	return false;
	//}


	for(int i=0;i<allWellCellId.size();i++)
	{
		for(int j=0;j<allWellCellId[i].size();j++)
		{
			double xmin,xmax,ymin,ymax,zmin,zmax;	
			pAllGridCell[allWellCellId[i][j]]->GetBoundingBox(xmin,xmax,ymin,ymax,zmin,zmax);
			double centerX,centerY,centerZ;
			centerX=(xmin+xmax)/2.0f;centerY=(ymin+ymax)/2.0f;centerZ=(zmin+zmax)/2.0f;
			m_pX[numOfCellofOneCurve[i]+j]=(centerX);
			m_pY[numOfCellofOneCurve[i]+j]=(centerY);
			m_pZ[numOfCellofOneCurve[i]+j]=(centerZ);
			m_pAtt[numOfCellofOneCurve[i]+j]=allWellCurveCellAtt[i][j];
			m_pGridIndex[numOfCellofOneCurve[i]+j]=(allWellCellId[i][j]);
			
			Node nod(centerX,centerY,centerZ,allWellCurveCellAtt[i][j]);
			m_vNodes.push_back(nod);

		}
	}

	m_nRefNumCell=allWellCellId.size();
	m_nSampleCell=numofSampleCell;
	allWellCellId.clear();
	allWellCurveCellAtt.clear();
	
	if (m_pKDTree)
	{
		delete m_pKDTree; 
		m_pKDTree = NULL;
	}
	
	m_pKDTree = new CXKDTree3D(3,m_pX, m_pY, m_pZ,numofSampleCell);
	m_pKDTree->build(1,numofSampleCell);
	return true;
}
void CRLThreadMakeRevAttribute::RunThread()
{
	if (IsStopped())
		return;

	/*if (m_vecOutput.empty())
	{
		QString strErrorMsg = "Cannot create a 3-D surface.";
		EmitGeneralErrorMsg(strErrorMsg);
		return; 
	}*/

	/*this->EmitSetWindowName("Make 2-D Grid");
	this->EmitSetTaskName("Interpolating 3-D surface...");
	this->EmitStartComputing();*/
	qApp->processEvents();

	// Progress info
	//this->m_nTotalStep = m_nK*m_nI;
	//this->m_nCurrentStep = 0;

	// Initialization
	if (!_InitData())
		return;

	/*for (int k=0; k<m_nK; ++k)
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
	}*/

	bool ifSuccess=_InterpolateOneCellWithKriging();

	if (!ifSuccess||IsStopped())
		return;

	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating intersection...");
	qApp->processEvents();
}

int CRLThreadMakeRevAttribute::_SearchIndex(int index)
{
	for (int i=0; i<m_nSampleCell; ++i)
	{
		if (index == m_pGridIndex[i])
		{
			return i;
		}
	}
	return -1;
}

bool CRLThreadMakeRevAttribute::_InterpolateOneCellWithKriging()
{

	double dX, dY, dZ, dSum;
	double xMin,xMax,yMin,yMax,zMin,zMax;
	int iInputIndex;
	unsigned ni,nj,nk;
	CXReservoirModel *pRevObj=dynamic_cast<CXReservoirModel*>(m_pSourceObj->GetParent()->GetParent());
	if(!pRevObj)
		return false;
	CXGridModel *pGridMode=pRevObj->GetGridModel();
	QList<CXGridCell*> pAllGridCell=pGridMode->GetAllCells();
	pGridMode->GetDimension(xMin,xMax,yMin,yMax,zMin,zMax);
	dX=xMax-xMin;dY=yMax-yMin,dZ=zMax-zMin;
	double radiusSample=sqrt(pow(dX,2)+pow(dY,2)+pow(dZ,2));
	pGridMode->GetIJKDimentionInfo( ni,nj,nk);

	bool ifBeginTrace=false;
	for (int i=0; i<pAllGridCell.size(); ++i)
	{
		
		if (IsStopped())
			return false;
		else
		{
			this->EmitUpdateProgress(i, pAllGridCell.size());
		}

			
		// The grid node matches an input node exactly.
		iInputIndex = _SearchIndex( i);
		if (iInputIndex > 0)
		{
			m_pSliceData[i] = m_pAtt[iInputIndex];
			ifBeginTrace=false;
			continue;
		}

		//m_nNPNum = m_pKDTree->NNearest(dX, dY, m_dRange, m_pIndex,m_pPara->GetMaxSampleNum());
				
				
		pAllGridCell[i]->GetBoundingBox(xMin,xMax,yMin,yMax,zMin,zMax);
		dX=(xMin+xMax)/2.0f;
		dY=(yMin+yMax)/2.0f;
		dZ=(zMin+zMax)/2.0f;

		
		/*unsigned short I,J,K;
		pAllGridCell[i]->GetIJK( I,J,K);
		if(I==29&&J==42&&K==62)
		{
			int kkkk=0;
		}*/
		//int iResult;
		int iResult = m_pKDTree->nearest(m_nRefNumCell,dX, dY, dZ,m_pIndex);

		if (iResult == 0)
		{
			m_pSliceData[i] = (float) m_pAtt[m_pIndex[0]];

		}
		else if (iResult == -1 )
		{
			this->EmitGeneralErrorMsg("The search radius is too small.");
			return false;

		}
		else
		{
			m_nNPNum = m_nRefNumCell;
			m_nCovNum = m_nNPNum + 1;
			////if(ifBeginTrace)
			//{
			//	/*unsigned short I,J,K;*/
			//	//pAllGridCell[i]->GetIJK( I,J,K);
			//	if(I==29&&J==42&&K==62)
			//	{

			//	
			//	CXLog::AddLog(QString("current cell info"));
			//	//+QString::number(i)+QString::number(I)+QString::number(J)+QString::number(K));
			//	CXLog::AddLog(QString::number(i));
			//	CXLog::AddLog(QString::number(I));
			//	CXLog::AddLog(QString::number(J));
			//	CXLog::AddLog(QString::number(K));
			//	
			//	for(int kk=0;kk<m_nNPNum;kk++)
			//	{
			//		double x=m_pX[m_pIndex[kk]];
			//		double y=m_pY[m_pIndex[kk]];
			//		double z=m_pZ[m_pIndex[kk]];
			//		double dist=sqrt((dX-x)*(dX-x)+(dY-y)*(dY-y)+(dZ-z)*(dZ-z));
			//		pAllGridCell[m_pGridIndex[m_pIndex[kk]]]->GetIJK(I,J,K);
			//		CXLog::AddLog(QString("ref cell info"));
			//		//+QString::number(kk)+QString::number(I)+QString::number(J)+QString::number(K)+QString::number(dist));
			//		CXLog::AddLog(QString::number(kk));
			//		CXLog::AddLog(QString::number(I));
			//		CXLog::AddLog(QString::number(J));
			//		CXLog::AddLog(QString::number(K));
			//		CXLog::AddLog(QString::number(dist));
			//	}
			//	ifBeginTrace=false;
			//	}
			//}
			
			// Calculate covariance matrix
			//{for (int ii=0; ii<m_nNPNum; ++ii)
			//{
			//	int curIndex=m_pGridIndex[m_pIndex[ii]];
			//	
			//	for (int jj=0; jj<=ii; ++jj)
			//	{
			//		m_p2DCov[ii][jj] = _CalcCov(m_pX[m_pIndex[ii]]-m_pX[m_pIndex[jj]], m_pY[m_pIndex[ii]]-m_pY[m_pIndex[jj]],m_pZ[m_pIndex[ii]]-m_pZ[m_pIndex[jj]]);
			//		m_p2DCov[jj][ii] = m_p2DCov[ii][jj];
			//	}
			//	m_p2DCov[m_nNPNum][ii] = 1.;
			//	m_p2DCov[ii][m_nNPNum] = 1.;
			//}
			//m_p2DCov[m_nNPNum][m_nNPNum] = 0.;

			//// Calculate G vector
			//for (int ii=0; ii<m_nNPNum; ++ii)
			//{
			//	m_pG[ii] = _CalcCov(dX-m_pX[m_pIndex[ii]], dY-m_pY[m_pIndex[ii]],dZ-m_pZ[m_pIndex[ii]]);
			//}
			//m_pG[m_nNPNum] = 1.0;

			//// Calculate Z vector
			//for (int ii=0; ii<m_nNPNum; ++ii)
			//{
			//	m_pZBar[ii] = m_pAtt[m_pIndex[ii]];
			//}
			//m_pZBar[m_nNPNum] = 0.;

			//// Calculate inverse covariance matrix
			//_CalcInverseMatrix();

			//// Calculate the result	Z'*Inv*G			
			//for (int ii=0; ii<m_nCovNum; ++ii)
			//{
			//	dSum = 0.0;
			//	for (int jj=0; jj<m_nCovNum; ++jj)
			//	{
			//		dSum += m_p2DInv[ii][jj]*m_pG[jj];
			//	}
			//	m_p1DTmp[ii] = dSum;
			//}
			//dSum = 0.0;
			//for (int ii=0; ii<m_nCovNum; ++ii)
			//{
			//	dSum += m_pZBar[ii]*m_p1DTmp[ii];
			//}		

			neighborhood voisin;		
			for (int ii=0; ii<m_nNPNum; ++ii)
			{
				Node node(m_pX[m_pIndex[ii]],
				m_pY[m_pIndex[ii]],
				m_pZ[m_pIndex[ii]],
				m_pAtt[m_pIndex[ii]]);
				voisin.add_node(node);
			}
			Basic_model<location_3d<double> > *variType=NULL;
			location_3d<double> center(dX,dY,dZ);
			std::vector<double> KT_weights;
			if(m_pPara->GetVariogramType()==m_pPara->Spherical)	
				variType=new Spherical_covariance<location_3d<double> >(m_pPara->GetMaxRange(),m_pPara->GetSill());
			if(m_pPara->GetVariogramType()==m_pPara->Exponential)
				variType=new Exponential_covariance<location_3d<double> >(m_pPara->GetMaxRange(),m_pPara->GetSill());
			if(m_pPara->GetVariogramType()==m_pPara->Gaussian)
				variType=new Gaussian_covariance<location_3d<double> >(m_pPara->GetMaxRange(),m_pPara->GetSill());
			
			if(m_pPara->GetAlgorithmType()==m_pPara->eOrdinaryKriging)
			{
				double ok_variance;
				OK_constraints OK;
				int status = kriging_weights(KT_weights, ok_variance,
					center, voisin,
					*variType, OK);
				m_pSliceData[i] = linear_combination(KT_weights.begin(),KT_weights.end(),voisin);;	
			}else if(m_pPara->GetAlgorithmType()==m_pPara->eSimpleKriging)
			{
				double sk_variance;
				SK_constraints SK;
				int status = kriging_weights(KT_weights, sk_variance,
					center, voisin,
					*variType, SK);
				m_pSliceData[i] = linear_combination(KT_weights.begin(),KT_weights.end(),voisin);;	
			}
			else
			{
				
				std::vector<functor> functArray;
				functor f0(id);
				functor f1(fx);
				functor f2(fy);
				functor f3(fz);
				functArray.push_back(f0);
				functArray.push_back(f1);
				functArray.push_back(f2);
				functArray.push_back(f3);

				typedef std::vector<functor>::iterator functIter;
				functIter it=functArray.begin();
				
				KT_constraints<functIter> KT(functArray.begin(),functArray.end());
				double kt_variance;
				int status = kriging_weights(KT_weights, kt_variance,
					center, voisin,
					*variType, KT);

				m_pSliceData[i]= linear_combination(KT_weights.begin(),KT_weights.end(),voisin);
	
			}
			if(variType)
			{
				delete variType;
				variType=NULL;
			}
		}
	}	
	return true;
}


double CRLThreadMakeRevAttribute::_CalcCov(double deltaX, double deltaY, double deltaZ)
{
	// small distance
	if ((deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ)< M_FEPS)
		return m_dNugget;

	//double dX1 = deltaX*m_dAnis[0] + deltaY*m_dAnis[1];
	//double dY1 = deltaX*m_dAnis[2] + deltaY*m_dAnis[3]/m_dRangeRatio;
	//double dz
	double h = sqrt(deltaX*deltaX+deltaY*deltaY+deltaZ*deltaZ);
	double a = m_dRange;

	double dCov=0., ha;
	switch(m_iVariogramType)
	{
	case CXParameterMakeRevInterpolation::Exponential:
		{
			dCov = (m_dSill-m_dNugget)*(1.0 - exp(-3.0*h/a)) + m_dNugget;			
		}
		break;

		case CXParameterMakeRevInterpolation::Spherical:
		{
			ha = h/a;
			if (ha < 1.)
				dCov = (m_dSill-m_dNugget)*ha*(1.5 - 0.5*ha*ha) + m_dNugget;
		}
		break;

		case CXParameterMakeRevInterpolation::Gaussian:
		{
			ha = h/a;
			dCov = (m_dSill-m_dNugget)*(1 - exp(-3.0*ha*ha)) + m_dNugget;
		}
		break;
	}
	return dCov;
}

void CRLThreadMakeRevAttribute::_CalcInverseMatrix()
{
	/*if (!NXBLAS::CholeskyInverse(m_nCovNum, m_p2DCov, m_p2DTmp, m_p2DInv))
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
	}*/
}