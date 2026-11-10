#include "xviewinfocppolygon.h"
#include "xglobal.h"

CXViewInfoCPPolygon::CXViewInfoCPPolygon()
{
	SetColor(::GetRandomColor());
	SetLineWidth(2);
	SetAlpha(0.4);
}

CXViewInfoCPPolygon::CXViewInfoCPPolygon(const CXViewInfoCPPolygon& other)
{
	*this = other;
}

CXViewInfoCPPolygon& CXViewInfoCPPolygon::operator=(const CXViewInfoCPPolygon& other)
{
	CXViewInfoObject::operator=(other);
	return *this;
}