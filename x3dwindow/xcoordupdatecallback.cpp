#include "xcoordupdatecallback.h"

#include <cassert>
#include <QList>
#include <osg/ComputeBoundsVisitor>
#include <osg/Switch>

void CXCoordUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Group* pCoordGroup = node->asGroup();

	if (!pCoordGroup || !m_pMainCamera.valid() || pCoordGroup->getNumChildren() == 0)
		return;

	osg::Switch* pFrameSwitch = pCoordGroup->getChild(0)->asSwitch();
	osg::Switch* pGridsSwitch = pCoordGroup->getChild(1)->asSwitch();
	osg::Switch* pTicksSwitch = pCoordGroup->getChild(2)->asSwitch();
	osg::Switch* pMarksSwitch = pCoordGroup->getChild(3)->asSwitch();

	// Scroll of ortho projection
	osg::Matrixd matrixd = m_pMainCamera->getProjectionMatrix();
	float fLeft, fRight, fTop, fBottom, fNear, fFar;

	if (matrixd.getOrtho(fLeft, fRight, fBottom, fTop, fNear, fFar))
	{
		m_pMainCamera->setProjectionMatrixAsOrtho(-0.7*fFar, 0.7*fFar, -0.3*fFar, 0.3*fFar, 1.0f, fFar);
	}

	osg::Vec3 vecEye, vecCenter, vecTop;
	m_pMainCamera->getViewMatrixAsLookAt(vecEye, vecCenter, vecTop);

	osg::Vec3 vecForward = vecCenter - vecEye;
	if (vecForward.x() == 0 && vecForward.y() == 0 && vecForward.z() == 0)
		return;

	pFrameSwitch->setAllChildrenOn();
	pGridsSwitch->setAllChildrenOn();
	pTicksSwitch->setAllChildrenOff();
	pMarksSwitch->setAllChildrenOff();

	auto _SetFrameAndGridVisible = [&pFrameSwitch, &pGridsSwitch](unsigned int pos, bool value)
	{
		pFrameSwitch->setValue(pos, value);
		pGridsSwitch->setValue(pos, value);
	};

	auto _SetTickAndMarkVisible = [&pTicksSwitch, &pMarksSwitch](unsigned int pos, bool value)
	{
		pTicksSwitch->setValue(pos, value);
		pMarksSwitch->setValue(pos, value);
	};

	if (vecForward.x() > 0.2) // the eye on the left
	{
		_SetFrameAndGridVisible(0, false);

		if (vecForward.y() > 0.2) // tend to near
		{
			_SetFrameAndGridVisible(2, false);

			_SetTickAndMarkVisible(18, true); // 9 -x
			_SetTickAndMarkVisible(21, true); // 10-y

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(2, true); // 1 -y
				_SetTickAndMarkVisible(5, true); // 2 -y
				_SetTickAndMarkVisible(10, true);// 5 -x
				_SetTickAndMarkVisible(13, true);// 6 -y
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(0, true); // 0 -y
				_SetTickAndMarkVisible(7, true); // 3 -z
				_SetTickAndMarkVisible(8, true); // 4 -x
				_SetTickAndMarkVisible(15, true);// 7 -z
			}
			else
			{
				_SetTickAndMarkVisible(1, true); // 0 -z
				_SetTickAndMarkVisible(3, true); // 1 -z
				_SetTickAndMarkVisible(9, true); // 4 -z
				_SetTickAndMarkVisible(11, true);// 5 -z
			}
		}
		else if (vecForward.y() < -0.2) // tend to far
		{
			_SetFrameAndGridVisible(3, false);

			_SetTickAndMarkVisible(16, true); // 8 -x
			_SetTickAndMarkVisible(23, true); // 11-y

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(1, true); // 0 -z
				_SetTickAndMarkVisible(6, true); // 3 -y
				_SetTickAndMarkVisible(10, true); //5 -x
				_SetTickAndMarkVisible(13, true); //6 -z
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(3, true); // 1 -z
				_SetTickAndMarkVisible(4, true); // 2 -y
				_SetTickAndMarkVisible(8, true); // 4 -x
				_SetTickAndMarkVisible(15, true); // 7 -z
			}
			else
			{
				_SetTickAndMarkVisible(5, true); // 2 -z
				_SetTickAndMarkVisible(7, true); // 3 -z
				_SetTickAndMarkVisible(9, true); // 4 -z
				_SetTickAndMarkVisible(11, true); //5 -z
			}
		}
		else
		{
			_SetTickAndMarkVisible(17, true); // 8-y
			_SetTickAndMarkVisible(19, true); // 9-y

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(0, true); // 0-y
				_SetTickAndMarkVisible(4, true); // 2-y
				_SetTickAndMarkVisible(11, true); //5-z
				_SetTickAndMarkVisible(13, true); //6-z
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(2, true); // 1-y
				_SetTickAndMarkVisible(6, true); // 3-y
				_SetTickAndMarkVisible(9, true); // 4-z
				_SetTickAndMarkVisible(15, true); //7-z
			}
			else
			{
				_SetTickAndMarkVisible(9, true); // 4-z
				_SetTickAndMarkVisible(11, true); //5-z
			}
		}
	}
	else if (vecForward.x() < -0.14) // the eye on the right
	{
		_SetFrameAndGridVisible(1, false);

		if (vecForward.y() > 0.3) // tend to near
		{
			_SetFrameAndGridVisible(2, false);

			_SetTickAndMarkVisible(17, true); // 8-y
			_SetTickAndMarkVisible(22, true); //11-x

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(2, true); //  1-y
				_SetTickAndMarkVisible(5, true); //  2-z
				_SetTickAndMarkVisible(9, true); //  4-z
				_SetTickAndMarkVisible(14, true); // 7-x
					
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(0, true); // 0-y
				_SetTickAndMarkVisible(7, true); // 3-z
				_SetTickAndMarkVisible(11, true); //5-z
				_SetTickAndMarkVisible(12, true); //6-x
			}
			else
			{
				_SetTickAndMarkVisible(1, true); // 0-z
				_SetTickAndMarkVisible(3, true); // 1-z
				_SetTickAndMarkVisible(13, true); //6-z
				_SetTickAndMarkVisible(15, true); //7-z
			}
		}
		else if (vecForward.y() < -0.2)  // tend to far
		{
			_SetFrameAndGridVisible(3, false);

			_SetTickAndMarkVisible(19, true); // 9-y
			_SetTickAndMarkVisible(20, true); //10-x

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(1, true); // 0-z
				_SetTickAndMarkVisible(6, true); // 3-y
				_SetTickAndMarkVisible(9, true); // 4-z
				_SetTickAndMarkVisible(14, true); //7-x
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(3, true); // 1-z
				_SetTickAndMarkVisible(5, true); // 2-y
				_SetTickAndMarkVisible(11, true); //5-z
				_SetTickAndMarkVisible(12, true); //6-x
			}
			else
			{
				_SetTickAndMarkVisible(5, true); // 2-z
				_SetTickAndMarkVisible(7, true); // 3-z
				_SetTickAndMarkVisible(13, true); //6-z
				_SetTickAndMarkVisible(15, true); //7-z
			}
		}
		else
		{
			_SetTickAndMarkVisible(21, true); // 10-y
			_SetTickAndMarkVisible(23, true); // 11-y

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(0, true); // 0-y
				_SetTickAndMarkVisible(4, true); // 2-y
				_SetTickAndMarkVisible(9, true); // 4-z
				_SetTickAndMarkVisible(15, true); //7-z
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(2, true); // 1-y
				_SetTickAndMarkVisible(6, true); // 3-y
				_SetTickAndMarkVisible(11, true); //5-z
				_SetTickAndMarkVisible(13, true); //6-z
			}
			else
			{
				_SetTickAndMarkVisible(13, true); // 6-z
				_SetTickAndMarkVisible(15, true); // 7-z
			}
		}
	}
	else
	{
		if (vecForward.y() > 0.3) // near
		{
			_SetFrameAndGridVisible(2, false);

			_SetTickAndMarkVisible(16, true);  // 8 -x
			_SetTickAndMarkVisible(20, true);  // 10-x

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(3, true); // 1-z
				_SetTickAndMarkVisible(5, true); // 2-z
				_SetTickAndMarkVisible(8, true); // 4-x
				_SetTickAndMarkVisible(12, true); //6-x
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(1, true); // 0-z
				_SetTickAndMarkVisible(7, true); // 3-z
				_SetTickAndMarkVisible(10, true); //5-x
				_SetTickAndMarkVisible(14, true); //7-x
			}
			else
			{
				_SetTickAndMarkVisible(1, true); // 0-z
				_SetTickAndMarkVisible(3, true); // 1-z
			}
		}
		else if (vecForward.y() < -0.2) // far
		{
			_SetFrameAndGridVisible(3, false);

			_SetTickAndMarkVisible(18, true);  // 9-x
			_SetTickAndMarkVisible(22, true); //11-x

			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(1, true); // 0-z
				_SetTickAndMarkVisible(7, true); // 3-z
				_SetTickAndMarkVisible(8, true); // 4-x
				_SetTickAndMarkVisible(12, true); //6-x
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(3, true); // 1-z
				_SetTickAndMarkVisible(5, true); // 2-z
				_SetTickAndMarkVisible(10, true); //5-x
				_SetTickAndMarkVisible(14, true); //7-x
			}
			else
			{
				_SetTickAndMarkVisible(5, true); // 2-z
				_SetTickAndMarkVisible(7, true); // 3-z
			}
		}
		else
		{
			if (vecForward.z() > 0.05) // tend to bottom
			{
				_SetFrameAndGridVisible(4, false);

				_SetTickAndMarkVisible(0, true); // 0-y
				_SetTickAndMarkVisible(4, true); // 2-y
				_SetTickAndMarkVisible(8, true); // 4-x
				_SetTickAndMarkVisible(12, true); //6-x
			}
			else if (vecForward.z() < -0.12) // tend to top
			{
				_SetFrameAndGridVisible(5, false);

				_SetTickAndMarkVisible(2, true); // 1-y
				_SetTickAndMarkVisible(6, true); // 3-y
				_SetTickAndMarkVisible(10, true); //5-x
				_SetTickAndMarkVisible(14, true); //7-x
			}
			else
			{
				assert(!"It's wrong!");
			}
		}
	}

	traverse(node, nv);
}