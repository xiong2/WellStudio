#ifndef XGMEDGE_H
#define XGMEDGE_H

#include "xgeomodel_global.h"

class CXGMPoint;

class XGEOMODEL_EXPORT CXGMEdge
{
public:
	CXGMEdge(CXGMPoint* pStart, CXGMPoint* pEnd):m_pStart(pStart), m_pEnd(pEnd) {}
	~CXGMEdge() {}

	CXGMPoint* m_pStart;
	CXGMPoint* m_pEnd;


private:
	
};

#endif // RFGMEDGE_H
