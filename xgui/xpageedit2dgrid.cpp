#include "xpageedit2dgrid.h"

#include <cassert>
#include <QtGui>

#include "xwelltops.h"
#include "xparametermake2dgrid.h"
#include "x2dgrid.h"
#include "x3dpoints.h"
#include "xmathmacro.h"

CXPageEdit2DGrid::CXPageEdit2DGrid(CXParameterMake2DGrid *pPara, CXObject *pObj, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);
	m_dXMin = m_dXMax = m_dYMin = m_dYMax = m_dZMin = m_dZMax = 0.0f;
	m_nI = m_nJ = DEFAULT_POINTS_NUM;

	assert(pPara && pObj);

	m_pPara = pPara;
	m_pObj = pObj;

	m_pScene = new QGraphicsScene;
	m_ui.view->setScene(m_pScene);
	m_ui.view->setBackgroundBrush(QBrush(QColor(0,0,0)));

	m_pGrid = new CX2DGrid;

	// connect spinBox with slider of rotation angle
	m_ui.m_dspbRotationAngle->setRange(0, 360);
	m_ui.m_hsliRotationAngle->setRange(0, 36000);

	connect(m_ui.m_pbtZoomOut, SIGNAL(clicked()), SLOT(slotShrink()));
	connect(m_ui.m_pbtZoomIn, SIGNAL(clicked()), SLOT(slotExpand()));
	connect(m_ui.m_pbtReset, SIGNAL(clicked()), SLOT(slotReset()));

	connect(m_ui.m_dspbRotationAngle, SIGNAL(valueChanged(double)), SLOT(slotSetSliderValue(double)));
	connect(m_ui.m_hsliRotationAngle, SIGNAL(valueChanged(int)), SLOT(slotSetDoubleSpinBoxValue(int)));
	connect(m_ui.m_dspbRotationAngle, SIGNAL(valueChanged(double)), SLOT(slotRotate(double)));

	connect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), SLOT(slotNIChanged(int)));
	connect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), SLOT(slotNJChanged(int)));
	connect(m_ui.m_dspbNIIterval, SIGNAL(valueChanged(double)), SLOT(slotNIItervalChanged(double)));
	connect(m_ui.m_dspbNJIterval, SIGNAL(valueChanged(double)), SLOT(slotNJItervalChanged(double)));

	// connect auto adjust
	connect(m_ui.m_chbAutoAdjust, SIGNAL(stateChanged(int)), SLOT(slotAutoAdjust(int)));
}

CXPageEdit2DGrid::~CXPageEdit2DGrid()
{
}

