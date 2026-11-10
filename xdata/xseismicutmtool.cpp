#include "xseismicutmtool.h"
#include "xutility.h"
#include "xgraphicsapi.h"

CXSeismicUTMTool::CXSeismicUTMTool(): CXUTMTool()
{
	m_iFirstInline = 0;
	m_iFirstCrossline = 0;
	m_iInlineInc = 1;
	m_iCrosslineInc = 1;
}

CXSeismicUTMTool::CXSeismicUTMTool(const CXSeismicUTMTool& other): CXUTMTool(other)
{
	m_iFirstInline = other.m_iFirstInline;
	m_iFirstCrossline = other.m_iFirstCrossline;
	m_iInlineInc = other.m_iInlineInc;
	m_iCrosslineInc = other.m_iCrosslineInc;
}

CXSeismicUTMTool::~CXSeismicUTMTool()
{
}

bool CXSeismicUTMTool::InitSize(int iFirstInline, int iNumInline, int iInlineInc, 
								int iFirstCrossline, int iNumCrossline, int iCrosslineInc)
{
	if(!CXUTMTool::InitSize(iNumInline, iNumCrossline))
		return false;

	m_iFirstInline = iFirstInline;
	m_iFirstCrossline = iFirstCrossline;
	m_iInlineInc = iInlineInc;
	m_iCrosslineInc = iCrosslineInc;

	return true;
}

/*	Intialize the coordinates by 3 input points, user should initialize size before call this function.
*	This 3 points are not necessary the 3 corners, but should not belong to one beeline,
*	unless the number of inline or crossline is only 1, in which case only the frist 2 points be used.
*/
bool CXSeismicUTMTool::InitCoordinates(int inline0, int crossline0, double x0, double y0, 
										int inline1, int crossline1, double x1, double y1, 
										int inline2, int crossline2, double x2, double y2)
{
	//	Size be initialized?
	if(m_nI * m_nJ <= 1)
		return false;

	//	Translate inline, crossline to i, j first.
	int i0, j0, i1, j1, i2, j2;
	LineToIJ(inline0, crossline0, i0, j0);
	LineToIJ(inline1, crossline1, i1, j1);
	LineToIJ(inline2, crossline2, i2, j2);

	//	Then call basic class' funtin.
	return CXUTMTool::InitCoordinates(i0, j0, x0, y0, i1, j1, x1, y1, i2, j2, x2, y2);
}

//	Create a new UTM based on current one and input parameters.
CXSeismicUTMTool* CXSeismicUTMTool::GenerateNewUTM(int iFirstInline, int iFirstCrossline,
													 int iNumInline, int iNumCrossline, 
													 int iInlineInc, int iCrosslineInc)
{
	///	Find 3 points' coordinate, guarantee this 3 points not on a beeline.
	int inline0, crossline0, inline1, crossline1, inline2, crossline2;
	double x0, y0, x1, y1, x2, y2;

	inline0 = iFirstInline;
	crossline0 = iFirstCrossline;
	inline1 = iFirstInline;
	crossline1 = iFirstCrossline + iCrosslineInc;
	inline2 = iFirstInline + iInlineInc;
	crossline2 = iFirstCrossline + iCrosslineInc;

	LineToXY(inline0, crossline0, x0, y0);
	LineToXY(inline1, crossline1, x1, y1);
	LineToXY(inline2, crossline2, x2, y2);

	//	Create the new UTM and intialize the coordinate.
	CXSeismicUTMTool *pUTM = new CXSeismicUTMTool;
	pUTM->InitSize(iFirstInline, iNumInline, iInlineInc, iFirstCrossline, iNumCrossline, iCrosslineInc);
	if(pUTM->InitCoordinates(inline0, crossline0, x0, y0, inline1, crossline1, x1, y1, inline2, crossline2, x2, y2))
	{
		return pUTM;
	}
	else
	{
		//	Coordinates not correct.
		delete pUTM;
		return NULL;
	}
}
//	Resize the inline & crossline range, but not change the coordinate.
bool CXSeismicUTMTool::Resize(int iFirstInline, int iFirstCrossline, int iNumInline, int iNumCrossline, int iInlineInc, int iCrosslineInc)
{

	//	Get the new original point index.
	int i0, j0;
	this->LineToIJ(iFirstInline, iFirstCrossline, i0, j0);

	m_iFirstInline = iFirstInline;
	m_iFirstCrossline = iFirstCrossline;

	//	Is the Inc changed?
	double fIInc = 1., fJInc = 1.;
	if(iInlineInc != 0 && m_iInlineInc != 0)
	{
		fIInc = (double) iInlineInc / m_iInlineInc;
		m_iInlineInc = iInlineInc;
	}
	if(iCrosslineInc != 0 && m_iCrosslineInc != 0)
	{
		fJInc = (double) iCrosslineInc / m_iCrosslineInc;
		m_iCrosslineInc = iCrosslineInc;
	}		

	return CXUTMTool::_resize(i0, j0, iNumInline, iNumCrossline, fIInc, fJInc);
}

