#ifndef XCOORDTRANSFORMER_H
#define XCOORDTRANSFORMER_H

#include "xsectionwindow_global.h"
#include <QRect>

class CXSectionScene;
class CX2DAxisHelper;


/**
*	@class	 CXCoordTransformer in the file "kecoordtransformer.h"
*	@brief	 The class provide methods to transform one coordinate to another
*	@date	 2/20/2017
*/
class XSECTIONWINDOW_EXPORT CXCoordTransformer
{
public:
	CXCoordTransformer(CXSectionScene* pScene);

	void View2Scene(int viewX, int viewY, double& sceneX, double& sceneY);
	void Scene2View(double sceneX, double sceneY, int& viewX, int& viewY);

	void World2Scene(double worldX, double worldY, double& sceneX, double& sceneY);
	void Scene2World(double sceneX, double sceneY, double& worldX, double& worldY);

	void World2View(double worldX, double worldY, int& viewX, int& viewY);
	void View2World(int viewX, int viewY, double& worldX, double& worldY);

	void Index2View(double indexX, double indexY, int& viewX, int& viewY);
	void View2Index(int viewX, int viewY, double& indexX, double& indexY);

	void Ratio2Scene(double ratioX, double ratioY, double& sceneX, double& sceneY);
	void Scene2Ratio(double sceneX, double sceneY, double& ratioX, double& ratioY);

private:
	CX2DAxisHelper* m_pXAxis;
	CX2DAxisHelper* m_pYAxis;

	QRectF m_rectScene;
	int m_nJ, m_nK;
};

#endif // KECOORDTRANSFORMER_H