void CXPageEdit2DGrid::initializePage()
{
	CXWellTops *pWellTops = dynamic_cast<CXWellTops*>(m_pObj);
	CX3DPoints *pPoint;
	if (pWellTops)
	{
		// init 2D grid item (TODO: only show the points of top formation now)
		QString topFormation = m_pPara->GetHorizonNameList().at(0);
		pPoint = pWellTops->Get3DPointsFromFormation(topFormation);
		if (pPoint == NULL) return;

		pPoint->GetDimension(m_dXMin, m_dXMax, m_dYMin, m_dYMax, m_dZMin, m_dZMax);
		if ((m_dXMin == 0) && (m_dXMax == 0) && (m_dYMin == 0) && (m_dYMax == 0) && (m_dZMin == 0) && (m_dZMax == 0)) return;

		// Get minX/maxX, minY/maxY from all the formation.
		for (int i=1; i<m_pPara->GetHorizonNameList().size(); ++i)
		{
			CX3DPoints *pTmpPoint = pWellTops->Get3DPointsFromFormation(m_pPara->GetHorizonNameList().at(i));
			double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;

			pTmpPoint->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
			m_dXMin = (m_dXMin < dXMin) ? m_dXMin : dXMin;
			m_dXMax = (m_dXMax > dXMax) ? m_dXMax : dXMax;
			m_dYMin = (m_dYMin < dYMin) ? m_dYMin : dYMin;
			m_dYMax = (m_dYMax > dYMax) ? m_dYMax : dYMax;

			delete pTmpPoint;
		}
	}
	else
	{
		pPoint = dynamic_cast<CX3DPoints*>(m_pObj);
		double dZMin, dZMax;
		pPoint->GetDimension(m_dXMin, m_dXMax, m_dYMin, m_dYMax, dZMin, dZMax);
	}

	_Reset3BasicPoint();

	// init points
	unsigned int nPointNum;
	double *pPoints = pPoint->GetData(nPointNum);
	QVector<QPointF> vecPoints;
	for (int i=0; i<nPointNum; i+=3)
	{
		QPointF point(pPoints[i]-m_dXMin,pPoints[i+1]-m_dYMin);	// relative position base on point(xMin, yMin)
		vecPoints.push_back(point);
	}
	if (pWellTops)
	{
		delete pPoint;
	}

	// init grid
	m_pScene->removeItem(m_pGrid);
	m_pGrid->_Init(m_dYMax - m_dYMin, m_dXMax - m_dXMin, vecPoints);
	
	// init pixel vertex
	QPointF centerPoint((m_dXMax-m_dXMin)/2+m_dXMin, (m_dYMax-m_dYMin)/2+m_dYMin);
	QPointF leftBottomPoint(m_vecXCoords[0], m_vecYCoords[0]);
	QPointF leftTopPoint(m_vecXCoords[1], m_vecYCoords[1]);
	QPointF rightBottomPoint(m_vecXCoords[2], m_vecYCoords[2]);

	leftBottomPoint -= centerPoint;
	leftTopPoint -= centerPoint;
	rightBottomPoint -= centerPoint;

	QVector<QPointF> vecPixelPoints;
	vecPixelPoints.push_back(leftBottomPoint);
	vecPixelPoints.push_back(leftTopPoint);
	vecPixelPoints.push_back(rightBottomPoint);
	m_pGrid->_SetVertex(vecPixelPoints);
	
	// init minX and minY
	m_ui.m_dspbMinX->setValue(m_dXMin);
	m_ui.m_dspbMinY->setValue(m_dYMin);

	// init nI and nJ(default is 100)
	m_ui.m_spbNI->setValue(DEFAULT_POINTS_NUM);
	m_ui.m_spbNJ->setValue(DEFAULT_POINTS_NUM);

	// init interval of direction I and J
	m_ui.m_dspbNIIterval->setValue((m_dYMax-m_dYMin)/(m_nI-1));
	m_ui.m_dspbNJIterval->setValue((m_dXMax-m_dXMin)/(m_nJ-1));

	// init angle of rotation
	m_ui.m_dspbRotationAngle->setValue(0.0f);

	m_pScene->addItem(m_pGrid);
}

bool CXPageEdit2DGrid::validatePage()
{
	_SetParameter();

	if (	m_pPara->GetNI() == 0 
		||	m_pPara->GetNJ() == 0
		||	m_pPara->GetVecIIndex().empty()
		||	m_pPara->GetVecJIndex().empty()
		||	m_pPara->GetVecXCoords().empty()
		||	m_pPara->GetVecYCoords().empty()
		)
		return false;

	return true;
}

void CXPageEdit2DGrid::slotSetSliderValue(double value)
{
	disconnect(m_ui.m_hsliRotationAngle, SIGNAL(valueChanged(int)), this, SLOT(slotSetDoubleSpinBoxValue(int)));

	int int_value = static_cast<int>(value*100);
	m_ui.m_hsliRotationAngle->setValue(int_value);

	connect(m_ui.m_hsliRotationAngle, SIGNAL(valueChanged(int)), SLOT(slotSetDoubleSpinBoxValue(int)));

}