bool CXSeismicUTMTool::MergeUTM(CXSeismicUTMTool& UTM)
{
	//	The being merged one should compatible with current one.
	if (!IsCompatible(&UTM))
		return false;

	bool bNeedExpand = false;

	int iFirstInline = UTM.GetFirstInline();
	int iInlineInc = UTM.GetInlineIncrement();
	int iLastInline = UTM.GetLastInline();

	if (iFirstInline >= m_iFirstInline)
		iFirstInline = m_iFirstInline;
	else
		bNeedExpand = true;

	if (iInlineInc >= m_iInlineInc)
		iInlineInc = m_iInlineInc;
	else
		bNeedExpand = true;

	if (iLastInline <= m_iFirstInline + m_iInlineInc * (GetNI() - 1))
		iLastInline = m_iFirstInline + m_iInlineInc * (GetNI() - 1);
	else
		bNeedExpand = true;

	int iFirstCrossline = UTM.GetFirstCrossline();
	int iCrosslineInc = UTM.GetCrosslineIncrement();
	int iLastCrossline = UTM.GetLastCrossline();

	if (iFirstCrossline >= m_iFirstCrossline)
		iFirstCrossline = m_iFirstCrossline;
	else
		bNeedExpand = true;

	if (iCrosslineInc >= m_iCrosslineInc)
		iCrosslineInc = m_iCrosslineInc;
	else
		bNeedExpand = true;

	if (iLastCrossline <= m_iFirstCrossline + m_iCrosslineInc * (GetNJ() - 1))
		iLastCrossline = m_iFirstCrossline + m_iCrosslineInc * (GetNJ() - 1);
	else
		bNeedExpand = true;

	if (!bNeedExpand)
		return true;

	int iNumInline = (iLastInline - iFirstInline) / iInlineInc + 1;
	int iNumCrossline = (iLastCrossline - iFirstCrossline) / iCrosslineInc + 1;

	//	Now handle the 1 line utm problem.
	if (m_nI == 1)
	{
		if (UTM.m_nI > 1)
		{
			m_fDIX = UTM.m_fDIX;
			m_fDIY = UTM.m_fDIY;
		}
		else
		{
			//	Need calculate the dIX and dIY.
			double x0, y0, x1, y1;
			int iL0 = GetFirstInline();
			int iL1 = UTM.GetFirstInline();
			LineToXY(iL0, iFirstCrossline, x0, y0);
			UTM.LineToXY(iL1, iFirstCrossline, x1, y1);

			if (iL1 != iL0)
			{
				m_fDIX = (x1 - x0) / (iL1 - iL0);
				m_fDIY = (y1 - y0) / (iL1 - iL0);
			}
		}
	}

	return Resize(iFirstInline, iFirstCrossline, iNumInline, iNumCrossline, iInlineInc, iCrosslineInc);
}

