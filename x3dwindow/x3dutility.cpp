#include "x3dutility.h"

#include <osg/Camera>
#include <osg/Matrix>

#include "xutility.h"
#include "xgraphicsapi.h"

osg::Vec3 X3DWINDOW_EXPORT NX3DUtility::MapToLocal(osg::Camera *pCamera, const osg::Vec3& vecScene)
{
	//! @brief	see model-view matrix of OpenGL.
	//! V(local) = Vs(Scene) * windowMatrix(inverse) * projectionMatrix(inverse) * modelViewMatrix(inverse)

	using osg::Matrix;
	const Matrix& windowMatrix = pCamera->getViewport()->computeWindowMatrix();
	const Matrix& projectionMatrix = pCamera->getProjectionMatrix();
	const Matrix& viewMatrix = pCamera->getViewMatrix();

	Matrix invMVPW = Matrix::inverse(windowMatrix) * Matrix::inverse(projectionMatrix) * Matrix::inverse(viewMatrix);
	return invMVPW.preMult(vecScene);
}

osg::Vec3 X3DWINDOW_EXPORT NX3DUtility::MapToScene(osg::Camera *pCamera, const osg::Vec3& vecLocal)
{
	//! @brief	see model-view matrix of OpenGL.
	//!	Vs(Scene) = V(local) * modelViewMatrix * projectionMatrix * windowMatrix.

	using osg::Matrix;
	const Matrix& windowMatrix = pCamera->getViewport()->computeWindowMatrix();
	const Matrix& projectionMatrix = pCamera->getProjectionMatrix();
	const Matrix& viewMatrix = pCamera->getViewMatrix();

	Matrix MVPW = viewMatrix * projectionMatrix * windowMatrix;
	return MVPW.preMult(vecLocal);
}

float X3DWINDOW_EXPORT NX3DUtility::DistPerMM(osg::Camera *pCamera)
{
	float disDPIX, disDPIY;
	NXUtility::GetMMPerDPI(disDPIX, disDPIY);

	float fDPIPerMM = 1.f / disDPIX;

	osg::Vec3 distLocal1MM = NX3DUtility::MapToLocal(pCamera, osg::Vec3(fDPIPerMM, 0, 0));
	osg::Vec3 distLocal2MM = NX3DUtility::MapToLocal(pCamera, osg::Vec3(fDPIPerMM * 2, 0, 0));

	return (distLocal1MM - distLocal2MM).length();
}

bool X3DWINDOW_EXPORT NX3DUtility::IsPolygonSelfIntersection(osg::Vec3Array * pVertex, float fX, float fY)
{
	if (pVertex->size() < 3)
		return false;

	const osg::Vec3& vf = pVertex->front();
	const osg::Vec3& vb = pVertex->back();

	for (int i = 1; i < pVertex->size(); ++i)
	{
		const osg::Vec3& p0 = pVertex->at(i - 1);
		const osg::Vec3& p1 = pVertex->at(i);

		float x0, y0, x1, y1;

		if ((CXGraphicsAPI::IntersectionOfTwoLines(vf.x(), vf.y(), fX, fY, p0.x(), p0.y(), p1.x(), p1.y(), x0, y0) && p0 != osg::Vec3f(x0, y0, p0.z()) && p1 != osg::Vec3f(x0, y0, p1.z()))
			|| (CXGraphicsAPI::IntersectionOfTwoLines(fX, fY, vb.x(), vb.y(), p0.x(), p0.y(), p1.x(), p1.y(), x1, y1) && p0 != osg::Vec3f(x1, y1, p0.z()) && p1 != osg::Vec3f(x1, y1, p1.z())))
			return true;
	}

	return false;
}

bool X3DWINDOW_EXPORT NX3DUtility::IsPolygonSelfIntersection(osg::Vec3Array * pVertex, int index)
{
	if (pVertex->size() < 3)
		return false;

	auto _Prev = [](int iPrev, int size) {
		iPrev -= 1;
		if (iPrev < 0)
			iPrev += size;
		return iPrev;
	};

	auto _Next = [](int iNext, int size) {
		iNext += 1;
		if (iNext > size - 1)
			iNext -= size;
		return iNext;
	};
	
	int iPrev = _Prev(index, pVertex->size());
	int iNext = _Next(index, pVertex->size());

	const osg::Vec3& v0 = pVertex->at(iPrev);
	const osg::Vec3& v1 = pVertex->at(index);
	const osg::Vec3& v2 = pVertex->at(iNext);

	for (int i = 0; i < pVertex->size(); ++i)
	{
		if (i == iPrev || i == index)
			continue;

		const osg::Vec3& p0 = pVertex->at(i);
		const osg::Vec3& p1 = pVertex->at(_Next(i, pVertex->size()));

		float x0, y0, x1, y1;
		if ((CXGraphicsAPI::IntersectionOfTwoLines(v0.x(), v0.y(), v1.x(), v1.y(), p0.x(), p0.y(), p1.x(), p1.y(), x0, y0) && p0 != osg::Vec3f(x0, y0, p0.z()) && p1 != osg::Vec3f(x0, y0, p1.z()))
			|| (CXGraphicsAPI::IntersectionOfTwoLines(v1.x(), v1.y(), v2.x(), v2.y(), p0.x(), p0.y(), p1.x(), p1.y(), x1, y1) && p0 != osg::Vec3f(x1, y1, p0.z()) && p1 != osg::Vec3f(x1, y1, p1.z())))
			return true;
	}

	return false;
}

QString X3DWINDOW_EXPORT NX3DUtility::OutputVec(const osg::Vec3 & vec)
{
	return QString("(%1, %2, %3)").arg(vec.x()).arg(vec.y()).arg(vec.z());
}

void X3DWINDOW_EXPORT NX3DUtility::SetSingleColor(osg::Geometry* pGeom, const QColor& color)
{
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	pGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);
}

osg::Vec4 X3DWINDOW_EXPORT NX3DUtility::Color2Vec(const QColor & color)
{
	return osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

osg::BoundingBox X3DWINDOW_EXPORT NX3DUtility::ExpandBox(const osg::BoundingBox& box)
{
	float fDeltaX = box.xMax() - box.xMin();
	float fDeltaY = box.yMax() - box.yMin();
	float fDeltaZ = box.zMax() - box.zMin();

	osg::BoundingBoxf boxExpand(box);

	boxExpand.xMin() -= 0.1*fDeltaX;
	boxExpand.xMax() += 0.1*fDeltaX;
	boxExpand.yMin() -= 0.1*fDeltaY;
	boxExpand.yMax() += 0.1*fDeltaY;
	boxExpand.zMin() -= 0.1*fDeltaZ;
	boxExpand.zMax() += 0.1*fDeltaZ;

	return boxExpand;
}