void CXPageEdit2DGrid::slotSetDoubleSpinBoxValue(int value)
{	
	disconnect(m_ui.m_dspbRotationAngle, SIGNAL(valueChanged(double)), this, SLOT(slotSetSliderValue(double)));

	double d_value = static_cast<double>(value)/100;
	m_ui.m_dspbRotationAngle->setValue(d_value);

	connect(m_ui.m_dspbRotationAngle, SIGNAL(valueChanged(double)), SLOT(slotSetSliderValue(double)));
}

void CXPageEdit2DGrid::slotRotate(double value)
{
	_Reset3BasicPoint();
	_RotateItem(value);

	m_pScene->removeItem(m_pGrid);
	m_pScene->addItem(m_pGrid);
}

void CXPageEdit2DGrid::slotAutoAdjust(int state)
{
	if (state == Qt::Checked)
		initializePage();
}

void CXPageEdit2DGrid::slotReset()
{
	initializePage();
}

void CXPageEdit2DGrid::_SetParameter()
{
	m_pPara->SetNI(m_nI);
	m_pPara->SetNJ(m_nJ);

	m_vecIIndex.push_back(0); m_vecIIndex.push_back(m_nI-1); m_vecIIndex.push_back(0);
	m_vecJIndex.push_back(0); m_vecJIndex.push_back(0); m_vecJIndex.push_back(m_nJ-1);
	m_pPara->SetVecIIndex(m_vecIIndex);
	m_pPara->SetVecJIndex(m_vecJIndex);
	m_pPara->SetVecXCoords(m_vecXCoords);
	m_pPara->SetVecYCoords(m_vecYCoords);
}

void CXPageEdit2DGrid::slotShrink()
{
	double dXAmount = (m_dXMax - m_dXMin)*GRID_ZOOM_FACTOR;
	double dYAmount = (m_dYMax - m_dYMin)*GRID_ZOOM_FACTOR;

	// reset three basic point coordinate
	m_vecXCoords[0] += dXAmount; m_vecYCoords[0] += dYAmount;
	m_vecXCoords[1]	+= dXAmount; m_vecYCoords[1] -= dYAmount;
	m_vecXCoords[2]	-= dXAmount; m_vecYCoords[2] += dYAmount;

	// set NI and NJ
	disconnect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), this, SLOT(slotNIChanged(int)));
	disconnect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), this, SLOT(slotNJChanged(int)));
	double dSpanNI = m_ui.m_dspbNIIterval->value();
	double dSpanNJ = m_ui.m_dspbNJIterval->value();
	m_ui.m_spbNI->setValue(std::ceil((m_vecYCoords[1] - m_vecYCoords[0])/dSpanNI));
	m_ui.m_spbNJ->setValue(std::ceil((m_vecXCoords[2] - m_vecXCoords[0])/dSpanNJ));
	connect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), SLOT(slotNIChanged(int)));
	connect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), SLOT(slotNJChanged(int)));

	QPointF centerPoint((m_dXMax-m_dXMin)/2+m_dXMin, (m_dYMax-m_dYMin)/2+m_dYMin);

	// Get the three points coordinate
	QPointF leftBottomPoint(m_vecXCoords[0], m_vecYCoords[0]);
	QPointF leftTopPoint(m_vecXCoords[1], m_vecYCoords[1]);
	QPointF rightBottomPoint(m_vecXCoords[2], m_vecYCoords[2]);

	// translate origin of coordinates
	leftBottomPoint -= centerPoint;
	leftTopPoint -= centerPoint;
	rightBottomPoint -= centerPoint;

	// translate to pixel coordinates
	QVector<QPointF> vecPixelPoints;
	vecPixelPoints.push_back(leftBottomPoint);
	vecPixelPoints.push_back(leftTopPoint);
	vecPixelPoints.push_back(rightBottomPoint);
	m_pGrid->_SetVertex(vecPixelPoints);
	m_pScene->removeItem(m_pGrid);
	m_pScene->addItem(m_pGrid);
}

