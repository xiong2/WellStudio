#include "xcursor.h"
#include "xglobal.h"
#include "xobjectfactory.h"  

CXCursor::CXCursor()
: CXObject()
{
	m_dX = m_dY = m_dZ = 0.;

	g_mapIDToObject.insert(GetObjectID(),this);
}

CXCursor::~CXCursor()
{
}

CXCursor& CXCursor::Instance()
{
	static CXCursor cursor;
	return cursor;
}

void CXCursor::SetPosition(double dX, double dY, double dZ)
{
	m_dX = dX;
	m_dY = dY;
	m_dZ = dZ;
}

void CXCursor::GetPosition(double& dX, double& dY, double& dZ)
{
	dX = m_dX;
	dY = m_dY;
	dZ = m_dZ;
}

