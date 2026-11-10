#include "xcoordtransformer.h"
#include "xsectionscene.h"
#include "x2dsectionwindow.h"
#include "x2dsectionaxis.h"
#include <cassert>
#include "x2daxishelper.h"

CXCoordTransformer::CXCoordTransformer(CXSectionScene* pScene)
{
	assert(pScene);
	CX2DSectionWindow* pWindow = pScene->GetWindow();
	assert(pWindow);
	CX2DSectionAxis* pAxis = pWindow->GetAxisWidget();
	assert(pAxis);
	m_pXAxis = pAxis->GetXAxis();
	m_pYAxis = pAxis->GetYAxis();
	assert(m_pXAxis && m_pYAxis);

	m_rectScene = pWindow->GetSceneRect();
	pScene->GetSectionDimension(m_nJ, m_nK);
}

// origin of the viewer is the same as that of scene rect (not scene coord)

void CXCoordTransformer::View2Scene(int viewX, int viewY, double& sceneX, double& sceneY)
{
	sceneX = viewX - m_rectScene.x();
	sceneY = viewY - m_rectScene.y();
}

void CXCoordTransformer::Scene2View(double sceneX, double sceneY, int& viewX, int& viewY)
{
	viewX = static_cast<int>(sceneX + m_rectScene.x());
	viewY = static_cast<int>(sceneY + m_rectScene.y());
}

void CXCoordTransformer::World2Scene(double worldX, double worldY, double& sceneX, double& sceneY)
{
	double axismin, axismax, axisinc;
	//x
	m_pXAxis->GetAxisRange(axismin, axismax);
	if (axismin == axismax)
		sceneX = 0.;
	else
		sceneX = (worldX - axismin) / (axismax - axismin)*m_rectScene.width();
	//y
	m_pYAxis->GetAxisRange(axismin, axismax);
	if (axismin == axismax)
		sceneY = 0.;
	else
		sceneY = (worldY - axismin) / (axismax - axismin)*m_rectScene.height();

}

void CXCoordTransformer::Scene2World(double sceneX, double sceneY, double& worldX, double& worldY)
{
	double axismin, axismax;
	//x
	m_pXAxis->GetAxisRange(axismin, axismax);
	if (axismin == axismax)
		worldX = m_rectScene.x();
	else
		worldX = sceneX / m_rectScene.width()*(axismax - axismin) + axismin;
	//y
	m_pYAxis->GetAxisRange(axismin, axismax);
	if (axismin == axismax)
		worldY = m_rectScene.y();
	else
		worldY = sceneY / m_rectScene.height()*(axismax - axismin) + axismin;

}

void CXCoordTransformer::World2View(double worldX, double worldY, int& viewX, int& viewY)
{
	double sceneX, sceneY;
	World2Scene(worldX, worldY, sceneX, sceneY);
	Scene2View(sceneX, sceneY, viewX, viewY);
}

void CXCoordTransformer::View2World(int viewX, int viewY, double& worldX, double& worldY)
{
	double sceneX, sceneY;
	View2Scene(viewX, viewY, sceneX, sceneY);
	Scene2World(sceneX, sceneY, worldX, worldY);
}

void CXCoordTransformer::Index2View(double indexX, double indexY, int& viewX, int& viewY)
{
	if (m_nJ == 0 || m_nK == 0)
	{
		viewX = 0;
		viewY = 0;
	}
	else

	{
		Scene2View(indexX / (m_nJ-1)*m_rectScene.width(), indexY / (m_nK-1)*m_rectScene.height(), viewX, viewY);
	}
}
void CXCoordTransformer::View2Index(int viewX, int viewY, double& indexX, double& indexY)
{
	double sceneX, sceneY;
	View2Scene(viewX, viewY, sceneX, sceneY);

	indexX = sceneX / m_rectScene.width()*(m_nJ-1);
	indexY = sceneY / m_rectScene.height()*(m_nK-1);

}

void CXCoordTransformer::Ratio2Scene(double ratioX, double ratioY, double& sceneX, double& sceneY)
{
	sceneX = ratioX*m_rectScene.width();
	sceneY = ratioY*m_rectScene.height();
}
void CXCoordTransformer::Scene2Ratio(double sceneX, double sceneY, double& ratioX, double& ratioY)
{
	ratioX = sceneX / m_rectScene.width();
	ratioY = sceneY / m_rectScene.height();
}