void CXPageEdit2DGrid::slotExpand()
{
	double dXAmount = (m_dXMax - m_dXMin)*GRID_ZOOM_FACTOR;
	double dYAmount = (m_dYMax - m_dYMin)*GRID_ZOOM_FACTOR;

	// reset three basic point coordinate
	m_vecXCoords[0] -= dXAmount; m_vecYCoords[0] -= dYAmount;
	m_vecXCoords[1]	-= dXAmount; m_vecYCoords[1] += dYAmount;
	m_vecXCoords[2]	+= dXAmount; m_vecYCoords[2] -= dYAmount;

	// set NI and NJ
	disconnect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), this, SLOT(slotNIChanged(int)));
	disconnect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), this, SLOT(slotNJChanged(int)));
	double dSpanNI = m_ui.m_dspbNIIterval->value();
	double dSpanNJ = m_ui.m_dspbNJIterval->value();
	m_ui.m_spbNI->setValue(std::ceil((m_vecYCoords[1] - m_vecYCoords[0])/dSpanNI));
	m_ui.m_spbNJ->setValue(std::ceil((m_vecXCoords[2] - m_vecXCoords[0])/dSpanNJ));
	connect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), SLOT(slotNIChanged(int)));
	connect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), SLOT(slotNJChanged(int)));

	QPointF centerPoint((m_dXMax-m_dXMin)/2+m_dXMin, (m_dYMax-m_dYMin)/2+m_dYMin);

	// Get the three points coordinate
	QPointF leftBottomPoint(m_vecXCoords[0], m_vecYCoords[0]);
	QPointF leftTopPoint(m_vecXCoords[1], m_vecYCoords[1]);
	QPointF rightBottomPoint(m_vecXCoords[2], m_vecYCoords[2]);

	// translate origin of coordinates
	leftBottomPoint -= centerPoint;
	leftTopPoint -= centerPoint;
	rightBottomPoint -= centerPoint;

	// translate to pixel coordinates
	QVector<QPointF> vecPixelPoints;
	vecPixelPoints.push_back(leftBottomPoint);
	vecPixelPoints.push_back(leftTopPoint);
	vecPixelPoints.push_back(rightBottomPoint);
	m_pGrid->_SetVertex(vecPixelPoints);
	m_pScene->removeItem(m_pGrid);
	m_pScene->addItem(m_pGrid);
}

void CXPageEdit2DGrid::_RotateItem(double angle)
{
	QPointF centerPoint((m_dXMax-m_dXMin)/2+m_dXMin, (m_dYMax-m_dYMin)/2+m_dYMin);

	// Get the three points coordinate
	QPointF leftBottomPoint(m_vecXCoords[0], m_vecYCoords[0]);
	QPointF leftTopPoint(m_vecXCoords[1], m_vecYCoords[1]);
	QPointF rightBottomPoint(m_vecXCoords[2], m_vecYCoords[2]);

	// translate origin of coordinates
	leftBottomPoint -= centerPoint;
	leftTopPoint -= centerPoint;
	rightBottomPoint -= centerPoint;

	// Get the coordinates after rotation
	m_vecXCoords[0] = leftBottomPoint.x()*std::cos(angle*M_RAD) - leftBottomPoint.y()*std::sin(angle*M_RAD);
	m_vecYCoords[0] = leftBottomPoint.x()*std::sin(angle*M_RAD) + leftBottomPoint.y()*std::cos(angle*M_RAD);
	m_vecXCoords[1] = leftTopPoint.x()*std::cos(angle*M_RAD) - leftTopPoint.y()*std::sin(angle*M_RAD);
	m_vecYCoords[1] = leftTopPoint.x()*std::sin(angle*M_RAD) + leftTopPoint.y()*std::cos(angle*M_RAD);
	m_vecXCoords[2] = rightBottomPoint.x()*std::cos(angle*M_RAD) - rightBottomPoint.y()*std::sin(angle*M_RAD);
	m_vecYCoords[2] = rightBottomPoint.x()*std::sin(angle*M_RAD) + rightBottomPoint.y()*std::cos(angle*M_RAD);

	// translate to pixel coordinates
	QVector<QPointF> vecPixelPoints;
	vecPixelPoints.push_back(QPointF(m_vecXCoords[0], m_vecYCoords[0]));
	vecPixelPoints.push_back(QPointF(m_vecXCoords[1], m_vecYCoords[1]));
	vecPixelPoints.push_back(QPointF(m_vecXCoords[2], m_vecYCoords[2]));

	// restore the origin of coordinates
	m_vecXCoords[0] += (m_dXMax-m_dXMin)/2+m_dXMin;
	m_vecYCoords[0] += (m_dYMax-m_dYMin)/2+m_dYMin;
	m_vecXCoords[1] += (m_dXMax-m_dXMin)/2+m_dXMin;
	m_vecYCoords[1] += (m_dYMax-m_dYMin)/2+m_dYMin;
	m_vecXCoords[2] += (m_dXMax-m_dXMin)/2+m_dXMin;
	m_vecYCoords[2] += (m_dYMax-m_dYMin)/2+m_dYMin;
	// Set current value to item
	m_pGrid->_SetVertex(vecPixelPoints);
}