bool CXSeismicUTMTool::IsCompatible(CXUTMTool *pUTM)
{
	CXSeismicUTMTool* pSeismicUTMTool =  dynamic_cast<CXSeismicUTMTool*>(pUTM);
	if (!pSeismicUTMTool )
		return false;
	
	/// First tell if the underlying grid is compatible?
	if (!CXUTMTool::IsCompatible(pUTM))
		return false;

	int nI = pUTM->GetNI();
	const double fErrorPercentage = 1.0;
	double fErrorEPS = qMax(GetIInterval(), GetJInterval())*fErrorPercentage;	


	if (m_nI == 1 && pSeismicUTMTool->GetNI() == 1)
	{
		//	Both are 1 line utm.
		double x00, y00, x01, y01, x10, y10, x11, y11, x, y;
		int iFirstInline0 = this->GetFirstInline();
		int iFirstCrossline0 = this->GetFirstCrossline();
		int iLastCrossline0 = this->GetLastCrossline();
		int iFirstInline1 = pSeismicUTMTool->GetFirstInline();
		int iFirstCrossline1 = pSeismicUTMTool->GetFirstCrossline();
		int iLastCrossline1 = pSeismicUTMTool->GetLastCrossline();
		LineToXY(iFirstInline0, iFirstCrossline0, x00, y00);
		LineToXY(iFirstInline0, iLastCrossline0, x01, y01);
		pSeismicUTMTool->LineToXY(iFirstInline1, iFirstCrossline1, x10, y10);
		pSeismicUTMTool->LineToXY(iFirstInline1, iLastCrossline1, x11, y11);

		//	Are they parallel?
		if (CXGraphicsAPI::IntersectionOfTwoLines(x00, y00, x01, y01, x10, y10, x11, y11, x, y))
			return false;

		//	Are they perpendicular?
		double x3, y3;
		this->LineToXY(iFirstInline0, iFirstCrossline1, x3, y3);
		if (!CXGraphicsAPI::SegmentsPerpendicular(x00, y00, x01, y01, x10, y10, x3, y3, 5))
			return false;
	}
	else
	{
		//	At least one utm more than 1 line.
		double x0, y0, x1, y1;
		int iFirstInline, iFirstCrossline, iLastCrossline;
		CXSeismicUTMTool *pUTM1 = this;
		CXSeismicUTMTool *pUTM2 = pSeismicUTMTool;

		if (m_nI == 1)
		{
			pUTM2 = this;
			pUTM1 = pSeismicUTMTool;
		}

		iFirstInline = pUTM2->GetFirstInline();
		iFirstCrossline = pUTM2->GetFirstCrossline();
		iLastCrossline = pUTM2->GetLastCrossline();

		pUTM1->LineToXY(iFirstInline, iFirstCrossline, x0, y0);
		pUTM2->LineToXY(iFirstInline, iFirstCrossline, x1, y1);
		if (qAbs(x0 - x1) > fErrorEPS || qAbs(y0 - y1) > fErrorEPS)
			return false;

		pUTM1->LineToXY(iFirstInline, iLastCrossline, x0, y0);
		pUTM2->LineToXY(iFirstInline, iLastCrossline, x1, y1);
		if (qAbs(x0 - x1) > fErrorEPS || qAbs(y0 - y1) > fErrorEPS)
			return false;
	}

	return true;
}

/// Tell if two UTM's are equal
bool CXSeismicUTMTool::Equals(CXUTMTool *pOther)
{
	CXSeismicUTMTool* pSeismicUTMTool =  dynamic_cast<CXSeismicUTMTool*>(pOther);
	if (pSeismicUTMTool == NULL)
		return false;

	if (!CXUTMTool::Equals(pOther))
		return false;

	if (this->m_iFirstInline			!= pSeismicUTMTool->m_iFirstInline ||
		this->m_iFirstCrossline		!= pSeismicUTMTool->m_iFirstCrossline ||
		this->m_iInlineInc				!= pSeismicUTMTool->m_iInlineInc ||
		this->m_iCrosslineInc		!= pSeismicUTMTool->m_iCrosslineInc
		)
		return false;
	else
		return true;
}

//	Copy everything from the source UTM.
void CXSeismicUTMTool::Copy(CXUTMTool *pSourceUTM)
{
	CXSeismicUTMTool* pSeismicUTMTool =  dynamic_cast<CXSeismicUTMTool*>(pSourceUTM);
	if( pSeismicUTMTool )
	{
		//	Call basic function first.
		CXUTMTool::Copy(pSourceUTM);

		m_iFirstInline = pSeismicUTMTool->m_iFirstInline;
		m_iFirstCrossline = pSeismicUTMTool->m_iFirstCrossline;
		m_iInlineInc = pSeismicUTMTool->m_iInlineInc;
		m_iCrosslineInc = pSeismicUTMTool->m_iCrosslineInc;
	}
}

//	Get inline, crossline number from index.
bool CXSeismicUTMTool::IJToLine(int i, int j, int& iInline, int& iCrossline)
{
	iInline = m_iFirstInline + i * m_iInlineInc;
	iCrossline = m_iFirstCrossline + j * m_iCrosslineInc;

	if(i >= m_nI || j >= m_nJ)
		return false;
	else
		return true;
}

//	Get I, J index from inline, crossline number.
bool CXSeismicUTMTool::LineToIJ(int iInline, int iCrossline, int &i, int &j) const
{
	int ii, jj;

	if (m_iInlineInc == 0)
		ii = 0;
	else
		ii = (iInline - m_iFirstInline) / m_iInlineInc;

	if (m_iCrosslineInc == 0)
		jj = 0;
	else
		jj = (iCrossline - m_iFirstCrossline) / m_iCrosslineInc;

	i = ii;
	j = jj;
	if (ii < 0 || ii >= m_nI || jj < 0 || jj >= m_nJ)
		return false;
	else
		return true;
}

//	Get I, J index from inline, crossline number.
bool CXSeismicUTMTool::LineToIJ2(float fInline, float fCrossline, int &i, int &j) const
{
	int ii, jj;

	if (m_iInlineInc == 0)
		ii = 0;
	else
		ii = (int)((fInline - m_iFirstInline) / m_iInlineInc + 0.5);

	if (m_iCrosslineInc == 0)
		jj = 0;
	else
		jj = (int)((fCrossline - m_iFirstCrossline) / m_iCrosslineInc + 0.5);

	i = ii;
	j = jj;
	if (ii < 0 || ii >= m_nI || jj < 0 || jj >= m_nJ)
		return false;
	else
		return true;
}

//	Get inline, crossline number from X, Y.
bool CXSeismicUTMTool::XYToLine(double x, double y, int& iInline, int& iCrossline)
{
	int i, j;

	bool bRes1 = this->XYToIJ(x, y, i, j);
	bool bRes2 = this->IJToLine(i, j, iInline, iCrossline);

	return bRes1 & bRes2;
}

//	Get inline, crossline number from X, Y.
bool CXSeismicUTMTool::XYToLine(double x, double y, float& fInline, float& fCrossline)
{
	float i, j;

	bool bRes1 = this->XYToIJ(x, y, i, j);

	fInline = m_iFirstInline + i * m_iInlineInc;
	fCrossline = m_iFirstCrossline + j * m_iCrosslineInc;

	return bRes1;
}

//	Get X, Y coordinate from inline, crossline number.
bool CXSeismicUTMTool::LineToXY(int iInline, int iCrossline, double &x, double &y) const
{
	int i, j;
	bool bRes1 = this->LineToIJ(iInline, iCrossline, i, j);
	bool bRes2 = this->IJToXY(i, j, x, y);

	return bRes1 & bRes2;
}

//	Standard way to save/load itself.
bool CXSeismicUTMTool::SerializeData(CXArchive& ar)
{
	if(ar.IsSaving())
    {
		//	Call basic one first.
		CXUTMTool::SerializeData(ar);

		ar<<m_iFirstInline;
		ar<<m_iFirstCrossline;
		ar<<m_iInlineInc;
		ar<<m_iCrosslineInc;

    }
    else
    {
		//	Call basic one first.
		CXUTMTool::SerializeData(ar);

		ar>>m_iFirstInline;
		ar>>m_iFirstCrossline;
		ar>>m_iInlineInc;
		ar>>m_iCrosslineInc;
	}

	return true;
}