void CXPageEdit2DGrid::_Reset3BasicPoint()
{
	m_vecXCoords.clear();
	m_vecYCoords.clear();

	// Set bottom-left as the first, top-left as the second, bottom-right as the third
	m_vecXCoords.push_back(m_dXMin); m_vecXCoords.push_back(m_dXMin); m_vecXCoords.push_back(m_dXMax);
	m_vecYCoords.push_back(m_dYMin); m_vecYCoords.push_back(m_dYMax); m_vecYCoords.push_back(m_dYMin);
}

void CXPageEdit2DGrid::slotNIChanged(int value)
{
	disconnect(m_ui.m_dspbNIIterval, SIGNAL(valueChanged(double)), this, SLOT(slotNIItervalChanged(double)));
	m_nI = value;
	m_ui.m_dspbNIIterval->setValue((m_vecYCoords[1] - m_vecYCoords[0])/(m_nI-1));
	connect(m_ui.m_dspbNIIterval, SIGNAL(valueChanged(double)), SLOT(slotNIItervalChanged(double)));
}

void CXPageEdit2DGrid::slotNJChanged(int value)
{
	disconnect(m_ui.m_dspbNJIterval, SIGNAL(valueChanged(double)), this, SLOT(slotNJItervalChanged(double)));
	m_nJ = value;
	m_ui.m_dspbNJIterval->setValue((m_vecXCoords[2] - m_vecXCoords[0])/(m_nJ-1));
	connect(m_ui.m_dspbNJIterval, SIGNAL(valueChanged(double)), SLOT(slotNJItervalChanged(double)));
}

void CXPageEdit2DGrid::slotNIItervalChanged(double value)
{
	disconnect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), this, SLOT(slotNIChanged(int)));
	m_nI = std::ceil((m_vecYCoords[1] - m_vecYCoords[0])/value);
	m_ui.m_spbNI->setValue(m_nI);
	connect(m_ui.m_spbNI, SIGNAL(valueChanged(int)), SLOT(slotNIChanged(int)));
}

void CXPageEdit2DGrid::slotNJItervalChanged(double value)
{
	disconnect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), this, SLOT(slotNJChanged(int)));
	m_nJ = std::ceil((m_vecXCoords[2] - m_vecXCoords[0])/value);
	m_ui.m_spbNJ->setValue(m_nJ);
	connect(m_ui.m_spbNJ, SIGNAL(valueChanged(int)), SLOT(slotNJChanged(int)));
}