//	Get the line range for convenient use.
void CXSeismicUTMTool::GetLineNumRange(int &iFirstInline, int &iLastInline, int &iInlineInc, int &iFirstCrossline, int &iLastCrossline, int &iCrosslineInc)
{
	iFirstInline = m_iFirstInline;
	iInlineInc = m_iInlineInc;
	iLastInline = m_iFirstInline + (GetNI() - 1) * m_iInlineInc;

	iFirstCrossline = m_iFirstCrossline;
	iCrosslineInc = m_iCrosslineInc;
	iLastCrossline = m_iFirstCrossline + (GetNJ() - 1) * m_iCrosslineInc;
}

qint64 CXSeismicUTMTool::GetIndexOfOneNode(int iInline, int iCrossline)
{
	if(iInline < m_iFirstInline || (iInline - m_iFirstInline) % m_iInlineInc != 0
		|| (iInline - m_iFirstInline) / m_iInlineInc + 1 > m_nI)
		return -1;

	if(iCrossline < m_iFirstCrossline || (iCrossline - m_iFirstCrossline) % m_iCrosslineInc != 0
		|| (iCrossline - m_iFirstCrossline) / m_iCrosslineInc + 1 > m_nJ)
		return -1;

	return ((iInline - m_iFirstInline) / m_iInlineInc) * m_nJ + (iCrossline - m_iFirstCrossline) / m_iCrosslineInc;
}

bool CXSeismicUTMTool::Contains(CXSeismicUTMTool* other)
{
	if (!this->IsCompatible(other))
		return false;

	if (NXUtility::GetGCD(other->m_iInlineInc, this->m_iInlineInc) != qAbs(this->m_iInlineInc) ||
		NXUtility::GetGCD(other->m_iCrosslineInc, this->m_iCrosslineInc) != qAbs(this->m_iCrosslineInc))
		return false;

	int i, j;
	if (!LineToIJ(other->m_iFirstInline,other->m_iFirstCrossline, i, j))
		return false;

	if (this->m_iFirstInline+i*this->m_iInlineInc != other->m_iFirstInline ||
		this->m_iFirstCrossline+j*this->m_iCrosslineInc != other->m_iFirstCrossline)
		return false;

	if (!LineToIJ(other->GetLastInline(),other->GetLastCrossline(), i, j))
		return false;

	if (this->m_iFirstInline+i*this->m_iInlineInc != other->GetLastInline() ||
		this->m_iFirstCrossline+j*this->m_iCrosslineInc != other->GetLastCrossline())
		return false;

	return true;
		
}

void CXSeismicUTMTool::ChangeCellSize(float fCellSize)
{
	int iIScale = (int)(fCellSize / GetIInterval() + 0.5);
	int iJScale = (int)(fCellSize / GetJInterval() + 0.5);
	iIScale = iIScale == 0 ? 1 : iIScale;
	iJScale = iJScale == 0 ? 1 : iJScale;

	m_nI = (int)(1. * m_nI / iIScale + 0.5);
	m_nJ = (int)(1. * m_nJ / iJScale + 0.5);

	m_fDIX *= iIScale;
	m_fDIY *= iIScale;
	m_fDJX *= iJScale;
	m_fDJY *= iJScale;

	m_iInlineInc *= iIScale;
	m_iCrosslineInc *= iJScale;
}

QPointF CXSeismicUTMTool::GetCenter()
{
	return QPointF(m_fX0 + m_nI * m_fDIX / 2 + m_nJ * m_fDJX / 2, m_fY0 + m_nI * m_fDIY / 2 + m_nJ * m_fDJY / 2);
}

QList<QPointF> CXSeismicUTMTool::GetCorners()
{
	QList<QPointF> listCorners;

	listCorners << QPointF(m_fX0, m_fY0)
		<< QPointF(m_fX0 + m_nJ * m_fDJX, m_fY0 + m_nJ * m_fDJY)
		<< QPointF(m_fX0 + m_nI * m_fDIX + m_nJ * m_fDJX, m_fY0 + m_nI * m_fDIY + m_nJ * m_fDJY)
		<< QPointF(m_fX0 + m_nI * m_fDIX, m_fY0 + m_nI * m_fDIY);

	return listCorners;
}